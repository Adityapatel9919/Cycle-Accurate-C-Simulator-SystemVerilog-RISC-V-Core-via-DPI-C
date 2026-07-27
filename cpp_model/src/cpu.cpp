#include "cpu.h"

#include <iomanip>
#include <iostream>

// ============================================================
// Constructor
// ============================================================

CPU::CPU(Memory& memory)
    : memory_(memory)
{
    reset();
}


// ============================================================
// Reset
// ============================================================

void CPU::reset()
{
    registers_.fill(0);

    pc_ = 0;
    instructionCount_ = 0;
}


// ============================================================
// Register access
// ============================================================

uint32_t CPU::getRegister(uint32_t index) const
{
    if (index >= registers_.size()) {
        return 0;
    }

    // x0 is architecturally hardwired to zero.
    if (index == 0) {
        return 0;
    }

    return registers_[index];
}


void CPU::writeRegister(uint32_t rd, uint32_t value)
{
    if (rd == 0 || rd >= registers_.size()) {
        return;
    }

    registers_[rd] = value;
}


uint32_t CPU::getPC() const
{
    return pc_;
}


uint64_t CPU::getInstructionCount() const
{
    return instructionCount_;
}


// ============================================================
// Execute one instruction without trace
//
// Existing regression code can continue using:
//
//     cpu.step();
//
// ============================================================

bool CPU::step()
{
    Commit ignoredCommit{};

    return step(ignoredCommit);
}


// ============================================================
// Execute one instruction WITH architectural commit information
// ============================================================

bool CPU::step(Commit& commit)
{
    // Clear previous commit information.
    commit = Commit{};

    // --------------------------------------------------------
    // Fetch
    // --------------------------------------------------------

    uint32_t instruction = 0;

    try {
        instruction = memory_.read32(pc_);
    }
    catch (...) {
        std::cerr
            << "Memory read error at PC 0x"
            << std::hex
            << std::setw(8)
            << std::setfill('0')
            << pc_
            << '\n';

        return false;
    }

    // --------------------------------------------------------
    // Create basic commit record BEFORE changing PC
    // --------------------------------------------------------

    commit.valid       = true;
    commit.pc          = pc_;
    commit.instruction = instruction;

    // Default: instruction does not write a register.
    commit.regWrite = false;
    commit.rd       = 0;
    commit.rdValue  = 0;

    // --------------------------------------------------------
    // Decode
    // --------------------------------------------------------

    

    DecodedInstruction decoded =
    Decoder::decode(instruction);

if (!decoded.valid) {

    std::cerr
        << "Invalid/unsupported instruction 0x"
        << std::hex
        << std::setw(8)
        << std::setfill('0')
        << instruction
        << " at PC 0x"
        << std::setw(8)
        << pc_
        << '\n';

    commit.valid = false;

    return false;
}
    // --------------------------------------------------------
    // Execute
    // --------------------------------------------------------

    if (!executeInstruction(decoded, commit)) {
        commit.valid = false;

        return false;
    }

    // x0 must always remain zero.
    registers_[0] = 0;

    ++instructionCount_;

    return true;
}


// ============================================================
// Execute decoded instruction
// ============================================================

bool CPU::executeInstruction(
    const DecodedInstruction& d,
    Commit& commit
)
{
    const uint32_t currentPC = pc_;

    // Sequential next PC unless a branch/jump changes it.
    uint32_t nextPC = currentPC + 4;

    const uint32_t rs1Value = getRegister(d.rs1);
    const uint32_t rs2Value = getRegister(d.rs2);

    uint32_t result = 0;

    // ========================================================
    // R-TYPE
    // ========================================================

    switch (d.operation) {
        case Operation::NOP:
    // Architectural NOP:
    // no register write
    // no memory write
    // PC advances normally by 4
    break;

        case Operation::ADD:
            result = rs1Value + rs2Value;

            writeRegister(d.rd, result);

            if (d.rd != 0) {
                commit.regWrite = true;
                commit.rd       = d.rd;
                commit.rdValue  = result;
            }

            break;


        case Operation::SUB:
            result = rs1Value - rs2Value;

            writeRegister(d.rd, result);

            if (d.rd != 0) {
                commit.regWrite = true;
                commit.rd       = d.rd;
                commit.rdValue  = result;
            }

            break;


        case Operation::SLL:
            result =
                rs1Value << (rs2Value & 0x1F);

            writeRegister(d.rd, result);

            if (d.rd != 0) {
                commit.regWrite = true;
                commit.rd       = d.rd;
                commit.rdValue  = result;
            }

            break;


        case Operation::SLT:
            result =
                static_cast<int32_t>(rs1Value) <
                static_cast<int32_t>(rs2Value);

            writeRegister(d.rd, result);

            if (d.rd != 0) {
                commit.regWrite = true;
                commit.rd       = d.rd;
                commit.rdValue  = result;
            }

            break;


        case Operation::SLTU:
            result = rs1Value < rs2Value;

            writeRegister(d.rd, result);

            if (d.rd != 0) {
                commit.regWrite = true;
                commit.rd       = d.rd;
                commit.rdValue  = result;
            }

            break;


        case Operation::XOR:
            result = rs1Value ^ rs2Value;

            writeRegister(d.rd, result);

            if (d.rd != 0) {
                commit.regWrite = true;
                commit.rd       = d.rd;
                commit.rdValue  = result;
            }

            break;


        case Operation::SRL:
            result =
                rs1Value >> (rs2Value & 0x1F);

            writeRegister(d.rd, result);

            if (d.rd != 0) {
                commit.regWrite = true;
                commit.rd       = d.rd;
                commit.rdValue  = result;
            }

            break;


        case Operation::SRA:
            result =
                static_cast<uint32_t>(
                    static_cast<int32_t>(rs1Value) >>
                    (rs2Value & 0x1F)
                );

            writeRegister(d.rd, result);

            if (d.rd != 0) {
                commit.regWrite = true;
                commit.rd       = d.rd;
                commit.rdValue  = result;
            }

            break;


        case Operation::OR:
            result = rs1Value | rs2Value;

            writeRegister(d.rd, result);

            if (d.rd != 0) {
                commit.regWrite = true;
                commit.rd       = d.rd;
                commit.rdValue  = result;
            }

            break;


        case Operation::AND:
            result = rs1Value & rs2Value;

            writeRegister(d.rd, result);

            if (d.rd != 0) {
                commit.regWrite = true;
                commit.rd       = d.rd;
                commit.rdValue  = result;
            }

            break;


        // ====================================================
        // I-TYPE ALU
        // ====================================================

        case Operation::ADDI:
            result =
                rs1Value +
                static_cast<uint32_t>(d.immediate);

            writeRegister(d.rd, result);

            if (d.rd != 0) {
                commit.regWrite = true;
                commit.rd       = d.rd;
                commit.rdValue  = result;
            }

            break;


        case Operation::SLTI:
            result =
                static_cast<int32_t>(rs1Value) <
                d.immediate;

            writeRegister(d.rd, result);

            if (d.rd != 0) {
                commit.regWrite = true;
                commit.rd       = d.rd;
                commit.rdValue  = result;
            }

            break;


        case Operation::SLTIU:
            result =
                rs1Value <
                static_cast<uint32_t>(d.immediate);

            writeRegister(d.rd, result);

            if (d.rd != 0) {
                commit.regWrite = true;
                commit.rd       = d.rd;
                commit.rdValue  = result;
            }

            break;


        case Operation::XORI:
            result =
                rs1Value ^
                static_cast<uint32_t>(d.immediate);

            writeRegister(d.rd, result);

            if (d.rd != 0) {
                commit.regWrite = true;
                commit.rd       = d.rd;
                commit.rdValue  = result;
            }

            break;


        case Operation::ORI:
            result =
                rs1Value |
                static_cast<uint32_t>(d.immediate);

            writeRegister(d.rd, result);

            if (d.rd != 0) {
                commit.regWrite = true;
                commit.rd       = d.rd;
                commit.rdValue  = result;
            }

            break;


        case Operation::ANDI:
            result =
                rs1Value &
                static_cast<uint32_t>(d.immediate);

            writeRegister(d.rd, result);

            if (d.rd != 0) {
                commit.regWrite = true;
                commit.rd       = d.rd;
                commit.rdValue  = result;
            }

            break;


        case Operation::SLLI:
            result =
                rs1Value <<
                (static_cast<uint32_t>(d.immediate) & 0x1F);

            writeRegister(d.rd, result);

            if (d.rd != 0) {
                commit.regWrite = true;
                commit.rd       = d.rd;
                commit.rdValue  = result;
            }

            break;


        case Operation::SRLI:
            result =
                rs1Value >>
                (static_cast<uint32_t>(d.immediate) & 0x1F);

            writeRegister(d.rd, result);

            if (d.rd != 0) {
                commit.regWrite = true;
                commit.rd       = d.rd;
                commit.rdValue  = result;
            }

            break;


        case Operation::SRAI:
            result =
                static_cast<uint32_t>(
                    static_cast<int32_t>(rs1Value) >>
                    (static_cast<uint32_t>(d.immediate) & 0x1F)
                );

            writeRegister(d.rd, result);

            if (d.rd != 0) {
                commit.regWrite = true;
                commit.rd       = d.rd;
                commit.rdValue  = result;
            }

            break;


        // ====================================================
        // LOAD
        // ====================================================

        case Operation::LW: {
            const uint32_t address =
                rs1Value +
                static_cast<uint32_t>(d.immediate);

            try {
                result = memory_.read32(address);
            }
            catch (...) {
                std::cerr
                    << "LW memory error at address 0x"
                    << std::hex
                    << address
                    << '\n';

                return false;
            }

            writeRegister(d.rd, result);

            if (d.rd != 0) {
                commit.regWrite = true;
                commit.rd       = d.rd;
                commit.rdValue  = result;
            }

            break;
        }


        // ====================================================
        // STORE
        // ====================================================

       case Operation::SW: {

    const uint32_t address =
        rs1Value +
        static_cast<uint32_t>(d.immediate);

    try {
        memory_.write32(address, rs2Value);
    }
    catch (...) {

        std::cerr
            << "SW memory error at address 0x"
            << std::hex
            << address
            << '\n';

        return false;
    }

    // Architectural memory commit
    commit.memWrite     = true;
    commit.memAddress   = address;
    commit.memValue     = rs2Value;
    commit.memWriteSize = 4;

    break;
}


        // ====================================================
        // CONDITIONAL BRANCHES
        // ====================================================

        case Operation::BEQ:
            if (rs1Value == rs2Value) {
                nextPC =
                    currentPC +
                    static_cast<uint32_t>(d.immediate);
            }

            break;


        case Operation::BNE:
            if (rs1Value != rs2Value) {
                nextPC =
                    currentPC +
                    static_cast<uint32_t>(d.immediate);
            }

            break;


        case Operation::BLT:
            if (
                static_cast<int32_t>(rs1Value) <
                static_cast<int32_t>(rs2Value)
            ) {
                nextPC =
                    currentPC +
                    static_cast<uint32_t>(d.immediate);
            }

            break;


        case Operation::BGE:
            if (
                static_cast<int32_t>(rs1Value) >=
                static_cast<int32_t>(rs2Value)
            ) {
                nextPC =
                    currentPC +
                    static_cast<uint32_t>(d.immediate);
            }

            break;


        case Operation::BLTU:
            if (rs1Value < rs2Value) {
                nextPC =
                    currentPC +
                    static_cast<uint32_t>(d.immediate);
            }

            break;


        case Operation::BGEU:
            if (rs1Value >= rs2Value) {
                nextPC =
                    currentPC +
                    static_cast<uint32_t>(d.immediate);
            }

            break;


        // ====================================================
        // JAL
        // ====================================================

        case Operation::JAL: {

            const uint32_t linkAddress =
                currentPC + 4;

            writeRegister(
                d.rd,
                linkAddress
            );

            if (d.rd != 0) {
                commit.regWrite = true;
                commit.rd       = d.rd;
                commit.rdValue  = linkAddress;
            }

            nextPC =
                currentPC +
                static_cast<uint32_t>(d.immediate);

            break;
        }


        // ====================================================
        // JALR
        // ====================================================

        case Operation::JALR: {

            const uint32_t linkAddress =
                currentPC + 4;

            // IMPORTANT:
            // Calculate target using the OLD rs1 value before
            // writing rd. This matters when rd == rs1.

            const uint32_t targetAddress =
                (
                    rs1Value +
                    static_cast<uint32_t>(d.immediate)
                ) & ~1u;

            writeRegister(
                d.rd,
                linkAddress
            );

            if (d.rd != 0) {
                commit.regWrite = true;
                commit.rd       = d.rd;
                commit.rdValue  = linkAddress;
            }

            nextPC = targetAddress;

            break;
        }


        // ====================================================
        // LUI
        // ====================================================

        case Operation::LUI:

            result =
                static_cast<uint32_t>(d.immediate);

            writeRegister(d.rd, result);

            if (d.rd != 0) {
                commit.regWrite = true;
                commit.rd       = d.rd;
                commit.rdValue  = result;
            }

            break;


        // ====================================================
        // AUIPC
        // ====================================================

        case Operation::AUIPC:

            result =
                currentPC +
                static_cast<uint32_t>(d.immediate);

            writeRegister(d.rd, result);

            if (d.rd != 0) {
                commit.regWrite = true;
                commit.rd       = d.rd;
                commit.rdValue  = result;
            }

            break;


        // ====================================================
        // Unsupported operation
        // ====================================================

        default:

            std::cerr
                << "Unsupported decoded operation at PC 0x"
                << std::hex
                << currentPC
                << '\n';

            return false;
    }


    // ========================================================
    // Architectural PC update
    // ========================================================

    pc_ = nextPC;
    commit.nextPC = nextPC;
    return true;
}


// ============================================================
// Run multiple instructions
// ============================================================

bool CPU::run(std::size_t instructionLimit)
{
    for (std::size_t i = 0;
         i < instructionLimit;
         ++i) {

        if (!step()) {
            return false;
        }
    }

    return true;
}


// ============================================================
// Register dump
// ============================================================

void CPU::dumpRegisters() const
{
    std::cout
        << "\n========================================\n"
        << "         RV32I REGISTER STATE\n"
        << "========================================\n";

    for (uint32_t i = 0; i < 32; ++i) {

        std::cout
            << "x"
            << std::dec
            << std::setw(2)
            << i
            << " = 0x"
            << std::hex
            << std::setw(8)
            << std::setfill('0')
            << getRegister(i)
            << std::setfill(' ')
            << '\n';
    }

    std::cout
        << "========================================\n"
        << "PC           = 0x"
        << std::hex
        << std::setw(8)
        << std::setfill('0')
        << pc_
        << std::setfill(' ')
        << '\n'

        << "Instructions = "
        << std::dec
        << instructionCount_
        << '\n'

        << "========================================\n";
}