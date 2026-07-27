module if_id (
    input  logic        clk,
    input  logic        rst,
    input  logic        write_enable,
    input  logic        flush,

    input  logic        valid_in,
    input  logic [31:0] pc_in,
    input  logic [31:0] instruction_in,

    output logic        valid_out,
    output logic [31:0] pc_out,
    output logic [31:0] instruction_out
);

    always_ff @(posedge clk or posedge rst) begin
        if (rst) begin
            valid_out       <= 1'b0;
            pc_out          <= 32'b0;
            instruction_out <= 32'h00000013;
        end
        else if (flush) begin
            valid_out       <= 1'b0;
            pc_out          <= 32'b0;
            instruction_out <= 32'h00000013;
        end
        else if (write_enable) begin
            valid_out       <= valid_in;
            pc_out          <= pc_in;
            instruction_out <= instruction_in;
        end
    end

endmodule