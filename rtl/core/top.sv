module top (
    input logic clk,
    input logic rst,
    output logic        commit_valid,
    output logic [31:0] commit_pc,
    output logic [31:0] commit_instr,

    output logic        commit_reg_write,
    output logic [4:0]  commit_rd,
    output logic [31:0] commit_rd_value
);

    // ============================================================
    // CONSTANTS
    // ============================================================

    localparam WB_ALU = 2'b00;
    localparam WB_MEM = 2'b01;
    localparam WB_PC4 = 2'b10;

    localparam ALU_A_RS1  = 2'b00;
    localparam ALU_A_PC   = 2'b01;
    localparam ALU_A_ZERO = 2'b10;


    // ============================================================
    // IF STAGE
    // ============================================================

    logic [31:0] pc_current;
    logic [31:0] pc_next;
    logic [31:0] pc_plus4_if;
    logic [31:0] instruction_if;

    logic pc_write;
    logic if_id_write;
    logic if_id_flush;

    assign pc_plus4_if = pc_current + 32'd4;


    // ============================================================
    // IF/ID PIPELINE REGISTER
    // ============================================================

    logic [31:0] if_id_pc;
    logic [31:0] if_id_instruction;

    logic if_id_valid;
logic id_ex_valid;
logic ex_mem_valid;
logic mem_wb_valid;
    // ============================================================
    // ID STAGE
    // ============================================================

    logic [6:0] opcode_id;

    logic [4:0] rs1_id;
    logic [4:0] rs2_id;
    logic [4:0] rd_id;

    logic [2:0] funct3_id;
    logic [6:0] funct7_id;

    logic [31:0] immediate_id;
    logic [31:0] pc_plus4_id;

    // Raw register-file outputs
    logic [31:0] rs1_data_raw;
    logic [31:0] rs2_data_raw;

    // Register values after WB -> ID bypass
    logic [31:0] rs1_data_id;
    logic [31:0] rs2_data_id;

    assign opcode_id = if_id_instruction[6:0];

    assign rd_id =
        if_id_instruction[11:7];

    assign funct3_id =
        if_id_instruction[14:12];

    assign rs1_id =
        if_id_instruction[19:15];

    assign rs2_id =
        if_id_instruction[24:20];

    assign funct7_id =
        if_id_instruction[31:25];

    assign pc_plus4_id =
        if_id_pc + 32'd4;


    // ============================================================
    // ID CONTROL SIGNALS
    // ============================================================

    logic uses_rs1_id;
    logic uses_rs2_id;

    logic       alu_src_id;
    logic [1:0] alu_op_id;
    logic [1:0] alu_a_sel_id;

    logic mem_read_id;
    logic mem_write_id;
    logic branch_id;

    logic jump_id;
    logic jalr_id;

    logic       reg_write_id;
    logic [1:0] wb_sel_id;


    // ============================================================
    // ID/EX PIPELINE REGISTER
    // ============================================================

    logic [31:0] id_ex_pc;
    logic [31:0] id_ex_pc_plus4;
    logic [31:0] id_ex_instr;
    logic [31:0] id_ex_rs1_data;
    logic [31:0] id_ex_rs2_data;
    logic [31:0] id_ex_immediate;

    logic [4:0] id_ex_rs1;
    logic [4:0] id_ex_rs2;
    logic [4:0] id_ex_rd;

    logic [2:0] id_ex_funct3;
    logic [6:0] id_ex_funct7;

    logic       id_ex_alu_src;
    logic [1:0] id_ex_alu_op;
    logic [1:0] id_ex_alu_a_sel;

    logic id_ex_mem_read;
    logic id_ex_mem_write;
    logic id_ex_branch;

    logic id_ex_jump;
    logic id_ex_jalr;

    logic       id_ex_reg_write;
    logic [1:0] id_ex_wb_sel;

    logic id_ex_flush_hazard;
    logic id_ex_flush;


    // ============================================================
    // EX STAGE
    // ============================================================

    logic [1:0] forward_a;
    logic [1:0] forward_b;

    logic [31:0] forwarded_rs1;
    logic [31:0] forwarded_rs2;

    logic [31:0] alu_operand_a;
    logic [31:0] alu_operand_b;

    logic [3:0] alu_ctrl_ex;

    logic [31:0] alu_result_ex;
    logic        alu_zero_ex;


    // ============================================================
    // EX/MEM SIGNALS
    //
    // Declared before forwarding logic because Icarus requires
    // signals to be declared before use.
    // ============================================================

    logic [31:0] ex_mem_alu_result;
    logic [31:0] ex_mem_rs2_data;
    logic [31:0] ex_mem_pc_plus4;
    logic [31:0] ex_mem_pc;
    logic [31:0] ex_mem_instr;
    logic [4:0] ex_mem_rd;

    logic ex_mem_mem_read;
    logic ex_mem_mem_write;

    logic       ex_mem_reg_write;
    logic [1:0] ex_mem_wb_sel;
    

    // ============================================================
    // MEM STAGE
    // ============================================================

    logic [31:0] memory_read_data;


    // ============================================================
    // MEM/WB SIGNALS
    // ============================================================

    logic [31:0] mem_wb_memory_data;
    logic [31:0] mem_wb_alu_result;
    logic [31:0] mem_wb_pc_plus4;
    logic [31:0] mem_wb_pc;
    logic [31:0] mem_wb_instr;
    logic [4:0] mem_wb_rd;

    logic       mem_wb_reg_write;
    logic [1:0] mem_wb_wb_sel;


    // ============================================================
    // WRITEBACK
    // ============================================================

    logic [31:0] writeback_data;

    always_comb begin

        case (mem_wb_wb_sel)

            WB_ALU:
                writeback_data =
                    mem_wb_alu_result;

            WB_MEM:
                writeback_data =
                    mem_wb_memory_data;

            WB_PC4:
                writeback_data =
                    mem_wb_pc_plus4;

            default:
                writeback_data =
                    32'b0;

        endcase

    end


    // ============================================================
    // WB -> ID BYPASS
    // ============================================================
    //
    // Handles:
    //
    // WB writes register X
    // ID reads register X
    //
    // during the same cycle.
    // ============================================================

    always_comb begin

        // Normal register-file values
        rs1_data_id = rs1_data_raw;
        rs2_data_id = rs2_data_raw;

        // WB -> rs1 bypass
        if (
            mem_wb_reg_write &&
            (mem_wb_rd != 5'd0) &&
            (mem_wb_rd == rs1_id)
        ) begin

            rs1_data_id = writeback_data;

        end

        // WB -> rs2 bypass
        if (
            mem_wb_reg_write &&
            (mem_wb_rd != 5'd0) &&
            (mem_wb_rd == rs2_id)
        ) begin

            rs2_data_id = writeback_data;

        end

    end


    // ============================================================
    // CONTROL FLOW
    // ============================================================

    logic branch_taken_ex;
    logic control_transfer_ex;

    logic [31:0] branch_target_ex;
    logic [31:0] jalr_target_ex;
    logic [31:0] redirect_target_ex;

    assign branch_target_ex =
        id_ex_pc + id_ex_immediate;

    assign jalr_target_ex =
        (forwarded_rs1 + id_ex_immediate)
        & 32'hFFFFFFFE;

    assign control_transfer_ex =
        (id_ex_branch && branch_taken_ex)
        || id_ex_jump;


    always_comb begin

        if (id_ex_jalr)
            redirect_target_ex =
                jalr_target_ex;

        else
            redirect_target_ex =
                branch_target_ex;

    end


    // ============================================================
    // NEXT PC
    // ============================================================

    always_comb begin

        pc_next = pc_plus4_if;

        if (control_transfer_ex)
            pc_next = redirect_target_ex;

    end


    // ============================================================
    // PIPELINE FLUSH
    // ============================================================

    assign if_id_flush =
        control_transfer_ex;

    assign id_ex_flush =
        id_ex_flush_hazard |
        control_transfer_ex;


    // ============================================================
    // FORWARDING MUX A
    // ============================================================

    always_comb begin

        case (forward_a)

            2'b00:
                forwarded_rs1 =
                    id_ex_rs1_data;

            2'b10:
                forwarded_rs1 =
                    ex_mem_alu_result;

            2'b01:
                forwarded_rs1 =
                    writeback_data;

            default:
                forwarded_rs1 =
                    id_ex_rs1_data;

        endcase

    end


    // ============================================================
    // FORWARDING MUX B
    // ============================================================

    always_comb begin

        case (forward_b)

            2'b00:
                forwarded_rs2 =
                    id_ex_rs2_data;

            2'b10:
                forwarded_rs2 =
                    ex_mem_alu_result;

            2'b01:
                forwarded_rs2 =
                    writeback_data;

            default:
                forwarded_rs2 =
                    id_ex_rs2_data;

        endcase

    end


    // ============================================================
    // ALU OPERAND A SELECTION
    // ============================================================

    always_comb begin

        case (id_ex_alu_a_sel)

            ALU_A_RS1:
                alu_operand_a =
                    forwarded_rs1;

            ALU_A_PC:
                alu_operand_a =
                    id_ex_pc;

            ALU_A_ZERO:
                alu_operand_a =
                    32'b0;

            default:
                alu_operand_a =
                    forwarded_rs1;

        endcase

    end


    // ============================================================
    // ALU OPERAND B
    // ============================================================

    assign alu_operand_b =
        id_ex_alu_src
            ? id_ex_immediate
            : forwarded_rs2;


    // ============================================================
    // PC
    // ============================================================

    pc pc_inst (
        .clk        (clk),
        .rst        (rst),
        .pc_write   (pc_write),
        .pc_next    (pc_next),
        .pc_current (pc_current)
    );


    // ============================================================
    // INSTRUCTION MEMORY
    // ============================================================

    instruction_memory #(
        .MEM_DEPTH(1024)
    ) imem_inst (
        .addr        (pc_current),
        .instruction (instruction_if)
    );


    // ============================================================
    // IF/ID
    // ============================================================

if_id if_id_inst (
    .clk             (clk),
    .rst             (rst),

    .write_enable    (if_id_write),
    .flush           (if_id_flush),

    .valid_in        (1'b1),
    .pc_in           (pc_current),
    .instruction_in  (instruction_if),

    .valid_out       (if_id_valid),
    .pc_out          (if_id_pc),
    .instruction_out (if_id_instruction)
);

    // ============================================================
    // CONTROL UNIT
    // ============================================================

    control_unit control_inst (
        .opcode    (opcode_id),

        .uses_rs1  (uses_rs1_id),
        .uses_rs2  (uses_rs2_id),

        .alu_src   (alu_src_id),
        .alu_op    (alu_op_id),
        .alu_a_sel (alu_a_sel_id),

        .mem_read  (mem_read_id),
        .mem_write (mem_write_id),
        .branch    (branch_id),

        .jump      (jump_id),
        .jalr      (jalr_id),

        .reg_write (reg_write_id),
        .wb_sel    (wb_sel_id)
    );


    // ============================================================
    // REGISTER FILE
    // ============================================================

    regfile regfile_inst (
        .clk      (clk),
        .rst      (rst),

        .rs1_addr (rs1_id),
        .rs1_data (rs1_data_raw),

        .rs2_addr (rs2_id),
        .rs2_data (rs2_data_raw),

        .we       (mem_wb_reg_write),
        .rd_addr  (mem_wb_rd),
        .rd_data  (writeback_data)
    );


    // ============================================================
    // IMMEDIATE GENERATOR
    // ============================================================

    imm_gen imm_gen_inst (
        .instr (if_id_instruction),
        .imm   (immediate_id)
    );


    // ============================================================
    // HAZARD UNIT
    // ============================================================

    hazard_unit hazard_inst (
        .id_ex_mem_read (id_ex_mem_read),
        .id_ex_rd       (id_ex_rd),

        .if_id_rs1      (rs1_id),
        .if_id_rs2      (rs2_id),

        .if_id_uses_rs1 (uses_rs1_id),
        .if_id_uses_rs2 (uses_rs2_id),

        .pc_write       (pc_write),
        .if_id_write    (if_id_write),
        .id_ex_flush    (id_ex_flush_hazard)
    );


    // ============================================================
    // ID/EX
    // ============================================================

id_ex id_ex_inst (
    .clk            (clk),
    .rst            (rst),
    .flush          (id_ex_flush),

    // Trace
    .valid_in       (if_id_valid),

    // Data
    .pc_in          (if_id_pc),
    .instr_in       (if_id_instruction),
    .pc_plus4_in    (pc_plus4_id),

    .rs1_data_in    (rs1_data_id),
    .rs2_data_in    (rs2_data_id),
    .immediate_in   (immediate_id),

    .rs1_in         (rs1_id),
    .rs2_in         (rs2_id),
    .rd_in          (rd_id),

    .funct3_in      (funct3_id),
    .funct7_in      (funct7_id),

    // EX control
    .alu_src_in     (alu_src_id),
    .alu_op_in      (alu_op_id),
    .alu_a_sel_in   (alu_a_sel_id),

    // MEM control
    .mem_read_in    (mem_read_id),
    .mem_write_in   (mem_write_id),
    .branch_in      (branch_id),

    // Control flow
    .jump_in        (jump_id),
    .jalr_in        (jalr_id),

    // WB control
    .reg_write_in   (reg_write_id),
    .wb_sel_in      (wb_sel_id),

    // Trace
    .valid_out      (id_ex_valid),

    // Data outputs
    .pc_out         (id_ex_pc),
    .instr_out      (id_ex_instr),
    .pc_plus4_out   (id_ex_pc_plus4),

    .rs1_data_out   (id_ex_rs1_data),
    .rs2_data_out   (id_ex_rs2_data),
    .immediate_out  (id_ex_immediate),

    .rs1_out        (id_ex_rs1),
    .rs2_out        (id_ex_rs2),
    .rd_out         (id_ex_rd),

    .funct3_out     (id_ex_funct3),
    .funct7_out     (id_ex_funct7),

    // EX control outputs
    .alu_src_out    (id_ex_alu_src),
    .alu_op_out     (id_ex_alu_op),
    .alu_a_sel_out  (id_ex_alu_a_sel),

    // MEM control outputs
    .mem_read_out   (id_ex_mem_read),
    .mem_write_out  (id_ex_mem_write),
    .branch_out     (id_ex_branch),

    // Control flow outputs
    .jump_out       (id_ex_jump),
    .jalr_out       (id_ex_jalr),

    // WB outputs
    .reg_write_out  (id_ex_reg_write),
    .wb_sel_out     (id_ex_wb_sel)
);

    // ============================================================
    // FORWARDING UNIT
    // ============================================================

    forwarding_unit forwarding_inst (
        .id_ex_rs1        (id_ex_rs1),
        .id_ex_rs2        (id_ex_rs2),

        .ex_mem_rd        (ex_mem_rd),
        .ex_mem_reg_write (ex_mem_reg_write),

        .mem_wb_rd        (mem_wb_rd),
        .mem_wb_reg_write (mem_wb_reg_write),

        .forward_a        (forward_a),
        .forward_b        (forward_b)
    );


    // ============================================================
    // ALU CONTROL
    // ============================================================

    alu_control alu_control_inst (
        .alu_op   (id_ex_alu_op),
        .funct3   (id_ex_funct3),
        .funct7   (id_ex_funct7),
        .alu_ctrl (alu_ctrl_ex)
    );


    // ============================================================
    // ALU
    // ============================================================

    alu alu_inst (
        .a        (alu_operand_a),
        .b        (alu_operand_b),

        .alu_ctrl (alu_ctrl_ex),

        .result   (alu_result_ex),
        .zero     (alu_zero_ex)
    );


    // ============================================================
    // BRANCH UNIT
    // ============================================================

    branch_unit branch_inst (
        .rs1_data     (forwarded_rs1),
        .rs2_data     (forwarded_rs2),

        .funct3       (id_ex_funct3),
        .branch       (id_ex_branch),

        .branch_taken (branch_taken_ex)
    );


    // ============================================================
    // EX/MEM
    // ============================================================

    ex_mem ex_mem_inst (
    .clk            (clk),
    .rst            (rst),
    .flush          (1'b0),

    // Trace metadata
    .valid_in       (id_ex_valid),
    .pc_in          (id_ex_pc),
    .instr_in       (id_ex_instr),

    // EX data
    .alu_result_in  (alu_result_ex),
    .rs2_data_in    (forwarded_rs2),
    .pc_plus4_in    (id_ex_pc_plus4),
    .rd_in          (id_ex_rd),

    // MEM control
    .mem_read_in    (id_ex_mem_read),
    .mem_write_in   (id_ex_mem_write),

    // WB control
    .reg_write_in   (id_ex_reg_write),
    .wb_sel_in      (id_ex_wb_sel),

    // Trace outputs
    .valid_out      (ex_mem_valid),
    .pc_out         (ex_mem_pc),
    .instr_out      (ex_mem_instr),

    // Data outputs
    .alu_result_out (ex_mem_alu_result),
    .rs2_data_out   (ex_mem_rs2_data),
    .pc_plus4_out   (ex_mem_pc_plus4),
    .rd_out         (ex_mem_rd),

    // MEM control outputs
    .mem_read_out   (ex_mem_mem_read),
    .mem_write_out  (ex_mem_mem_write),

    // WB control outputs
    .reg_write_out  (ex_mem_reg_write),
    .wb_sel_out     (ex_mem_wb_sel)
);


    // ============================================================
    // DATA MEMORY
    // ============================================================

    data_memory #(
        .MEM_DEPTH(1024)
    ) dmem_inst (
        .clk        (clk),

        .mem_read   (ex_mem_mem_read),
        .mem_write  (ex_mem_mem_write),

        .addr       (ex_mem_alu_result),
        .write_data (ex_mem_rs2_data),

        .read_data  (memory_read_data)
    );


    // ============================================================
    // MEM/WB
    // ============================================================

  mem_wb mem_wb_inst (
    .clk            (clk),
    .rst            (rst),

    .valid_in       (ex_mem_valid),
    .pc_in          (ex_mem_pc),
    .instr_in       (ex_mem_instr),

    .alu_result_in  (ex_mem_alu_result),

    // FIXED
    .mem_data_in    (memory_read_data),

    .pc_plus4_in    (ex_mem_pc_plus4),
    .rd_in          (ex_mem_rd),

    .reg_write_in   (ex_mem_reg_write),
    .wb_sel_in      (ex_mem_wb_sel),

    .valid_out      (mem_wb_valid),
    .pc_out         (mem_wb_pc),
    .instr_out      (mem_wb_instr),

    .alu_result_out (mem_wb_alu_result),

    // FIXED
    .mem_data_out   (mem_wb_memory_data),

    .pc_plus4_out   (mem_wb_pc_plus4),
    .rd_out         (mem_wb_rd),

    .reg_write_out  (mem_wb_reg_write),
    .wb_sel_out     (mem_wb_wb_sel)
);
always_comb begin

    commit_valid     = mem_wb_valid;
    commit_pc        = mem_wb_pc;
    commit_instr     = mem_wb_instr;

    commit_reg_write = mem_wb_valid
                     && mem_wb_reg_write
                     && (mem_wb_rd != 5'd0);

    commit_rd        = mem_wb_rd;

    commit_rd_value  = writeback_data;

end

endmodule