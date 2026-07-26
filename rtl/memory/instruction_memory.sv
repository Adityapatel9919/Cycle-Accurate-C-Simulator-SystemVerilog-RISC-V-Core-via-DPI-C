module instruction_memory #(
    parameter MEM_DEPTH = 1024
)(
    input  logic [31:0] addr,
    output logic [31:0] instruction
);

    // ============================================================
    // INSTRUCTION MEMORY
    // ============================================================

    logic [31:0] memory [0:MEM_DEPTH-1];

    // Fixed-size filename storage.
    // Avoids SystemVerilog "string" compatibility issues in Icarus.
    reg [8*256-1:0] program_file;

    integer i;


    // ============================================================
    // MEMORY INITIALISATION
    // ============================================================

    initial begin

        // --------------------------------------------------------
        // Initialise complete instruction memory with NOP
        //
        // RISC-V:
        //
        // addi x0, x0, 0
        //
        // encoding = 0x00000013
        //
        // This prevents X values after the test program ends.
        // --------------------------------------------------------

        for (i = 0; i < MEM_DEPTH; i = i + 1) begin
            memory[i] = 32'h00000013;
        end


        // --------------------------------------------------------
        // Get program filename from simulator command line
        //
        // Example:
        //
        // vvp sim/cpu_sim \
        //     +PROGRAM=tests/directed/alu.hex
        //
        // --------------------------------------------------------

        if (!$value$plusargs("PROGRAM=%s", program_file)) begin

            // Default program
            program_file = "program.hex";

        end


        // --------------------------------------------------------
        // Display selected program
        // --------------------------------------------------------

        $display("");
        $display("Loading program: %s", program_file);
        $display("");


        // --------------------------------------------------------
        // Load machine code
        // --------------------------------------------------------

        $readmemh(program_file, memory);

    end


    // ============================================================
    // INSTRUCTION FETCH
    // ============================================================
    //
    // RISC-V instructions are 32 bits = 4 bytes.
    //
    // PC:
    //
    // 0x00 -> memory[0]
    // 0x04 -> memory[1]
    // 0x08 -> memory[2]
    // 0x0C -> memory[3]
    //
    // Therefore:
    //
    // memory index = addr >> 2
    //
    // ============================================================

    always @(*) begin

        if (addr[31:2] < MEM_DEPTH)
            instruction = memory[addr[31:2]];

        else
            instruction = 32'h00000013;

    end

endmodule