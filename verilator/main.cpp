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

#include "verilated.h"
#include "svdpi.h"

#include "Vtb_soc_j68.h"
#include "Vtb_soc_j68_tb_soc_j68.h"
#include "Vtb_soc_j68_tb_clock.h"

#include "./clock_gen/clock_gen.h"

#include <ctime>

#if VM_TRACE
#include "verilated_vcd_c.h"
#endif

// Period for a 100 MHz clock
#define PERIOD_100MHz_ps      ((vluint64_t)10000)

// Clocks generation (global)
ClockGen *clk;

int main(int argc, char **argv, char **env)
{
    // Simulation duration
    time_t beg, end;
    double secs;
    // Trace index
    int trc_idx = 0;
    int min_idx = 0;
    // Image size
    int width, height;
    // File name generation
    char file_name[256];
    // Simulation steps
    vluint64_t max_step;
    // Testbench configuration
    const char *arg;
    // Clocks generation
    vluint8_t *clk_100;
  
    beg = time(0);
    
    // Parse parameters
    Verilated::commandArgs(argc, argv);
    
    // Default : 1 msec
    max_step = (vluint64_t)1000000000;
    
    // Simulation duration : +usec=<num>
    arg = Verilated::commandArgsPlusMatch("usec=");
    if ((arg) && (arg[0]))
    {
        arg += 6;
        max_step = (vluint64_t)atoi(arg) * (vluint64_t)1000000;
    }
    
    // Simulation duration : +msec=<num>
    arg = Verilated::commandArgsPlusMatch("msec=");
    if ((arg) && (arg[0]))
    {
        arg += 6;
        max_step = (vluint64_t)atoi(arg) * (vluint64_t)1000000000;
    }
    
    // Trace start index : +tidx=<num>
    arg = Verilated::commandArgsPlusMatch("tidx=");
    if ((arg) && (arg[0]))
    {
        arg += 6;
        min_idx = atoi(arg);
    }
    else
    {
        min_idx = 0;
    }
    
    // Init top verilog instance
    Vtb_soc_j68* top = new Vtb_soc_j68;
  
    // Initialize clock generator    
    clk = new ClockGen(1, max_step);
    // 100 MHz
    clk->NewClock(0, PERIOD_100MHz_ps, 0);
    clk->StartClock(0);
    clk_100 = &top->tb_soc_j68->U_tb_clock->r_clk_100;
    
#if VM_TRACE
    // Init VCD trace dump
    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace (tfp, 99);
    tfp->spTrace()->set_time_resolution ("1 ps");
    sprintf(file_name, "soc_j68_%04d.vcd", trc_idx++);
    tfp->open (file_name);
#endif /* VM_TRACE */
  
    // Initialize simulation inputs
    top->UART0_RX = (vluint8_t)0;
    top->UART1_RX = (vluint8_t)0;
  
    // Simulation loop
    while (!clk->EndOfSimulation())
    {
        clk->AdvanceClocks();
        *clk_100 = clk->GetClockStateDiv1(0,0);
        
        // Evaluate verilated model
        top->eval ();

#if VM_TRACE
        // Dump signals into VCD file
        if (tfp)
        {
            if (0)
            {
                // New VCD file
                tfp->close ();
                sprintf(file_name, "j68_%04d.vcd", trc_idx++);
                tfp->open (file_name);
            }
            tfp->dump (clk->GetTimeStampPs());
        }
#endif /* VM_TRACE */

        if (Verilated::gotFinish()) break;
    }
    top->final();
  
#if VM_TRACE
    if (tfp) tfp->close();
#endif /* VM_TRACE */

    // Calculate running time
    end = time(0);
    secs = difftime(end, beg);
    printf("\n\nSeconds elapsed : %f\n", secs);
    
    exit(0);
}
