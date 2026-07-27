module id_ex (
    input logic clk,
    input logic rst,
    input logic flush,

    // ============================================================
    // DATA FROM ID STAGE
    // ============================================================

    input logic [31:0] pc_in,
    input  logic        valid_in,

    
    input logic [31:0] instr_in,
    input logic [31:0] pc_plus4_in,

    input logic [31:0] rs1_data_in,
    input logic [31:0] rs2_data_in,
    input logic [31:0] immediate_in,

    input logic [4:0] rs1_in,
    input logic [4:0] rs2_in,
    input logic [4:0] rd_in,

    input logic [2:0] funct3_in,
    input logic [6:0] funct7_in,

    // ============================================================
    // EX CONTROL SIGNALS
    // ============================================================

    input logic       alu_src_in,
    input logic [1:0] alu_op_in,
    input logic [1:0] alu_a_sel_in,

    // ============================================================
    // MEM CONTROL SIGNALS
    // ============================================================

    input logic mem_read_in,
    input logic mem_write_in,
    input logic branch_in,

    // ============================================================
    // CONTROL-FLOW SIGNALS
    // ============================================================

    input logic jump_in,
    input logic jalr_in,

    // ============================================================
    // WB CONTROL SIGNALS
    // ============================================================

    input logic       reg_write_in,
    input logic [1:0] wb_sel_in,

    // ============================================================
    // DATA OUTPUTS TO EX STAGE
    // ============================================================

    output logic [31:0] pc_out,
    output logic [31:0] instr_out,
    output logic        valid_out,
    output logic [31:0] pc_plus4_out,

    output logic [31:0] rs1_data_out,
    output logic [31:0] rs2_data_out,
    output logic [31:0] immediate_out,

    output logic [4:0] rs1_out,
    output logic [4:0] rs2_out,
    output logic [4:0] rd_out,

    output logic [2:0] funct3_out,
    output logic [6:0] funct7_out,

    // ============================================================
    // EX CONTROL OUTPUTS
    // ============================================================

    output logic       alu_src_out,
    output logic [1:0] alu_op_out,
    output logic [1:0] alu_a_sel_out,

    // ============================================================
    // MEM CONTROL OUTPUTS
    // ============================================================

    output logic mem_read_out,
    output logic mem_write_out,
    output logic branch_out,

    // ============================================================
    // CONTROL-FLOW OUTPUTS
    // ============================================================

    output logic jump_out,
    output logic jalr_out,

    // ============================================================
    // WB CONTROL OUTPUTS
    // ============================================================

    output logic       reg_write_out,
    output logic [1:0] wb_sel_out
);

    always_ff @(posedge clk or posedge rst) begin

        // ========================================================
        // RESET / FLUSH
        // Insert a bubble into the EX stage
        // ========================================================

        if (rst || flush) begin

            
            pc_out       <= 32'b0;
            instr_out    <= 32'h00000013; // NOP
            pc_plus4_out <= 32'b0;
            valid_out <= 1'b0;
            rs1_data_out    <= 32'b0;
            rs2_data_out    <= 32'b0;
            immediate_out   <= 32'b0;

            rs1_out         <= 5'b0;
            rs2_out         <= 5'b0;
            rd_out          <= 5'b0;

            funct3_out      <= 3'b0;
            funct7_out      <= 7'b0;

            // EX controls
            alu_src_out     <= 1'b0;
            alu_op_out      <= 2'b00;
            alu_a_sel_out   <= 2'b00;

            // MEM controls
            mem_read_out    <= 1'b0;
            mem_write_out   <= 1'b0;
            branch_out      <= 1'b0;

            // Control flow
            jump_out        <= 1'b0;
            jalr_out        <= 1'b0;

            // WB controls
            reg_write_out   <= 1'b0;
            wb_sel_out      <= 2'b00;

        end

        // ========================================================
        // NORMAL PIPELINE ADVANCE
        // ========================================================

        else begin

            valid_out       <= valid_in;

            pc_out          <= pc_in;
            instr_out       <= instr_in;
            pc_plus4_out    <= pc_plus4_in;

            rs1_data_out    <= rs1_data_in;
            rs2_data_out    <= rs2_data_in;
            immediate_out   <= immediate_in;

            rs1_out         <= rs1_in;
            rs2_out         <= rs2_in;
            rd_out          <= rd_in;

            funct3_out      <= funct3_in;
            funct7_out      <= funct7_in;

            // EX controls
            alu_src_out     <= alu_src_in;
            alu_op_out      <= alu_op_in;
            alu_a_sel_out   <= alu_a_sel_in;

            // MEM controls
            mem_read_out    <= mem_read_in;
            mem_write_out   <= mem_write_in;
            branch_out      <= branch_in;

            // Control flow
            jump_out        <= jump_in;
            jalr_out        <= jalr_in;

            // WB controls
            reg_write_out   <= reg_write_in;
            wb_sel_out      <= wb_sel_in;

        end

    end

endmodule