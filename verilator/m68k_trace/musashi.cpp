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

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

#include "musashi/m68k.h"

#define FLG_C(r) (r & 1)  ? '1' : '0'
#define FLG_V(r) (r & 2)  ? '1' : '0'
#define FLG_Z(r) (r & 4)  ? '1' : '0'
#define FLG_N(r) (r & 8)  ? '1' : '0'
#define FLG_X(r) (r & 16) ? '1' : '0'

void         m68k_instr_hook(void) { }
unsigned int m68k_read_disassembler_8  (unsigned int addr) { return m68k_read_memory_8(addr); }
unsigned int m68k_read_disassembler_16 (unsigned int addr) { return m68k_read_memory_16(addr); }
unsigned int m68k_read_disassembler_32 (unsigned int addr) { return m68k_read_memory_32(addr); }

// Hack to integrate musashi into the C++ framework that verilator needs
#include "musashi/m68kopac.c"
#include "musashi/m68kopdm.c"
#include "musashi/m68kopnz.c"
#include "musashi/m68kops.c"
#include "musashi/m68kcpu.c"
#include "musashi/m68kdasm.c"

#ifdef __cplusplus
}
#endif
