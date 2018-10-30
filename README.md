
J68 - A Size-Optimized Microcoded 68000 CPU
===========================================

J68 is a CPU core that implements the Motorola/Freescale/NXP [68000 Instruction Set](https://www.nxp.com/files/archives/doc/ref_manual/M68000PRM.pdf).

J68 is free and open hardware licensed under the [ISC license](http://en.wikipedia.org/wiki/ISC_license)
(a license that is similar in terms to the MIT license or the 2-clause BSD license).

Features and Typical Applications
---------------------------------

- Small (1900 LUTs + 8 x M9k on a Cyclone III)
- High f<sub>max</sub> (90 MHz on a Cyclone III, 180 MHz on a Stratix II)
- Stack based CPU with Forth-like microcode
- Not cycle exact : needs a frequency ~3 times higher
- All 68000 instructions are implemented
- Almost all 68000 exceptions are implemented (only bus error missing)
- Only auto-vector interrupts supported

This CPU is meant to be used in Retro gaming / Retro compututing applications. Due to its high f<sub>max</sub>,
it can operate at the SDRAM controller frequency, without clock domain crossing.

Files in this Repository
------------------------

#### README.md

You are reading it right now.

#### rtl/cpu_j68.v

This is the top level of the J68 CPU

#### rtl/j68_addsub_32.v

Optimized 32-bit add / subtract.

#### rtl/j68_alu.v

The 16-bit ALU (ADD, SUB, AND, OR, XOR, NOT and bitmask) with C and V flags generation.

#### rtl/j68_decode.v

Instruction decoder, it generates a 8-bit index for a 256-entry jump table.
It also generates the 4-bit effective address indexes and the immediate values.
Finally, it detects the invalid and privileged instructions.

#### rtl/j68_decode_rom.v

ROM containing the 256-entry jump table.

#### rtl/j68_dpram_2048x20.v

2048 x 20-bit ROM/RAM containing microcode and CPU registers (D0-D7, A0-A7).

#### rtl/j68_flags.v

Flags read / write in the condition code register (CCR).

#### rtl/j68_loop.v

Microcode loop for multi-cycle instructions (MUL, DIV, MOVEM).

#### rtl/j68_test.v

Microcode conditional branching.

#### rtl/j68_mem_io.v

External bus management and special registers (PC, SR, EA1, EA2, VBR, ACCU, SHIFTER).

#### rtl/soc_j68.v

A system-on-a-chip that re-create the Raymatic M68000 development board (68000 + 16 KB ROM + 32 KB RAM + 2 x ACIAs 6850).
The VUBUG debugger can run on this SOC (https://www.retro.co.za/68000/VUBUG/).

#### rtl/acia_6850.v

The 6850 ACIA from the Suska project (https://www.experiment-s.de/en/), translated into verilog.

#### rtl/onchip_ram.v

Parameterized RAM block for Verilator and Altera Cyclone III.

#### rtl/onchip_rom.v

Parameterized ROM block for Verilator and Altera Cyclone III.

#### rtl/tb/tb_clock.v

100 MHz clock and reset generator for the Verilator testbench.

#### rtl/tb/tb_soc_j68.v

Verilator testbench top level.

#### verilator/clock_gen/

Configurable clock generator for Verilator.

#### verilator/m68k_trace/musashi/

Musashi 680x0 trace/emulator from MAME project (https://github.com/kstenerud/Musashi).

#### verilator/m68k_trace/m68k_trace.cpp

DPI-C interface for Musashi.

#### verilator/m68k_trace/musashi.cpp

C++ wrapper for the Musashi 680x0 trace/emulator.

#### verilator/compile

Compile script for the Verilator testbench.

#### verilator/main.cpp

Main loop of the Verilator testbench.

#### verilator/tb_top.v

Verilator testbench configuration file.

#### tools/microcode20/

Micro-code assembler.

#### tools/srecord/

SRecord v1.64 tool (http://srecord.sourceforge.net/).

#### tools/vasmm68k/

VASM M68k assembler (http://sun.hasenbraten.de/vasm/).

#### roms/rom_vubug.asm

Assembly source code of the VUBUG debugger ROM.

#### roms/rom_testbench.asm

Assembly source code of the 1500+ test cases.

#### ucode/j68_ucode.asm

The J68 Forth-like microcode.
