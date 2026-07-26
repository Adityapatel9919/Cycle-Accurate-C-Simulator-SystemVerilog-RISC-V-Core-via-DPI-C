module mem_wb (
    input logic clk,
    input logic rst,
    input logic flush,

    // ============================================================
    // DATA FROM MEM STAGE
    // ============================================================

    input logic [31:0] memory_data_in,
    input logic [31:0] alu_result_in,
    input logic [31:0] pc_plus4_in,

    input logic [4:0] rd_in,

    // ============================================================
    // WB CONTROL SIGNALS
    // ============================================================

    input logic       reg_write_in,
    input logic [1:0] wb_sel_in,

    // ============================================================
    // OUTPUTS TO WB STAGE
    // ============================================================

    output logic [31:0] memory_data_out,
    output logic [31:0] alu_result_out,
    output logic [31:0] pc_plus4_out,

    output logic [4:0] rd_out,

    output logic       reg_write_out,
    output logic [1:0] wb_sel_out
);

    always_ff @(posedge clk or posedge rst) begin

        // ========================================================
        // RESET / FLUSH
        // ========================================================

        if (rst || flush) begin

            memory_data_out <= 32'b0;
            alu_result_out  <= 32'b0;
            pc_plus4_out    <= 32'b0;

            rd_out          <= 5'b0;

            reg_write_out   <= 1'b0;
            wb_sel_out      <= 2'b00;

        end

        // ========================================================
        // NORMAL PIPELINE ADVANCE
        // ========================================================

        else begin

            memory_data_out <= memory_data_in;
            alu_result_out  <= alu_result_in;
            pc_plus4_out    <= pc_plus4_in;

            rd_out          <= rd_in;

            reg_write_out   <= reg_write_in;
            wb_sel_out      <= wb_sel_in;

        end

    end

endmodule