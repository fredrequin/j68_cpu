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

// Trace configuration
// -------------------
`verilator_config

// 68000 CPU :
//============
tracing_on -file "../rtl/j68_alu.v"
tracing_on -file "../rtl/j68_flags.v"
tracing_on -file "../rtl/j68_test.v"
tracing_on -file "../rtl/j68_loop.v"
tracing_on -file "../rtl/j68_addsub_32.v"
tracing_on -file "../rtl/j68_decode.v"
tracing_on -file "../rtl/j68_decode_rom.v"
tracing_on -file "../rtl/j68_mem_io.v"
tracing_on -file "../rtl/j68_dpram_2048x20.v"
tracing_on -file "../rtl/cpu_j68.v"
tracing_off -file "../rtl/acia_6850.v"
tracing_off -file "../rtl/onchip_ram.v"
tracing_off -file "../rtl/onchip_rom.v"
tracing_on -file "../rtl/soc_j68.v"

// TEST BENCH :
//=============
tracing_off -file "../rtl/tb/tb_clock.v"
tracing_on -file "../rtl/tb/tb_soc_j68.v"

`verilog

`include "../rtl/_ip_soc_j68.v"
`include "../rtl/tb/tb_clock.v"
`include "../rtl/tb/tb_soc_j68.v"
