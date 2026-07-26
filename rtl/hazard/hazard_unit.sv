module hazard_unit (
    // Instruction currently in EX stage
    input  logic       id_ex_mem_read,
    input  logic [4:0] id_ex_rd,

    // Instruction currently in ID stage
    input  logic [4:0] if_id_rs1,
    input  logic [4:0] if_id_rs2,

    // Does the ID-stage instruction actually use these operands?
    input  logic       if_id_uses_rs1,
    input  logic       if_id_uses_rs2,

    // Pipeline control
    output logic       pc_write,
    output logic       if_id_write,
    output logic       id_ex_flush
);

    logic load_use_hazard;

    always_comb begin

        // --------------------------------------------------------
        // Detect load-use RAW hazard
        // --------------------------------------------------------

        load_use_hazard =
            id_ex_mem_read &&
            (id_ex_rd != 5'd0) &&
            (
                (if_id_uses_rs1 && (id_ex_rd == if_id_rs1)) ||
                (if_id_uses_rs2 && (id_ex_rd == if_id_rs2))
            );

        // --------------------------------------------------------
        // Default: pipeline advances normally
        // --------------------------------------------------------

        pc_write    = 1'b1;
        if_id_write = 1'b1;
        id_ex_flush = 1'b0;

        // --------------------------------------------------------
        // Hazard: freeze IF/ID and insert bubble into EX
        // --------------------------------------------------------

        if (load_use_hazard) begin
            pc_write    = 1'b0;
            if_id_write = 1'b0;
            id_ex_flush = 1'b1;
        end

    end

endmodule