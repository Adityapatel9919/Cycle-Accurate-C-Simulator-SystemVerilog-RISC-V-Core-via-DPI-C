module alu_control (
    input  logic [1:0] alu_op,
    input  logic [2:0] funct3,
    input  logic [6:0] funct7,

    output logic [3:0] alu_ctrl
);

always_comb
 begin

    case (alu_op)

        // LW, SW -> ADD
        2'b00: begin
            alu_ctrl = 4'b0000;
        end

        // BEQ, BNE -> SUB
        2'b01: begin
            alu_ctrl = 4'b0001;
        end

        // R-Type / I-Type
       2'b10,
2'b11: begin

    case (funct3)

        3'b000: begin
            if (funct7 == 7'b0100000)
                alu_ctrl = 4'b0001;
            else
                alu_ctrl = 4'b0000;
        end

        3'b001: alu_ctrl = 4'b0101;
        3'b010: alu_ctrl = 4'b1000;
        3'b011: alu_ctrl = 4'b1001;
        3'b100: alu_ctrl = 4'b0100;

        3'b101: begin
            if (funct7 == 7'b0100000)
                alu_ctrl = 4'b0111;
            else
                alu_ctrl = 4'b0110;
        end

        3'b110: alu_ctrl = 4'b0011;
        3'b111: alu_ctrl = 4'b0010;

        default: alu_ctrl = 4'b0000;

    endcase

        end

        default: begin
            alu_ctrl = 4'b0000;
        end

    endcase

end

endmodule