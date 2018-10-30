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

#include "svdpi.h"

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

#define RESET_ADDR (0x00000000)

static int           reset;          // Reset state (2 -> 1 -> 0)
static unsigned long reset_ssp;      // Initial SSP (vector #0)
static unsigned long reset_pc;       // Initial PC (vector #1)

static int           data_cnt[2];    // 0 : read, 1 : write
static unsigned long data_rd[32][3]; // 0 : data, 1 : mask, 2 : address
static unsigned long data_wr[32][3]; // 0 : data, 1 : mask, 2 : address

static int           prog_cnt;       // read only
static unsigned long prog_rd[32][3]; // 0 : data, 1 : mask, 2 : address

static int           vect_cnt;       // read only
static unsigned long vect_rd[32][3]; // 0 : data, 1 : mask, 2 : address

static unsigned long regs[16];
static unsigned long prev_pc;
static int           prev_lvl;

static FILE         *fh_m;           // Musashi log file handle
static FILE         *fh_j;           // J68 core log file handle
static char          fname_m[20];    // Musashi log file name
static char          fname_j[20];    // J68 core log file name
static int           inst_cnt;       // Instruction count

static void inc_logfile(char *name)
{
    if (name[11] == '9')
    {
        name[11] = '0';
        if (name[10] == '9')
        {
            name[10] = '0';
            if (name[9] == '9')
            {
                name[9] = '0';
              
                name[8]++;
            }
            else
            {
                name[9]++;
            }
        }
        else
        {
            name[10]++;
        }
    }
    else
    {
        name[11]++;
    }
}

unsigned int m68k_read_memory_8(unsigned int addr)
{
  int i;
    
  for (i = 0; i < data_cnt[0]; i++)
  {
    if ((data_rd[i][2] & 0xFFFFFFFE) == (addr & 0xFFFFFFFE))
    {
      if (addr & 1)
        return data_rd[i][0] & 0xFF;
      else
        return (data_rd[i][0] >> 8) & 0xFF;
    }
  }
  if (fh_m) fprintf(fh_m, "!!! Byte read access mismatch @ 0x%08lX !!!\n", addr);

  return 0x00;
}

unsigned int m68k_read_memory_16(unsigned int addr)
{
    int i;
      
    for (i = 0; i < prog_cnt; i++)
    {
        if (prog_rd[i][2] == addr)
        {
            return prog_rd[i][0];
        }
    }
    
    for (i = 0; i < data_cnt[0]; i++)
    {
        if (data_rd[i][2] == addr)
        {
            return data_rd[i][0];
        }
    }
    
    for (i = 0; i < vect_cnt; i++)
    {
        if (vect_rd[i][2] == addr)
        {
            return vect_rd[i][0];
        }
    }
    if (fh_m) fprintf(fh_m, "!!! Word read access mismatch @ 0x%08lX !!!\n", addr);
    
    return 0x0000;
}

unsigned int m68k_read_memory_32(unsigned int addr)
{
    switch (reset)
    {
        case 2 :
            reset--;
            return reset_ssp;
        case 1 :
            reset--;
            return reset_pc;
        default :
            return (m68k_read_memory_16(addr) << 16) | (m68k_read_memory_16(addr + 2));
    }
}

void m68k_write_memory_8(unsigned int addr, unsigned int data)
{
    int i;
    
    for (i = 0; i < data_cnt[1]; i++)
    {
        if ((data_wr[i][2] & 0xFFFFFFFE) == (addr & 0xFFFFFFFE))
        {
            if (addr & 1)
            {
                if ((data_wr[i][0] & 0xFF) == data) return;
            }
            else
            {
                if ((data_wr[i][0] >> 8) == data) return;
            }
        }
    }
    if (fh_m) fprintf(fh_m, "!!! Byte write access mismatch @ 0x%08lX, value = 0x%02X !!!\n", addr, data);
}

void m68k_write_memory_16(unsigned int addr, unsigned int data)
{
    int i;
    
    for (i = 0; i < data_cnt[1]; i++)
    {
        if ((data_wr[i][2] == addr) && (data_wr[i][0] == data))
        {
            return;
        }
    }
    if (fh_m) fprintf(fh_m, "!!! Word write access mismatch @ 0x%08lX, value = 0x%04X !!!\n", addr, data);
}

void m68k_write_memory_32(unsigned int addr, unsigned int data)
{
    m68k_write_memory_16(addr,     data >> 16);
    m68k_write_memory_16(addr + 2, data & 0xFFFF);
}

void m68k_trace_init(int vect_0, int vect_1)
{
    int i;
    
    /* Clear traces */
    data_cnt[0] = 0;
    data_cnt[1] = 0;
    prog_cnt    = 0;
    vect_cnt    = 0;
    /* Clear registers */
    for (i = 0; i < 16; i++)
    {
      regs[i] = 0;
    }
    prev_pc   = RESET_ADDR;
    prev_lvl  = 0;
    reset_ssp = vect_0;
    reset_pc  = vect_1;
    reset     = 2;
    
    /* Musashi init */
    m68k_set_cpu_type(M68K_CPU_TYPE_68000);
    m68k_init();
    m68k_pulse_reset();
    
    /* Log files init */
    strcpy(fname_m, "musashi_0000.log");
    fh_m = fopen(fname_m, "w");
    strcpy(fname_j, "j68core_0000.log");
    fh_j = fopen(fname_j, "w");
    inst_cnt = 0;
}

void m68k_trace_fetch(int sr, int pc, int usp, int ssp, int lvl)
{
    char dis_buff[256];
    int  reg;
    int  i;
    
    /*
    for (i = 0; i < vect_cnt; i++)
    {
        printf("Read vector %04X @ %08X\n", vect_rd[i][0], vect_rd[i][2]);
    }
    for (i = 0; i < data_cnt[0]; i++)
    {
        printf("Read data %04X @ %08X\n", data_rd[i][0], data_rd[i][2]);
    }
    for (i = 0; i < data_cnt[1]; i++)
    {
        printf("Write data %04X @ %08X\n", data_wr[i][0], data_wr[i][2]);
    }
    */
    
    if (prev_pc != RESET_ADDR)
    {
        /* Disassemble current instruction */  
        if (fh_j)
        {
            m68k_disassemble(dis_buff, prev_pc, M68K_CPU_TYPE_68010);
            fprintf(fh_j, "PC=%08lX  %s\n", prev_pc, dis_buff);
        }
        
        /* Dump registers */
        if (fh_j)
        {
            fprintf(fh_j, "D0=%08X %08X %08X %08X %08X %08X %08X %08X \n",
                    regs[0], regs[1],  regs[2],  regs[3],  regs[4],  regs[5],  regs[6],  regs[7]);
            fprintf(fh_j, "A0=%08X %08X %08X %08X %08X %08X %08X %08X \n",
                    regs[8], regs[9], regs[10], regs[11], regs[12], regs[13], regs[14], regs[15]);
            fprintf(fh_j, "USP=%08X SSP=%08X SR=%04X", usp, ssp, sr);
            fprintf(fh_j, " XNZVC=%c%c%c%c%c\n\n", FLG_X(sr), FLG_N(sr), FLG_Z(sr), FLG_V(sr), FLG_C(sr));
            fflush(fh_j);
        }
    }
    
    if (prev_pc != RESET_ADDR)
    {
        /* Disassemble current instruction */
        if (fh_m)
        {
            reg = m68k_get_reg((void *)NULL, M68K_REG_PC);
            m68k_disassemble(dis_buff, reg, M68K_CPU_TYPE_68010);
            fprintf(fh_m, "PC=%08lX  %s\n", reg, dis_buff);
        }
      
        /* Musashi call */
        m68k_execute(1);
        
        /* Dump registers */
        if (fh_m)
        {
            fprintf(fh_m, "D0=");
            for (i = (int)M68K_REG_D0; i <= (int)M68K_REG_D7; i++)
            {
                reg = m68k_get_reg((void *)NULL, (m68k_register_t)i);
                fprintf(fh_m, "%08lX ", reg);
            }
            fprintf(fh_m, "\nA0=");
            for (i = (int)M68K_REG_A0; i <= (int)M68K_REG_A7; i++)
            {
                reg = m68k_get_reg((void *)NULL, (m68k_register_t)i);
                fprintf(fh_m, "%08lX ", reg);
            }
            fprintf(fh_m, "\nUSP=");
            reg = m68k_get_reg((void *)NULL, M68K_REG_USP);
            fprintf(fh_m, "%08lX SSP=", reg);
            reg = m68k_get_reg((void *)NULL, M68K_REG_ISP);
            fprintf(fh_m, "%08lX SR=", reg);
            reg = m68k_get_reg((void *)NULL, M68K_REG_SR);
            fprintf(fh_m, "%04lX", reg & 0xFFFF);
            fprintf(fh_m, " XNZVC=%c%c%c%c%c\n\n", FLG_X(reg), FLG_N(reg), FLG_Z(reg), FLG_V(reg), FLG_C(reg));
            fflush(fh_m);
        }
    }
    
    /* Interrupt level */
    if (prev_lvl != lvl)
    {
        if (fh_j) fprintf(fh_j, "Interrupt level #%d triggered\n\n", lvl);
        if (fh_m) fprintf(fh_m, "Interrupt level #%d triggered\n\n", lvl);
    }
    m68k_set_irq(lvl);
    
    inst_cnt++;
    if (inst_cnt == 100000)
    {
        fclose(fh_m);
        fclose(fh_j);
        
        inc_logfile(fname_m);
        fh_m = fopen(fname_m, "w");
        inc_logfile(fname_j);
        fh_j = fopen(fname_j, "w");
        inst_cnt = 0;
    }
    
    prev_pc     = pc;
    prev_lvl    = lvl;
    /* Clear traces */
    data_cnt[0] = 0;
    data_cnt[1] = 0;
    prog_cnt    = 0;
    vect_cnt    = 0;
}

void m68k_trace_regs(int addr, int wren, int data)
{
    /* Update internal registers */
    if (wren & 1) regs[addr] = (regs[addr] & 0xFFFFFF00) | (((unsigned long)data & 0x00FF) << 0);
    if (wren & 2) regs[addr] = (regs[addr] & 0xFFFF00FF) | (((unsigned long)data & 0xFF00) << 0);
    if (wren & 4) regs[addr] = (regs[addr] & 0xFF00FFFF) | (((unsigned long)data & 0x00FF) << 16);
    if (wren & 8) regs[addr] = (regs[addr] & 0x00FFFFFF) | (((unsigned long)data & 0xFF00) << 16);
}

void m68k_trace_read(int fc, int bena, int addr, int data)
{
    switch(fc)
    {
        case 1:
        case 5:
        {
            /* Data */
            data_rd[data_cnt[0]][0] = data;
            data_rd[data_cnt[0]][1] = bena;
            data_rd[data_cnt[0]][2] = addr;
            data_cnt[0] = (data_cnt[0] + 1) & 31;
            break;
        }
        case 2:
        case 6:
        {
            /* Program */
            prog_rd[prog_cnt][0] = data;
            prog_rd[prog_cnt][1] = bena;
            prog_rd[prog_cnt][2] = addr;
            prog_cnt = (prog_cnt + 1) & 31;
            break;
        }
        case 3:
        case 7:
        {
            /* Vector */
            vect_rd[vect_cnt][0] = data;
            vect_rd[vect_cnt][1] = bena;
            vect_rd[vect_cnt][2] = addr;
            vect_cnt = (vect_cnt + 1) & 31;
            break;
        }
        default:
        {
            /* Undefined FC */
        }
    }
}


void m68k_trace_write(int fc, int bena, int addr, int data)
{
    switch(fc)
    {
        case 1:
        case 5:
        {
            /* Data */
            data_wr[data_cnt[1]][0] = data;
            data_wr[data_cnt[1]][1] = bena;
            data_wr[data_cnt[1]][2] = addr;
            data_cnt[1] = (data_cnt[1] + 1) & 31;
            break;
        }
        default:
        {
            /* Undefined FC */
        }
    }
}

#ifdef __cplusplus
}
#endif
