#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>

#include "commit.h"
#include "cpu.h"
#include "memory.h"

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
    //     ./trace_model program.hex
    //
    // Example:
    //
    //     ./trace_model tests/directed/alu.hex
    //
    // Execution now terminates automatically when the current
    // PC leaves the address range occupied by the loaded
    // program.
    // --------------------------------------------------------

    if (argc != 2) {

        std::cerr
            << "Usage: "
            << argv[0]
            << " <program.hex>\n";

        return EXIT_FAILURE;
    }

    const std::string programFile = argv[1];


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
    // Reject empty programs
    // --------------------------------------------------------

    if (memory.getProgramWordCount() == 0) {

        std::cerr
            << "ERROR: Program contains no instructions\n";

        return EXIT_FAILURE;
    }


    // --------------------------------------------------------
    // Create CPU
    // --------------------------------------------------------

    CPU cpu(memory);


    // --------------------------------------------------------
    // Execute and generate architectural trace
    //
    // Continue until control flow leaves the loaded program.
    // --------------------------------------------------------

    while (cpu.isPCInProgram()) {

        Commit commit{};

        if (!cpu.step(commit)) {

            std::cerr
                << "ERROR: CPU execution failed at PC 0x"
                << std::hex
                << std::setw(8)
                << std::setfill('0')
                << cpu.getPC()
                << '\n';

            return EXIT_FAILURE;
        }

        if (commit.valid) {
            printCommit(commit);
        }
    }


    return EXIT_SUCCESS;
}