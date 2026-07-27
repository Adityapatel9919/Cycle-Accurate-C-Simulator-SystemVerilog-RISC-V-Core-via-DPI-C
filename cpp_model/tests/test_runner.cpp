#include "cpu.h"
#include "memory.h"

#include <cstdint>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

// ============================================================
// TEST DESCRIPTION
// ============================================================

struct RegisterExpectation
{
    uint8_t reg;
    uint32_t expected;
};

struct TestCase
{
    std::string name;
    std::string hexFile;

    std::vector<RegisterExpectation> expectations;

    // Number of architectural instructions expected to retire.
    std::size_t instructionCount;
};


// ============================================================
// REGISTER CHECK
// ============================================================

bool checkRegister(
    const CPU& cpu,
    uint8_t reg,
    uint32_t expected
)
{
    const uint32_t actual =
        cpu.getRegister(reg);

    if (actual != expected) {

        std::cout
            << "[FAIL] x"
            << static_cast<unsigned>(reg)
            << " expected 0x"
            << std::hex
            << std::setw(8)
            << std::setfill('0')
            << expected
            << ", got 0x"
            << std::setw(8)
            << actual
            << std::dec
            << std::setfill(' ')
            << '\n';

        return false;
    }

    std::cout
        << "[PASS] x"
        << static_cast<unsigned>(reg)
        << " = "
        << static_cast<int32_t>(actual)
        << " (0x"
        << std::hex
        << std::setw(8)
        << std::setfill('0')
        << actual
        << std::dec
        << std::setfill(' ')
        << ")\n";

    return true;
}


// ============================================================
// COMMIT TRACE
// ============================================================

void printCommit(const Commit& commit)
{
    if (!commit.valid) {
        return;
    }

    std::cout
        << "COMMIT"
        << " PC=0x"
        << std::hex
        << std::setw(8)
        << std::setfill('0')
        << commit.pc

        << " INSTR=0x"
        << std::setw(8)
        << commit.instruction;

    if (commit.regWrite) {

        std::cout
            << " RD=x"
            << std::dec
            << static_cast<unsigned>(commit.rd)

            << " VALUE=0x"
            << std::hex
            << std::setw(8)
            << std::setfill('0')
            << commit.rdValue;
    }

    if (commit.memWrite) {

        std::cout
            << " MEM_ADDR=0x"
            << std::hex
            << std::setw(8)
            << std::setfill('0')
            << commit.memAddress

            << " MEM_VALUE=0x"
            << std::setw(8)
            << commit.memValue

            << " MEM_SIZE="
            << std::dec
            << static_cast<unsigned>(
                   commit.memWriteSize
               );
    }

    std::cout
        << " NEXT_PC=0x"
        << std::hex
        << std::setw(8)
        << std::setfill('0')
        << commit.nextPC

        << std::dec
        << std::setfill(' ')
        << '\n';
}


// ============================================================
// RUN ONE TEST
// ============================================================

bool runTest(const TestCase& test)
{
    std::cout
        << "\n--------------------------------------------------\n"
        << "[TEST] "
        << test.name
        << "\n--------------------------------------------------\n";

    // --------------------------------------------------------
    // Fresh memory for every test
    // --------------------------------------------------------

    Memory memory;

    // --------------------------------------------------------
    // Load program
    // --------------------------------------------------------

    if (!memory.loadHexFile(test.hexFile)) {

        std::cout
            << "[FAIL] Could not load "
            << test.hexFile
            << '\n';

        return false;
    }

    // --------------------------------------------------------
    // Fresh CPU
    // --------------------------------------------------------

    CPU cpu(memory);

    cpu.reset();

    // --------------------------------------------------------
    // Execute exact architectural instruction count
    // --------------------------------------------------------

    for (std::size_t i = 0;
         i < test.instructionCount;
         ++i) {

        Commit commit{};

        if (!cpu.step(commit)) {

            std::cout
                << "[FAIL] CPU execution failed at retired "
                << "instruction "
                << i
                << '\n';

            cpu.dumpRegisters();

            return false;
        }

        // Enable when commit debugging is required:
        //
        // printCommit(commit);
    }

    // --------------------------------------------------------
    // x0 architectural check
    // --------------------------------------------------------

    bool passed = true;

    if (cpu.getRegister(0) != 0) {

        std::cout
            << "[FAIL] x0 was modified\n";

        passed = false;
    }
    else {

        std::cout
            << "[PASS] x0 = 0\n";
    }

    // --------------------------------------------------------
    // Expected architectural register state
    // --------------------------------------------------------

    for (const auto& expectation :
         test.expectations) {

        if (!checkRegister(
                cpu,
                expectation.reg,
                expectation.expected
            )) {

            passed = false;
        }
    }

    // --------------------------------------------------------
    // Result
    // --------------------------------------------------------

    if (passed) {

        std::cout
            << "[PASS] "
            << test.name
            << '\n';
    }
    else {

        std::cout
            << "[FAIL] "
            << test.name
            << '\n';

        cpu.dumpRegisters();
    }

    return passed;
}


// ============================================================
// MAIN
// ============================================================

int main()
{
    std::cout
        << "==================================================\n"
        << "       RV32I C++ REFERENCE REGRESSION\n"
        << "==================================================\n";


    // ========================================================
    // DIRECTED TESTS
    // ========================================================

    const std::vector<TestCase> tests = {

        // ====================================================
        // 1. ALU
        // ====================================================

        {
            "alu",
            "tests/directed/alu.hex",

            {
                {1, 10},
                {2, 20},
                {3, 30},
                {4, 20}
            },

            6
        },


        // ====================================================
        // 2. FORWARDING
        // ====================================================

        {
            "forwarding",
            "tests/directed/forwarding.hex",

            {
                {1, 5},
                {2, 10},
                {3, 15},
                {4, 25},
                {5, 40}
            },

            7
        },


        // ====================================================
        // 3. LOAD / STORE
        // ====================================================

        {
            "load_store",
            "tests/directed/load_store.hex",

            {
                {1, 42},
                {2, 42}
            },

            5
        },


        // ====================================================
        // 4. LOAD-USE
        // ====================================================

        {
            "load_use",
            "tests/directed/load_use.hex",

            {
                {1, 42},
                {5, 42},
                {6, 84}
            },

            6
        },


        // ====================================================
        // 5. BEQ TAKEN
        // ====================================================

        {
            "beq_taken",
            "tests/directed/beq_taken.hex",

            {
                {1, 10},
                {2, 10},
                {3, 0},
                {4, 0},
                {5, 42}
            },

            6
        },


        // ====================================================
        // 6. BEQ NOT TAKEN
        // ====================================================

        {
            "beq_not_taken",
            "tests/directed/beq_not_taken.hex",

            {
                {1, 10},
                {2, 20}
            },

            8
        },


        // ====================================================
        // 7. BRANCHES
        // ====================================================

        {
            "branches",
            "tests/directed/branches.hex",

            {
                {1, 10},
                {2, 20},
                {3, 3},
                {4, 0xFFFFFFFFu},
                {5, 1},
                {6, 6},
                {7, 7},
                {8, 8},
                {9, 9}
            },

            17
        },


        // ====================================================
        // 8. JAL
        // ====================================================

        {
            "jal",
            "tests/directed/jal.hex",

            {
                {1, 4},
                {2, 0},
                {3, 0},
                {4, 42}
            },

            4
        },


        // ====================================================
        // 9. JALR
        // ====================================================

        {
            "jalr",
            "tests/directed/jalr.hex",

            {
                {1, 20},
                {2, 0},
                {3, 0},
                {4, 42},
                {5, 12}
            },

            6
        },


        // ====================================================
        // 10. FULL REGRESSION
        // ====================================================

        {
            "full_regression",
            "tests/directed/full_regression.hex",

            {
                {1,  10},
                {2,  20},
                {3,  30},
                {4,  20},
                {5,  20},

                {16, 16},
                {17, 17},

                {18, 18},
                {20, 124},

                {19, 156},
                {21, 148},
                {22, 22}
            },

            32
        }
    };


    // ========================================================
    // RUN REGRESSION
    // ========================================================

    std::size_t passedCount = 0;

    for (const auto& test : tests) {

        if (runTest(test)) {
            ++passedCount;
        }
    }


    const std::size_t failedCount =
        tests.size() - passedCount;


    // ========================================================
    // SUMMARY
    // ========================================================

    std::cout
        << "\n==================================================\n"
        << "              REGRESSION SUMMARY\n"
        << "==================================================\n\n"

        << "Total tests : "
        << tests.size()
        << '\n'

        << "Passed      : "
        << passedCount
        << '\n'

        << "Failed      : "
        << failedCount
        << '\n'

        << "\n==================================================\n";


    if (failedCount == 0) {

        std::cout
            << "              REGRESSION PASSED\n"
            << "==================================================\n";

        return EXIT_SUCCESS;
    }


    std::cout
        << "              REGRESSION FAILED\n"
        << "==================================================\n";

    return EXIT_FAILURE;
}