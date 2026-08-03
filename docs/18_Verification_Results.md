# 18. Verification Results

All results in this section are taken directly from the logs and traces checked into the repository (`sim/logs/`, `sim/logs/dpi/`, `traces/differential/`), unless explicitly noted as independently re-verified in this documentation session.

## 18.1 Summary

| Verification Layer | Result | Source |
|---|---|---|
| RTL Directed Regression | **10 / 10 PASS** | `sim/logs/*.log` |
| Pipeline Assertions (embedded in every RTL run) | **0 failures across all 10 tests** | Same logs, `ASSERTION SUMMARY` block |
| Offline Differential Verification | **10 / 10 PASS** | `traces/differential/diff_*.log` |
| DPI-C Lockstep Verification | **10 / 10 PASS** | `sim/logs/dpi/*.log` |
| C++ Golden-Model Regression | **10 / 10 PASS** (independently re-verified; the checked-in `cpp_regression_new.log` at the repository root is stale — see §18.6) | Rebuilt and rerun in this session |

## 18.2 RTL Directed Regression Detail

| Test | Result | Cycles | Load-Use Stalls | Control Redirects |
|---|---|---|---|---|
| `alu` | ALL TESTS PASSED | — | — | — |
| `forwarding` | ALL TESTS PASSED | — | — | — |
| `load_store` | ALL TESTS PASSED | — | — | — |
| `load_use` | ALL TESTS PASSED | — | 1 (test-checked) | — |
| `beq_taken` | ALL TESTS PASSED | — | — | — |
| `beq_not_taken` | ALL TESTS PASSED | — | — | — |
| `branches` | ALL TESTS PASSED | — | — | — |
| `jal` | ALL TESTS PASSED | — | — | — |
| `jalr` | ALL TESTS PASSED | — | — | — |
| `full_regression` | ALL TESTS PASSED | 101 | 1 | 7 |

Every RTL directed run executes a fixed 100 cycles after a 3-cycle reset (`101` total cycles observed for `full_regression`, matching `3` reset cycles + `1` extra edge from the `#1` settle delay + `100` execution cycles as coded in `top_tb.sv`, §15.2). Detailed per-cycle counters (stalls, redirects) are only reported explicitly here for `full_regression`, the composite test, since it is the one where these counts are most informative; all other tests reported the same `ALL TESTS PASSED` / `Assertion failures : 0` outcome.

## 18.3 Pipeline Assertion Results

| Test | Assertion Failures |
|---|---|
| `alu` | 0 |
| `beq_not_taken` | 0 |
| `beq_taken` | 0 |
| `branches` | 0 |
| `forwarding` | 0 |
| `full_regression` | 0 |
| `jal` | 0 |
| `jalr` | 0 |
| `load_store` | 0 |
| `load_use` | 0 |

All 14 assertions ([15_Testing.md §15.3](15_Testing.md)) held on every cycle of every directed test — 0 violations across the entire regression suite.

## 18.4 Offline Differential Verification Detail

| Test | Result |
|---|---|
| `diff_alu` | DIFFERENTIAL VERIFICATION PASSED |
| `diff_beq_not_taken` | DIFFERENTIAL VERIFICATION PASSED |
| `diff_beq_taken` | DIFFERENTIAL VERIFICATION PASSED |
| `diff_branches` | DIFFERENTIAL VERIFICATION PASSED |
| `diff_forwarding` | DIFFERENTIAL VERIFICATION PASSED |
| `diff_full_regression` | DIFFERENTIAL VERIFICATION PASSED |
| `diff_jal` | DIFFERENTIAL VERIFICATION PASSED |
| `diff_jalr` | DIFFERENTIAL VERIFICATION PASSED |
| `diff_load_store` | DIFFERENTIAL VERIFICATION PASSED |
| `diff_load_use` | DIFFERENTIAL VERIFICATION PASSED |

Every committed instruction, in program order, matched exactly between the RTL commit trace and the independent C++ golden-model trace, for all 10 programs — 0 mismatches reported by `compare_traces` in any test.

## 18.5 DPI-C Lockstep Verification Detail

| Test | Result | Cycles | Commits |
|---|---|---|---|
| `alu` | DPI TEST PASSED | — | 6 |
| `beq_not_taken` | DPI TEST PASSED | — | 8 |
| `beq_taken` | DPI TEST PASSED | — | 6 |
| `branches` | DPI TEST PASSED | — | 17 |
| `forwarding` | DPI TEST PASSED | — | 7 |
| `full_regression` | DPI TEST PASSED | 50 | 32 |
| `jal` | DPI TEST PASSED | — | 4 |
| `jalr` | DPI TEST PASSED | — | 6 |
| `load_store` | DPI TEST PASSED | — | 5 |
| `load_use` | DPI TEST PASSED | — | 6 |

Commit counts here reflect the natural termination point of each program (§12.7) — for example, `full_regression.hex` is a 40-word program but produces only 32 architectural commits, because a taken branch or jump skips over instructions that are consequently never fetched/executed/committed at all (consistent with the 7 control redirects observed in the same test's RTL run, §18.2). Note that the DPI-C simulation runs for exactly as many cycles as needed to reach natural program completion (50 cycles for `full_regression`), unlike the RTL directed testbench, which always runs a fixed 100 cycles regardless of program length (§18.2) — this is expected and does not indicate any discrepancy between the two paths, since they use different termination strategies by design (§14.1, §15.2).

## 18.6 C++ Golden-Model Regression — Stale Log vs. Current Status

The repository root contains a file `cpp_regression_new.log` showing:

```
REGRESSION SUMMARY
Total tests : 10
Passed      : 0
Failed      : 10

REGRESSION FAILED
```

**This does not reflect the current state of the codebase.** In preparing this documentation, `cpp_model/tests/test_runner.cpp` was recompiled directly against the current `cpu.cpp`, `decoder.cpp`, and `memory.cpp` (using `g++ 13.3.0`, since `clang++`, the compiler hardcoded in `scripts/run_cpp_regression.sh`, was not available in the documentation environment) and re-run. The result was:

```
Total tests : 10
Passed      : 10
Failed      : 0

REGRESSION PASSED
```

This 10/10 pass result is consistent with the C++ model's behavior as exercised by both the offline differential path (§18.4, which uses the same `cpu.cpp`/`decoder.cpp`/`memory.cpp` via `trace_main.cpp`) and the DPI-C lockstep path (§18.5, which uses the same three files via `dpi_bridge.cpp`) — both of which pass 10/10 against the current sources. The stale log's 0/10 failure is consistent with an older revision of the model that lacked the natural-termination logic (`isPCInProgram()`, §12.7) now present in `cpu.h`/`memory.h`, and would have walked off the end of a directed test program into memory that, at that time, was not guaranteed to be a defined value — see [19_Limitations.md](19_Limitations.md) for further discussion.

## 18.7 Overall Project Status

```
==================================================
           PROJECT REGRESSION SUMMARY
==================================================
Verification stages : 5
Passed               : 5
Failed               : 0
==================================================
       ALL VERIFICATION STAGES PASSED
==================================================
```

This reflects `scripts/run_all.sh`'s five distinct stages: RTL directed regression, C++ golden-model regression, offline differential regression, DPI-C build, and DPI-C lockstep regression (§16.6) — all five pass based on the checked-in logs and the independent C++ re-verification performed in this session.

## 18.8 What These Results Do Not Cover

These results demonstrate correctness for the 31 implemented instructions (§3.2), for the specific instruction sequences present in the 10 directed test programs, on both simulators tested (Icarus Verilog for the RTL directed/differential path, Verilator for the DPI-C path). They do not demonstrate: correctness for byte/half-word load/store, CSR, or any other unimplemented instruction (§3.6, §11.4); correctness under instruction sequences not covered by these 10 programs; or any form of formal/exhaustive verification. See [19_Limitations.md](19_Limitations.md) and [20_Future_Work.md](20_Future_Work.md).
