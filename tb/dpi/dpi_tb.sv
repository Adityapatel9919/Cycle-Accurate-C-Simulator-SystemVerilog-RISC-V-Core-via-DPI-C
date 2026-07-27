`timescale 1ns/1ps

module dpi_tb;

    // ============================================================
    // CLOCK / RESET
    // ============================================================

    logic clk;
    logic rst;


    // ============================================================
    // PROGRAM
    // ============================================================

    string program_file;


    // ============================================================
    // DUT COMMIT INTERFACE
    // ============================================================

    logic        commit_valid;
    logic [31:0] commit_pc;
    logic [31:0] commit_instr;

    logic        commit_reg_write;
    logic [4:0]  commit_rd;
    logic [31:0] commit_rd_value;


    // ============================================================
    // TESTBENCH STATE
    // ============================================================

    integer cycle_count;
    integer commit_count;

    integer dpi_status;
    integer reference_finished;

    localparam integer MAX_CYCLES = 1000;


    // ============================================================
    // DPI-C IMPORTS
    // ============================================================

    import "DPI-C" function int dpi_init(
        input string program_file
    );

    import "DPI-C" function int dpi_check_commit(
        input int unsigned rtl_pc,
        input int unsigned rtl_instruction,
        input int          rtl_reg_write,
        input int unsigned rtl_rd,
        input int unsigned rtl_rd_value
    );

    import "DPI-C" function int dpi_reference_finished();

    import "DPI-C" function int dpi_finish();


    // ============================================================
    // DUT
    // ============================================================

    top dut (
        .clk              (clk),
        .rst              (rst),

        .commit_valid     (commit_valid),
        .commit_pc        (commit_pc),
        .commit_instr     (commit_instr),

        .commit_reg_write (commit_reg_write),
        .commit_rd        (commit_rd),
        .commit_rd_value  (commit_rd_value)
    );


    // ============================================================
    // CLOCK GENERATION
    // ============================================================

    initial begin
        clk = 1'b0;

        forever #5 clk = ~clk;
    end


    // ============================================================
    // INITIALIZATION
    // ============================================================

    initial begin

        rst          = 1'b1;
        cycle_count  = 0;
        commit_count = 0;

        dpi_status         = 0;
        reference_finished = 0;


        // --------------------------------------------------------
        // Read program filename
        //
        // Example:
        //
        // +PROGRAM=tests/directed/alu.hex
        // --------------------------------------------------------

        if (!$value$plusargs(
                "PROGRAM=%s",
                program_file
            )) begin

            $fatal(
                1,
                "[DPI TB] Missing +PROGRAM=<file.hex>"
            );

        end


        $display("");
        $display("==================================================");
        $display("       RV32I DPI LOCKSTEP VERIFICATION");
        $display("==================================================");
        $display("");

        $display(
            "[DPI TB] Program: %s",
            program_file
        );


        // --------------------------------------------------------
        // Initialize C++ golden model
        // --------------------------------------------------------

        dpi_status = dpi_init(program_file);

        if (dpi_status == 0) begin

            $fatal(
                1,
                "[DPI TB] Failed to initialize C++ golden model"
            );

        end


        // --------------------------------------------------------
        // Hold reset
        // --------------------------------------------------------

        repeat (5) @(posedge clk);

        rst = 1'b0;

        $display("[DPI TB] Reset released");
        $display("");

    end


    // ============================================================
    // CYCLE COUNTER / TIMEOUT
    // ============================================================

    always @(posedge clk) begin

        if (rst) begin

            cycle_count <= 0;

        end
        else begin

            cycle_count <= cycle_count + 1;


            // ----------------------------------------------------
            // Safety timeout
            //
            // Prevents malformed programs or control-flow bugs
            // from running the simulation forever.
            // ----------------------------------------------------

            if (cycle_count >= MAX_CYCLES) begin

                $fatal(
                    1,
                    "[DPI TB] TIMEOUT after %0d cycles",
                    cycle_count
                );

            end

        end

    end


    // ============================================================
    // DPI LOCKSTEP CHECKER
    // ============================================================

    always @(posedge clk) begin

        if (!rst && commit_valid) begin

            commit_count = commit_count + 1;


            // ----------------------------------------------------
            // Compare this RTL retirement against exactly one
            // architectural step of the C++ golden model.
            // ----------------------------------------------------

            dpi_status = dpi_check_commit(
                commit_pc,
                commit_instr,
                commit_reg_write,
                {27'b0, commit_rd},
                commit_rd_value
            );


            // ----------------------------------------------------
            // Stop immediately on first architectural mismatch.
            // ----------------------------------------------------

            if (dpi_status == 0) begin

                $display("");
                $display(
                    "[DPI TB] Lockstep failure at commit %0d",
                    commit_count
                );

                $fatal(
                    1,
                    "[DPI TB] RTL / C++ architectural mismatch"
                );

            end


            // ----------------------------------------------------
            // Check whether the C++ architectural model has now
            // reached the end of the loaded program.
            // ----------------------------------------------------

            reference_finished =
                dpi_reference_finished();


            if (reference_finished != 0) begin

                // ------------------------------------------------
                // Final consistency check
                // ------------------------------------------------

                dpi_status = dpi_finish();


                if (dpi_status == 0) begin

                    $fatal(
                        1,
                        "[DPI TB] Golden model final check failed"
                    );

                end


                // ------------------------------------------------
                // Successful lockstep completion
                // ------------------------------------------------

                $display("");
                $display("==================================================");
                $display("              DPI TEST PASSED");
                $display("==================================================");
                $display(
                    "Cycles  : %0d",
                    cycle_count
                );
                $display(
                    "Commits : %0d",
                    commit_count
                );
                $display("==================================================");
                $display("");

                $finish;

            end

        end

    end

endmodule