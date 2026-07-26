#include "decoder.h"

// ============================================================
// MAIN DECODER
// ============================================================

DecodedInstruction Decoder::decode(uint32_t instruction)
{
    DecodedInstruction decoded;

    decoded.raw = instruction;

    // --------------------------------------------------------
    // Extract common instruction fields
    // --------------------------------------------------------

    const uint8_t opcode_value = extractOpcode(instruction);

    decoded.rd     = extractRd(instruction);
    decoded.funct3 = extractFunct3(instruction);
    decoded.rs1    = extractRs1(instruction);
    decoded.rs2    = extractRs2(instruction);
    decoded.funct7 = extractFunct7(instruction);

    decoded.opcode = static_cast<Opcode>(opcode_value);

    // --------------------------------------------------------
    // NOP
    //
    // Standard RV32I NOP:
    //
    // addi x0, x0, 0
    // 0x00000013
    // --------------------------------------------------------

    if (instruction == 0x00000013) {

        decoded.opcode    = Opcode::OP_IMM;
        decoded.format    = InstructionFormat::I_TYPE;
        decoded.operation = Operation::NOP;
        decoded.immediate = 0;
        decoded.valid     = true;

        return decoded;
    }


    // ========================================================
    // DECODE BY OPCODE
    // ========================================================

    switch (opcode_value) {

        // ====================================================
        // R-TYPE
        // ====================================================

        case 0x33:

            decoded.opcode = Opcode::OP;
            decoded.format = InstructionFormat::R_TYPE;

            decoded.operation =
                decodeRType(
                    decoded.funct3,
                    decoded.funct7
                );

            decoded.immediate = 0;

            break;


        // ====================================================
        // I-TYPE ALU
        // ====================================================

        case 0x13:

            decoded.opcode = Opcode::OP_IMM;
            decoded.format = InstructionFormat::I_TYPE;

            decoded.operation =
                decodeOpImmediate(
                    decoded.funct3,
                    decoded.funct7
                );

            decoded.immediate =
                extractImmediateI(instruction);

            break;


        // ====================================================
        // LOAD
        // ====================================================

        case 0x03:

            decoded.opcode = Opcode::LOAD;
            decoded.format = InstructionFormat::I_TYPE;

            decoded.operation =
                decodeLoad(decoded.funct3);

            decoded.immediate =
                extractImmediateI(instruction);

            break;


        // ====================================================
        // STORE
        // ====================================================

        case 0x23:

            decoded.opcode = Opcode::STORE;
            decoded.format = InstructionFormat::S_TYPE;

            decoded.operation =
                decodeStore(decoded.funct3);

            decoded.immediate =
                extractImmediateS(instruction);

            break;


        // ====================================================
        // BRANCH
        // ====================================================

        case 0x63:

            decoded.opcode = Opcode::BRANCH;
            decoded.format = InstructionFormat::B_TYPE;

            decoded.operation =
                decodeBranch(decoded.funct3);

            decoded.immediate =
                extractImmediateB(instruction);

            break;


        // ====================================================
        // JAL
        // ====================================================

        case 0x6F:

            decoded.opcode    = Opcode::JAL;
            decoded.format    = InstructionFormat::J_TYPE;
            decoded.operation = Operation::JAL;

            decoded.immediate =
                extractImmediateJ(instruction);

            break;


        // ====================================================
        // JALR
        // ====================================================

        case 0x67:

            decoded.opcode = Opcode::JALR;
            decoded.format = InstructionFormat::I_TYPE;

            // JALR is only valid for funct3 = 000.
            if (decoded.funct3 == 0x0) {
                decoded.operation = Operation::JALR;
            }
            else {
                decoded.operation = Operation::INVALID;
            }

            decoded.immediate =
                extractImmediateI(instruction);

            break;


        // ====================================================
        // LUI
        // ====================================================

        case 0x37:

            decoded.opcode    = Opcode::LUI;
            decoded.format    = InstructionFormat::U_TYPE;
            decoded.operation = Operation::LUI;

            decoded.immediate =
                extractImmediateU(instruction);

            break;


        // ====================================================
        // AUIPC
        // ====================================================

        case 0x17:

            decoded.opcode    = Opcode::AUIPC;
            decoded.format    = InstructionFormat::U_TYPE;
            decoded.operation = Operation::AUIPC;

            decoded.immediate =
                extractImmediateU(instruction);

            break;


        // ====================================================
        // UNKNOWN OPCODE
        // ====================================================

        default:

            decoded.opcode    = Opcode::INVALID;
            decoded.format    = InstructionFormat::INVALID;
            decoded.operation = Operation::INVALID;
            decoded.immediate = 0;

            break;
    }


    // ========================================================
    // VALIDITY
    // ========================================================

    decoded.valid =
        (decoded.operation != Operation::INVALID);

    return decoded;
}


// ============================================================
// R-TYPE DECODER
// ============================================================

Operation Decoder::decodeRType(
    uint8_t funct3,
    uint8_t funct7
)
{
    switch (funct3) {

        // ----------------------------------------------------
        // ADD / SUB
        // ----------------------------------------------------

        case 0x0:

            if (funct7 == 0x00)
                return Operation::ADD;

            if (funct7 == 0x20)
                return Operation::SUB;

            return Operation::INVALID;


        // ----------------------------------------------------
        // SLL
        // ----------------------------------------------------

        case 0x1:

            if (funct7 == 0x00)
                return Operation::SLL;

            return Operation::INVALID;


        // ----------------------------------------------------
        // SLT
        // ----------------------------------------------------

        case 0x2:

            if (funct7 == 0x00)
                return Operation::SLT;

            return Operation::INVALID;


        // ----------------------------------------------------
        // SLTU
        // ----------------------------------------------------

        case 0x3:

            if (funct7 == 0x00)
                return Operation::SLTU;

            return Operation::INVALID;


        // ----------------------------------------------------
        // XOR
        // ----------------------------------------------------

        case 0x4:

            if (funct7 == 0x00)
                return Operation::XOR;

            return Operation::INVALID;


        // ----------------------------------------------------
        // SRL / SRA
        // ----------------------------------------------------

        case 0x5:

            if (funct7 == 0x00)
                return Operation::SRL;

            if (funct7 == 0x20)
                return Operation::SRA;

            return Operation::INVALID;


        // ----------------------------------------------------
        // OR
        // ----------------------------------------------------

        case 0x6:

            if (funct7 == 0x00)
                return Operation::OR;

            return Operation::INVALID;


        // ----------------------------------------------------
        // AND
        // ----------------------------------------------------

        case 0x7:

            if (funct7 == 0x00)
                return Operation::AND;

            return Operation::INVALID;


        default:
            return Operation::INVALID;
    }
}


// ============================================================
// I-TYPE ALU DECODER
// ============================================================

Operation Decoder::decodeOpImmediate(
    uint8_t funct3,
    uint8_t funct7
)
{
    switch (funct3) {

        // ADDI
        case 0x0:
            return Operation::ADDI;


        // SLLI
        case 0x1:

            if (funct7 == 0x00)
                return Operation::SLLI;

            return Operation::INVALID;


        // SLTI
        case 0x2:
            return Operation::SLTI;


        // SLTIU
        case 0x3:
            return Operation::SLTIU;


        // XORI
        case 0x4:
            return Operation::XORI;


        // SRLI / SRAI
        case 0x5:

            if (funct7 == 0x00)
                return Operation::SRLI;

            if (funct7 == 0x20)
                return Operation::SRAI;

            return Operation::INVALID;


        // ORI
        case 0x6:
            return Operation::ORI;


        // ANDI
        case 0x7:
            return Operation::ANDI;


        default:
            return Operation::INVALID;
    }
}


// ============================================================
// LOAD DECODER
// ============================================================

Operation Decoder::decodeLoad(uint8_t funct3)
{
    switch (funct3) {

        case 0x0:
            return Operation::LB;

        case 0x1:
            return Operation::LH;

        case 0x2:
            return Operation::LW;

        case 0x4:
            return Operation::LBU;

        case 0x5:
            return Operation::LHU;

        default:
            return Operation::INVALID;
    }
}


// ============================================================
// STORE DECODER
// ============================================================

Operation Decoder::decodeStore(uint8_t funct3)
{
    switch (funct3) {

        case 0x0:
            return Operation::SB;

        case 0x1:
            return Operation::SH;

        case 0x2:
            return Operation::SW;

        default:
            return Operation::INVALID;
    }
}


// ============================================================
// BRANCH DECODER
// ============================================================

Operation Decoder::decodeBranch(uint8_t funct3)
{
    switch (funct3) {

        case 0x0:
            return Operation::BEQ;

        case 0x1:
            return Operation::BNE;

        case 0x4:
            return Operation::BLT;

        case 0x5:
            return Operation::BGE;

        case 0x6:
            return Operation::BLTU;

        case 0x7:
            return Operation::BGEU;

        default:
            return Operation::INVALID;
    }
}