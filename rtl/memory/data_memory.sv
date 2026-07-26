module data_memory #(
    parameter MEM_DEPTH = 1024
)(
    input  logic        clk,

    input  logic        mem_read,
    input  logic        mem_write,

    input  logic [31:0] addr,
    input  logic [31:0] write_data,

    output logic [31:0] read_data
);

    // 1024 x 32-bit word-addressable memory
    logic [31:0] mem [0:MEM_DEPTH-1];

    // -------------------------
    // Memory Read
    // -------------------------
    always_comb begin
        if (mem_read && (addr[31:2] < MEM_DEPTH))
            read_data = mem[addr[31:2]];
        else
            read_data = 32'b0;
    end

    // -------------------------
    // Memory Write
    // -------------------------
    always_ff @(posedge clk) begin
        if (mem_write && (addr[31:2] < MEM_DEPTH))
            mem[addr[31:2]] <= write_data;
    end

endmodule