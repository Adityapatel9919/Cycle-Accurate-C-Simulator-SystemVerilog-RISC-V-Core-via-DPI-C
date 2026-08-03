# 16. Build Guide

## 16.1 Prerequisites

| Tool | Used For | Verified In This Documentation Effort |
|---|---|---|
| [Icarus Verilog](http://iverilog.icarus.com/) (`iverilog`, `vvp`), `-g2012` support | RTL directed regression (§16.2) | Not installed in the environment used to prepare this documentation; commands below are taken directly from `scripts/run_regression.sh` and were not re-executed here |
| [Verilator](https://www.veripool.org/verilator/) 5.x, `--timing` support | DPI-C lockstep build/regression (§16.4) | Not installed in the environment used to prepare this documentation; commands below are taken directly from `scripts/build_dpi.sh` |
| A C++17 compiler | C++ golden model, offline differential tooling | `g++ 13.3.0` was used successfully in this session as a substitute for the `clang++` hardcoded in `scripts/run_cpp_regression.sh` — both compiled the model cleanly with no source changes required |
| `bash` | All orchestration scripts in `scripts/` | Available |

This distinction matters for anyone reproducing these results: the RTL-based regression counts quoted in this documentation set ([18_Verification_Results.md](18_Verification_Results.md)) come from the logs checked into the repository (`sim/logs/`, `sim/logs/dpi/`, `traces/differential/`), not from re-running Icarus Verilog/Verilator in this session. The C++-only regression, by contrast, was independently rebuilt and re-run here and confirmed to match the checked-in differential/DPI results (see [19_Limitations.md](19_Limitations.md) for why this matters).

## 16.2 RTL Directed Regression

### Manual Build

```bash
iverilog -g2012 -Wall \
    -o sim/cpu_sim \
    rtl/alu/alu.sv \
    rtl/regfile/regfile.sv \
    rtl/decoder/imm_gen.sv \
    rtl/decoder/control_unit.sv \
    rtl/decoder/alu_control.sv \
    rtl/core/pc.sv \
    rtl/core/branch_unit.sv \
    rtl/memory/instruction_memory.sv \
    rtl/memory/data_memory.sv \
    rtl/pipeline/if_id.sv \
    rtl/pipeline/id_ex.sv \
    rtl/pipeline/ex_mem.sv \
    rtl/pipeline/mem_wb.sv \
    rtl/hazard/forwarding_unit.sv \
    rtl/hazard/hazard_unit.sv \
    rtl/core/top.sv \
    tb/assertions/pipeline_assertions.sv \
    tb/basic/top_tb.sv
```

### Manual Run (One Test)

```bash
vvp sim/cpu_sim +TEST_ID=1 +PROGRAM=tests/directed/alu.hex
```

`TEST_ID` selects which set of `check_reg` expectations `top_tb.sv` applies (§15.2); `PROGRAM` selects which `.hex` file `instruction_memory.sv` loads via `$readmemh`. Both must correspond to the same logical test (see the `TESTS` array in `scripts/run_regression.sh` for the canonical `TEST_ID:name` pairing) or the register checks will fail against the wrong program.

### Scripted (Recommended)

```bash
./scripts/run_regression.sh
```

Builds once, then runs all 10 directed tests in sequence, writing one log per test to `sim/logs/<name>.log` and a waveform dump to `waves/top.vcd`. Determines pass/fail per test by checking each log for the literal string `ALL TESTS PASSED`.

## 16.3 C++ Golden-Model Regression

### Manual Build

```bash
g++ -std=c++17 -Wall -Wextra \
    -Icpp_model/include \
    cpp_model/src/cpu.cpp \
    cpp_model/src/decoder.cpp \
    cpp_model/src/memory.cpp \
    cpp_model/tests/test_runner.cpp \
    -o cpp_model/build/cpp_regression
```

(`scripts/run_cpp_regression.sh` invokes `clang++` instead of `g++` — both compile this codebase without modification, since it uses no compiler-specific extensions.)

### Manual Run

```bash
cpp_model/build/cpp_regression
```

### Scripted (Recommended)

```bash
./scripts/run_cpp_regression.sh
```

## 16.4 Offline Differential Verification

This requires both the RTL simulation binary (§16.2) and the C++ trace tool and comparator to be built first:

```bash
g++ -std=c++17 -Icpp_model/include \
    cpp_model/src/cpu.cpp cpp_model/src/decoder.cpp cpp_model/src/memory.cpp \
    cpp_model/src/trace_main.cpp \
    -o cpp_model/build/trace_model

g++ -std=c++17 -Icpp_model/include \
    cpp_model/include/trace_parser.h cpp_model/src/trace_parser.cpp \
    cpp_model/tools/compare_traces.cpp \
    -o cpp_model/build/compare_traces
```

Then:

```bash
./scripts/run_differential.sh
```

This script expects `sim/cpu_sim`, `cpp_model/build/trace_model`, and `cpp_model/build/compare_traces` to already exist (it checks for all three and exits with an error naming whichever is missing) — it does not build any of them itself. For each of the 10 tests it: runs the RTL simulation into `traces/differential/rtl_<name>.log`, runs the C++ trace tool into `traces/differential/cpp_<name>.log`, counts the C++ model's `COMMIT` lines, and runs `compare_traces` against exactly that many commits from both logs, writing the result to `traces/differential/diff_<name>.log`.

## 16.5 DPI-C Lockstep Build and Regression

### Build

```bash
./scripts/build_dpi.sh
```

Internally runs:

```bash
verilator \
    --binary --timing --sv \
    --top-module dpi_tb \
    --Mdir sim/dpi_build/obj_dir \
    -Wall -Wno-fatal \
    -Irtl/core -Irtl/pipeline -Irtl/decoder -Irtl/alu -Irtl/regfile -Irtl/hazard -Irtl/memory \
    -CFLAGS "-std=c++17 -I$(pwd)/cpp_model/include" \
    rtl/core/top.sv rtl/core/pc.sv rtl/core/branch_unit.sv \
    rtl/pipeline/if_id.sv rtl/pipeline/id_ex.sv rtl/pipeline/ex_mem.sv rtl/pipeline/mem_wb.sv \
    rtl/decoder/control_unit.sv rtl/decoder/alu_control.sv rtl/decoder/imm_gen.sv \
    rtl/alu/alu.sv rtl/regfile/regfile.sv \
    rtl/hazard/hazard_unit.sv rtl/hazard/forwarding_unit.sv \
    rtl/memory/instruction_memory.sv rtl/memory/data_memory.sv \
    tb/dpi/dpi_tb.sv \
    cpp_model/src/cpu.cpp cpp_model/src/decoder.cpp cpp_model/src/memory.cpp \
    cpp_model/dpi/dpi_bridge.cpp
```

Produces `sim/dpi_build/obj_dir/Vdpi_tb`.

### Manual Run (One Test)

```bash
sim/dpi_build/obj_dir/Vdpi_tb +PROGRAM=tests/directed/alu.hex
```

### Scripted Regression

```bash
./scripts/run_dpi_regression.sh
```

Runs all 10 tests through the built binary, logging to `sim/logs/dpi/<name>.log`, and determines pass/fail by checking the process exit status and the presence of `DPI LOCKSTEP VERIFICATION PASSED` in the log.

## 16.6 Full Project Verification

```bash
./scripts/run_all.sh
```

Runs all **five** stages in sequence via a shared `run_stage` helper: RTL directed regression, C++ golden-model regression, offline differential regression, DPI-C build, and DPI-C lockstep regression — and prints a final summary counting all five as independent stages (`Verification stages : 5`), stopping to report which named stages failed, if any, rather than halting at the first failure.

## 16.7 Output Locations Summary

| Layer | Binary/Artifact | Logs |
|---|---|---|
| RTL directed regression | `sim/cpu_sim` | `sim/logs/*.log` |
| C++ golden-model regression | `cpp_model/build/cpp_regression` | stdout only (not redirected to a file by the script) |
| Offline differential | `cpp_model/build/trace_model`, `cpp_model/build/compare_traces` | `traces/differential/{rtl,cpp,diff}_*.log` |
| DPI-C lockstep | `sim/dpi_build/obj_dir/Vdpi_tb` | `sim/logs/dpi/*.log` |

## 16.8 Rebuilding from a Clean Checkout

```bash
git clone <repository-url>
cd Riscvprocessor
chmod +x scripts/*.sh
./scripts/run_all.sh
```

`run_all.sh` creates every output directory it needs (`sim/`, `sim/logs/`, `waves/`, `cpp_model/build/`, `traces/differential/`, `sim/dpi_build/`) via the individual stage scripts, so no manual directory setup is required beyond having the prerequisite tools in `PATH`.
