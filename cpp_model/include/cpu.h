#ifndef CPU_H
#define CPU_H

#include <array>
#include <cstddef>
#include <cstdint>

#include "commit.h"
#include "decoder.h"
#include "instruction.h"
#include "memory.h"

class CPU
{
public:
    explicit CPU(Memory& memory);

    // Reset architectural CPU state
    void reset();

    // ========================================================
    // EXECUTION
    // ========================================================

    // Execute one instruction without requesting commit info.
    // Keeps existing code/test_runner.cpp compatible.
    bool step();

    // Execute one instruction and return architectural
    // commit information for differential verification.
    bool step(Commit& commit);

    // Execute multiple instructions.
    bool run(std::size_t instructionLimit);

    // ========================================================
    // ARCHITECTURAL STATE ACCESS
    // ========================================================

    uint32_t getRegister(uint32_t index) const;

    uint32_t getPC() const;

    uint64_t getInstructionCount() const;

    // Debug helper
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
    // x0 is always hardwired to zero.
    void writeRegister(
        uint32_t rd,
        uint32_t value
    );

    // Execute decoded instruction.
    //
    // commit is filled with the architectural effects of the
    // instruction being executed.
    bool executeInstruction(
        const DecodedInstruction& decoded,
        Commit& commit
    );
};

#endif