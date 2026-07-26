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

    std::size_t maxInstructions = 200;
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
    // Create fresh memory for every test.
    // --------------------------------------------------------

    Memory memory;


    // --------------------------------------------------------
    // Load program.
    // --------------------------------------------------------

    if (!memory.loadHexFile(test.hexFile)) {

        std::cout
            << "[FAIL] Could not load "
            << test.hexFile
            << '\n';

        return false;
    }


    // --------------------------------------------------------
    // Create fresh CPU.
    // --------------------------------------------------------

    CPU cpu(memory);

    cpu.reset();


    // --------------------------------------------------------
    // Execute program.
    // --------------------------------------------------------

    const bool executionOK =
        cpu.run(test.maxInstructions);


    if (!executionOK) {

        std::cout
            << "[FAIL] CPU execution failed\n";

        cpu.dumpRegisters();

        return false;
    }


    // --------------------------------------------------------
    // Architectural x0 check.
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
    // Expected register values.
    // --------------------------------------------------------

    for (const auto& expectation : test.expectations) {

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
    //
    // IMPORTANT:
    //
    // These expected values must correspond to the actual HEX
    // programs in tests/directed/.
    //
    // We'll start with values already confirmed by your RTL
    // regression and expand them as required.
    //
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
            }
        },


        // ====================================================
        // 2. FORWARDING
        //
        // Architectural model does NOT model forwarding.
        //
        // It only checks the final committed state.
        // ====================================================

        {
            "forwarding",

            "tests/directed/forwarding.hex",

            {
                {1, 10},
                {2, 20},
                {3, 30}
            }
        },


        // ====================================================
        // 3. LOAD / STORE
        // ====================================================

        {
            "load_store",

            "tests/directed/load_store.hex",

            {
                {1, 42},
                {5, 42}
            }
        },


        // ====================================================
        // 4. LOAD-USE
        //
        // Again, the C++ architectural model doesn't stall.
        //
        // RTL must stall.
        // Architectural result must still match.
        // ====================================================

        {
            "load_use",

            "tests/directed/load_use.hex",

            {
                {1, 42},
                {5, 42},
                {6, 84}
            }
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
            }
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
            }
        },


        // ====================================================
        // 7. BRANCHES
        //
        // Values taken from the branch regression you already
        // validated in RTL.
        // ====================================================

        {
            "branches",

            "tests/directed/branches.hex",

            {
                {1,  10},
                {2,  20},
                {3,   3},
                {4, 0xFFFFFFFFu},
                {5,   1},
                {6,   6},
                {7,   7},
                {8,   8},
                {9,   9}
            }
        },


        // ====================================================
        // 8. JAL
        // ====================================================

        {
            "jal",

            "tests/directed/jal.hex",

            {
                {18, 18},
                {20, 124}
            }
        },


        // ====================================================
        // 9. JALR
        // ====================================================

        {
            "jalr",

            "tests/directed/jalr.hex",

            {
                {19, 156},
                {21, 148},
                {22, 22}
            }
        }
    };


    // ========================================================
    // RUN TESTS
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