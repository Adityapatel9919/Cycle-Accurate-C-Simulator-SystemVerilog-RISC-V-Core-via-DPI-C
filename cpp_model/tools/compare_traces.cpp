#include "trace_parser.h"
#include "commit.h"

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

// ============================================================
// PRINT ONE COMMIT
// ============================================================

void printCommit(
    const std::string& name,
    const Commit& commit
)
{
    std::cout
        << name
        << ":\n"

        << "  PC          = 0x"
        << std::hex
        << std::setw(8)
        << std::setfill('0')
        << commit.pc
        << '\n'

        << "  Instruction = 0x"
        << std::setw(8)
        << commit.instruction
        << '\n';

    if (commit.regWrite) {

        std::cout
            << "  Reg write   = x"
            << std::dec
            << static_cast<unsigned>(commit.rd)
            << '\n'

            << "  Reg value   = 0x"
            << std::hex
            << std::setw(8)
            << std::setfill('0')
            << commit.rdValue
            << '\n';
    }
    else {

        std::cout
            << "  Reg write   = none\n";
    }

    if (commit.memWrite) {

        std::cout
            << "  Mem write   = yes\n"

            << "  Mem address = 0x"
            << std::hex
            << std::setw(8)
            << std::setfill('0')
            << commit.memAddress
            << '\n'

            << "  Mem value   = 0x"
            << std::setw(8)
            << commit.memValue
            << '\n'

            << "  Mem size    = "
            << std::dec
            << static_cast<unsigned>(
                   commit.memWriteSize
               )
            << '\n';
    }
    else {

        std::cout
            << "  Mem write   = no\n";
    }

    if (commit.nextPC != 0) {

        std::cout
            << "  Next PC     = 0x"
            << std::hex
            << std::setw(8)
            << std::setfill('0')
            << commit.nextPC
            << '\n';
    }

    std::cout
        << std::dec
        << std::setfill(' ');
}


// ============================================================
// COMPARE ONE COMMIT
// ============================================================

bool compareCommit(
    const Commit& rtl,
    const Commit& reference,
    std::size_t index
)
{
    bool passed = true;

    // --------------------------------------------------------
    // PC
    // --------------------------------------------------------

    if (rtl.pc != reference.pc) {

        std::cout
            << "[MISMATCH] PC\n";

        passed = false;
    }

    // --------------------------------------------------------
    // Instruction
    // --------------------------------------------------------

    if (rtl.instruction !=
        reference.instruction) {

        std::cout
            << "[MISMATCH] Instruction\n";

        passed = false;
    }

    // --------------------------------------------------------
    // Register-write enable
    // --------------------------------------------------------

    if (rtl.regWrite !=
        reference.regWrite) {

        std::cout
            << "[MISMATCH] Register write enable\n";

        passed = false;
    }

    // --------------------------------------------------------
    // Register destination/value
    // --------------------------------------------------------

    if (
        rtl.regWrite &&
        reference.regWrite
    ) {

        if (rtl.rd != reference.rd) {

            std::cout
                << "[MISMATCH] Destination register\n";

            passed = false;
        }

        if (rtl.rdValue !=
            reference.rdValue) {

            std::cout
                << "[MISMATCH] Register value\n";

            passed = false;
        }
    }

    // --------------------------------------------------------
    // Memory-write enable
    // --------------------------------------------------------

    if (rtl.memWrite !=
        reference.memWrite) {

        std::cout
            << "[MISMATCH] Memory write enable\n";

        passed = false;
    }

    // --------------------------------------------------------
    // Memory side effects
    // --------------------------------------------------------

    if (
        rtl.memWrite &&
        reference.memWrite
    ) {

        if (rtl.memAddress !=
            reference.memAddress) {

            std::cout
                << "[MISMATCH] Memory address\n";

            passed = false;
        }

        if (rtl.memValue !=
            reference.memValue) {

            std::cout
                << "[MISMATCH] Memory value\n";

            passed = false;
        }

        if (rtl.memWriteSize !=
            reference.memWriteSize) {

            std::cout
                << "[MISMATCH] Memory write size\n";

            passed = false;
        }
    }

    // --------------------------------------------------------
    // NEXT_PC
    //
    // Compare only if both traces provide it.
    // A zero currently means "not present" to TraceParser.
    // --------------------------------------------------------

    if (
        rtl.nextPC != 0 &&
        reference.nextPC != 0 &&
        rtl.nextPC != reference.nextPC
    ) {

        std::cout
            << "[MISMATCH] Next PC\n";

        passed = false;
    }


    // ========================================================
    // FAILURE REPORT
    // ========================================================

    if (!passed) {

        std::cout
            << "\n==================================================\n"
            << "      DIFFERENTIAL VERIFICATION FAILURE\n"
            << "==================================================\n\n"

            << "Commit index : "
            << index
            << "\n\n";

        printCommit(
            "RTL",
            rtl
        );

        std::cout << '\n';

        printCommit(
            "C++ Reference",
            reference
        );

        std::cout
            << "\n==================================================\n";

        return false;
    }

    return true;
}


// ============================================================
// MAIN
// ============================================================

int main(
    int argc,
    char* argv[]
)
{
    // --------------------------------------------------------
    // Arguments
    // --------------------------------------------------------

    if (
        argc != 3 &&
        argc != 4
    ) {

        std::cerr
            << "Usage:\n\n"
            << "  "
            << argv[0]
            << " <rtl_trace> <cpp_trace> [commit_count]\n\n"

            << "Example:\n\n"
            << "  "
            << argv[0]
            << " traces/rtl_alu.log"
            << " traces/cpp_alu.log"
            << " 6\n";

        return EXIT_FAILURE;
    }


    const std::string rtlFilename =
        argv[1];

    const std::string cppFilename =
        argv[2];


    // ========================================================
    // LOAD RTL TRACE
    // ========================================================

    std::vector<Commit> rtlCommits;

    if (!TraceParser::parseFile(
            rtlFilename,
            rtlCommits
        )) {

        std::cerr
            << "ERROR: Failed to parse RTL trace\n";

        return EXIT_FAILURE;
    }


    // ========================================================
    // LOAD C++ TRACE
    // ========================================================

    std::vector<Commit> cppCommits;

    if (!TraceParser::parseFile(
            cppFilename,
            cppCommits
        )) {

        std::cerr
            << "ERROR: Failed to parse C++ trace\n";

        return EXIT_FAILURE;
    }


    // ========================================================
    // DETERMINE COMPARISON COUNT
    // ========================================================

    std::size_t compareCount = 0;

    if (argc == 4) {

        // ----------------------------------------------------
        // Explicit count supplied
        // ----------------------------------------------------

        try {

            std::size_t position = 0;

            const unsigned long count =
                std::stoul(
                    argv[3],
                    &position,
                    10
                );

            if (
                position !=
                std::string(argv[3]).size()
            ) {

                std::cerr
                    << "ERROR: Invalid commit count\n";

                return EXIT_FAILURE;
            }

            if (count == 0) {

                std::cerr
                    << "ERROR: Commit count must be > 0\n";

                return EXIT_FAILURE;
            }

            compareCount =
                static_cast<std::size_t>(count);
        }
        catch (...) {

            std::cerr
                << "ERROR: Invalid commit count\n";

            return EXIT_FAILURE;
        }


        if (
            rtlCommits.size() <
            compareCount
        ) {

            std::cerr
                << "ERROR: RTL trace contains only "
                << rtlCommits.size()
                << " commits, but "
                << compareCount
                << " were requested\n";

            return EXIT_FAILURE;
        }


        if (
            cppCommits.size() <
            compareCount
        ) {

            std::cerr
                << "ERROR: C++ trace contains only "
                << cppCommits.size()
                << " commits, but "
                << compareCount
                << " were requested\n";

            return EXIT_FAILURE;
        }
    }
    else {

        // ----------------------------------------------------
        // Without explicit count, trace lengths must match.
        // ----------------------------------------------------

        if (
            rtlCommits.size() !=
            cppCommits.size()
        ) {

            std::cerr
                << "\n==================================================\n"
                << "              TRACE LENGTH MISMATCH\n"
                << "==================================================\n\n"

                << "RTL commits : "
                << rtlCommits.size()
                << '\n'

                << "C++ commits : "
                << cppCommits.size()
                << '\n'

                << "\n==================================================\n";

            return EXIT_FAILURE;
        }

        compareCount =
            rtlCommits.size();
    }


    // ========================================================
    // INFORMATION
    // ========================================================

    std::cout
        << "==================================================\n"
        << "       RV32I DIFFERENTIAL VERIFICATION\n"
        << "==================================================\n\n"

        << "RTL trace      : "
        << rtlFilename
        << '\n'

        << "C++ trace      : "
        << cppFilename
        << '\n'

        << "RTL commits    : "
        << rtlCommits.size()
        << '\n'

        << "C++ commits    : "
        << cppCommits.size()
        << '\n'

        << "Compare count  : "
        << compareCount
        << "\n\n";


    // ========================================================
    // COMPARE
    // ========================================================

    for (
        std::size_t i = 0;
        i < compareCount;
        ++i
    ) {

        if (!compareCommit(
                rtlCommits[i],
                cppCommits[i],
                i
            )) {

            return EXIT_FAILURE;
        }
    }


    // ========================================================
    // PASS
    // ========================================================

    std::cout
        << "==================================================\n"
        << "       DIFFERENTIAL VERIFICATION PASSED\n"
        << "==================================================\n\n"

        << "Commits compared : "
        << compareCount
        << '\n'

        << "Mismatches       : 0\n\n"

        << "==================================================\n";

    return EXIT_SUCCESS;
}