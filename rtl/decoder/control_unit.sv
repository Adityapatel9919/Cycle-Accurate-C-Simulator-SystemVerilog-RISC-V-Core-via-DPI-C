module control_unit (
    input  logic [6:0] opcode,

    // Register usage information for hazard detection
    output logic       uses_rs1,
    output logic       uses_rs2,

    // EX controls
    output logic       alu_src,
    output logic [1:0] alu_op,
    output logic [1:0] alu_a_sel,

    // MEM controls
    output logic       mem_read,
    output logic       mem_write,
    output logic       branch,

    // Control-flow
    output logic       jump,
    output logic       jalr,

    // WB controls
    output logic       reg_write,
    output logic [1:0] wb_sel
);

    // ============================================================
    // ALU A source encoding
    // ============================================================
    //
    // 00 = rs1
    // 01 = PC
    // 10 = zero
    //
    localparam ALU_A_RS1  = 2'b00;
    localparam ALU_A_PC   = 2'b01;
    localparam ALU_A_ZERO = 2'b10;


    // ============================================================
    // Write-back source encoding
    // ============================================================
    //
    // 00 = ALU result
    // 01 = Data memory
    // 10 = PC + 4
    //
    localparam WB_ALU = 2'b00;
    localparam WB_MEM = 2'b01;
    localparam WB_PC4 = 2'b10;


    always_comb begin

        // ========================================================
        // Defaults
        // ========================================================

        uses_rs1 = 1'b0;
        uses_rs2 = 1'b0;

        alu_src   = 1'b0;
        alu_op    = 2'b00;
        alu_a_sel = ALU_A_RS1;

        mem_read  = 1'b0;
        mem_write = 1'b0;
        branch    = 1'b0;

        jump      = 1'b0;
        jalr      = 1'b0;

        reg_write = 1'b0;
        wb_sel    = WB_ALU;


        // ========================================================
        // Instruction Decode
        // ========================================================

        case (opcode)

            // ----------------------------------------------------
            // R-Type
            //
            // ADD, SUB, SLL, SLT, SLTU, XOR, SRL, SRA, OR, AND
            // ----------------------------------------------------

            7'b0110011: begin

                uses_rs1 = 1'b1;
                uses_rs2 = 1'b1;

                alu_src   = 1'b0;
                alu_op    = 2'b10;
                alu_a_sel = ALU_A_RS1;

                reg_write = 1'b1;
                wb_sel    = WB_ALU;

            end


            // ----------------------------------------------------
            // I-Type ALU
            //
            // ADDI, SLTI, SLTIU, XORI, ORI, ANDI
            // SLLI, SRLI, SRAI
            // ----------------------------------------------------

            7'b0010011: begin

                uses_rs1 = 1'b1;
                uses_rs2 = 1'b0;

                alu_src   = 1'b1;
                alu_op    = 2'b11;
                alu_a_sel = ALU_A_RS1;

                reg_write = 1'b1;
                wb_sel    = WB_ALU;

            end


            // ----------------------------------------------------
            // LOAD
            //
            // LB, LH, LW, LBU, LHU
            // ----------------------------------------------------

            7'b0000011: begin

                uses_rs1 = 1'b1;
                uses_rs2 = 1'b0;

                alu_src   = 1'b1;
                alu_op    = 2'b00;
                alu_a_sel = ALU_A_RS1;

                mem_read  = 1'b1;

                reg_write = 1'b1;
                wb_sel    = WB_MEM;

            end


            // ----------------------------------------------------
            // STORE
            //
            // SB, SH, SW
            // ----------------------------------------------------

            7'b0100011: begin

                uses_rs1 = 1'b1;
                uses_rs2 = 1'b1;

                alu_src   = 1'b1;
                alu_op    = 2'b00;
                alu_a_sel = ALU_A_RS1;

                mem_write = 1'b1;

            end


            // ----------------------------------------------------
            // BRANCH
            //
            // BEQ, BNE, BLT, BGE, BLTU, BGEU
            // ----------------------------------------------------

            7'b1100011: begin

                uses_rs1 = 1'b1;
                uses_rs2 = 1'b1;

                alu_src   = 1'b0;
                alu_op    = 2'b01;
                alu_a_sel = ALU_A_RS1;

                branch    = 1'b1;

            end


            // ----------------------------------------------------
            // JAL
            //
            // rd = PC + 4
            // PC = PC + immediate
            // ----------------------------------------------------

            7'b1101111: begin

                uses_rs1 = 1'b0;
                uses_rs2 = 1'b0;

                jump      = 1'b1;
                jalr      = 1'b0;

                reg_write = 1'b1;
                wb_sel    = WB_PC4;

            end


            // ----------------------------------------------------
            // JALR
            //
            // rd = PC + 4
            // PC = (rs1 + immediate) & ~1
            // ----------------------------------------------------

            7'b1100111: begin

                uses_rs1 = 1'b1;
                uses_rs2 = 1'b0;

                alu_src   = 1'b1;
                alu_op    = 2'b00;
                alu_a_sel = ALU_A_RS1;

                jump      = 1'b1;
                jalr      = 1'b1;

                reg_write = 1'b1;
                wb_sel    = WB_PC4;

            end


            // ----------------------------------------------------
            // LUI
            //
            // rd = immediate
            //
            // Implement using:
            //
            // ALU A = 0
            // ALU B = immediate
            // ADD
            // ----------------------------------------------------

            7'b0110111: begin

                uses_rs1 = 1'b0;
                uses_rs2 = 1'b0;

                alu_src   = 1'b1;
                alu_op    = 2'b00;
                alu_a_sel = ALU_A_ZERO;

                reg_write = 1'b1;
                wb_sel    = WB_ALU;

            end


            // ----------------------------------------------------
            // AUIPC
            //
            // rd = PC + immediate
            //
            // Implement using:
            //
            // ALU A = PC
            // ALU B = immediate
            // ADD
            // ----------------------------------------------------

            7'b0010111: begin

                uses_rs1 = 1'b0;
                uses_rs2 = 1'b0;

                alu_src   = 1'b1;
                alu_op    = 2'b00;
                alu_a_sel = ALU_A_PC;

                reg_write = 1'b1;
                wb_sel    = WB_ALU;

            end


            // ----------------------------------------------------
            // Unknown / unsupported opcode
            // ----------------------------------------------------

            default: begin
                // Defaults already create a no-side-effect operation.
            end

        endcase

    end

endmodule