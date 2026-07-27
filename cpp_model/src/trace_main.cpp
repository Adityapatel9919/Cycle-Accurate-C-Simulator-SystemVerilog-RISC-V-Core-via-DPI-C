#include "cpu.h"
#include "commit.h"
#include "memory.h"

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>

// ============================================================
// PRINT ONE ARCHITECTURAL COMMIT
// ============================================================
//
// Keep this format deterministic.
//
// Later the SystemVerilog RTL will emit the same fields so
// an offline comparator can compare:
//
//      C++ commit N <-> RTL commit N
//
// ============================================================

static void printCommit(
    std::size_t commitNumber,
    const CommitInfo& commit
)
{
    if (!commit.valid) {
        return;
    }

    std::cout
        << "COMMIT "
        << std::dec
        << commitNumber

        << " PC="
        << std::hex
        << std::setw(8)
        << std::setfill('0')
        << commit.pc

        << " INSTR="
        << std::setw(8)
        << commit.instruction

        << " REG_WRITE="
        << std::dec
        << (commit.regWrite ? 1 : 0)

        << " RD="
        << static_cast<unsigned>(commit.rd)

        << " RD_VALUE="
        << std::hex
        << std::setw(8)
        << std::setfill('0')
        << commit.rdValue

        << " MEM_WRITE="
        << std::dec
        << (commit.memWrite ? 1 : 0)

        << " MEM_ADDR="
        << std::hex
        << std::setw(8)
        << std::setfill('0')
        << commit.memAddress

        << " MEM_VALUE="
        << std::setw(8)
        << commit.memValue

        << " MEM_SIZE="
        << std::dec
        << static_cast<unsigned>(
            commit.memWriteSize
        )

        << " NEXT_PC="
        << std::hex
        << std::setw(8)
        << std::setfill('0')
        << commit.nextPC

        << std::dec
        << std::setfill(' ')
        << '\n';
}


// ============================================================
// MAIN
// ============================================================

int main(int argc, char* argv[])
{
    // ========================================================
    // COMMAND-LINE CHECK
    // ========================================================

    if (argc < 2 || argc > 3) {

        std::cerr
            << "Usage:\n"
            << "  "
            << argv[0]
            << " <program.hex> [max_instructions]\n";

        return EXIT_FAILURE;
    }


    const std::string programFile =
        argv[1];


    // Default safety limit.
    std::size_t maxInstructions = 1000;


    // ========================================================
    // OPTIONAL INSTRUCTION LIMIT
    // ========================================================

    if (argc == 3) {

        try {

            const unsigned long long parsed =
                std::stoull(argv[2]);

            if (parsed == 0) {

                std::cerr
                    << "ERROR: max_instructions must be "
                    << "greater than zero\n";

                return EXIT_FAILURE;
            }

            maxInstructions =
                static_cast<std::size_t>(parsed);

        }
        catch (const std::exception& e) {

            std::cerr
                << "ERROR: Invalid instruction limit: "
                << argv[2]
                << '\n';

            return EXIT_FAILURE;
        }
    }


    // ========================================================
    // MEMORY
    // ========================================================

    Memory memory;


    if (!memory.loadHexFile(programFile)) {

        std::cerr
            << "ERROR: Failed to load program\n";

        return EXIT_FAILURE;
    }


    // ========================================================
    // CPU
    // ========================================================

    CPU cpu(memory);

    cpu.reset(memory.getProgramStart());


    // ========================================================
    // TRACE HEADER
    // ========================================================

    std::cout
        << "\n"
        << "==================================================\n"
        << "          RV32I C++ COMMIT TRACE\n"
        << "==================================================\n"
        << "Program : "
        << programFile
        << '\n'
        << "Start   : 0x"
        << std::hex
        << std::setw(8)
        << std::setfill('0')
        << memory.getProgramStart()
        << '\n'
        << "End     : 0x"
        << std::setw(8)
        << memory.getProgramEnd()
        << std::dec
        << std::setfill(' ')
        << '\n'
        << "==================================================\n";


    // ========================================================
    // EXECUTE INSTRUCTION-BY-INSTRUCTION
    // ========================================================

    std::size_t commitNumber = 0;

    while (commitNumber < maxInstructions) {

        // ----------------------------------------------------
        // Normal completion
        // ----------------------------------------------------

        if (cpu.getPC() == memory.getProgramEnd()) {
            break;
        }


        // ----------------------------------------------------
        // Detect control flow outside loaded program
        // ----------------------------------------------------

        if (
            cpu.getPC() < memory.getProgramStart() ||
            cpu.getPC() > memory.getProgramEnd()
        ) {

            std::cerr
                << "ERROR: PC outside loaded program: 0x"
                << std::hex
                << std::setw(8)
                << std::setfill('0')
                << cpu.getPC()
                << std::dec
                << std::setfill(' ')
                << '\n';

            return EXIT_FAILURE;
        }


        // ----------------------------------------------------
        // Execute exactly one instruction
        // ----------------------------------------------------

        if (!cpu.step()) {

            std::cerr
                << "ERROR: CPU execution failed at commit "
                << commitNumber
                << '\n';

            return EXIT_FAILURE;
        }


        // ----------------------------------------------------
        // Obtain architectural retirement information
        // ----------------------------------------------------

        const CommitInfo& commit =
            cpu.getLastCommit();


        if (!commit.valid) {

            std::cerr
                << "ERROR: CPU step completed without "
                << "a valid commit record\n";

            return EXIT_FAILURE;
        }


        // ----------------------------------------------------
        // Print commit
        // ----------------------------------------------------

        printCommit(
            commitNumber,
            commit
        );


        ++commitNumber;
    }


    // ========================================================
    // INSTRUCTION LIMIT CHECK
    // ========================================================

    if (
        commitNumber == maxInstructions &&
        cpu.getPC() != memory.getProgramEnd()
    ) {

        std::cerr
            << "\nERROR: Maximum instruction limit reached\n"
            << "Possible infinite loop or incorrect control flow.\n"
            << "PC = 0x"
            << std::hex
            << std::setw(8)
            << std::setfill('0')
            << cpu.getPC()
            << std::dec
            << std::setfill(' ')
            << '\n';

        return EXIT_FAILURE;
    }


    // ========================================================
    // SUMMARY
    // ========================================================

    std::cout
        << "==================================================\n"
        << "TRACE COMPLETE\n"
        << "Commits  : "
        << commitNumber
        << '\n'
        << "Final PC : 0x"
        << std::hex
        << std::setw(8)
        << std::setfill('0')
        << cpu.getPC()
        << std::dec
        << std::setfill(' ')
        << '\n'
        << "==================================================\n";


    return EXIT_SUCCESS;
}