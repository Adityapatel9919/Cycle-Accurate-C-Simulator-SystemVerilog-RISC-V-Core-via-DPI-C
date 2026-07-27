module mem_wb (
    input logic clk,
    input logic rst,

    // ========================================================
    // COMMIT / TRACE TRACKING
    // ========================================================

    input logic        valid_in,
    input logic [31:0] pc_in,
    input logic [31:0] instr_in,

    // ========================================================
    // DATA FROM MEM STAGE
    // ========================================================

    input logic [31:0] alu_result_in,
    input logic [31:0] mem_data_in,
    input logic [31:0] pc_plus4_in,
    input logic [4:0]  rd_in,

    // ========================================================
    // WB CONTROL
    // ========================================================

    input logic       reg_write_in,
    input logic [1:0] wb_sel_in,

    // ========================================================
    // COMMIT / TRACE OUTPUT
    // ========================================================

    output logic        valid_out,
    output logic [31:0] pc_out,
    output logic [31:0] instr_out,

    // ========================================================
    // DATA TO WB STAGE
    // ========================================================

    output logic [31:0] alu_result_out,
    output logic [31:0] mem_data_out,
    output logic [31:0] pc_plus4_out,
    output logic [4:0]  rd_out,

    // ========================================================
    // WB CONTROL OUTPUT
    // ========================================================

    output logic       reg_write_out,
    output logic [1:0] wb_sel_out
);

    always_ff @(posedge clk or posedge rst) begin

        if (rst) begin

            // Commit tracking
            valid_out      <= 1'b0;
            pc_out         <= 32'b0;
            instr_out      <= 32'h00000013;

            // Data
            alu_result_out <= 32'b0;
            mem_data_out   <= 32'b0;
            pc_plus4_out   <= 32'b0;
            rd_out         <= 5'b0;

            // WB control
            reg_write_out  <= 1'b0;
            wb_sel_out     <= 2'b00;

        end
        else begin

            // Commit tracking
            valid_out      <= valid_in;
            pc_out         <= pc_in;
            instr_out      <= instr_in;

            // Data
            alu_result_out <= alu_result_in;
            mem_data_out   <= mem_data_in;
            pc_plus4_out   <= pc_plus4_in;
            rd_out         <= rd_in;

            // WB control
            reg_write_out  <= reg_write_in;
            wb_sel_out     <= wb_sel_in;

        end

    end

endmodule