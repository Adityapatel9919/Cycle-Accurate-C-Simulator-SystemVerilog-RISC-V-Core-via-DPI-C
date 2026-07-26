module pc (
    input  logic        clk,
    input  logic        rst,
    input  logic        pc_write,
    input  logic [31:0] pc_next,

    output logic [31:0] pc_current
);

    always_ff @(posedge clk or posedge rst) begin
        if (rst)
            pc_current <= 32'h00000000;
        else if (pc_write)
            pc_current <= pc_next;
    end

endmodule