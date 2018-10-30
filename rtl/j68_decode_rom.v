// Copyright 2011-2018 Frederic Requin
//
// This file is part of the MCC216 project
//
// The J68 core:
// -------------
// Simple re-implementation of the MC68000 CPU
// The core has the following characteristics:
//  - Tested on a Cyclone III (90 MHz) and a Stratix II (180 MHz)
//  - from 1500 (~70 MHz) to 1900 LEs (~90 MHz) on Cyclone III
//  - 2048 x 20-bit microcode ROM
//  - 256 x 28-bit decode ROM
//  - 2 x block RAM for the data and instruction stacks
//  - stack based CPU with forth-like microcode
//  - not cycle-exact : needs a frequency ~3 x higher
//  - all 68000 instructions are implemented
//  - almost all 68000 exceptions are implemented (only bus error missing)
//  - only auto-vector interrupts supported

module j68_decode_rom
(
    input         clock,
    input   [7:0] address,
    output [35:0] q
);
    parameter USE_CLK_ENA = 0;

`ifdef verilator3
  
    // Testbench
    reg  [35:0] r_mem_blk [0:255];
    reg  [35:0] r_q;
    
    initial begin
        if (USE_CLK_ENA)
            $readmemb("j68_dec_c.mem", r_mem_blk);
        else
            $readmemb("j68_dec.mem", r_mem_blk);
    end
    
    always@(posedge clock) begin : READ_PORT
        r_q <= r_mem_blk[address];
    end
    
    assign q = r_q;

`else

    // Synthesis
    altsyncram
    #(
        .clock_enable_input_a   ("BYPASS"),
        .clock_enable_output_a  ("BYPASS"),
        .init_file              ((USE_CLK_ENA) ? "j68_dec_c.mif" : "j68_dec.mif"),
        .intended_device_family ("Cyclone III"),
        .lpm_hint               ("ENABLE_RUNTIME_MOD=NO"),
        .lpm_type               ("altsyncram"),
        .numwords_a             (256),
        .operation_mode         ("ROM"),
        .outdata_aclr_a         ("NONE"),
        .outdata_reg_a          ("UNREGISTERED"),
        .widthad_a              (8),
        .width_a                (36),
        .width_byteena_a        (1)
    )
    altsyncram_256x36
    (
        .clock0                 (clock),
        .address_a              (address),
        .q_a                    (q),
        .aclr0                  (1'b0),
        .aclr1                  (1'b0),
        .address_b              (1'b1),
        .addressstall_a         (1'b0),
        .addressstall_b         (1'b0),
        .byteena_a              (1'b1),
        .byteena_b              (1'b1),
        .clock1                 (1'b1),
        .clocken0               (1'b1),
        .clocken1               (1'b1),
        .clocken2               (1'b1),
        .clocken3               (1'b1),
        .data_a                 ({36{1'b1}}),
        .data_b                 (1'b1),
        .eccstatus              (),
        .q_b                    (),
        .rden_a                 (1'b1),
        .rden_b                 (1'b1),
        .wren_a                 (1'b0),
        .wren_b                 (1'b0)
    );

`endif

endmodule
