`timescale 1ns/1ps

module top_tb;

    // ============================================================
    // SIGNALS
    // ============================================================

    logic clk;
    logic rst;

    integer errors;
    integer cycles;
    integer stall_count;
    integer redirect_count;

    integer test_id;
    logic        commit_valid;
    logic [31:0] commit_pc;
    logic [31:0] commit_instr;

    logic        commit_reg_write;
    logic [4:0]  commit_rd;
    logic [31:0] commit_rd_value;


    // ============================================================
    // DUT
    // ============================================================

  top dut (
    .clk              (clk),
    .rst              (rst),

    .commit_valid      (commit_valid),
    .commit_pc         (commit_pc),
    .commit_instr      (commit_instr),

    .commit_reg_write  (commit_reg_write),
    .commit_rd         (commit_rd),
    .commit_rd_value   (commit_rd_value)
);

pipeline_assertions assertions_inst (

    .clk                (clk),
    .rst                (rst),

    .pc                 (dut.pc_current),

    .x0_value           (dut.regfile_inst.regs[0]),

    .pc_write           (dut.pc_write),
    .if_id_write        (dut.if_id_write),
    .id_ex_flush        (dut.id_ex_flush),

    .control_transfer   (dut.control_transfer_ex),
    .if_id_flush        (dut.if_id_flush),

    .forward_a          (dut.forward_a),
    .forward_b          (dut.forward_b),

    .id_ex_rs1          (dut.id_ex_rs1),
    .id_ex_rs2          (dut.id_ex_rs2),

    .ex_mem_rd          (dut.ex_mem_rd),
    .ex_mem_reg_write   (dut.ex_mem_reg_write),

    .mem_wb_rd          (dut.mem_wb_rd),
    .mem_wb_reg_write   (dut.mem_wb_reg_write),

    .wb_reg_write       (dut.mem_wb_reg_write),
    .wb_rd              (dut.mem_wb_rd)

);

    // ============================================================
    // CLOCK
    // ============================================================

    initial begin
        clk = 1'b0;
        forever #5 clk = ~clk;
    end


    // ============================================================
    // WAVEFORM
    // ============================================================

    initial begin
        $dumpfile("waves/top.vcd");
        $dumpvars(0, top_tb);
    end


    // ============================================================
    // PIPELINE EVENT COUNTERS
    // ============================================================

    always @(posedge clk) begin

        if (rst) begin

            cycles         <= 0;
            stall_count    <= 0;
            redirect_count <= 0;

        end
        else begin

            cycles <= cycles + 1;

            if (!dut.pc_write)
                stall_count <= stall_count + 1;

            if (dut.control_transfer_ex)
                redirect_count <= redirect_count + 1;

        end

    end


    // ============================================================
    // REGISTER CHECK TASK
    // ============================================================

    task check_reg;

        input integer reg_num;
        input [31:0] expected;

        reg [31:0] actual;

        begin

            actual = dut.regfile_inst.regs[reg_num];

            if (actual !== expected) begin

                $display(
                    "[FAIL] x%0d expected %0d (0x%08h), got %0d (0x%08h)",
                    reg_num,
                    $signed(expected),
                    expected,
                    $signed(actual),
                    actual
                );

                errors = errors + 1;

            end
            else begin

                $display(
                    "[PASS] x%0d = %0d (0x%08h)",
                    reg_num,
                    $signed(actual),
                    actual
                );

            end

        end

    endtask


    // ============================================================
    // TEST 1
    // ALU
    // ============================================================

    task test_alu;

        begin

            $display("");
            $display("----------------------------------------");
            $display("ALU TEST");
            $display("----------------------------------------");

            check_reg(1, 32'd10);
            check_reg(2, 32'd20);
            check_reg(3, 32'd30);
            check_reg(4, 32'd20);

        end

    endtask


    // ============================================================
    // TEST 2
    // FORWARDING
    // ============================================================

    task test_forwarding;

        begin

            $display("");
            $display("----------------------------------------");
            $display("FORWARDING TEST");
            $display("----------------------------------------");

            check_reg(1, 32'd5);
            check_reg(2, 32'd10);
            check_reg(3, 32'd15);
            check_reg(4, 32'd25);
            check_reg(5, 32'd40);

        end

    endtask


    // ============================================================
    // TEST 3
    // LOAD / STORE
    // ============================================================

    task test_load_store;

        begin

            $display("");
            $display("----------------------------------------");
            $display("LOAD / STORE TEST");
            $display("----------------------------------------");

            check_reg(1, 32'd42);
            check_reg(2, 32'd42);

        end

    endtask


    // ============================================================
    // TEST 4
    // LOAD-USE HAZARD
    // ============================================================

    task test_load_use;

        begin

            $display("");
            $display("----------------------------------------");
            $display("LOAD-USE HAZARD TEST");
            $display("----------------------------------------");

            check_reg(1, 32'd42);
            check_reg(5, 32'd42);
            check_reg(6, 32'd84);

            if (stall_count < 1) begin

                $display(
                    "[FAIL] Expected load-use stall"
                );

                errors = errors + 1;

            end
            else begin

                $display(
                    "[PASS] Load-use stall detected"
                );

                $display(
                    "       Stall count = %0d",
                    stall_count
                );

            end

        end

    endtask


    // ============================================================
    // TEST 5
    // BEQ TAKEN
    // ============================================================

    task test_beq_taken;

        begin

            $display("");
            $display("----------------------------------------");
            $display("BEQ TAKEN TEST");
            $display("----------------------------------------");

            check_reg(1, 32'd10);
            check_reg(2, 32'd10);

            // Wrong-path instructions must not commit.
            check_reg(3, 32'd0);
            check_reg(4, 32'd0);

            check_reg(5, 32'd42);

            if (redirect_count < 1) begin

                $display(
                    "[FAIL] Expected BEQ redirect"
                );

                errors = errors + 1;

            end
            else begin

                $display(
                    "[PASS] BEQ redirect detected"
                );

            end

        end

    endtask


    // ============================================================
    // TEST 6
    // BEQ NOT TAKEN
    // ============================================================

    task test_beq_not_taken;

        begin

            $display("");
            $display("----------------------------------------");
            $display("BEQ NOT-TAKEN TEST");
            $display("----------------------------------------");

            check_reg(1, 32'd10);
            check_reg(2, 32'd20);
            check_reg(3, 32'd33);
            check_reg(4, 32'd44);
            check_reg(5, 32'd55);

            if (redirect_count != 0) begin

                $display(
                    "[FAIL] Unexpected redirect count = %0d",
                    redirect_count
                );

                errors = errors + 1;

            end
            else begin

                $display(
                    "[PASS] No redirect occurred"
                );

            end

        end

    endtask


    // ============================================================
    // TEST 7
    // BRANCHES
    // ============================================================

    task test_branches;

        begin

            $display("");
            $display("----------------------------------------");
            $display("BRANCH INSTRUCTION TEST");
            $display("----------------------------------------");

            check_reg(1, 32'd10);
            check_reg(2, 32'd20);

            // BNE result
            check_reg(3, 32'd3);

            // Signed comparison operands
            check_reg(4, 32'hFFFFFFFF);
            check_reg(5, 32'd1);

            // BLT / BGE results
            check_reg(6, 32'd6);
            check_reg(7, 32'd7);

            // BLTU / BGEU results
            check_reg(8, 32'd8);
            check_reg(9, 32'd9);

        end

    endtask


    // ============================================================
    // TEST 8
    // JAL
    // ============================================================

    task test_jal;

        begin

            $display("");
            $display("----------------------------------------");
            $display("JAL TEST");
            $display("----------------------------------------");

            // JAL at PC 0
            // x1 should receive PC + 4.
            check_reg(1, 32'd4);

            // Wrong-path instructions.
            check_reg(2, 32'd0);
            check_reg(3, 32'd0);

            // Target instruction.
            check_reg(4, 32'd42);

            if (redirect_count < 1) begin

                $display(
                    "[FAIL] Expected JAL redirect"
                );

                errors = errors + 1;

            end
            else begin

                $display(
                    "[PASS] JAL redirect detected"
                );

            end

        end

    endtask


    // ============================================================
    // TEST 9
    // JALR
    // ============================================================

    task test_jalr;

        begin

            $display("");
            $display("----------------------------------------");
            $display("JALR TEST");
            $display("----------------------------------------");

            // AUIPC + ADDI target
            check_reg(1, 32'd20);

            // Wrong-path instructions
            check_reg(2, 32'd0);
            check_reg(3, 32'd0);

            // Target instruction
            check_reg(4, 32'd42);

            // JALR at PC 0x08
            // link = PC + 4 = 0x0C
            check_reg(5, 32'd12);

            if (redirect_count < 1) begin

                $display(
                    "[FAIL] Expected JALR redirect"
                );

                errors = errors + 1;

            end
            else begin

                $display(
                    "[PASS] JALR redirect detected"
                );

            end

        end

    endtask


    // ============================================================
    // TEST 10
    // FULL REGRESSION
    // ============================================================

    task test_full_regression;

        begin

            $display("");
            $display("----------------------------------------");
            $display("FULL DIRECTED REGRESSION");
            $display("----------------------------------------");


            // ----------------------------------------------------
            // ALU / forwarding
            // ----------------------------------------------------

            check_reg(1,  32'd10);
            check_reg(2,  32'd20);
            check_reg(3,  32'd30);
            check_reg(4,  32'd20);


            // ----------------------------------------------------
            // Memory / load-use
            // ----------------------------------------------------

            check_reg(5,  32'd20);
            check_reg(6,  32'd40);


            // ----------------------------------------------------
            // BEQ taken
            // ----------------------------------------------------

            check_reg(7,  32'd7);
            check_reg(8,  32'd0);


            // ----------------------------------------------------
            // BEQ not taken
            // ----------------------------------------------------

            check_reg(9,  32'd9);
            check_reg(10, 32'd10);


            // ----------------------------------------------------
            // BNE
            // ----------------------------------------------------

            check_reg(11, 32'd11);


            // ----------------------------------------------------
            // Signed branches
            // ----------------------------------------------------

            check_reg(12, 32'hFFFFFFFF);
            check_reg(13, 32'd1);
            check_reg(14, 32'd14);
            check_reg(15, 32'd15);


            // ----------------------------------------------------
            // Unsigned branches
            // ----------------------------------------------------

            check_reg(16, 32'd16);
            check_reg(17, 32'd17);


            // ----------------------------------------------------
            // JAL
            // ----------------------------------------------------

            check_reg(18, 32'd18);
            check_reg(20, 32'h0000007C);


            // ----------------------------------------------------
            // JALR
            // ----------------------------------------------------

            check_reg(19, 32'h0000009C);
            check_reg(21, 32'h00000094);
            check_reg(22, 32'd22);


            // ----------------------------------------------------
            // Hazard behaviour
            // ----------------------------------------------------

            if (stall_count < 1) begin

                $display(
                    "[FAIL] Expected at least one load-use stall"
                );

                errors = errors + 1;

            end
            else begin

                $display(
                    "[PASS] Load-use stalls = %0d",
                    stall_count
                );

            end


            if (redirect_count < 1) begin

                $display(
                    "[FAIL] Expected control redirects"
                );

                errors = errors + 1;

            end
            else begin

                $display(
                    "[PASS] Control redirects = %0d",
                    redirect_count
                );

            end

        end

    endtask


    // ============================================================
    // MAIN TEST SEQUENCE
    // ============================================================

    initial begin

        errors         = 0;
        cycles         = 0;
        stall_count    = 0;
        redirect_count = 0;

        rst = 1'b1;


        // --------------------------------------------------------
        // GET NUMERIC TEST ID
        // --------------------------------------------------------

        if (!$value$plusargs("TEST_ID=%d", test_id)) begin

            $display("");
            $display("ERROR: TEST_ID was not supplied.");
            $display("");
            $display("Examples:");
            $display("");
            $display(
                "vvp sim/cpu_sim +TEST_ID=1 +PROGRAM=tests/directed/alu.hex"
            );

            $display(
                "vvp sim/cpu_sim +TEST_ID=10 +PROGRAM=tests/directed/full_regression.hex"
            );

            $display("");

            $finish;

        end


        // --------------------------------------------------------
        // TEST INFORMATION
        // --------------------------------------------------------

        $display("");
        $display("==================================================");
        $display("       RV32I 5-STAGE PIPELINE TEST");
        $display("==================================================");
        $display("TEST_ID = %0d", test_id);
        $display("");


        // --------------------------------------------------------
        // RESET
        // --------------------------------------------------------

        repeat (3)
            @(posedge clk);

        rst = 1'b0;


        // --------------------------------------------------------
        // EXECUTE
        // --------------------------------------------------------
        //
        // 100 cycles is intentionally larger than required for
        // these small directed programs.
        //
        // --------------------------------------------------------

        repeat (100)
            @(posedge clk);

        #1;


        // ========================================================
        // ARCHITECTURAL x0 CHECK
        // ========================================================

        $display("");
        $display("----------------------------------------");
        $display("ARCHITECTURAL x0 CHECK");
        $display("----------------------------------------");

        check_reg(0, 32'd0);


        // ========================================================
        // SELECT TEST
        // ========================================================

        case (test_id)

            1: begin
                test_alu;
            end

            2: begin
                test_forwarding;
            end

            3: begin
                test_load_store;
            end

            4: begin
                test_load_use;
            end

            5: begin
                test_beq_taken;
            end

            6: begin
                test_beq_not_taken;
            end

            7: begin
                test_branches;
            end

            8: begin
                test_jal;
            end

            9: begin
                test_jalr;
            end

            10: begin
                test_full_regression;
            end

            default: begin

                $display("");
                $display(
                    "[FAIL] Unknown TEST_ID = %0d",
                    test_id
                );

                errors = errors + 1;

            end

        endcase


        // ========================================================
        // PIPELINE STATISTICS
        // ========================================================

        $display("");
        $display("----------------------------------------");
        $display("PIPELINE STATISTICS");
        $display("----------------------------------------");

        $display(
            "Cycles            : %0d",
            cycles
        );

        $display(
            "Load-use stalls   : %0d",
            stall_count
        );

        $display(
            "Control redirects : %0d",
            redirect_count
        );


        // ========================================================
        // FINAL RESULT
        // ========================================================

        $display("");
        $display("==================================================");

        if (errors == 0) begin

            $display("ALL TESTS PASSED");
            $display("TEST_ID: %0d", test_id);

        end
        else begin

            $display("TEST FAILED");
            $display("TEST_ID: %0d", test_id);
            $display("ERRORS: %0d", errors);

        end

        $display("==================================================");
        $display("");

        $finish;

    end


    // ============================================================
    // TIMEOUT
    // ============================================================

    initial begin

        #5000;

        $display("");
        $display("==================================================");
        $display("ERROR: SIMULATION TIMEOUT");
        $display("==================================================");
        $display("");

        $finish;

    end
    always @(posedge clk) begin

    if (!rst && commit_valid) begin

        if (commit_reg_write) begin

            $display(
                "COMMIT PC=%08x INSTR=%08x RD=%0d VALUE=%08x",
                commit_pc,
                commit_instr,
                commit_rd,
                commit_rd_value
            );

        end
        else begin

            $display(
                "COMMIT PC=%08x INSTR=%08x RD=- VALUE=-",
                commit_pc,
                commit_instr
            );

        end

    end

end


endmodule