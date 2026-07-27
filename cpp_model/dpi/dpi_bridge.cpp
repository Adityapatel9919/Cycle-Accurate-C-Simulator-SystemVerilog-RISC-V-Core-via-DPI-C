#include <cstdint>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <memory>
#include <string>

#include "commit.h"
#include "cpu.h"
#include "memory.h"


static std::unique_ptr<Memory> g_memory;
static std::unique_ptr<CPU>    g_cpu;

static uint64_t g_commitCount = 0;
static uint64_t g_mismatches  = 0;




extern "C" int dpi_init(const char* programFile)
{
    if (programFile == nullptr) {
        std::cerr << "[DPI ERROR] Null program filename\n";
        return 0;
    }

    g_memory = std::make_unique<Memory>();

    if (!g_memory->loadHexFile(programFile, 0)) {
        std::cerr
            << "[DPI ERROR] Failed to load program: "
            << programFile
            << '\n';

        g_memory.reset();

        return 0;
    }

    g_cpu = std::make_unique<CPU>(*g_memory);

    g_commitCount = 0;
    g_mismatches  = 0;

    std::cout
        << "[DPI] Golden model initialized: "
        << programFile
        << '\n';

    return 1;
}




extern "C" int dpi_check_commit(
    uint32_t rtlPC,
    uint32_t rtlInstruction,
    int      rtlRegWrite,
    uint32_t rtlRD,
    uint32_t rtlRDValue
)
{
    if (!g_cpu || !g_memory) {
        std::cerr
            << "[DPI ERROR] Golden model not initialized\n";

        return 0;
    }

    if (!g_cpu->isPCInProgram()) {
        std::cerr
            << "[DPI ERROR] RTL produced an extra commit after "
               "the C++ model finished\n";

        return 0;
    }

    Commit reference{};

    if (!g_cpu->step(reference)) {
        std::cerr
            << "[DPI ERROR] C++ execution failed at PC 0x"
            << std::hex
            << std::setw(8)
            << std::setfill('0')
            << g_cpu->getPC()
            << '\n';

        return 0;
    }

    ++g_commitCount;

    bool match = true;

    

    if (rtlPC != reference.pc) {
        match = false;
    }

    

    if (rtlInstruction != reference.instruction) {
        match = false;
    }

   

    const bool rtlWritesRegister =
        (rtlRegWrite != 0) && (rtlRD != 0);

    const bool cppWritesRegister =
        reference.regWrite && (reference.rd != 0);

    if (rtlWritesRegister != cppWritesRegister) {
        match = false;
    }

    

    if (rtlWritesRegister && cppWritesRegister) {

        if (rtlRD != reference.rd) {
            match = false;
        }

        if (rtlRDValue != reference.rdValue) {
            match = false;
        }
    }


    if (!match) {

        ++g_mismatches;

        std::cerr
            << "\n==================================================\n"
            << "        DPI LOCKSTEP MISMATCH\n"
            << "==================================================\n\n"

            << "Commit index : "
            << std::dec
            << g_commitCount
            << "\n\n"

            << "RTL:\n"

            << "  PC          = 0x"
            << std::hex
            << std::setw(8)
            << std::setfill('0')
            << rtlPC
            << '\n'

            << "  Instruction = 0x"
            << std::setw(8)
            << rtlInstruction
            << '\n'

            << "  Reg write   = "
            << (rtlWritesRegister ? "yes" : "no")
            << '\n';

        if (rtlWritesRegister) {

            std::cerr
                << "  RD          = x"
                << std::dec
                << rtlRD
                << '\n'

                << "  Value       = 0x"
                << std::hex
                << std::setw(8)
                << rtlRDValue
                << '\n';
        }

        std::cerr
            << "\nC++ Reference:\n"

            << "  PC          = 0x"
            << std::hex
            << std::setw(8)
            << reference.pc
            << '\n'

            << "  Instruction = 0x"
            << std::setw(8)
            << reference.instruction
            << '\n'

            << "  Reg write   = "
            << (cppWritesRegister ? "yes" : "no")
            << '\n';

        if (cppWritesRegister) {

            std::cerr
                << "  RD          = x"
                << std::dec
                << static_cast<unsigned>(reference.rd)
                << '\n'

                << "  Value       = 0x"
                << std::hex
                << std::setw(8)
                << reference.rdValue
                << '\n';
        }

        std::cerr
            << "\n==================================================\n";

        return 0;
    }


  

    std::cout
        << "[DPI PASS] Commit "
        << std::dec
        << g_commitCount

        << " PC=0x"
        << std::hex
        << std::setw(8)
        << std::setfill('0')
        << rtlPC
        << '\n';

    return 1;
}


extern "C" int dpi_reference_finished()
{
    if (!g_cpu || !g_memory) {

        std::cerr
            << "[DPI ERROR] Golden model not initialized\n";

        return 0;
    }

    return g_cpu->isPCInProgram() ? 0 : 1;
}



extern "C" int dpi_finish()
{
    if (!g_cpu) {
        std::cerr
            << "[DPI ERROR] Golden model not initialized\n";

        return 0;
    }

    // C++ should also have reached the end of the program.
    if (g_cpu->isPCInProgram()) {

        std::cerr
            << "[DPI ERROR] Simulation ended before the "
               "C++ model finished\n"

            << "C++ next PC = 0x"
            << std::hex
            << std::setw(8)
            << std::setfill('0')
            << g_cpu->getPC()
            << '\n';

        return 0;
    }

    std::cout
        << "\n==================================================\n"
        << "       DPI LOCKSTEP VERIFICATION PASSED\n"
        << "==================================================\n"
        << "Commits    : "
        << std::dec
        << g_commitCount
        << '\n'
        << "Mismatches : "
        << g_mismatches
        << '\n'
        << "==================================================\n";

    return g_mismatches == 0 ? 1 : 0;
}