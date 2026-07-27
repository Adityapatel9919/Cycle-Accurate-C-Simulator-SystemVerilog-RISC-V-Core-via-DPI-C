#ifndef CPU_H
#define CPU_H

#include <array>
#include <cstddef>
#include <cstdint>

#include "commit.h"
#include "decoder.h"
#include "instruction.h"
#include "memory.h"

// ============================================================
// RV32I CPU REFERENCE MODEL
// ============================================================

class CPU
{
public:

    explicit CPU(Memory& memory);


    // ========================================================
    // RESET
    // ========================================================

    void reset();


    // ========================================================
    // EXECUTION
    // ========================================================

    // Execute one instruction.
    bool step();

    // Execute one instruction and return architectural
    // commit information.
    bool step(Commit& commit);

    // Execute a fixed number of instructions.
    //
    // Kept for compatibility with existing directed tests.
    bool run(std::size_t instructionLimit);


    // ========================================================
    // PROGRAM EXECUTION STATE
    // ========================================================

    // Returns true when the current PC points to an
    // instruction inside the loaded program.
    //
    // This allows trace/differential execution to terminate
    // naturally when control flow leaves the program.
    bool isPCInProgram() const;


    // ========================================================
    // ARCHITECTURAL STATE ACCESS
    // ========================================================

    uint32_t getRegister(
        uint32_t index
    ) const;

    uint32_t getPC() const;

    uint64_t getInstructionCount() const;


    // ========================================================
    // DEBUG
    // ========================================================

    void dumpRegisters() const;


private:

    // ========================================================
    // ARCHITECTURAL STATE
    // ========================================================

    Memory& memory_;

    std::array<uint32_t, 32> registers_{};

    uint32_t pc_ = 0;

    uint64_t instructionCount_ = 0;


    // ========================================================
    // INTERNAL HELPERS
    // ========================================================

    // Architectural register write.
    // x0 is permanently hardwired to zero.
    void writeRegister(
        uint32_t rd,
        uint32_t value
    );


    // Execute one decoded instruction and record its
    // architectural effects.
    bool executeInstruction(
        const DecodedInstruction& decoded,
        Commit& commit
    );
};

#endif // CPU_H