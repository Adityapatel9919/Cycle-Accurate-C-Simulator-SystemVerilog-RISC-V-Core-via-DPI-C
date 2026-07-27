#include <cstdint>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>

#include "cpu.h"
#include "memory.h"
#include "commit.h"

// ============================================================
// Print one architectural commit in RTL-compatible format
// ============================================================

static void printCommit(const Commit& commit)
{
    std::cout
        << "COMMIT PC="
        << std::hex
        << std::setfill('0')
        << std::setw(8)
        << commit.pc

        << " INSTR="
        << std::setw(8)
        << commit.instruction;

    if (commit.regWrite && commit.rd != 0) {

        std::cout
            << " RD="
            << std::dec
            << static_cast<unsigned>(commit.rd)

            << " VALUE="
            << std::hex
            << std::setw(8)
            << commit.rdValue;
    }
    else {

        std::cout
            << " RD=- VALUE=-";
    }

    std::cout << '\n';
}


// ============================================================
// MAIN
// ============================================================

int main(int argc, char* argv[])
{
    // --------------------------------------------------------
    // Command-line arguments
    //
    // Usage:
    //
    // ./trace_model program.hex instruction_count
    //
    // Example:
    //
    // ./trace_model tests/directed/alu.hex 6
    // --------------------------------------------------------

    if (argc != 3) {

        std::cerr
            << "Usage: "
            << argv[0]
            << " <program.hex> <instruction_count>\n";

        return EXIT_FAILURE;
    }

    const std::string programFile = argv[1];

    std::size_t instructionLimit = 0;

    try {

        instructionLimit =
            static_cast<std::size_t>(
                std::stoul(argv[2])
            );

    }
    catch (...) {

        std::cerr
            << "ERROR: Invalid instruction count: "
            << argv[2]
            << '\n';

        return EXIT_FAILURE;
    }


    // --------------------------------------------------------
    // Create architectural memory
    // --------------------------------------------------------

    Memory memory;


    // --------------------------------------------------------
    // Load HEX program
    // --------------------------------------------------------

    if (!memory.loadHexFile(programFile, 0)) {

        std::cerr
            << "ERROR: Failed to load program\n";

        return EXIT_FAILURE;
    }


    // --------------------------------------------------------
    // Create CPU
    // --------------------------------------------------------

    CPU cpu(memory);


    // --------------------------------------------------------
    // Execute and generate architectural trace
    // --------------------------------------------------------

    for (std::size_t i = 0;
         i < instructionLimit;
         ++i) {

        Commit commit{};

        const bool success = cpu.step(commit);

        if (!success) {

            std::cerr
                << "ERROR: CPU execution failed at instruction "
                << i
                << '\n';

            return EXIT_FAILURE;
        }

        printCommit(commit);
    }


    return EXIT_SUCCESS;
}