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

`ifdef verilator3

// Testbench
module j68_dpram_2048x20
(
    // Clock & reset
    input         reset,
    input         clock,
    input         clocken,
    // Port A : micro-instruction fetch
    input         rden_a,
    input  [10:0] address_a,
    output [19:0] q_a,
    // Port B : m68k registers read/write
    input   [1:0] wren_b,
    input  [10:0] address_b,
    input  [15:0] data_b,
    output [15:0] q_b
);
    parameter RAM_INIT_FILE = "j68_ram.mem";

    // Inferred block RAM
    reg  [19:0] r_mem_blk [0:2047];

    initial begin
        $readmemb(RAM_INIT_FILE, r_mem_blk);
    end

    reg  [19:0] r_q_a;
    reg  [15:0] r_q_b;

    // Port A (read only)
    always@(posedge reset or posedge clock) begin : PORT_A
    
        if (reset) begin
            r_q_a <= 20'hC0458; // NOP instruction
        end
        else if (rden_a & clocken) begin
            r_q_a <= r_mem_blk[address_a];
        end
    end

    assign q_a = r_q_a;

    // Port B (read/write)
    always@(posedge clock) begin : PORT_B
    
        if (clocken) begin
            r_q_b <= r_mem_blk[address_b][15:0];
            if (wren_b[0]) begin
                r_mem_blk[address_b][7:0]  <= data_b[7:0];
            end
            if (wren_b[1]) begin
                r_mem_blk[address_b][15:8] <= data_b[15:8];
            end
        end
    end

    assign q_b = r_q_b;

endmodule

`else

// Synthesis
module j68_dpram_2048x4
(
    // Clock & reset
    input         reset,
    input         clock,
    input         clocken,
    // Port A : micro-instruction fetch
    input         rden_a,
    input  [10:0] address_a,
    output [3:0]  q_a,
    // Port B : m68k registers read/write
    input         wren_b,
    input  [10:0] address_b,
    input  [3:0]  data_b,
    output [3:0]  q_b
);
    parameter RAM_INIT_FILE = "j68_ram.mif";

    altsyncram
    #(
        .address_reg_b                      ("CLOCK0"),
        .byteena_reg_b                      ("CLOCK0"),
        .byte_size                          (8),
        .clock_enable_input_a               ("BYPASS"),
        .clock_enable_input_b               ("BYPASS"),
        .clock_enable_output_a              ("BYPASS"),
        .clock_enable_output_b              ("BYPASS"),
        .indata_reg_b                       ("CLOCK0"),
        .init_file                          (RAM_INIT_FILE),
        .intended_device_family             ("Cyclone III"),
        .lpm_type                           ("altsyncram"),
        .numwords_a                         (2048),
        .numwords_b                         (2048),
        .operation_mode                     ("BIDIR_DUAL_PORT"),
        .outdata_aclr_a                     ("CLEAR0"),
        .outdata_aclr_b                     ("CLEAR0"),
        .outdata_reg_a                      ("UNREGISTERED"),
        .outdata_reg_b                      ("UNREGISTERED"),
        .power_up_uninitialized             ("FALSE"),
        .ram_block_type                     ("AUTO"),
        .read_during_write_mode_mixed_ports ("OLD_DATA"),
        .read_during_write_mode_port_a      ("NEW_DATA_WITH_NBE_READ"),
        .read_during_write_mode_port_b      ("NEW_DATA_WITH_NBE_READ"),
        .widthad_a                          (11),
        .widthad_b                          (11),
        .width_a                            (4),
        .width_b                            (4),
        .width_byteena_a                    (1),
        .width_byteena_b                    (1),
        .wrcontrol_wraddress_reg_b          ("CLOCK0")
    )
    altsyncram_2048x4
    (
        .clock0         (clock),
        .wren_a         (1'b0),
        .wren_b         (wren_b),
        .address_a      (address_a),
        .address_b      (address_b),
        .data_a         (4'b0000),
        .data_b         (data_b),
        .q_a            (q_a),
        .q_b            (q_b),
        .aclr0          (reset),
        .aclr1          (1'b0),
        .addressstall_a (~rden_a),
        .addressstall_b (1'b0),
        .byteena_a      (1'b1),
        .byteena_b      (1'b1),
        .clock1         (1'b1),
        .clocken0       (clocken),
        .clocken1       (1'b1),
        .clocken2       (1'b1),
        .clocken3       (1'b1),
        .eccstatus      (),
        .rden_a         (1'b1),
        .rden_b         (1'b1)
    );

endmodule

`endif
