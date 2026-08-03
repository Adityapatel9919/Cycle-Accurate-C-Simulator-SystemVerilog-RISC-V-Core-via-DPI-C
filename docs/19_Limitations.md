# 19. Limitations

This section consolidates every gap, inconsistency, and unimplemented feature identified during the repository analysis and documentation process — both architectural limitations (things the processor does not do) and repository/tooling issues (things present in the codebase that do not work as apparently intended). Nothing here was assumed; each item is traceable to a specific file and, where applicable, was independently confirmed by re-compiling or re-inspecting the source in this session.

## 19.1 Architectural Limitations

### 19.1.1 Byte/Half-Word Load and Store Not Implemented

RV32I defines `LB`, `LH`, `LW`, `LBU`, `LHU` and `SB`, `SH`, `SW`, distinguished by `funct3` under the same two opcodes. In this design:

- `control_unit.sv` does not inspect `funct3` for LOAD/STORE at all — every instruction under these opcodes gets the same `mem_read`/`mem_write` treatment ([05_Control_Unit.md §5.4](05_Control_Unit.md)).
- `data_memory.sv` has no access-width input — every read/write is a full 32-bit word ([11_Memory_System.md §11.3](11_Memory_System.md)).
- The C++ decoder correctly distinguishes all six operations via `funct3` and marks them `valid`, but `CPU::executeInstruction`'s `switch` only has cases for `Operation::LW` and `Operation::SW` — every other load/store operation falls to `default:` and causes the C++ model to halt with an error ([12_CPP_Golden_Model.md §12.3](12_CPP_Golden_Model.md)).

**Impact:** only word-aligned `LW`/`SW` are functionally correct. A program using any other load/store variant would behave incorrectly on the RTL side (silently treated as if it were `LW`/`SW`) and would cause the C++ model to halt on the reference side — meaning this specific gap would not be caught by a graceful differential mismatch, but by a C++ reference-model execution failure instead.

### 19.1.2 No CSR, Privileged Architecture, or System Instructions

`FENCE`, `ECALL`, `EBREAK`, and all CSR instructions (`CSRRW`, `CSRRS`, `CSRRC`, and their immediate variants) are absent from both the RTL `control_unit.sv` opcode case statement and the C++ `Opcode` enum. There is no privileged architecture, no trap/exception handling, and no interrupt support of any kind.

### 19.1.3 No M-Extension

No multiply or divide instructions (`MUL`, `DIV`, `REM`, and variants) are implemented in either the RTL or the C++ model.

### 19.1.4 No Branch Prediction

Every branch and jump is resolved in EX with no prediction of any kind, incurring a fixed 2-cycle flush penalty on every taken control transfer ([10_Control_Hazards.md](10_Control_Hazards.md)). This is a performance characteristic, not a correctness gap, but is worth noting for anyone evaluating this design's throughput characteristics.

### 19.1.5 Unsupported Opcodes Silently No-Op in RTL, Hard-Fail in C++

`control_unit.sv`'s `default:` case produces a full set of no-op control signals for any unrecognized opcode, meaning the RTL will silently execute an unsupported instruction as if it had no architectural effect, with no error indication ([05_Control_Unit.md §5.3](05_Control_Unit.md)). The C++ model, by contrast, treats an unrecognized decode as `Operation::INVALID` and halts execution with an error ([12_CPP_Golden_Model.md §12.3](12_CPP_Golden_Model.md)). This asymmetry means:

- A program accidentally containing an unsupported instruction would fail loudly in the C++ model but continue silently (and incorrectly, from the perspective of "this should have trapped") in the RTL.
- None of the 10 directed test programs exercise this path, so it has not surfaced as a regression failure in either direction.

### 19.1.6 Data Memory Has No Defined Reset State

`data_memory.sv`'s `mem` array has no initialization loop, unlike `instruction_memory.sv`'s explicit NOP-fill ([11_Memory_System.md §11.6](11_Memory_System.md)). Reading a data address before it has ever been written would return an unspecified value in RTL simulation, whereas the C++ `Memory` class is zero-initialized by construction. No current directed test reads data memory before writing it, so this asymmetry has not been observed to cause a failure, but it is a real gap that would need addressing before this design could be considered robust against arbitrary test programs.

## 19.2 Repository and Tooling Issues

### 19.2.1 Empty README Files

`README.md` (repository root) and `cpp_model/README.md` are both 0 bytes. This documentation set's own `README.md` ([README.md](README.md)) was written from scratch based on the repository's actual contents, not derived from or replacing any pre-existing description.

### 19.2.2 Empty CI Workflow

`.github/workflows/ci.yml` is 0 bytes — despite the file's presence, no continuous integration is currently configured for this repository.

### 19.2.3 Empty C++ Makefile

`cpp_model/Makefile` is 0 bytes. All C++ building is actually done ad hoc by the shell scripts in `scripts/` (`run_cpp_regression.sh`, `build_dpi.sh`, and the manual commands in [16_Build_Guide.md](16_Build_Guide.md)), not by this Makefile.

### 19.2.4 `main.cpp` (the `rv32_ref` Tool) Does Not Compile

`cpp_model/src/main.cpp` calls `cpu.reset(0)`, but `CPU::reset()` takes no arguments in the current `cpu.h`. This was confirmed directly in this session:

```
main.cpp:140:18: error: no matching function for call to 'CPU::reset(int)'
cpu.h:28:10: note: candidate: 'void CPU::reset()'
```

This file is not referenced by any regression script (`run_cpp_regression.sh` uses `test_runner.cpp`; `run_differential.sh` uses `trace_main.cpp`), so this does not affect any of the four verification layers' results — but it is broken, uncompilable code as currently checked into the repository.

### 19.2.5 Stale C++ Regression Log at Repository Root

`cpp_regression_new.log` (repository root) shows a 0/10 failing run, apparently from a revision of the C++ model that predates the natural-termination logic (`isPCInProgram()`) now present in `cpu.h`/`memory.h`. Rebuilding `test_runner.cpp` against the current `cpu.cpp`/`decoder.cpp`/`memory.cpp` in this session produced a clean 10/10 pass, consistent with the other three verification layers ([18_Verification_Results.md §18.6](18_Verification_Results.md)). This log should not be treated as reflecting the current state of the codebase.

### 19.2.6 Stray `program.hex` at Repository Root

`program.hex` exists at the repository root and is the default filename `instruction_memory.sv` falls back to if no `+PROGRAM=` plusarg is supplied ([11_Memory_System.md §11.2](11_Memory_System.md)), but every script in `scripts/` explicitly passes `+PROGRAM=<specific test file>`, so this default path is never actually exercised by the regression suite. Its contents were not analyzed as part of this documentation effort since it plays no role in any verification flow.

### 19.2.7 RTL Commit Trace Does Not Emit Memory-Write Fields

The C++ `Commit` struct and the offline comparator (`compare_traces.cpp`) both support comparing `memWrite`/`memAddress`/`memValue`/`memWriteSize` fields, and `TraceParser` documents a trace-line format that includes `MEM_ADDR=`/`MEM_VALUE=`/`MEM_SIZE=` — but `top.sv`'s actual `$display`-based commit output only ever emits `PC=`, `INSTR=`, `RD=`, `VALUE=` ([12_CPP_Golden_Model.md §12.6](12_CPP_Golden_Model.md), [13_Differential_Verification.md §13.6](13_Differential_Verification.md)). This means store-instruction memory writes are currently verified only indirectly, through the values that subsequent loads read back, not through a direct memory-write commit comparison at the point the store executes.

### 19.2.8 No VCD Dump for the DPI-C Testbench

`tb/dpi/dpi_tb.sv` contains no `$dumpfile`/`$dumpvars` block, unlike `tb/basic/top_tb.sv`. A DPI-C lockstep failure therefore cannot currently be debugged with a waveform in the same way an RTL directed-regression failure can — the debugging guide ([17_Debugging_Guide.md §17.5](17_Debugging_Guide.md)) notes this and relies on cross-referencing against the offline differential trace for the same test as an alternative.

## 19.3 Testing Scope Limitations

### 19.3.1 Directed Testing Only

All coverage in this project comes from 10 hand-written directed programs. There is no constrained-random instruction generation, no formal/model-checking verification, and no functional or code coverage collection configured anywhere in the build scripts ([15_Testing.md §15.6](15_Testing.md)). Passing all four verification layers demonstrates correctness for these specific instruction sequences, not exhaustive correctness across the full space of programs the pipeline could execute.

### 19.3.2 Toolchain Not Independently Re-Verified for RTL/DPI Layers

The RTL directed regression, offline differential, and DPI-C lockstep results quoted throughout this documentation ([18_Verification_Results.md](18_Verification_Results.md)) are taken from the logs checked into the repository. Icarus Verilog and Verilator were not available in the environment used to prepare this documentation, so these specific results were not independently re-executed here — only the pure C++ golden-model regression was rebuilt and re-run directly ([16_Build_Guide.md §16.1](16_Build_Guide.md)).

## 19.4 Summary Table

| # | Category | Item | Impact |
|---|---|---|---|
| 19.1.1 | Architecture | Byte/half-word load/store unimplemented | Only `LW`/`SW` are correct |
| 19.1.2 | Architecture | No CSR/privileged/system instructions | No traps, interrupts, or CSR access |
| 19.1.3 | Architecture | No M-extension | No multiply/divide |
| 19.1.4 | Architecture | No branch prediction | Fixed 2-cycle penalty per taken control transfer (performance, not correctness) |
| 19.1.5 | Architecture | Unsupported opcodes: silent no-op (RTL) vs. hard fail (C++) | Asymmetric failure behavior, uncaught by current tests |
| 19.1.6 | Architecture | Data memory has no defined reset state | Unspecified RTL value on read-before-write |
| 19.2.1 | Repository | Empty READMEs | No pre-existing project description |
| 19.2.2 | Repository | Empty CI workflow | No CI currently configured |
| 19.2.3 | Repository | Empty C++ Makefile | Building done via shell scripts instead |
| 19.2.4 | Repository | `main.cpp` fails to compile | Dead code, unused by any verification flow |
| 19.2.5 | Repository | Stale `cpp_regression_new.log` | Reflects an old, since-fixed model revision |
| 19.2.6 | Repository | Stray `program.hex` | Unused default, never exercised by scripts |
| 19.2.7 | Repository | RTL trace omits memory-write fields | Store correctness verified only indirectly |
| 19.2.8 | Repository | No DPI-C testbench VCD dump | Reduced debuggability for this specific layer |
| 19.3.1 | Testing | Directed testing only | No random/formal coverage |
| 19.3.2 | Testing | RTL/DPI layers not re-executed in this session | Results taken from checked-in logs |

See [20_Future_Work.md](20_Future_Work.md) for concrete suggestions addressing several of these.
