// Copyright 2011-2018 Frederic Requin
//
// Clock generator C++ object for Verilator
//

#include "verilated.h"
#include "clock_gen.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// Constructor
ClockGen::ClockGen(int num_clk, vluint64_t end_ps)
{
    num_clock      = num_clk;
    end_stamp_ps   = (vluint64_t)end_ps;
    max_stamp_ps   = (vluint64_t)0;
    curr_stamp_ps  = (vluint64_t)0;
    next_stamp_ps  = (vluint64_t)0;
    p_clk_stamp_ps = new vluint64_t[num_clk];
    p_clk_phase_ps = new vluint64_t[num_clk];
    p_clk_hper_ps  = new vluint64_t[num_clk];
    p_clk_state    = new vluint8_t[num_clk];
    p_clk_enable   = new bool[num_clk];
    
    for (int i = 0; i < num_clk; i++)
    {
        p_clk_stamp_ps[i] = (vluint64_t)0;
        p_clk_phase_ps[i] = (vluint64_t)0;
        p_clk_hper_ps[i]  = (vluint64_t)0;
        p_clk_state[i]    = (vluint8_t)0;
        p_clk_enable[i]   = false;
    }
}

// Destructor
ClockGen::~ClockGen()
{
    delete [] p_clk_stamp_ps;
    delete [] p_clk_phase_ps;
    delete [] p_clk_hper_ps;
    delete [] p_clk_state;
    delete [] p_clk_enable;
}

// Create a new clock
void ClockGen::NewClock(int clk_idx, vluint64_t period_ps, vluint64_t phase_ps)
{
    if (clk_idx < num_clock)
    {
        p_clk_phase_ps[clk_idx] = phase_ps;
        p_clk_hper_ps[clk_idx] = period_ps / 2;
        if ((max_stamp_ps * 2) < period_ps)
        {
            max_stamp_ps = period_ps / 2 + 1;
        }
    }
}

// Start a clock
void ClockGen::StartClock(int clk_idx)
{
    if (clk_idx < num_clock)
    {
        // Start with a 0
        p_clk_state[clk_idx] = (vluint8_t)0;
        // Next edge : one half period later
        p_clk_stamp_ps[clk_idx] = curr_stamp_ps + p_clk_hper_ps[clk_idx];
        // Enable the clock if the half period is not null
        p_clk_enable[clk_idx] = (p_clk_hper_ps[clk_idx]) ? true : false;
        
        printf("StartClock(%d) : time = %lld, phase = 0, stamp = %lld\n",
               clk_idx, curr_stamp_ps, p_clk_stamp_ps[clk_idx]);
    }
}

// Start a clock with a phase
void ClockGen::StartClock(int clk_idx, vluint64_t phase_ps)
{
    if (clk_idx < num_clock)
    {
        // Start with a 0
        p_clk_state[clk_idx] = (vluint8_t)0;
        // Rising edge : phase shift + one half period later
        p_clk_stamp_ps[clk_idx] = curr_stamp_ps + p_clk_hper_ps[clk_idx] + phase_ps;
        // Adjust next time stamp if necessary
        if (p_clk_stamp_ps[clk_idx] < next_stamp_ps)
        {
            next_stamp_ps = p_clk_stamp_ps[clk_idx];
        }
        // Enable the clock if the half period is not null
        p_clk_enable[clk_idx] = (p_clk_hper_ps[clk_idx]) ? true : false;
        
        printf("StartClock(%d) : time = %lld, phase = %lld, stamp = %lld\n",
               clk_idx, curr_stamp_ps, phase_ps, p_clk_stamp_ps[clk_idx]);
    }
}

// Stop a clock
void ClockGen::StopClock(int clk_idx)
{
    if (clk_idx < num_clock)
    {
        p_clk_enable[clk_idx] = false;
    }
}

// Not divided clock, phase can be 0 (0 deg) or 1 (180 deg)
vluint8_t ClockGen::GetClockStateDiv1(int clk_idx, vluint8_t phase)
{
    if (clk_idx < num_clock)
        return (p_clk_state[clk_idx] - phase) & 1;
    else
        return (vluint8_t)0;
}

// Clock divided by 2, phase can be 0 (0 deg), 1 (90 deg), 2 (180 deg) or 3 (270 deg)
vluint8_t ClockGen::GetClockStateDiv2(int clk_idx, vluint8_t phase)
{
    if (clk_idx < num_clock)
        return ((p_clk_state[clk_idx] - phase) >> 1) & 1;
    else
        return (vluint8_t)0;
}

// Clock divided by 4, phase can be 0 (0 deg) - 7 (315 deg)
vluint8_t ClockGen::GetClockStateDiv4(int clk_idx, vluint8_t phase)
{
    if (clk_idx < num_clock)
        return ((p_clk_state[clk_idx] - phase) >> 2) & 1;
    else
        return (vluint8_t)0;
}

// Clock divided by 8, phase can be 0 (0 deg) - 15 (337.5 deg)
vluint8_t ClockGen::GetClockStateDiv8(int clk_idx, vluint8_t phase)
{
    if (clk_idx < num_clock)
        return ((p_clk_state[clk_idx] - phase) >> 3) & 1;
    else
        return (vluint8_t)0;
}

// Clock divided by 16, phase can be 0 (0 deg) - 31 (348.75 deg)
vluint8_t ClockGen::GetClockStateDiv16(int clk_idx, vluint8_t phase)
{
    if (clk_idx < num_clock)
        return ((p_clk_state[clk_idx] - phase) >> 4) & 1;
    else
        return (vluint8_t)0;
}

// Clock divided by 32, phase can be 0 (0 deg) - 63 (354.375 deg)
vluint8_t ClockGen::GetClockStateDiv32(int clk_idx, vluint8_t phase)
{
    if (clk_idx < num_clock)
        return ((p_clk_state[clk_idx] - phase) >> 5) & 1;
    else
        return (vluint8_t)0;
}

// Get current time stamp
vluint64_t ClockGen::GetTimeStampPs()
{
    return curr_stamp_ps;
}

// Update clock states, compute next time stamp
void ClockGen::AdvanceClocks()
{
    curr_stamp_ps = next_stamp_ps;
    next_stamp_ps += max_stamp_ps;
    
    for (int i = 0; i < num_clock; i++)
    {
        if (p_clk_enable[i])
        {
            // Update clock state
            if (p_clk_stamp_ps[i] == curr_stamp_ps)
            {
                p_clk_state[i]++;
                p_clk_stamp_ps[i] += p_clk_hper_ps[i];
            }
            // Find next time stamp
            if (p_clk_stamp_ps[i] < next_stamp_ps)
            {
                next_stamp_ps = p_clk_stamp_ps[i];
            }
        }
    }
    
    // Show progress
    if ((curr_stamp_ps & 0x3FFFF) == 0)
    {
        printf("\r%lld us", curr_stamp_ps / 1000000 );
        fflush(stdout);
    }
}

// Return true if simulation is over
bool ClockGen::EndOfSimulation()
{
    return (curr_stamp_ps >= end_stamp_ps);
}