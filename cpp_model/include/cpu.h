#ifndef CPU_H
#define CPU_H

#include <cstdint>
#include <cstddef>
#include <array>

#include "memory.h"
#include "instruction.h"

// ============================================================
// RV32I REFERENCE CPU
// ============================================================
//
// This is the architectural golden model.
//
// It is NOT pipelined yet.
//
// Each call to step():
//
//      Fetch
//        ↓
//      Decode
//        ↓
//      Execute
//        ↓
//      Memory
//        ↓
//      Writeback
//        ↓
//      Update PC
//
// One complete instruction is executed per step().
//
// ============================================================

class CPU
{
public:

    // ========================================================
    // REGISTER COUNT
    // ========================================================

    static constexpr std::size_t NUM_REGISTERS = 32;


    // ========================================================
    // CONSTRUCTOR
    // ========================================================

    explicit CPU(Memory& memory);


    // ========================================================
    // RESET
    // ========================================================
    //
    // PC = resetPC
    // x0-x31 = 0
    // counters = 0
    //
    // ========================================================

    void reset(uint32_t resetPC = 0);


    // ========================================================
    // EXECUTE ONE INSTRUCTION
    // ========================================================
    //
    // Returns:
    //
    // true  -> instruction executed successfully
    // false -> invalid/unsupported instruction encountered
    //
    // ========================================================

    bool step();


    // ========================================================
    // RUN
    // ========================================================
    //
    // Execute up to maxInstructions.
    //
    // This prevents the reference model from running forever
    // if a program contains an infinite loop.
    //
    // ========================================================

    bool run(std::size_t maxInstructions);


    // ========================================================
    // PROGRAM COUNTER
    // ========================================================

    uint32_t getPC() const;


    // ========================================================
    // REGISTER ACCESS
    // ========================================================

    uint32_t getRegister(uint8_t index) const;

    void setRegister(
        uint8_t index,
        uint32_t value
    );


    // ========================================================
    // EXECUTION STATISTICS
    // ========================================================

    uint64_t getInstructionCount() const;


    // ========================================================
    // REGISTER DUMP
    // ========================================================

    void dumpRegisters() const;


private:

    // ========================================================
    // ARCHITECTURAL STATE
    // ========================================================

    uint32_t pc;

    std::array<uint32_t, NUM_REGISTERS> registers;

    Memory& memory;

    uint64_t instructionCount;


    // ========================================================
    // EXECUTION
    // ========================================================

    bool execute(
        const DecodedInstruction& instruction
    );


    // ========================================================
    // REGISTER WRITEBACK
    // ========================================================
    //
    // All register writes should go through this function.
    //
    // This guarantees:
    //
    //              x0 always remains zero
    //
    // ========================================================

    void writeRegister(
        uint8_t rd,
        uint32_t value
    );


    // ========================================================
    // ALU / INTEGER OPERATIONS
    // ========================================================

    void executeInteger(
        const DecodedInstruction& instruction
    );


    // ========================================================
    // LOAD OPERATIONS
    // ========================================================

    void executeLoad(
        const DecodedInstruction& instruction
    );


    // ========================================================
    // STORE OPERATIONS
    // ========================================================

    void executeStore(
        const DecodedInstruction& instruction
    );


    // ========================================================
    // BRANCH OPERATIONS
    // ========================================================

    void executeBranch(
        const DecodedInstruction& instruction
    );


    // ========================================================
    // JUMP OPERATIONS
    // ========================================================

    void executeJump(
        const DecodedInstruction& instruction
    );


    // ========================================================
    // UPPER IMMEDIATE OPERATIONS
    // ========================================================

    void executeUpperImmediate(
        const DecodedInstruction& instruction
    );
};

#endif // CPU_H