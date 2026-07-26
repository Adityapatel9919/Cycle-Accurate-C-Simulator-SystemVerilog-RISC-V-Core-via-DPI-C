`timescale 1ns/1ps

module pipeline_assertions (
    input logic        clk,
    input logic        rst,

    // ------------------------------------------------------------
    // Architectural state
    // ------------------------------------------------------------
    input logic [31:0] pc,
    input logic [31:0] x0_value,

    // ------------------------------------------------------------
    // Hazard-unit signals
    // ------------------------------------------------------------
    input logic        pc_write,
    input logic        if_id_write,
    input logic        id_ex_flush,

    // ------------------------------------------------------------
    // Control-hazard signals
    // ------------------------------------------------------------
    input logic        control_transfer,
    input logic        if_id_flush,

    // ------------------------------------------------------------
    // Forwarding
    // ------------------------------------------------------------
    input logic [1:0]  forward_a,
    input logic [1:0]  forward_b,

    input logic [4:0]  id_ex_rs1,
    input logic [4:0]  id_ex_rs2,

    input logic [4:0]  ex_mem_rd,
    input logic        ex_mem_reg_write,

    input logic [4:0]  mem_wb_rd,
    input logic        mem_wb_reg_write,

    // ------------------------------------------------------------
    // Writeback
    // ------------------------------------------------------------
    input logic        wb_reg_write,
    input logic [4:0]  wb_rd
);

    integer assertion_errors;


    // ============================================================
    // INITIALISATION
    // ============================================================

    initial begin
        assertion_errors = 0;
    end


    // ============================================================
    // ASSERTION 1
    //
    // x0 MUST ALWAYS REMAIN ZERO
    // ============================================================

    always @(posedge clk) begin

        if (!rst) begin

            if (x0_value !== 32'b0) begin

                $error(
                    "[ASSERT FAIL] x0 modified! value = 0x%08h",
                    x0_value
                );

                assertion_errors = assertion_errors + 1;

            end

        end

    end


    // ============================================================
    // ASSERTION 2
    //
    // PC MUST ALWAYS BE 4-BYTE ALIGNED
    //
    // RV32I instructions in our core are 32-bit instructions.
    // Therefore:
    //
    // PC[1:0] == 00
    // ============================================================

    always @(posedge clk) begin

        if (!rst) begin

            if (pc[1:0] !== 2'b00) begin

                $error(
                    "[ASSERT FAIL] PC misaligned! PC = 0x%08h",
                    pc
                );

                assertion_errors = assertion_errors + 1;

            end

        end

    end


    // ============================================================
    // ASSERTION 3
    //
    // IF PC IS STALLED, IF/ID SHOULD ALSO BE STALLED
    // ============================================================

    always @(posedge clk) begin

        if (!rst) begin

            if (!pc_write && if_id_write) begin

                $error(
                    "[ASSERT FAIL] PC stalled but IF/ID still writing"
                );

                assertion_errors = assertion_errors + 1;

            end

        end

    end


    // ============================================================
    // ASSERTION 4
    //
    // LOAD-USE STYLE STALL MUST INSERT A BUBBLE INTO ID/EX
    //
    // In our pipeline:
    //
    // pc_write   = 0
    // if_id_write = 0
    //
    // means the front of the pipeline is stalled.
    //
    // ID/EX must therefore be flushed to create a bubble.
    // ============================================================

    always @(posedge clk) begin

        if (!rst) begin

            if ((!pc_write) && (!if_id_write)) begin

                if (!id_ex_flush) begin

                    $error(
                        "[ASSERT FAIL] Pipeline stalled without ID/EX bubble"
                    );

                    assertion_errors = assertion_errors + 1;

                end

            end

        end

    end


    // ============================================================
    // ASSERTION 5
    //
    // CONTROL TRANSFER MUST FLUSH IF/ID
    //
    // Applies to:
    //
    // taken branch
    // JAL
    // JALR
    // ============================================================

    always @(posedge clk) begin

        if (!rst) begin

            if (control_transfer) begin

                if (!if_id_flush) begin

                    $error(
                        "[ASSERT FAIL] Control transfer without IF/ID flush"
                    );

                    assertion_errors = assertion_errors + 1;

                end

            end

        end

    end


    // ============================================================
    // ASSERTION 6
    //
    // CONTROL TRANSFER MUST FLUSH ID/EX
    // ============================================================

    always @(posedge clk) begin

        if (!rst) begin

            if (control_transfer) begin

                if (!id_ex_flush) begin

                    $error(
                        "[ASSERT FAIL] Control transfer without ID/EX flush"
                    );

                    assertion_errors = assertion_errors + 1;

                end

            end

        end

    end


    // ============================================================
    // ASSERTION 7
    //
    // FORWARD A = 10
    //
    // Means operand A should come from EX/MEM.
    // Therefore EX/MEM must actually contain the producer.
    // ============================================================

    always @(posedge clk) begin

        if (!rst) begin

            if (forward_a == 2'b10) begin

                if (
                    !ex_mem_reg_write ||
                    (ex_mem_rd == 5'd0) ||
                    (ex_mem_rd != id_ex_rs1)
                ) begin

                    $error(
                        "[ASSERT FAIL] Invalid EX/MEM forwarding on operand A"
                    );

                    assertion_errors = assertion_errors + 1;

                end

            end

        end

    end


    // ============================================================
    // ASSERTION 8
    //
    // FORWARD B = 10
    //
    // Means operand B should come from EX/MEM.
    // ============================================================

    always @(posedge clk) begin

        if (!rst) begin

            if (forward_b == 2'b10) begin

                if (
                    !ex_mem_reg_write ||
                    (ex_mem_rd == 5'd0) ||
                    (ex_mem_rd != id_ex_rs2)
                ) begin

                    $error(
                        "[ASSERT FAIL] Invalid EX/MEM forwarding on operand B"
                    );

                    assertion_errors = assertion_errors + 1;

                end

            end

        end

    end


    // ============================================================
    // ASSERTION 9
    //
    // FORWARD A = 01
    //
    // Means operand A comes from MEM/WB.
    // ============================================================

    always @(posedge clk) begin

        if (!rst) begin

            if (forward_a == 2'b01) begin

                if (
                    !mem_wb_reg_write ||
                    (mem_wb_rd == 5'd0) ||
                    (mem_wb_rd != id_ex_rs1)
                ) begin

                    $error(
                        "[ASSERT FAIL] Invalid MEM/WB forwarding on operand A"
                    );

                    assertion_errors = assertion_errors + 1;

                end

            end

        end

    end


    // ============================================================
    // ASSERTION 10
    //
    // FORWARD B = 01
    //
    // Means operand B comes from MEM/WB.
    // ============================================================

    always @(posedge clk) begin

        if (!rst) begin

            if (forward_b == 2'b01) begin

                if (
                    !mem_wb_reg_write ||
                    (mem_wb_rd == 5'd0) ||
                    (mem_wb_rd != id_ex_rs2)
                ) begin

                    $error(
                        "[ASSERT FAIL] Invalid MEM/WB forwarding on operand B"
                    );

                    assertion_errors = assertion_errors + 1;

                end

            end

        end

    end


    // ============================================================
    // ASSERTION 11
    //
    // EX/MEM FORWARDING MUST HAVE PRIORITY OVER MEM/WB
    //
    // If both stages contain a valid producer for rs1,
    // forward_a should select EX/MEM.
    // ============================================================

    always @(posedge clk) begin

        if (!rst) begin

            if (
                ex_mem_reg_write &&
                mem_wb_reg_write &&
                (ex_mem_rd != 5'd0) &&
                (ex_mem_rd == id_ex_rs1) &&
                (mem_wb_rd == id_ex_rs1)
            ) begin

                if (forward_a !== 2'b10) begin

                    $error(
                        "[ASSERT FAIL] EX/MEM priority failure on operand A"
                    );

                    assertion_errors = assertion_errors + 1;

                end

            end

        end

    end


    // ============================================================
    // ASSERTION 12
    //
    // SAME PRIORITY CHECK FOR OPERAND B
    // ============================================================

    always @(posedge clk) begin

        if (!rst) begin

            if (
                ex_mem_reg_write &&
                mem_wb_reg_write &&
                (ex_mem_rd != 5'd0) &&
                (ex_mem_rd == id_ex_rs2) &&
                (mem_wb_rd == id_ex_rs2)
            ) begin

                if (forward_b !== 2'b10) begin

                    $error(
                        "[ASSERT FAIL] EX/MEM priority failure on operand B"
                    );

                    assertion_errors = assertion_errors + 1;

                end

            end

        end

    end


    // ============================================================
    // ASSERTION 13
    //
    // FORWARDING UNIT SHOULD NEVER GENERATE 11
    // ============================================================

    always @(posedge clk) begin

        if (!rst) begin

            if (forward_a === 2'b11) begin

                $error(
                    "[ASSERT FAIL] Illegal ForwardA value 11"
                );

                assertion_errors = assertion_errors + 1;

            end


            if (forward_b === 2'b11) begin

                $error(
                    "[ASSERT FAIL] Illegal ForwardB value 11"
                );

                assertion_errors = assertion_errors + 1;

            end

        end

    end


    // ============================================================
    // ASSERTION 14
    //
    // WRITING x0 IS ARCHITECTURALLY IGNORED.
    //
    // This isn't necessarily an RTL bug if wb_rd == 0 while
    // reg_write is asserted, because the register file can simply
    // suppress the write.
    //
    // Therefore this is informational rather than an error.
    // ============================================================

    always @(posedge clk) begin

        if (!rst) begin

            if (wb_reg_write && (wb_rd == 5'd0)) begin

                $display(
                    "[ASSERT INFO] Register write requested for x0; write must be ignored"
                );

            end

        end

    end


    // ============================================================
    // FINAL ASSERTION REPORT
    // ============================================================

    final begin

        $display("");
        $display("==================================================");
        $display("            ASSERTION SUMMARY");
        $display("==================================================");

        if (assertion_errors == 0) begin

            $display("Assertion failures : 0");
            $display("ASSERTIONS PASSED");

        end
        else begin

            $display(
                "Assertion failures : %0d",
                assertion_errors
            );

            $display("ASSERTIONS FAILED");

        end

        $display("==================================================");
        $display("");

    end

endmodule