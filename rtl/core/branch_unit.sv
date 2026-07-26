module branch_unit (
    input  logic [31:0] rs1_data,
    input  logic [31:0] rs2_data,
    input  logic [2:0]  funct3,
    input  logic        branch,

    output logic        branch_taken
);

    always_comb begin

        // Default: branch not taken
        branch_taken = 1'b0;

        if (branch) begin

            case (funct3)

                // BEQ
                3'b000:
                    branch_taken = (rs1_data == rs2_data);

                // BNE
                3'b001:
                    branch_taken = (rs1_data != rs2_data);

                // BLT - signed comparison
                3'b100:
                    branch_taken =
                        ($signed(rs1_data) < $signed(rs2_data));

                // BGE - signed comparison
                3'b101:
                    branch_taken =
                        ($signed(rs1_data) >= $signed(rs2_data));

                // BLTU - unsigned comparison
                3'b110:
                    branch_taken =
                        (rs1_data < rs2_data);

                // BGEU - unsigned comparison
                3'b111:
                    branch_taken =
                        (rs1_data >= rs2_data);

                default:
                    branch_taken = 1'b0;

            endcase

        end

    end

endmodule