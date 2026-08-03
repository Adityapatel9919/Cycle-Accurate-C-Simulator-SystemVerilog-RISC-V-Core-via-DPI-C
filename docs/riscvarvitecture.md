# 03. RISC-V Architecture Implemented

## 3.1 ISA Base

The processor implements a subset of the **RV32I base integer instruction set**: 32-bit instructions, 32-bit registers, 32 general-purpose registers with `x0` hardwired to zero. There is no support for the M, A, F, D, or C extensions, and no privileged architecture (CSRs, traps, interrupts).

This subset is identical between the SystemVerilog RTL (`rtl/decoder/control_unit.sv`) and the C++ golden model (`cpp_model/include/instruction.h`, `cpp_model/src/decoder.cpp`) — this was confirmed directly by inspecting both decoders side by side during this documentation effort.

## 3.2 Supported Instructions

| Format | Instructions | Opcode (binary) | Count |
|---|---|---|---|
| R-Type | `ADD SUB SLL SLT SLTU XOR SRL SRA OR AND` | `0110011` | 10 |
| I-Type (ALU) | `ADDI SLTI SLTIU XORI ORI ANDI SLLI SRLI SRAI` | `0010011` | 9 |
| I-Type (Load) | `LW` | `0000011` | 1 |
| S-Type (Store) | `SW` | `0100011` | 1 |
| B-Type (Branch) | `BEQ BNE BLT BGE BLTU BGEU` | `1100011` | 6 |
| J-Type | `JAL` | `1101111` | 1 |
| I-Type (Jump) | `JALR` | `1100111` | 1 |
| U-Type | `LUI` | `0110111` | 1 |
| U-Type | `AUIPC` | `0010111` | 1 |
| **Total** | | | **31** |

Note: the LOAD opcode (`0000011`) and STORE opcode (`0100011`) architecturally cover `LB/LH/LW/LBU/LHU` and `SB/SH/SW` respectively. In this implementation, `control_unit.sv` does not branch on `funct3` for these opcodes, and `data_memory.sv` always performs a full 32-bit access — so only word-aligned `LW`/`SW` behave correctly. This is documented in full in [19_Limitations.md](19_Limitations.md) and [11_Memory_System.md](11_Memory_System.md).

## 3.3 Instruction Encoding Formats

All six standard RV32I formats are decoded by `rtl/decoder/imm_gen.sv`:

| Format | Bit Layout | Used By |
|---|---|---|
| R-Type | `funct7[31:25] rs2[24:20] rs1[19:15] funct3[14:12] rd[11:7] opcode[6:0]` | ALU R-type |
| I-Type | `imm[31:20] rs1[19:15] funct3[14:12] rd[11:7] opcode[6:0]` | ALU I-type, `LW`, `JALR` |
| S-Type | `imm[31:25] rs2[24:20] rs1[19:15] funct3[14:12] imm[11:7] opcode[6:0]` | `SW` |
| B-Type | `imm[31,7] rs2[24:20] rs1[19:15] funct3[14:12] imm[11:8,30:25]... opcode[6:0]` | Branches |
| U-Type | `imm[31:12] rd[11:7] opcode[6:0]` | `LUI`, `AUIPC` |
| J-Type | `imm[31,19:12,20,30:21] rd[11:7] opcode[6:0]` | `JAL` |

### Immediate Generation (`rtl/decoder/imm_gen.sv`)

```systemverilog
// I-Type
7'b0010011, // ADDI, ANDI, ORI...
7'b0000011, // LW
7'b1100111: // JALR
begin
    imm = {{20{instr[31]}}, instr[31:20]};
end

// B-Type
7'b1100011: // BEQ, BNE
begin
    imm = {{19{instr[31]}},
           instr[31],
           instr[7],
           instr[30:25],
           instr[11:8],
           1'b0};
end
```

This is a single combinational block driven purely by `opcode` (not `funct3`), because within RV32I the immediate encoding is determined entirely by instruction format, and every instruction under a given opcode shares one format. The B-type case reconstructs the 13-bit signed branch offset from its scrambled bit positions (a property of the RV32I encoding intended to minimize hardware for sign extension and rs1/rs2 field alignment across formats) and appends the implicit `1'b0` low bit, since branch/jump targets are always 2-byte aligned at minimum.

## 3.4 Register File

- 32 general-purpose registers, each 32 bits (`rtl/regfile/regfile.sv`)
- `x0` is hardwired to zero: writes to `x0` are structurally prevented, and reads of `x0` always return zero, independent of the memory array contents.
- Two combinational read ports (`rs1_addr`/`rs1_data`, `rs2_addr`/`rs2_data`), one synchronous write port (`rd_addr`/`rd_data`/`we`), gated by `we` and by the destination register in the register-file write logic.

## 3.5 Opcode Map Reference

| Opcode (binary) | Mnemonic(s) | RTL Decode Location |
|---|---|---|
| `0110011` | R-type ALU | `control_unit.sv` case `7'b0110011` |
| `0010011` | I-type ALU | `control_unit.sv` case `7'b0010011` |
| `0000011` | `LW` | `control_unit.sv` case `7'b0000011` |
| `0100011` | `SW` | `control_unit.sv` case `7'b0100011` |
| `1100011` | Branches | `control_unit.sv` case `7'b1100011` |
| `1101111` | `JAL` | `control_unit.sv` case `7'b1101111` |
| `1100111` | `JALR` | `control_unit.sv` case `7'b1100111` |
| `0110111` | `LUI` | `control_unit.sv` case `7'b0110111` |
| `0010111` | `AUIPC` | `control_unit.sv` case `7'b0010111` |
| any other | unsupported | `control_unit.sv` `default:` — all control signals held at their no-op reset values |

## 3.6 What Is Deliberately Not Implemented

This is a teaching/portfolio-scale core, not a production RV32I implementation. The following are explicitly outside the implemented ISA subset, confirmed absent from both `control_unit.sv`'s case statement and the C++ `Opcode` enum:

- CSR instructions (`CSRRW`, `CSRRS`, etc.)
- `FENCE`, `ECALL`, `EBREAK`
- Byte/half-word load and store variants
- The RV32M multiply/divide extension
- Any exception, trap, or interrupt handling

These are revisited with concrete extension suggestions in [20_Future_Work.md](20_Future_Work.md).