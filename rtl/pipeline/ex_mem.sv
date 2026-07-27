module ex_mem (
    input logic clk,
    input logic rst,
    input logic flush,

    // ============================================================
    // COMMIT / TRACE METADATA
    // ============================================================

    input logic        valid_in,
    input logic [31:0] pc_in,
    input logic [31:0] instr_in,

    // ============================================================
    // DATA FROM EX STAGE
    // ============================================================

    input logic [31:0] alu_result_in,
    input logic [31:0] rs2_data_in,
    input logic [31:0] pc_plus4_in,
    input logic [4:0]  rd_in,

    // ============================================================
    // MEM CONTROL
    // ============================================================

    input logic mem_read_in,
    input logic mem_write_in,

    // ============================================================
    // WB CONTROL
    // ============================================================

    input logic       reg_write_in,
    input logic [1:0] wb_sel_in,

    // ============================================================
    // COMMIT / TRACE METADATA OUTPUT
    // ============================================================

    output logic        valid_out,
    output logic [31:0] pc_out,
    output logic [31:0] instr_out,

    // ============================================================
    // DATA OUTPUT
    // ============================================================

    output logic [31:0] alu_result_out,
    output logic [31:0] rs2_data_out,
    output logic [31:0] pc_plus4_out,
    output logic [4:0]  rd_out,

    // ============================================================
    // MEM CONTROL OUTPUT
    // ============================================================

    output logic mem_read_out,
    output logic mem_write_out,

    // ============================================================
    // WB CONTROL OUTPUT
    // ============================================================

    output logic       reg_write_out,
    output logic [1:0] wb_sel_out
);

    always_ff @(posedge clk or posedge rst) begin

        // ========================================================
        // RESET / FLUSH
        // ========================================================

        if (rst || flush) begin

            // Trace metadata
            valid_out      <= 1'b0;
            pc_out         <= 32'b0;
            instr_out      <= 32'h00000013;

            // Data
            alu_result_out <= 32'b0;
            rs2_data_out   <= 32'b0;
            pc_plus4_out   <= 32'b0;
            rd_out         <= 5'b0;

            // MEM control
            mem_read_out   <= 1'b0;
            mem_write_out  <= 1'b0;

            // WB control
            reg_write_out  <= 1'b0;
            wb_sel_out     <= 2'b00;

        end

        // ========================================================
        // NORMAL PIPELINE ADVANCE
        // ========================================================

        else begin

            // Trace metadata
            valid_out      <= valid_in;
            pc_out         <= pc_in;
            instr_out      <= instr_in;

            // Data
            alu_result_out <= alu_result_in;
            rs2_data_out   <= rs2_data_in;
            pc_plus4_out   <= pc_plus4_in;
            rd_out         <= rd_in;

            // MEM control
            mem_read_out   <= mem_read_in;
            mem_write_out  <= mem_write_in;

            // WB control
            reg_write_out  <= reg_write_in;
            wb_sel_out     <= wb_sel_in;

        end

    end

endmodule