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

module onchip_ram
(
    input                   clock,
    input                   wren,
    input  [1:0]            byteena,
    input  [ADDR_WIDTH-1:1] address,
    input  [15:0]           data,
    output [15:0]           q
);
    // 12 : 4KB, 13 : 8KB, ...
    parameter ADDR_WIDTH = 12;

`ifdef verilator3

    // Testbench
    reg  [15:0] r_mem_blk [0:(1 << (ADDR_WIDTH - 1)) - 1];
    reg  [15:0] r_q;
    
    // Read / write
    always@(posedge clock) begin
        r_q <= r_mem_blk[address][15:0];
        if (wren) begin
            if (byteena[0]) r_mem_blk[address][7:0]  <= data[7:0];
            if (byteena[1]) r_mem_blk[address][15:8] <= data[15:8];
        end
    end
    
    assign q = r_q;
    
`else

    // Synthesis
    altsyncram
    #(
        .byte_size                     (8),
        .clock_enable_input_a          ("BYPASS"),
        .clock_enable_output_a         ("BYPASS"),
        .intended_device_family        ("Cyclone III"),
        .lpm_hint                      ("ENABLE_RUNTIME_MOD=YES,INSTANCE_NAME=1"),
        .lpm_type                      ("altsyncram"),
        .numwords_a                    (1 << (ADDR_WIDTH - 1)),
        .operation_mode                ("SINGLE_PORT"),
        .outdata_aclr_a                ("NONE"),
        .outdata_reg_a                 ("UNREGISTERED"),
        .power_up_uninitialized        ("FALSE"),
        .read_during_write_mode_port_a ("NEW_DATA_NO_NBE_READ"),
        .widthad_a                     (ADDR_WIDTH - 1),
        .width_a                       (16),
        .width_byteena_a               (2)
    )
    U_altsyncram
    (
        .wren_a         (wren),
        .clock0         (clock),
        .byteena_a      (byteena),
        .address_a      (address),
        .data_a         (data),
        .q_a            (q),
        .aclr0          (1'b0),
        .aclr1          (1'b0),
        .address_b      (1'b1),
        .addressstall_a (1'b0),
        .addressstall_b (1'b0),
        .byteena_b      (1'b1),
        .clock1         (1'b1),
        .clocken0       (1'b1),
        .clocken1       (1'b1),
        .clocken2       (1'b1),
        .clocken3       (1'b1),
        .data_b         (1'b1),
        .eccstatus      (),
        .q_b            (),
        .rden_a         (1'b1),
        .rden_b         (1'b1),
        .wren_b         (1'b0)
    );

`endif

endmodule
