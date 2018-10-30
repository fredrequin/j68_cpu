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

`ifdef _IP_CPU_J68_DEF_
/* !! Already included !! */ 
`else
`define _IP_CPU_J68_DEF_

`include "../rtl/j68_alu.v"
`include "../rtl/j68_flags.v"
`include "../rtl/j68_test.v"
`include "../rtl/j68_loop.v"
`include "../rtl/j68_addsub_32.v"
`include "../rtl/j68_decode.v"
`include "../rtl/j68_decode_rom.v"
`include "../rtl/j68_mem_io.v"
`ifdef verilator3
`include "../rtl/j68_dpram_2048x20.v"
`else
`include "../rtl/j68_dpram_2048x4.v"
`endif
`include "../rtl/cpu_j68.v"

`endif /* _IP_CPU_J68_DEF_ */
