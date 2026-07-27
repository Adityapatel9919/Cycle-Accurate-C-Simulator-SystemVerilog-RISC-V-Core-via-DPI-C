#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <cstdint>


// RV32I OPCODES


enum class Opcode : uint8_t {

    LOAD      = 0x03,
    OP_IMM    = 0x13,
    AUIPC     = 0x17,
    STORE     = 0x23,
    OP        = 0x33,
    LUI       = 0x37,
    BRANCH    = 0x63,
    JALR      = 0x67,
    JAL       = 0x6F,

    INVALID   = 0xFF
};



// INSTRUCTION FORMAT


enum class InstructionFormat {

    R_TYPE,
    I_TYPE,
    S_TYPE,
    B_TYPE,
    U_TYPE,
    J_TYPE,

    INVALID
};



// RV32I OPERATIONS
//
// This represents the actual decoded instruction.
//
// Example:
//
// 0x002081B3
//
// opcode = OP
// funct3 = 000
// funct7 = 0000000
//
// operation = ADD


enum class Operation {

    // --------------------------------------------------------
    // R-Type
    // --------------------------------------------------------

    ADD,
    SUB,

    SLL,
    SLT,
    SLTU,

    XOR,
    SRL,
    SRA,

    OR,
    AND,


    // --------------------------------------------------------
    // I-Type Arithmetic
    // --------------------------------------------------------

    ADDI,

    SLTI,
    SLTIU,

    XORI,
    ORI,
    ANDI,

    SLLI,
    SRLI,
    SRAI,


    // --------------------------------------------------------
    // Loads
    // --------------------------------------------------------

    LB,
    LH,
    LW,
    LBU,
    LHU,


    // --------------------------------------------------------
    // Stores
    // --------------------------------------------------------

    SB,
    SH,
    SW,


    // --------------------------------------------------------
    // Branches
    // --------------------------------------------------------

    BEQ,
    BNE,

    BLT,
    BGE,

    BLTU,
    BGEU,


    // --------------------------------------------------------
    // Jumps
    // --------------------------------------------------------

    JAL,
    JALR,


    // --------------------------------------------------------
    // Upper Immediate
    // --------------------------------------------------------

    LUI,
    AUIPC,


    // --------------------------------------------------------
    // Special
    // --------------------------------------------------------

    NOP,

    INVALID
};



// DECODED INSTRUCTION

//
// Decoder converts:
//
//          32-bit machine instruction
//
//                    ↓
//
//          DecodedInstruction
//
// Example:
//
// add x3, x1, x2
//
// raw       = 0x002081B3
// operation = ADD
// rd        = 3
// rs1       = 1
// rs2       = 2
//


struct DecodedInstruction {

    // Original 32-bit machine instruction
    uint32_t raw = 0;


    // --------------------------------------------------------
    // Basic decode information
    // --------------------------------------------------------

    Opcode opcode = Opcode::INVALID;

    InstructionFormat format =
        InstructionFormat::INVALID;

    Operation operation =
        Operation::INVALID;


    // --------------------------------------------------------
    // Register fields
    // --------------------------------------------------------

    uint8_t rd  = 0;
    uint8_t rs1 = 0;
    uint8_t rs2 = 0;


    // --------------------------------------------------------
    // Function fields
    // --------------------------------------------------------

    uint8_t funct3 = 0;
    uint8_t funct7 = 0;


    // --------------------------------------------------------
    // Immediate
    //
    // Signed because branch offsets, ADDI values, etc.
    // can be negative.
    // --------------------------------------------------------

    int32_t immediate = 0;


    // --------------------------------------------------------
    // Validity
    // --------------------------------------------------------

    bool valid = false;
};



// OPCODE EXTRACTION


inline uint8_t extractOpcode(uint32_t instruction)
{
    return static_cast<uint8_t>(
        instruction & 0x7F
    );
}



// RD EXTRACTION
//
// instruction[11:7]


inline uint8_t extractRd(uint32_t instruction)
{
    return static_cast<uint8_t>(
        (instruction >> 7) & 0x1F
    );
}



// FUNCT3 EXTRACTION
//
// instruction[14:12]


inline uint8_t extractFunct3(uint32_t instruction)
{
    return static_cast<uint8_t>(
        (instruction >> 12) & 0x07
    );
}



// RS1 EXTRACTION
//
// instruction[19:15]


inline uint8_t extractRs1(uint32_t instruction)
{
    return static_cast<uint8_t>(
        (instruction >> 15) & 0x1F
    );
}



// RS2 EXTRACTION

// instruction[24:20]


inline uint8_t extractRs2(uint32_t instruction)
{
    return static_cast<uint8_t>(
        (instruction >> 20) & 0x1F
    );
}


// ============================================================
// FUNCT7 EXTRACTION
//
// instruction[31:25]
// ============================================================

inline uint8_t extractFunct7(uint32_t instruction)
{
    return static_cast<uint8_t>(
        (instruction >> 25) & 0x7F
    );
}


// ============================================================
// SIGN EXTENSION HELPER
// ============================================================
//
// Example:
//
// 12-bit:
//
// 1111 1111 1111
//
// represents -1.
//
// We need:
//
// 11111111 11111111 11111111 11111111
//
// ============================================================

inline int32_t signExtend(
    uint32_t value,
    unsigned bits
)
{
    const uint32_t sign_bit =
        1u << (bits - 1);

    return static_cast<int32_t>(
        (value ^ sign_bit) - sign_bit
    );
}


// ============================================================
// I-TYPE IMMEDIATE
//
// imm[11:0] = instruction[31:20]
// ============================================================

inline int32_t extractImmediateI(
    uint32_t instruction
)
{
    uint32_t imm =
        (instruction >> 20) & 0xFFF;

    return signExtend(imm, 12);
}


// ============================================================
// S-TYPE IMMEDIATE
//
// imm[11:5] = instruction[31:25]
// imm[4:0]  = instruction[11:7]
// ============================================================

inline int32_t extractImmediateS(
    uint32_t instruction
)
{
    uint32_t imm11_5 =
        (instruction >> 25) & 0x7F;

    uint32_t imm4_0 =
        (instruction >> 7) & 0x1F;

    uint32_t immediate =
        (imm11_5 << 5) |
        imm4_0;

    return signExtend(immediate, 12);
}


// ============================================================
// B-TYPE IMMEDIATE
//
// Immediate layout:
//
// imm[12]   = instruction[31]
// imm[11]   = instruction[7]
// imm[10:5] = instruction[30:25]
// imm[4:1]  = instruction[11:8]
// imm[0]    = 0
// ============================================================

inline int32_t extractImmediateB(
    uint32_t instruction
)
{
    uint32_t imm12 =
        (instruction >> 31) & 0x1;

    uint32_t imm11 =
        (instruction >> 7) & 0x1;

    uint32_t imm10_5 =
        (instruction >> 25) & 0x3F;

    uint32_t imm4_1 =
        (instruction >> 8) & 0xF;

    uint32_t immediate =
        (imm12   << 12) |
        (imm11   << 11) |
        (imm10_5 << 5)  |
        (imm4_1  << 1);

    return signExtend(immediate, 13);
}



// U-TYPE IMMEDIATE
//
// imm[31:12] = instruction[31:12]


inline int32_t extractImmediateU(
    uint32_t instruction
)
{
    return static_cast<int32_t>(
        instruction & 0xFFFFF000
    );
}



// J-TYPE IMMEDIATE
//
// imm[20]    = instruction[31]
// imm[10:1]  = instruction[30:21]
// imm[11]    = instruction[20]
// imm[19:12] = instruction[19:12]
// imm[0]     = 0


inline int32_t extractImmediateJ(
    uint32_t instruction
)
{
    uint32_t imm20 =
        (instruction >> 31) & 0x1;

    uint32_t imm10_1 =
        (instruction >> 21) & 0x3FF;

    uint32_t imm11 =
        (instruction >> 20) & 0x1;

    uint32_t imm19_12 =
        (instruction >> 12) & 0xFF;

    uint32_t immediate =
        (imm20    << 20) |
        (imm19_12 << 12) |
        (imm11    << 11) |
        (imm10_1  << 1);

    return signExtend(immediate, 21);
}

#endif // INSTRUCTION_H