# 20. Future Work

This section outlines concrete, scoped extensions suggested directly by the gaps identified in [19_Limitations.md](19_Limitations.md), organized from smallest/most mechanical to largest/most architectural.

## 20.1 Repository Hygiene (Low Effort)

- **Fill in `README.md` and `cpp_model/README.md`.** This documentation set's own [README.md](README.md) can serve as a starting point for the root file; `cpp_model/README.md` could specifically document the C++ model's build/test commands for someone working in that subdirectory in isolation.
- **Populate `.github/workflows/ci.yml`.** A minimal CI workflow could run `scripts/run_all.sh` on every push/PR, given a container image with Icarus Verilog, Verilator, and a C++17 compiler pre-installed — turning the existing five-stage local verification suite into an automated gate.
- **Either populate `cpp_model/Makefile` to match what the shell scripts actually do, or remove it**, so the repository does not present two different (and currently inconsistent) build mechanisms for the same code.
- **Fix or remove `cpp_model/src/main.cpp`.** The one-line fix is changing `cpu.reset(0)` to `cpu.reset()` to match the current `CPU::reset()` signature ([19_Limitations.md §19.2.4](19_Limitations.md)); alternatively, since no verification flow uses this file, it could be removed in favor of `trace_main.cpp`, which already serves as a more actively-used standalone CLI entry point.
- **Regenerate `cpp_regression_new.log`** by re-running `scripts/run_cpp_regression.sh` against the current sources, replacing the stale 0/10 artifact with a current 10/10 result, or remove the stale file entirely.
- **Remove or document the purpose of the stray `program.hex`** at the repository root, since it is currently unreferenced by any script.

## 20.2 Extending Memory-Write Verification

Add `MEM_ADDR=`/`MEM_VALUE=`/`MEM_SIZE=` fields to `top.sv`'s commit `$display` output (the `TraceParser` and `compare_traces.cpp` already support parsing and comparing these fields, per [19_Limitations.md §19.2.7](19_Limitations.md) — only the RTL emission side needs to change). This would let offline differential verification and DPI-C lockstep verification catch store-address or store-value bugs directly at the point of the store, rather than only indirectly through a later load.

## 20.3 Byte/Half-Word Load and Store Support

This is the most impactful correctness extension, given that the C++ `Memory` class already implements genuine byte/half-word/word accessors (`read8`/`read16`/`read32`, `write8`/`write16`/`write32`, §11.7) — only the RTL datapath and the C++ `executeInstruction` dispatch need to change:

- **RTL:** `control_unit.sv` would need to pass `funct3` through (or a derived access-width signal) to `data_memory.sv`; `data_memory.sv` would need byte-enable write logic and width/sign-aware read logic (extracting and sign- or zero-extending a sub-word from the addressed 32-bit line, analogous to what the C++ `read8`/`read16` already do at the byte-array level).
- **C++:** `CPU::executeInstruction`'s `switch` would need `case Operation::LB/LH/LBU/LHU` and `case Operation::SB/SH` blocks, using the existing `memory_.read8/16`/`write8/16` methods — the decoder already produces these operations correctly (§12.3), so this is purely an execution-side gap to close.
- New directed test programs exercising each width/sign combination would be needed, following the existing pattern in `tests/directed/`.

## 20.4 CSR and Trap Support

Adding even a minimal CSR subsystem (e.g. just `mcycle`/`minstret` performance counters, or a basic `mtvec`/`mepc`/`mcause` trap mechanism for illegal-instruction and misaligned-access exceptions) would let the processor replace its current silent-no-op-on-unsupported-opcode behavior (§19.1.5) with an actual illegal-instruction trap — directly closing one of the more concerning correctness gaps identified in this documentation, since a silently-ignored instruction is a harder class of bug to detect than a rejected one.

## 20.5 M-Extension (Multiply/Divide)

`MUL`/`MULH`/`MULHSU`/`MULHU`/`DIV`/`DIVU`/`REM`/`REMU` would extend the R-type opcode space (RV32M reuses the `0110011` opcode with `funct7 = 0000001`, distinguished from the base RV32I R-type operations already decoded there) — this would require an additional multiplier/divider execution unit, likely multi-cycle given RV32I's single-cycle EX-stage assumption throughout this design, which would in turn require extending the hazard unit to stall for multi-cycle EX operations rather than just the current single load-use case (§8).

## 20.6 Branch Prediction

Even a simple static predictor (e.g. "predict backward branches taken, forward branches not taken," or a small BHT/BTB) would reduce the current fixed 2-cycle penalty on every taken branch/jump (§10) for the common case, at the cost of adding misprediction-recovery logic (which, in this design, would look structurally similar to the existing flush logic in §10.4, but would need to fire only on an actual misprediction rather than unconditionally on every taken transfer).

## 20.7 Constrained-Random and Coverage-Driven Verification

Building on the existing four-layer verification infrastructure (which already has a working golden model, commit interface, and both offline and live comparison paths — the hard infrastructure work is done), a natural next step is:

- A constrained-random RV32I instruction sequence generator, producing programs that exercise register/hazard/forwarding combinations not covered by the 10 current directed tests.
- Functional coverage collection (e.g. cross-coverage of `forward_a`/`forward_b` values against instruction type, or of stall/flush combinations) to quantify how much of the pipeline's actual state space the test suite reaches — directly addressing the directed-testing-only limitation noted in [19_Limitations.md §19.3.1](19_Limitations.md).
- Since the DPI-C lockstep infrastructure ([14_DPI_Lockstep_Verification.md](14_DPI_Lockstep_Verification.md)) already checks every commit against the golden model in real time, randomly generated programs could be checked with zero additional comparator work — only the generator itself would be new.

## 20.8 DPI-C Testbench Waveform Support

Add a `$dumpfile`/`$dumpvars` block to `tb/dpi/dpi_tb.sv`, matching `top_tb.sv`'s existing waveform dump, to close the debuggability gap noted in [19_Limitations.md §19.2.8](19_Limitations.md) — this is a small, mechanical change with a direct debugging-workflow benefit.

## 20.9 Priority Ordering

If undertaking these in sequence, the following ordering maximizes value per unit of effort:

1. Repository hygiene (§20.1) — near-zero risk, immediate clarity benefit
2. DPI-C waveform support (§20.8) — near-zero risk, direct debugging benefit
3. Memory-write commit fields (§20.2) — closes a real verification gap using infrastructure that already exists
4. Byte/half-word load/store (§20.3) — the single highest-value correctness extension, since the C++ memory layer already supports it
5. CSR/trap support (§20.4) — meaningfully improves robustness against malformed/unsupported instructions
6. Constrained-random verification (§20.7) — the highest-leverage verification investment, reusing all existing infrastructure
7. M-extension (§20.5) and branch prediction (§20.6) — larger architectural additions, best undertaken once the above are in place
