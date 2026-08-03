# 01. Project Overview

## 1.1 What This Project Is

This project is a from-scratch implementation of an **RV32I five-stage in-order pipelined processor**, written in SystemVerilog, paired with an independently written **cycle-accurate C++ golden reference model** of the same architecture. The two implementations are not related by code generation or shared logic — they are two separate descriptions of the same architectural behavior, deliberately kept independent so that agreement between them is meaningful evidence of correctness rather than a shared-bug artifact.

The project exists to demonstrate, end to end, the verification discipline used when bringing up a CPU core in industry: directed testing, assertion-based checking, a golden reference model, offline differential verification, and live co-simulation via DPI-C. Each of these is present in this repository and independently runnable.

## 1.2 Scope

**In scope** (implemented and verified):

- A synthesizable 5-stage RV32I pipeline: IF, ID, EX, MEM, WB
- Full base-integer ALU and I-type/R-type operations
- All six branch conditions, JAL, and JALR
- LUI and AUIPC
- Word-aligned load/store (`LW`/`SW`)
- Operand forwarding (EX/MEM and MEM/WB into EX)
- Load-use hazard detection with pipeline stall
- A same-cycle WB→ID bypass for the register file
- An architectural commit interface at the processor boundary
- A C++17 golden reference model with an equivalent commit interface
- Offline differential verification (RTL trace vs. C++ trace)
- Live DPI-C lockstep verification (C++ model driven inside the Verilator simulation)
- Ten directed regression programs and a 14-assertion concurrent checker

**Out of scope** (not implemented in either RTL or C++ model — see [19_Limitations.md](19_Limitations.md)):

- Byte/half-word loads and stores (`LB`, `LH`, `LBU`, `LHU`, `SB`, `SH` are decoded but not executed)
- CSR instructions, `FENCE`, `ECALL`, `EBREAK`
- The M-extension (multiply/divide)
- Branch prediction of any kind
- Exceptions, interrupts, and privileged modes
- Multi-issue, out-of-order execution, or caches

## 1.3 Why a Golden Model, Not Just a Testbench

A directed SystemVerilog testbench can check that specific programs produce specific expected register values, but it cannot generically check *every* instruction the processor executes without hand-writing an expected value for each one. A cycle-accurate golden model solves this differently: it independently computes what *should* have happened, and the RTL is checked against it automatically, instruction by instruction, for any program — not only the ones a human anticipated.

This project pushes that idea through three levels of increasing rigor:

1. **Directed regression** — does the RTL produce the right final register state for a fixed set of programs?
2. **Offline differential verification** — does every single committed instruction, in order, match a reference trace, for the same programs?
3. **Live DPI-C lockstep** — does every committed instruction match the reference model in real time, inside the same simulation process, with no possibility of trace post-processing masking a mismatch?

## 1.4 Intended Audience

This documentation assumes the reader is comfortable with digital design (RTL, testbenches, synthesis concepts) but does not assume prior exposure to pipelined CPU microarchitecture. Pipeline hazards, forwarding, and control-flow resolution are explained from first principles in Sections 4–10.

## 1.5 Document Map

This document is part of a 20-section documentation set. See the [README](README.md) for the full index. The recommended reading order for someone unfamiliar with the project is:

1. This overview
2. [02_Repository_Architecture.md](02_Repository_Architecture.md) — where everything lives
3. [03_RISCV_Architecture.md](03_RISCV_Architecture.md) — what the processor implements
4. [04_Five_Stage_Pipeline.md](04_Five_Stage_Pipeline.md) through [11_Memory_System.md](11_Memory_System.md) — how the RTL works
5. [12_CPP_Golden_Model.md](12_CPP_Golden_Model.md) through [15_Testing.md](15_Testing.md) — how it is verified
6. [16_Build_Guide.md](16_Build_Guide.md) through [20_Future_Work.md](20_Future_Work.md) — how to build it, debug it, and what is left to do