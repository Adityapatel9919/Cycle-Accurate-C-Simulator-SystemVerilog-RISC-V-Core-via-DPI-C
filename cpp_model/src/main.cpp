#include "cpu.h"
#include "memory.h"

#include <cstdlib>
#include <exception>
#include <iostream>
#include <string>

// ============================================================
// MAIN
// ============================================================
//
// Usage:
//
//   ./rv32_ref <program.hex> [max_instructions]
//
// Example:
//
//   ./rv32_ref tests/directed/alu.hex 20
//
// ============================================================

int main(int argc, char* argv[])
{
    // ========================================================
    // COMMAND-LINE ARGUMENTS
    // ========================================================

    if (argc < 2 || argc > 3) {

        std::cerr
            << "Usage:\n"
            << "  "
            << argv[0]
            << " <program.hex> [max_instructions]\n\n"

            << "Example:\n"
            << "  "
            << argv[0]
            << " tests/directed/alu.hex 20\n";

        return EXIT_FAILURE;
    }


    const std::string programFile = argv[1];


    // ========================================================
    // DEFAULT INSTRUCTION LIMIT
    // ========================================================

    std::size_t maxInstructions = 100;


    if (argc == 3) {

        try {

            maxInstructions =
                static_cast<std::size_t>(
                    std::stoull(argv[2])
                );

        }
        catch (const std::exception&) {

            std::cerr
                << "ERROR: Invalid instruction limit: "
                << argv[2]
                << '\n';

            return EXIT_FAILURE;
        }


        if (maxInstructions == 0) {

            std::cerr
                << "ERROR: max_instructions must be greater than 0\n";

            return EXIT_FAILURE;
        }
    }


    // ========================================================
    // STARTUP MESSAGE
    // ========================================================

    std::cout
        << "==================================================\n"
        << "          RV32I C++ REFERENCE MODEL\n"
        << "==================================================\n\n";

    std::cout
        << "Program          : "
        << programFile
        << '\n';

    std::cout
        << "Instruction limit: "
        << maxInstructions
        << "\n\n";


    try {

        // ====================================================
        // CREATE MEMORY
        // ====================================================

        Memory memory;


        // ====================================================
        // LOAD PROGRAM
        // ====================================================

        if (!memory.loadHexFile(programFile)) {

            std::cerr
                << "\nERROR: Failed to load program.\n";

            return EXIT_FAILURE;
        }


        // ====================================================
        // CREATE CPU
        // ====================================================

        CPU cpu(memory);


        // ====================================================
        // RESET CPU
        // ====================================================

        cpu.reset(0);


        // ====================================================
        // RUN
        // ====================================================

        std::cout
            << "\nStarting simulation...\n\n";


        bool success =
            cpu.run(maxInstructions);


        // ====================================================
        // FINAL ARCHITECTURAL STATE
        // ====================================================

        cpu.dumpRegisters();


        // ====================================================
        // RESULT
        // ====================================================

        if (!success) {

            std::cerr
                << "\n==================================================\n"
                << "        SIMULATION STOPPED / FAILED\n"
                << "==================================================\n"
                << "The CPU encountered an invalid instruction,\n"
                << "unsupported instruction, or memory error.\n";

            return EXIT_FAILURE;
        }


        std::cout
            << "\n==================================================\n"
            << "             SIMULATION COMPLETE\n"
            << "==================================================\n"
            << "Instructions executed: "
            << cpu.getInstructionCount()
            << '\n'
            << "Final PC             : 0x"
            << std::hex
            << cpu.getPC()
            << std::dec
            << '\n'
            << "==================================================\n";


        return EXIT_SUCCESS;
    }


    // ========================================================
    // EXCEPTION HANDLER
    // ========================================================

    catch (const std::exception& e) {

        std::cerr
            << "\nFATAL ERROR: "
            << e.what()
            << '\n';

        return EXIT_FAILURE;
    }
}