#ifndef COMMIT_H
#define COMMIT_H

#include <cstdint>

// ============================================================
// ARCHITECTURAL COMMIT INFORMATION
// ============================================================
//
// One CommitInfo object represents ONE architecturally
// completed RISC-V instruction.
//
// IMPORTANT:
//
// This describes architectural effects, NOT pipeline activity.
//
// The C++ reference model may execute an instruction directly,
// while the RTL may require several cycles because of:
//
//   - pipeline stages
//   - forwarding
//   - stalls
//   - branch flushes
//
// We compare the two implementations at COMMIT/RETIRE time.
//
// ============================================================

struct CommitInfo
{
    // ========================================================
    // INSTRUCTION INFORMATION
    // ========================================================

    // Address of the instruction that committed.
    uint32_t pc = 0;

    // Raw 32-bit RISC-V instruction.
    uint32_t instruction = 0;


    // ========================================================
    // REGISTER WRITEBACK
    // ========================================================

    // True if this instruction writes an architectural
    // register.
    bool regWrite = false;

    // Destination register x0-x31.
    uint8_t rd = 0;

    // Value written to rd.
    uint32_t rdValue = 0;


    // ========================================================
    // MEMORY WRITE
    // ========================================================

    // True if this instruction performs a store.
    bool memWrite = false;

    // Effective byte address of the store.
    uint32_t memAddress = 0;

    // Store data.
    uint32_t memValue = 0;


    // ========================================================
    // MEMORY WRITE SIZE
    // ========================================================
    //
    // 0 -> no memory write
    // 1 -> byte      (SB)
    // 2 -> halfword  (SH)
    // 4 -> word      (SW)
    //
    // ========================================================

    uint8_t memWriteSize = 0;


    // ========================================================
    // NEXT PC
    // ========================================================
    //
    // Architectural PC after this instruction executes.
    //
    // Examples:
    //
    // ADD:
    //      nextPC = pc + 4
    //
    // taken BEQ:
    //      nextPC = pc + immediate
    //
    // JAL:
    //      nextPC = pc + immediate
    //
    // JALR:
    //      nextPC = (rs1 + immediate) & ~1
    //
    // ========================================================

    uint32_t nextPC = 0;


    // ========================================================
    // VALID
    // ========================================================
    //
    // Allows us to distinguish a real committed instruction
    // from an empty/default CommitInfo object.
    //
    // ========================================================

    bool valid = false;
};

#endif // COMMIT_H