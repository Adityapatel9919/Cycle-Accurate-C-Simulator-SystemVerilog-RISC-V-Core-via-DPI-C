#include "cpu.h"
#include "decoder.h"

#include <iomanip>
#include <iostream>
#include <stdexcept>

// ============================================================
// CONSTRUCTOR
// ============================================================

CPU::CPU(Memory& memory)
    : pc(0),
      registers{},
      memory(memory),
      instructionCount(0)
{
    reset();
}


// ============================================================
// RESET
// ============================================================

void CPU::reset(uint32_t resetPC)
{
    pc = resetPC;

    registers.fill(0);

    instructionCount = 0;

    lastCommit = CommitInfo{};
}


// ============================================================
// PROGRAM COUNTER
// ============================================================

uint32_t CPU::getPC() const
{
    return pc;
}


// ============================================================
// REGISTER ACCESS
// ============================================================

uint32_t CPU::getRegister(uint8_t index) const
{
    if (index >= NUM_REGISTERS) {
        throw std::out_of_range("Invalid register index");
    }

    // x0 is architecturally hardwired to zero.
    if (index == 0) {
        return 0;
    }

    return registers[index];
}


void CPU::setRegister(
    uint8_t index,
    uint32_t value
)
{
    if (index >= NUM_REGISTERS) {
        throw std::out_of_range(
            "Invalid register index"
        );
    }

    if (index != 0) {
        registers[index] = value;
    }

    registers[0] = 0;
}


// ============================================================
// INTERNAL REGISTER WRITE
// ============================================================

void CPU::writeRegister(
    uint8_t rd,
    uint32_t value
)
{
    if (rd >= NUM_REGISTERS) {
        throw std::out_of_range(
            "Invalid destination register"
        );
    }

    // ========================================================
    // x0 IS HARDWIRED TO ZERO
    // ========================================================

    if (rd == 0) {
        registers[0] = 0;
        return;
    }


    // ========================================================
    // ARCHITECTURAL WRITEBACK
    // ========================================================

    registers[rd] = value;


    // ========================================================
    // COMMIT INFORMATION
    // ========================================================

    lastCommit.regWrite = true;

    lastCommit.rd = rd;

    lastCommit.rdValue = value;


    // Defensive x0 enforcement
    registers[0] = 0;
}


// ============================================================
// INSTRUCTION COUNT
// ============================================================

uint64_t CPU::getInstructionCount() const
{
    return instructionCount;
}


// ============================================================
// EXECUTE ONE INSTRUCTION
// ============================================================

bool CPU::step()
{
    // ========================================================
    // CLEAR PREVIOUS COMMIT
    // ========================================================

    lastCommit = CommitInfo{};


    // ========================================================
    // FETCH
    // ========================================================

    const uint32_t instructionPC = pc;

    uint32_t rawInstruction = 0;

    try {

        rawInstruction =
            memory.read32(instructionPC);

    }
    catch (const std::exception& e) {

        std::cerr
            << "Instruction fetch failed at PC 0x"
            << std::hex
            << std::setw(8)
            << std::setfill('0')
            << instructionPC
            << std::dec
            << ": "
            << e.what()
            << '\n';

        return false;
    }


    // ========================================================
    // DECODE
    // ========================================================

    DecodedInstruction instruction =
        Decoder::decode(rawInstruction);


    if (!instruction.valid) {

        std::cerr
            << "Invalid/unsupported instruction 0x"
            << std::hex
            << std::setw(8)
            << std::setfill('0')
            << rawInstruction
            << " at PC 0x"
            << std::setw(8)
            << instructionPC
            << std::dec
            << '\n';

        return false;
    }


    // ========================================================
    // INITIALISE COMMIT RECORD
    // ========================================================

    lastCommit.pc =
        instructionPC;

    lastCommit.instruction =
        rawInstruction;


    // ========================================================
    // EXECUTE
    // ========================================================

    try {

        if (!execute(instruction)) {
            return false;
        }

    }
    catch (const std::exception& e) {

        std::cerr
            << "Execution failed at PC 0x"
            << std::hex
            << std::setw(8)
            << std::setfill('0')
            << instructionPC
            << std::dec
            << ": "
            << e.what()
            << '\n';

        lastCommit = CommitInfo{};

        return false;
    }


    // ========================================================
    // ARCHITECTURAL x0 ENFORCEMENT
    // ========================================================

    registers[0] = 0;


    // ========================================================
    // COMPLETE COMMIT RECORD
    // ========================================================

    lastCommit.nextPC = pc;

    lastCommit.valid = true;


    ++instructionCount;

    return true;
}

// ============================================================
// RUN
// ============================================================
bool CPU::run(std::size_t maxInstructions)
{
    for (std::size_t i = 0; i < maxInstructions; ++i) {

        // ----------------------------------------------------
        // NORMAL PROGRAM COMPLETION
        // ----------------------------------------------------

        if (pc == memory.getProgramEnd()) {
            return true;
        }

        // ----------------------------------------------------
        // PC outside loaded instruction region
        // ----------------------------------------------------

        if (
            pc < memory.getProgramStart() ||
            pc > memory.getProgramEnd()
        ) {
            std::cerr
                << "ERROR: PC outside loaded program: 0x"
                << std::hex
                << pc
                << std::dec
                << '\n';

            return false;
        }

        if (!step()) {
            return false;
        }
    }

    return true;
}


// ============================================================
// MAIN EXECUTION DISPATCH
// ============================================================

bool CPU::execute(
    const DecodedInstruction& instruction
)
{
    switch (instruction.opcode) {

        // ----------------------------------------------------
        // Integer ALU operations
        // ----------------------------------------------------

        case Opcode::OP:
        case Opcode::OP_IMM:

            executeInteger(instruction);
            return true;


        // ----------------------------------------------------
        // Loads
        // ----------------------------------------------------

        case Opcode::LOAD:

            executeLoad(instruction);
            return true;


        // ----------------------------------------------------
        // Stores
        // ----------------------------------------------------

        case Opcode::STORE:

            executeStore(instruction);
            return true;


        // ----------------------------------------------------
        // Branches
        // ----------------------------------------------------

        case Opcode::BRANCH:

            executeBranch(instruction);
            return true;


        // ----------------------------------------------------
        // Jumps
        // ----------------------------------------------------

        case Opcode::JAL:
        case Opcode::JALR:

            executeJump(instruction);
            return true;


        // ----------------------------------------------------
        // LUI / AUIPC
        // ----------------------------------------------------

        case Opcode::LUI:
        case Opcode::AUIPC:

            executeUpperImmediate(instruction);
            return true;


        default:

            std::cerr
                << "Unsupported opcode during execution\n";

            return false;
    }
}


// ============================================================
// INTEGER / ALU OPERATIONS
// ============================================================

void CPU::executeInteger(
    const DecodedInstruction& instruction
)
{
    const uint32_t rs1 =
        getRegister(instruction.rs1);

    const uint32_t rs2 =
        getRegister(instruction.rs2);

    const uint32_t immediate =
        static_cast<uint32_t>(
            instruction.immediate
        );

    uint32_t result = 0;


    switch (instruction.operation) {

        // ====================================================
        // R-TYPE
        // ====================================================

        case Operation::ADD:

            result = rs1 + rs2;
            break;


        case Operation::SUB:

            result = rs1 - rs2;
            break;


        case Operation::SLL:

            result =
                rs1 << (rs2 & 0x1F);

            break;


        case Operation::SLT:

            result =
                static_cast<int32_t>(rs1) <
                static_cast<int32_t>(rs2);

            break;


        case Operation::SLTU:

            result = rs1 < rs2;
            break;


        case Operation::XOR:

            result = rs1 ^ rs2;
            break;


        case Operation::SRL:

            result =
                rs1 >> (rs2 & 0x1F);

            break;


        case Operation::SRA:

            result =
                static_cast<uint32_t>(
                    static_cast<int32_t>(rs1) >>
                    (rs2 & 0x1F)
                );

            break;


        case Operation::OR:

            result = rs1 | rs2;
            break;


        case Operation::AND:

            result = rs1 & rs2;
            break;


        // ====================================================
        // I-TYPE
        // ====================================================

        case Operation::ADDI:

            result = rs1 + immediate;
            break;


        case Operation::SLTI:

            result =
                static_cast<int32_t>(rs1) <
                instruction.immediate;

            break;


        case Operation::SLTIU:

            result =
                rs1 <
                static_cast<uint32_t>(
                    instruction.immediate
                );

            break;


        case Operation::XORI:

            result = rs1 ^ immediate;
            break;


        case Operation::ORI:

            result = rs1 | immediate;
            break;


        case Operation::ANDI:

            result = rs1 & immediate;
            break;


        case Operation::SLLI:

            result =
                rs1 << (immediate & 0x1F);

            break;


        case Operation::SRLI:

            result =
                rs1 >> (immediate & 0x1F);

            break;


        case Operation::SRAI:

            result =
                static_cast<uint32_t>(
                    static_cast<int32_t>(rs1) >>
                    (immediate & 0x1F)
                );

            break;


        // ====================================================
        // NOP
        // ====================================================

        case Operation::NOP:

            pc += 4;
            return;


        default:

            throw std::runtime_error(
                "Invalid integer operation"
            );
    }


    // --------------------------------------------------------
    // WRITEBACK
    // --------------------------------------------------------

    writeRegister(
        instruction.rd,
        result
    );


    // --------------------------------------------------------
    // NEXT INSTRUCTION
    // --------------------------------------------------------

    pc += 4;
}


// ============================================================
// LOAD OPERATIONS
// ============================================================

void CPU::executeLoad(
    const DecodedInstruction& instruction
)
{
    const uint32_t base =
        getRegister(instruction.rs1);

    const uint32_t address =
        base +
        static_cast<uint32_t>(
            instruction.immediate
        );

    uint32_t value = 0;


    switch (instruction.operation) {

        // ----------------------------------------------------
        // LB
        // ----------------------------------------------------

        case Operation::LB:
        {
            const int8_t byte =
                static_cast<int8_t>(
                    memory.read8(address)
                );

            value =
                static_cast<uint32_t>(
                    static_cast<int32_t>(byte)
                );

            break;
        }


        // ----------------------------------------------------
        // LH
        // ----------------------------------------------------

        case Operation::LH:
        {
            const int16_t half =
                static_cast<int16_t>(
                    memory.read16(address)
                );

            value =
                static_cast<uint32_t>(
                    static_cast<int32_t>(half)
                );

            break;
        }


        // ----------------------------------------------------
        // LW
        // ----------------------------------------------------

        case Operation::LW:

            value =
                memory.read32(address);

            break;


        // ----------------------------------------------------
        // LBU
        // ----------------------------------------------------

        case Operation::LBU:

            value =
                static_cast<uint32_t>(
                    memory.read8(address)
                );

            break;


        // ----------------------------------------------------
        // LHU
        // ----------------------------------------------------

        case Operation::LHU:

            value =
                static_cast<uint32_t>(
                    memory.read16(address)
                );

            break;


        default:

            throw std::runtime_error(
                "Invalid load operation"
            );
    }


    writeRegister(
        instruction.rd,
        value
    );

    pc += 4;
}


// ============================================================
// STORE OPERATIONS
// ============================================================

void CPU::executeStore(
    const DecodedInstruction& instruction
)
{
    const uint32_t base =
        getRegister(instruction.rs1);

    const uint32_t value =
        getRegister(instruction.rs2);

    const uint32_t address =
        base +
        static_cast<uint32_t>(
            instruction.immediate
        );


    switch (instruction.operation) {

        // ====================================================
        // SB
        // ====================================================

        case Operation::SB:
        {
            const uint8_t storeValue =
                static_cast<uint8_t>(
                    value & 0xFF
                );

            memory.write8(
                address,
                storeValue
            );


            lastCommit.memWrite = true;

            lastCommit.memAddress =
                address;

            lastCommit.memValue =
                static_cast<uint32_t>(
                    storeValue
                );

            lastCommit.memWriteSize = 1;

            break;
        }


        // ====================================================
        // SH
        // ====================================================

        case Operation::SH:
        {
            const uint16_t storeValue =
                static_cast<uint16_t>(
                    value & 0xFFFF
                );

            memory.write16(
                address,
                storeValue
            );


            lastCommit.memWrite = true;

            lastCommit.memAddress =
                address;

            lastCommit.memValue =
                static_cast<uint32_t>(
                    storeValue
                );

            lastCommit.memWriteSize = 2;

            break;
        }


        // ====================================================
        // SW
        // ====================================================

        case Operation::SW:
        {
            memory.write32(
                address,
                value
            );


            lastCommit.memWrite = true;

            lastCommit.memAddress =
                address;

            lastCommit.memValue =
                value;

            lastCommit.memWriteSize = 4;

            break;
        }


        default:

            throw std::runtime_error(
                "Invalid store operation"
            );
    }


    pc += 4;
}
// ============================================================
// BRANCH OPERATIONS
// ============================================================

void CPU::executeBranch(
    const DecodedInstruction& instruction
)
{
    const uint32_t rs1 =
        getRegister(instruction.rs1);

    const uint32_t rs2 =
        getRegister(instruction.rs2);

    bool branchTaken = false;


    switch (instruction.operation) {

        // ----------------------------------------------------
        // BEQ
        // ----------------------------------------------------

        case Operation::BEQ:

            branchTaken =
                (rs1 == rs2);

            break;


        // ----------------------------------------------------
        // BNE
        // ----------------------------------------------------

        case Operation::BNE:

            branchTaken =
                (rs1 != rs2);

            break;


        // ----------------------------------------------------
        // BLT - signed
        // ----------------------------------------------------

        case Operation::BLT:

            branchTaken =
                static_cast<int32_t>(rs1) <
                static_cast<int32_t>(rs2);

            break;


        // ----------------------------------------------------
        // BGE - signed
        // ----------------------------------------------------

        case Operation::BGE:

            branchTaken =
                static_cast<int32_t>(rs1) >=
                static_cast<int32_t>(rs2);

            break;


        // ----------------------------------------------------
        // BLTU - unsigned
        // ----------------------------------------------------

        case Operation::BLTU:

            branchTaken =
                rs1 < rs2;

            break;


        // ----------------------------------------------------
        // BGEU - unsigned
        // ----------------------------------------------------

        case Operation::BGEU:

            branchTaken =
                rs1 >= rs2;

            break;


        default:

            throw std::runtime_error(
                "Invalid branch operation"
            );
    }


    // --------------------------------------------------------
    // PC UPDATE
    // --------------------------------------------------------

    if (branchTaken) {

        pc =
            pc +
            static_cast<uint32_t>(
                instruction.immediate
            );

    }
    else {

        pc += 4;
    }
}


// ============================================================
// JUMP OPERATIONS
// ============================================================

void CPU::executeJump(
    const DecodedInstruction& instruction
)
{
    // PC+4 must be calculated using the OLD PC.

    const uint32_t returnAddress =
        pc + 4;


    switch (instruction.operation) {

        // ----------------------------------------------------
        // JAL
        //
        // rd = PC + 4
        // PC = PC + immediate
        // ----------------------------------------------------

        case Operation::JAL:

            writeRegister(
                instruction.rd,
                returnAddress
            );

            pc =
                pc +
                static_cast<uint32_t>(
                    instruction.immediate
                );

            break;


        // ----------------------------------------------------
        // JALR
        //
        // rd = PC + 4
        //
        // PC = (rs1 + immediate) & ~1
        // ----------------------------------------------------

        case Operation::JALR:
        {
            // Read rs1 before writeback.
            //
            // Important for cases such as:
            //
            // jalr x1, 0(x1)

            const uint32_t rs1 =
                getRegister(instruction.rs1);

            const uint32_t target =
                (
                    rs1 +
                    static_cast<uint32_t>(
                        instruction.immediate
                    )
                ) & ~1u;

            writeRegister(
                instruction.rd,
                returnAddress
            );

            pc = target;

            break;
        }


        default:

            throw std::runtime_error(
                "Invalid jump operation"
            );
    }
}


// ============================================================
// UPPER IMMEDIATE OPERATIONS
// ============================================================

void CPU::executeUpperImmediate(
    const DecodedInstruction& instruction
)
{
    switch (instruction.operation) {

        // ----------------------------------------------------
        // LUI
        //
        // rd = immediate
        // ----------------------------------------------------

        case Operation::LUI:

            writeRegister(
                instruction.rd,
                static_cast<uint32_t>(
                    instruction.immediate
                )
            );

            pc += 4;

            break;


        // ----------------------------------------------------
        // AUIPC
        //
        // rd = PC + immediate
        // ----------------------------------------------------

        case Operation::AUIPC:

            writeRegister(
                instruction.rd,
                pc +
                static_cast<uint32_t>(
                    instruction.immediate
                )
            );

            pc += 4;

            break;


        default:

            throw std::runtime_error(
                "Invalid upper-immediate operation"
            );
    }
}


// ============================================================
// REGISTER DUMP
// ============================================================

void CPU::dumpRegisters() const
{
    std::cout
        << "\n========================================\n"
        << "         RV32I REGISTER STATE\n"
        << "========================================\n";


    for (std::size_t i = 0;
         i < NUM_REGISTERS;
         ++i) {

        std::cout
            << "x"
            << std::setw(2)
            << std::setfill(' ')
            << i
            << " = 0x"
            << std::hex
            << std::setw(8)
            << std::setfill('0')
            << getRegister(
                   static_cast<uint8_t>(i)
               )
            << std::dec
            << std::setfill(' ')
            << '\n';
    }


    std::cout
        << "========================================\n"
        << "PC           = 0x"
        << std::hex
        << std::setw(8)
        << std::setfill('0')
        << pc
        << std::dec
        << std::setfill(' ')
        << '\n'
        << "Instructions = "
        << instructionCount
        << '\n'
        << "========================================\n";
}
const CommitInfo& CPU::getLastCommit() const
{
    return lastCommit;
}