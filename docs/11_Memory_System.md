# 11. Memory System

## 11.1 Two Independent Memories

This design uses a classic Harvard-style split: separate instruction and data memories, each a standalone module with no shared port or arbitration logic. Both are word-addressable, 1024-word (`MEM_DEPTH = 1024`) arrays, giving a 4 KB (0x000–0xFFC) addressable range for each.

## 11.2 Instruction Memory (`rtl/memory/instruction_memory.sv`)

### Interface

```systemverilog
module instruction_memory #(
    parameter MEM_DEPTH = 1024
)(
    input  logic [31:0] addr,
    output logic [31:0] instruction
);
```

Purely combinational read, no clock — this reflects the fact that in this design the IF stage reads the instruction memory asynchronously in the same cycle as the PC updates, rather than modeling a synchronous-read instruction ROM/cache.

### Initialization and Loading

```systemverilog
initial begin
    for (i = 0; i < MEM_DEPTH; i = i + 1) begin
        memory[i] = 32'h00000013;
    end

    if (!$value$plusargs("PROGRAM=%s", program_file)) begin
        program_file = "program.hex";
    end

    $display("Loading program: %s", program_file);
    $readmemh(program_file, memory);
end
```

Two details matter here:

1. **Every one of the 1024 words is pre-filled with the RV32I NOP encoding (`0x00000013`)**, not left as `X` (unknown) or zero, *before* `$readmemh` loads the actual program on top of it. This means any address beyond the loaded program — including the very next fetch after a small program's last instruction — reads back as a harmless NOP rather than an uninitialized or all-zero (potentially invalid-opcode) value. This is the RTL-side half of the convention discussed in [07_Pipeline_Registers.md §7.2](07_Pipeline_Registers.md): both pipeline bubbles and "off the end of the program" memory reads resolve to the same NOP encoding in this design.
2. **The program filename is supplied at simulation runtime** via `+PROGRAM=<path>` (a Verilog `$value$plusargs` command-line argument), defaulting to `program.hex` if omitted. Every test script in `scripts/` passes this argument explicitly (e.g. `+PROGRAM=tests/directed/alu.hex`), so the `program.hex` default is never actually exercised by the regression suite — this is the same stray `program.hex` file noted in [02_Repository_Architecture.md §2.9](02_Repository_Architecture.md).

### Fetch Logic

```systemverilog
always @(*) begin
    if (addr[31:2] < MEM_DEPTH)
        instruction = memory[addr[31:2]];
    else
        instruction = 32'h00000013;
end
```

`addr[31:2]` divides the byte address by 4 to index the word array (`addr >> 2`), and any address beyond `MEM_DEPTH` words also safely returns a NOP rather than an out-of-range access. Since every RV32I instruction is exactly 4 bytes, `addr[1:0]` (the low two bits) is never examined for indexing — it is only checked for alignment by `pipeline_assertions.sv`'s PC-alignment assertion (see [15_Testing.md](15_Testing.md)).

## 11.3 Data Memory (`rtl/memory/data_memory.sv`)

### Interface

```systemverilog
module data_memory #(
    parameter MEM_DEPTH = 1024
)(
    input  logic        clk,
    input  logic        mem_read,
    input  logic        mem_write,
    input  logic [31:0] addr,
    input  logic [31:0] write_data,
    output logic [31:0] read_data
);
```

### Read

```systemverilog
always_comb begin
    if (mem_read && (addr[31:2] < MEM_DEPTH))
        read_data = mem[addr[31:2]];
    else
        read_data = 32'b0;
end
```

Combinational read, gated by `mem_read` — when `mem_read` is deasserted (i.e., this is not a load), `read_data` is forced to zero rather than reflecting whatever the address happens to index; this avoids any accidental dependency on stale/undriven data downstream.

### Write

```systemverilog
always_ff @(posedge clk) begin
    if (mem_write && (addr[31:2] < MEM_DEPTH))
        mem[addr[31:2]] <= write_data;
end
```

A single synchronous write port, gated by `mem_write` and the same bounds check as the read path. There is no separate byte-enable/write-strobe input — every write updates the entire 32-bit word at the addressed location, which is consistent with the fact that only `SW` is functionally supported (§11.4).

## 11.4 Word-Only Access — the Key Limitation

Both the RTL and C++ decoders recognize the LOAD opcode (`0000011`) and STORE opcode (`0100011`) as covering the full RV32I set — `LB`, `LH`, `LW`, `LBU`, `LHU` and `SB`, `SH`, `SW` respectively, distinguished architecturally by `funct3`. In this implementation, that distinction is not carried through to the datapath:

- `control_unit.sv` asserts `mem_read`/`mem_write` based on opcode alone; it never inspects `funct3` for LOAD/STORE (§5.4).
- `data_memory.sv` has no access-width input at all — every read and every write operates on a full 32-bit word, unconditionally.
- On the C++ side, `Decoder::decodeLoad`/`decodeStore` in `cpp_model/src/decoder.cpp` *do* correctly distinguish `LB/LH/LW/LBU/LHU` and `SB/SH/SW` by `funct3`, and the decoder marks all of them `valid` — but `CPU::executeInstruction` in `cpp_model/src/cpu.cpp` only implements `case Operation::LW` and `case Operation::SW`; every other load/store operation falls to the `default:` case, prints `"Unsupported decoded operation"`, and returns `false`.

The practical consequence: **this processor only correctly executes word-aligned `LW`/`SW`.** Any program using `LB`, `LH`, `LBU`, `LHU`, `SB`, or `SH` will either behave incorrectly (RTL side — silently treated identically to `LW`/`SW` since `control_unit` doesn't distinguish them) or halt execution with an error (C++ side — `executeInstruction` explicitly rejects them). This asymmetry between "silently wrong" (RTL) and "explicitly rejected" (C++) is itself worth being aware of: it means differential verification would *not* automatically catch a byte/half-word load/store bug through a graceful mismatch — the C++ model would simply stop executing, and `run_differential.sh` would report a C++ reference-model failure rather than a commit mismatch. This limitation is not incidental — none of the ten directed test programs exercise anything but `LW`/`SW`, so it has not surfaced as a regression failure.

## 11.5 Address Calculation

For both loads and stores, the effective address is computed identically: `rs1 + immediate`, via the shared ALU (§6.3), using the I-type immediate for `LW` and the S-type immediate for `SW` (§3.3). This is standard — RISC-V loads and stores always compute their address the same way, differing only in immediate encoding (I-type vs. S-type) because store instructions need to encode both a source register (`rs2`, the data) and a destination register (`rs1`, part of the address) plus an immediate, which does not fit the I-type layout.

## 11.6 Memory Map Summary

| Region | Size | Access | Notes |
|---|---|---|---|
| Instruction memory | 1024 words (4 KB), byte addresses `0x000`–`0xFFC` | Read-only from the pipeline's perspective (loaded once via `$readmemh` at simulation start) | Pre-filled entirely with NOP before program load |
| Data memory | 1024 words (4 KB), byte addresses `0x000`–`0xFFC` | Read/write via `LW`/`SW` | Zero-initialized (SystemVerilog default for unpacked arrays without explicit init is actually `X` in real hardware/synthesis semantics, but Icarus Verilog simulation defaults uninitialized `logic` arrays to `X` as well — no explicit reset/zero-fill block exists for `mem` in `data_memory.sv`, unlike `instruction_memory.sv`'s explicit NOP-fill loop) |

The absence of an explicit initialization loop for `data_memory.sv`'s `mem` array (unlike the instruction memory's NOP-fill loop) means that reading a data address before it has ever been written to would return simulator-dependent `X`/unknown bits in RTL simulation, rather than a defined zero value. None of the current directed tests read data memory before writing it, so this has not been observed as a functional issue, but it is a real asymmetry between the two memories worth flagging (see [19_Limitations.md](19_Limitations.md)).

## 11.7 The C++ Memory Model — Byte-Addressable, Not Word-Addressable

`cpp_model/include/memory.h`/`memory.cpp` model memory very differently at the storage level, even though the *architectural* behavior (word-only load/store) ends up matching:

```cpp
std::vector<uint8_t> data;
```

The C++ `Memory` class is a flat byte array (default size 1 MB — far larger than the RTL's 4 KB, since the C++ model has no reason to mirror the RTL's small simulation-scale memory footprint), with `read8`/`read16`/`read32`/`write8`/`write16`/`write32` all implemented as genuine byte/half/word accessors with correct little-endian packing:

```cpp
uint32_t Memory::read32(uint32_t address) const
{
    checkAddress(address, 4);
    uint32_t value = 0;
    value |= static_cast<uint32_t>(data[address]);
    value |= static_cast<uint32_t>(data[address + 1]) << 8;
    value |= static_cast<uint32_t>(data[address + 2]) << 16;
    value |= static_cast<uint32_t>(data[address + 3]) << 24;
    return value;
}
```

This means the C++ *memory* is fully capable of byte/half-word access — the limitation documented in §11.4 is entirely in `CPU::executeInstruction`'s missing `switch` cases, not in the underlying `Memory` class. If `LB`/`LH`/etc. support were added to this project in the future ([20_Future_Work.md](20_Future_Work.md)), the C++ memory layer would need no changes at all; only `executeInstruction` and the RTL's `control_unit.sv`/`data_memory.sv` would need to change.

The C++ model's memory is **zero-initialized by construction** (`std::vector<uint8_t> data(size, 0)` in the `Memory` constructor), unlike the RTL data memory's undefined-until-written behavior noted in §11.6 — another asymmetry that has not surfaced as a problem only because no current test relies on reading unwritten data memory.

## 11.8 Program Bounds Tracking (C++ only)

The C++ `Memory` class additionally tracks the address range of the currently loaded program:

```cpp
bool Memory::isProgramAddress(uint32_t address) const
{
    return programWordCount != 0 &&
           address >= programStart &&
           address < programEnd;
}
```

This has no RTL equivalent — the RTL has no concept of "where the program ends," since its instruction memory is uniformly NOP-filled and simply keeps fetching NOPs forever past the end of a real program (bounded only by the testbench's fixed cycle count). The C++ model instead uses `isProgramAddress`/`isPCInProgram()` to know precisely when to *stop* executing, which is what makes natural (non-fixed-count) termination possible — this is central to how the offline differential and DPI-C verification flows work, covered in [12_CPP_Golden_Model.md](12_CPP_Golden_Model.md) and [13_Differential_Verification.md](13_Differential_Verification.md).

## 11.9 Failure Modes and Verification

| Failure Mode | Symptom | Caught By |
|---|---|---|
| Wrong address computed for a load/store | Wrong value loaded, or a store lands at the wrong location | `load_store.hex` directed test, differential verification |
| `mem_read`/`mem_write` gating wrong | A non-memory instruction accidentally reads/writes data memory, or vice versa | Differential verification (any resulting register/memory-visible corruption) |
| Data memory read before write (undefined RTL value) | RTL `X` propagates into a register, differing from the C++ model's zero-initialized read | Would surface as a differential/DPI mismatch if exercised — not currently exercised by any directed test |
| Byte/half-word load or store used in a program | RTL silently behaves as if it were `LW`/`SW`; C++ model halts with an "unsupported operation" error | Not gracefully caught — would manifest as a C++ reference-model failure in `run_differential.sh`, or a DPI-C initialization/execution failure, rather than a clean commit mismatch |

## 11.10 Related Tests

- `tests/directed/load_store.hex` — the only directed test exercising the memory system directly
- `tests/directed/load_use.hex` — exercises the load-use hazard interaction with the memory system (§8)
- `tests/directed/full_regression.hex` — likely re-exercises `LW`/`SW` within the composite program
