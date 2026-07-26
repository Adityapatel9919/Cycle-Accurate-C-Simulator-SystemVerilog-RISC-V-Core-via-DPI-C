#ifndef DECODER_H
#define DECODER_H

#include <cstdint>

#include "instruction.h"

// ============================================================
// RV32I INSTRUCTION DECODER
// ============================================================
//
// Converts a raw 32-bit RISC-V instruction:
//
//      uint32_t instruction
//
// into:
//
//      DecodedInstruction
//
// Example:
//
//      0x002081B3
//
//            ↓
//
//      operation = ADD
//      rd        = 3
//      rs1       = 1
//      rs2       = 2
//
// ============================================================

class Decoder
{
public:

    // ========================================================
    // MAIN DECODE FUNCTION
    // ========================================================
    //
    // This is the main interface used by the CPU.
    //
    // Example:
    //
    // uint32_t raw = memory.read32(pc);
    //
    // DecodedInstruction inst =
    //     Decoder::decode(raw);
    //
    // ========================================================

    static DecodedInstruction decode(uint32_t instruction);


private:

    // ========================================================
    // R-TYPE DECODER
    //
    // Handles:
    //
    // ADD
    // SUB
    // SLL
    // SLT
    // SLTU
    // XOR
    // SRL
    // SRA
    // OR
    // AND
    // ========================================================

    static Operation decodeRType(
        uint8_t funct3,
        uint8_t funct7
    );


    // ========================================================
    // I-TYPE ARITHMETIC DECODER
    //
    // Handles:
    //
    // ADDI
    // SLTI
    // SLTIU
    // XORI
    // ORI
    // ANDI
    // SLLI
    // SRLI
    // SRAI
    // ========================================================

    static Operation decodeOpImmediate(
        uint8_t funct3,
        uint8_t funct7
    );


    // ========================================================
    // LOAD DECODER
    //
    // Handles:
    //
    // LB
    // LH
    // LW
    // LBU
    // LHU
    // ========================================================

    static Operation decodeLoad(
        uint8_t funct3
    );


    // ========================================================
    // STORE DECODER
    //
    // Handles:
    //
    // SB
    // SH
    // SW
    // ========================================================

    static Operation decodeStore(
        uint8_t funct3
    );


    // ========================================================
    // BRANCH DECODER
    //
    // Handles:
    //
    // BEQ
    // BNE
    // BLT
    // BGE
    // BLTU
    // BGEU
    // ========================================================

    static Operation decodeBranch(
        uint8_t funct3
    );
};

#endif // DECODER_H