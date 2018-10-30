// Copyright 2011-2018 Frederic Requin
//
// Clock generator C++ object for Verilator
//

#ifndef _CLOCK_GEN_H_
#define _CLOCK_GEN_H_

#include "verilated.h"

class ClockGen
{
    public:
        // Constructor and destructor
        ClockGen(int num_clk, vluint64_t end_ps);
        ~ClockGen();
        // Methods
        void        NewClock(int clk_idx, vluint64_t period_ps, vluint64_t phase_ps);
        void        StartClock(int clk_idx);
        void        StartClock(int clk_idx, vluint64_t phase_ps);
        void        StopClock(int clk_idx);
        vluint8_t   GetClockStateDiv1(int clk_idx, vluint8_t phase); // phase : 0 - 1
        vluint8_t   GetClockStateDiv2(int clk_idx, vluint8_t phase); // phase : 0 - 3
        vluint8_t   GetClockStateDiv4(int clk_idx, vluint8_t phase); // phase : 0 - 7
        vluint8_t   GetClockStateDiv8(int clk_idx, vluint8_t phase); // phase : 0 - 15
        vluint8_t   GetClockStateDiv16(int clk_idx, vluint8_t phase); // phase : 0 - 31
        vluint8_t   GetClockStateDiv32(int clk_idx, vluint8_t phase); // phase : 0 - 63
        vluint64_t  GetTimeStampPs();
        void        AdvanceClocks();
        bool        EndOfSimulation();
    private:
        int         num_clock;      // Number of clocks
        vluint64_t  end_stamp_ps;   // End of simulation time stamp (in ps)
        vluint64_t  max_stamp_ps;   // Maximal time stamp step (in ps)
        vluint64_t  curr_stamp_ps;  // Current time stamp (in ps)
        vluint64_t  next_stamp_ps;  // Next time stamp (in ps)
        vluint64_t *p_clk_stamp_ps; // Clocks' time stamps (in ps)
        vluint64_t *p_clk_phase_ps; // Clocks' phase (in ps)
        vluint64_t *p_clk_hper_ps;  // Clocks' half period (in ps)
        vluint8_t  *p_clk_state;    // Clocks' states (0 - 255)
        bool       *p_clk_enable;   // Enabled clocks 
};

#endif /* _CLOCK_GEN_H_ */
