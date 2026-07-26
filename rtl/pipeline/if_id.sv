module if_id (
    input  logic        clk,
    input  logic        rst,

    // Pipeline control
    input  logic        write_enable,
    input  logic        flush,

    // Inputs from IF stage
    input  logic [31:0] pc_in,
    input  logic [31:0] instruction_in,

    // Outputs to ID stage
    output logic [31:0] pc_out,
    output logic [31:0] instruction_out
);

    always_ff @(posedge clk or posedge rst) begin

        if (rst) begin
            pc_out          <= 32'b0;
            instruction_out <= 32'h00000013; // NOP
        end

        else if (flush) begin
            pc_out          <= 32'b0;
            instruction_out <= 32'h00000013; // NOP
        end

        else if (write_enable) begin
            pc_out          <= pc_in;
            instruction_out <= instruction_in;
        end

    end

endmodule