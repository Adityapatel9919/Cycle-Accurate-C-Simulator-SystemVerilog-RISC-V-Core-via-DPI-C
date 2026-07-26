module forwarding_unit (
    // Source registers of instruction currently in EX stage
    input  logic [4:0] id_ex_rs1,
    input  logic [4:0] id_ex_rs2,

    // Destination register of instruction in MEM stage
    input  logic [4:0] ex_mem_rd,
    input  logic       ex_mem_reg_write,

    // Destination register of instruction in WB stage
    input  logic [4:0] mem_wb_rd,
    input  logic       mem_wb_reg_write,

    // Forwarding selections
    output logic [1:0] forward_a,
    output logic [1:0] forward_b
);

    always_comb begin

        // Default: no forwarding
        forward_a = 2'b00;
        forward_b = 2'b00;

        // ========================================================
        // EX/MEM -> EX forwarding
        // Highest priority
        // ========================================================

        if (ex_mem_reg_write &&
            (ex_mem_rd != 5'd0) &&
            (ex_mem_rd == id_ex_rs1)) begin

            forward_a = 2'b10;

        end

        if (ex_mem_reg_write &&
            (ex_mem_rd != 5'd0) &&
            (ex_mem_rd == id_ex_rs2)) begin

            forward_b = 2'b10;

        end

        // ========================================================
        // MEM/WB -> EX forwarding
        // Only if EX/MEM isn't already forwarding
        // ========================================================

        if (mem_wb_reg_write &&
            (mem_wb_rd != 5'd0) &&
            !(ex_mem_reg_write &&
              (ex_mem_rd != 5'd0) &&
              (ex_mem_rd == id_ex_rs1)) &&
            (mem_wb_rd == id_ex_rs1)) begin

            forward_a = 2'b01;

        end

        if (mem_wb_reg_write &&
            (mem_wb_rd != 5'd0) &&
            !(ex_mem_reg_write &&
              (ex_mem_rd != 5'd0) &&
              (ex_mem_rd == id_ex_rs2)) &&
            (mem_wb_rd == id_ex_rs2)) begin

            forward_b = 2'b01;

        end

    end

endmodule