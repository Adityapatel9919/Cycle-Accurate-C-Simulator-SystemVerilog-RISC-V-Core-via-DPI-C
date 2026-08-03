# 15. Testing

## 15.1 The Ten Directed Test Programs

Every verification layer in this project — RTL regression, C++ regression, offline differential, and DPI-C lockstep — is built around the same set of 10 directed `.hex` programs in `tests/directed/`. Using one shared set of programs across all four layers is deliberate: it means "test N passes" has exactly one meaning across the whole project, rather than each layer having its own bespoke notion of coverage.

| Test | Focus |
|---|---|
| `alu` | R-type/I-type ALU operations |
| `forwarding` | EX/MEM and MEM/WB forwarding paths |
| `load_store` | `LW`/`SW` |
| `load_use` | Load-use hazard stall |
| `beq_taken` | `BEQ`, taken |
| `beq_not_taken` | `BEQ`, not taken |
| `branches` | All six branch conditions |
| `jal` | `JAL` |
| `jalr` | `JALR` |
| `full_regression` | Composite program covering the above |

## 15.2 RTL Directed Testbench (`tb/basic/top_tb.sv`)

### Structure

The testbench selects a test via a `+TEST_ID=<n>` command-line plusarg (1–10, matching the table above), loads the corresponding program via `+PROGRAM=<path>`, holds reset for 3 cycles, then runs for a fixed **100 cycles** — described in the source as "intentionally larger than required for these small directed programs" — before checking results:

```systemverilog
if (!$value$plusargs("TEST_ID=%d", test_id)) begin
    $display("ERROR: TEST_ID was not supplied.");
    $finish;
end

repeat (3) @(posedge clk);
rst = 1'b0;

repeat (100) @(posedge clk);
#1;

check_reg(0, 32'd0);   // architectural x0 check, every test

case (test_id)
    1: test_alu;
    2: test_forwarding;
    3: test_load_store;
    4: test_load_use;
    5: test_beq_taken;
    6: test_beq_not_taken;
    7: test_branches;
    8: test_jal;
    9: test_jalr;
    10: test_full_regression;
    default: begin
        $display("[FAIL] Unknown TEST_ID = %0d", test_id);
        errors = errors + 1;
    end
endcase
```

### Register-Value Checking

```systemverilog
task check_reg;
    input integer reg_num;
    input [31:0] expected;
    reg [31:0] actual;
    begin
        actual = dut.regfile_inst.regs[reg_num];
        if (actual !== expected) begin
            $display("[FAIL] x%0d expected %0d (0x%08h), got %0d (0x%08h)", ...);
            errors = errors + 1;
        end else begin
            $display("[PASS] x%0d = %0d (0x%08h)", ...);
        end
    end
endtask
```

Each per-test task (e.g. `test_alu`, `test_load_use`) is a fixed sequence of `check_reg` calls against hand-computed expected values for that specific program — for example:

```systemverilog
task test_load_use;
    begin
        check_reg(1, 32'd42);
        check_reg(5, 32'd42);
        check_reg(6, 32'd84);
        if (stall_count < 1) begin
            // ... hazard-specific check that at least one stall occurred
        end
    end
endtask
```

Note that `test_load_use` additionally checks `stall_count`, a cycle counter incremented whenever `!dut.pc_write` — this is a directed test doing double duty: it checks both the *architectural result* (correct final register values) and a *microarchitectural property* (a stall actually happened), which is stronger than checking final values alone, since a hazard-detection bug that happened to still produce the correct final register values (for instance, by having enough surrounding NOP-equivalent cycles to mask a missing stall) would still be caught by the stall-count check.

### Pipeline Statistics

Every run also reports:

```
Cycles            : <n>
Load-use stalls   : <n>
Control redirects : <n>
```

driven by simple counters (`cycles`, `stall_count`, `redirect_count`) incremented in a dedicated `always @(posedge clk)` block, giving a lightweight visibility into pipeline behavior beyond pass/fail.

### Result Reporting

```systemverilog
if (errors == 0) begin
    $display("ALL TESTS PASSED");
    $display("TEST_ID: %0d", test_id);
end else begin
    $display("TEST FAILED");
    $display("TEST_ID: %0d", test_id);
    $display("ERRORS: %0d", errors);
end
```

`scripts/run_regression.sh` greps each test's log for `"ALL TESTS PASSED"` to determine pass/fail (see [16_Build_Guide.md](16_Build_Guide.md) for the full script).

## 15.3 Pipeline Assertions (`tb/assertions/pipeline_assertions.sv`)

Instantiated alongside the DUT in `top_tb.sv`, wired directly to internal `dut.*` signals (e.g. `dut.pc_current`, `dut.regfile_inst.regs[0]`, `dut.forward_a`) — this module runs its 14 checks on **every cycle of every directed test**, not just a dedicated assertion-specific test, giving continuous invariant checking across the entire regression suite.

| # | Assertion | Checks |
|---|---|---|
| 1 | x0 integrity | `x0_value !== 32'b0` never holds |
| 2 | PC alignment | `pc[1:0] == 2'b00` always |
| 3 | Stall consistency | `!pc_write` implies `!if_id_write` |
| 4 | Bubble-on-stall | `!pc_write && !if_id_write` implies `id_ex_flush` |
| 5 | Flush-on-control-transfer (IF/ID) | `control_transfer` implies `if_id_flush` |
| 6 | Flush-on-control-transfer (ID/EX) | `control_transfer` implies `id_ex_flush` |
| 7 | Forward A = EX/MEM legality | `forward_a == 2'b10` implies a genuine EX/MEM producer for `rs1` |
| 8 | Forward B = EX/MEM legality | Same, for `rs2` |
| 9 | Forward A = MEM/WB legality | `forward_a == 2'b01` implies a genuine MEM/WB producer for `rs1` |
| 10 | Forward B = MEM/WB legality | Same, for `rs2` |
| 11 | EX/MEM priority (A) | If both EX/MEM and MEM/WB are valid producers for `rs1`, `forward_a` must select EX/MEM |
| 12 | EX/MEM priority (B) | Same, for `rs2` |
| 13 | Illegal forwarding encoding | `forward_a`/`forward_b` must never be `2'b11` |
| 14 | x0-write informational | A write targeting `x0` is logged (`$display`, not `$error`) as informational, not a failure, since the register file correctly suppresses it |

Every assertion increments a shared `assertion_errors` counter on violation (via `$error`, which both prints and would be caught by any tooling scanning for error-severity messages), and a `final` block prints a summary:

```systemverilog
final begin
    if (assertion_errors == 0) begin
        $display("Assertion failures : 0");
        $display("ASSERTIONS PASSED");
    end else begin
        $display("Assertion failures : %0d", assertion_errors);
        $display("ASSERTIONS FAILED");
    end
end
```

Assertions 11 and 12 are worth calling out specifically: they encode the exact forwarding-priority invariant established in [09_Forwarding.md §9.3](09_Forwarding.md) as a machine-checked property, rather than relying solely on the directed tests happening to exercise that priority ordering and a human noticing a wrong final value.

## 15.4 C++ Unit Test Suite (`cpp_model/tests/test_runner.cpp`)

Structured as an array of `TestCase` entries — name, hex file, a list of expected `(register, value)` pairs, and (retained for compatibility, though not the primary termination mechanism) an `instructionCount`:

```cpp
struct TestCase {
    std::string name;
    std::string hexFile;
    std::vector<std::pair<int, uint32_t>> expectations;
    std::size_t instructionCount;
};
```

Ten `TestCase` entries exist, one per directed test — `alu`, `forwarding`, `load_store`, `load_use`, `beq_taken`, `beq_not_taken`, `branches`, `jal`, `jalr`, `full_regression` — the identical set and naming used by the RTL and DPI-C suites (§15.1–15.2, §14.7). For each, the runner loads the `.hex` file into a fresh `Memory`/`CPU`, steps the model, and checks the listed registers against expected values via `CPU::getRegister`, printing `[PASS]`/`[FAIL]` per register and a final summary:

```
Total tests : 10
Passed      : 10
Failed      : 0

REGRESSION PASSED
```

This was independently re-confirmed in this documentation session by recompiling `test_runner.cpp` against the current `cpu.cpp`/`decoder.cpp`/`memory.cpp` and running it directly — see [19_Limitations.md](19_Limitations.md) regarding the stale `cpp_regression_new.log` checked into the repository root, which reflects an older, now-superseded version of this test harness.

## 15.5 Test Coverage Matrix

| Test | RTL Directed | C++ Unit Test | Offline Differential | DPI-C Lockstep |
|---|---|---|---|---|
| `alu` | ✓ | ✓ | ✓ | ✓ |
| `forwarding` | ✓ | ✓ | ✓ | ✓ |
| `load_store` | ✓ | ✓ | ✓ | ✓ |
| `load_use` | ✓ | ✓ | ✓ | ✓ |
| `beq_taken` | ✓ | ✓ | ✓ | ✓ |
| `beq_not_taken` | ✓ | ✓ | ✓ | ✓ |
| `branches` | ✓ | ✓ | ✓ | ✓ |
| `jal` | ✓ | ✓ | ✓ | ✓ |
| `jalr` | ✓ | ✓ | ✓ | ✓ |
| `full_regression` | ✓ | ✓ | ✓ | ✓ |

All 10 programs are exercised identically by all four verification layers — there is no test present in one layer but absent from another.

## 15.6 What Is Directed-Only (No Constrained-Random or Formal Layer)

All testing in this project is **directed**: every one of the 10 programs was hand-written to exercise a specific, named feature. There is no constrained-random instruction generator, no formal/model-checking layer, and no code-coverage or functional-coverage collection configured in any of the build scripts. This is appropriate for a project of this scope, but it does mean that correctness has only been demonstrated for the instruction sequences these 10 programs contain, not exhaustively across the full state space the pipeline could reach — see [20_Future_Work.md](20_Future_Work.md) for concrete suggestions in this direction.

## 15.7 Related Files

- `tb/basic/top_tb.sv` — directed RTL testbench
- `tb/assertions/pipeline_assertions.sv` — 14 concurrent assertions
- `cpp_model/tests/test_runner.cpp` — C++ unit test suite
- `tests/directed/*.hex` — the 10 shared test programs
- `scripts/run_regression.sh`, `scripts/run_cpp_regression.sh` — orchestration for the two RTL/C++-local layers (offline differential and DPI-C lockstep are covered in Sections 13–14)
