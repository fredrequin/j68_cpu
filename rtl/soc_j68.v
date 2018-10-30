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

module soc_j68
(
    input           rst,
    input           clk,
    input           clk_ena,
    // UART #0 (Load port)
    input           uart0_rxd,
    input           uart0_cts_n,
    input           uart0_dcd_n,
    output          uart0_txd,
    output          uart0_rts_n,
    // UART #1 (Terminal)
    input           uart1_rxd,
    input           uart1_cts_n,
    input           uart1_dcd_n,
    output          uart1_txd,
    output          uart1_rts_n
);
    // Initial SSP (for debug)
    parameter VECT_0 = 32'h0000413C;
    // Initial PC (for debug)
    parameter VECT_1 = 32'h0000011C;

    // Peripherals
    reg   [9:0] r_eclk;
    reg         r_ser_clk;
    reg   [3:0] r_ser_ctr;
    wire        w_uart0_txd;
    reg   [2:0] r_uart0_txd;
    reg   [2:0] r_uart0_rxd;
    wire        w_uart1_txd;
    reg   [2:0] r_uart1_txd;
    reg   [2:0] r_uart1_rxd;
    
    // Read/write controls
    reg         r_rden_dly;
    wire        w_cpu_rden;
    wire        w_cpu_wren;
    wire        w_cpu_rw_n;
    wire        w_ram_wren;
    wire        w_cpu_dtack;
    
    // Address bus
    wire  [1:0] w_cpu_bena;
    wire [31:0] w_cpu_addr;
    wire        w_cpu_vpa;
    
    // Data bus
    wire [15:0] w_cpu_wdata;
    reg  [15:0] w_cpu_rdata;
    wire [15:0] w_q_rom;
    wire [15:0] w_q_ram;
    reg   [7:0] r_q_acia;
    wire  [7:0] w_aciaa_data_out;
    wire        w_aciaa_data_en;
    wire  [7:0] w_aciab_data_out;
    wire        w_aciab_data_en;
    
    // Interrupts
    wire  [2:0] w_cpu_fc;
    reg   [2:0] r_cpu_ipl_n;
    wire        w_irq_1_n;
    wire        w_irq_2_n;
    wire        w_irq_3_n;
    
    // Debug
    reg  [31:0] r_dbg_regs[15:0];
    wire  [3:0] w_dbg_reg_addr;
    wire  [3:0] w_dbg_reg_wren;
    wire [15:0] w_dbg_reg_data;
    wire [15:0] w_dbg_sr_reg;
    wire [31:0] w_dbg_pc_reg;
    wire [31:0] w_dbg_usp_reg;
    wire [31:0] w_dbg_ssp_reg;
    wire [31:0] w_dbg_cycles;
    wire        w_dbg_ifetch;
    wire  [2:0] w_dbg_irq_lvl;
    
    // ========================================================================
    // 68000 core
    // ========================================================================
    
    cpu_j68 U_j68
    (
        .rst          (rst),
        .clk          (clk),
        .clk_ena      (clk_ena),
        .rd_ena       (w_cpu_rden),
        .wr_ena       (w_cpu_wren),
        .data_ack     (w_cpu_dtack),
        .byte_ena     (w_cpu_bena),
        .address      (w_cpu_addr),
        .rd_data      (w_cpu_rdata),
        .wr_data      (w_cpu_wdata),
        .fc           (w_cpu_fc),
        .ipl_n        (r_cpu_ipl_n),
        .dbg_reg_addr (w_dbg_reg_addr),
        .dbg_reg_wren (w_dbg_reg_wren),
        .dbg_reg_data (w_dbg_reg_data),
        .dbg_sr_reg   (w_dbg_sr_reg),
        .dbg_pc_reg   (w_dbg_pc_reg),
        .dbg_usp_reg  (w_dbg_usp_reg),
        .dbg_ssp_reg  (w_dbg_ssp_reg),
        .dbg_vbr_reg  (),
        .dbg_cycles   (w_dbg_cycles),
        .dbg_ifetch   (w_dbg_ifetch),
        .dbg_irq_lvl  (w_dbg_irq_lvl)
    );
    
    // Valid peripheral address
    assign w_cpu_vpa  = (^w_cpu_addr[14:13]) & w_cpu_addr[15];
    
    // Write control
    assign w_cpu_rw_n = w_cpu_rden & ~w_cpu_wren;
    assign w_ram_wren = w_cpu_wren & w_cpu_addr[14] & ~w_cpu_addr[15];
    
`ifdef verilator3

    import "DPI-C" function void m68k_trace_init
    (
        input int vect_0,
        input int vect_1
    );
    import "DPI-C" function void m68k_trace_fetch
    (
        input int sr,
        input int pc,
        input int usp,
        input int ssp,
        input int lvl
    );
    import "DPI-C" function void m68k_trace_regs
    (
        input int addr,
        input int wren,
        input int data
    );
    import "DPI-C" function void m68k_trace_read
    (
        input int fc,
        input int bena,
        input int addr,
        input int data
    );
    import "DPI-C" function void m68k_trace_write
    (
        input int fc,
        input int bena,
        input int addr,
        input int data
    );
    
    initial begin
        m68k_trace_init(VECT_0, VECT_1);
    end

    always@(posedge clk) begin : M68K_TRACE_CPP
    
        if (clk_ena) begin
            // Instruction fetch
            if (w_dbg_ifetch)
                m68k_trace_fetch({16'd0, w_dbg_sr_reg}, w_dbg_pc_reg, w_dbg_usp_reg, w_dbg_ssp_reg, {29'd0, w_dbg_irq_lvl});
            // Registers update
            m68k_trace_regs({28'd0, w_dbg_reg_addr}, {28'd0, w_dbg_reg_wren}, {16'd0, w_dbg_reg_data});
            // Read/write access
            if (w_cpu_dtack) begin
                if (w_cpu_rden)
                    m68k_trace_read({29'd0, w_cpu_fc}, {30'd0, w_cpu_bena}, w_cpu_addr, {16'd0, w_cpu_rdata});
                if (w_cpu_wren)
                    m68k_trace_write({29'd0, w_cpu_fc}, {30'd0, w_cpu_bena}, w_cpu_addr, {16'd0, w_cpu_wdata});
            end
        end
    end
    
    /*
    always@(posedge rst or posedge clk) begin : M68K_TRACE_VER
    
        if (rst) begin
            // D0 - D7
            r_dbg_regs[0]  <= 32'd0;
            r_dbg_regs[1]  <= 32'd0;
            r_dbg_regs[2]  <= 32'd0;
            r_dbg_regs[3]  <= 32'd0;
            r_dbg_regs[4]  <= 32'd0;
            r_dbg_regs[5]  <= 32'd0;
            r_dbg_regs[6]  <= 32'd0;
            r_dbg_regs[7]  <= 32'd0;
            // A0 - A7
            r_dbg_regs[8]  <= 32'd0;
            r_dbg_regs[9]  <= 32'd0;
            r_dbg_regs[10] <= 32'd0;
            r_dbg_regs[11] <= 32'd0;
            r_dbg_regs[12] <= 32'd0;
            r_dbg_regs[13] <= 32'd0;
            r_dbg_regs[14] <= 32'd0;
            r_dbg_regs[15] <= 32'd0;
        end
        else if (clk_ena) begin
            if (w_dbg_reg_wren[3]) r_dbg_regs[w_dbg_reg_addr][31:24] <= w_dbg_reg_data[15: 8];
            if (w_dbg_reg_wren[2]) r_dbg_regs[w_dbg_reg_addr][23:16] <= w_dbg_reg_data[ 7: 0];
            if (w_dbg_reg_wren[1]) r_dbg_regs[w_dbg_reg_addr][15: 8] <= w_dbg_reg_data[15: 8];
            if (w_dbg_reg_wren[0]) r_dbg_regs[w_dbg_reg_addr][ 7: 0] <= w_dbg_reg_data[ 7: 0];
            if (w_dbg_ifetch) begin
                $display("PC=%x (cycle=%d)",
                    w_dbg_pc_reg, w_dbg_cycles);
                $display("D0=%x %x %x %x %x %x %x %x",
                    r_dbg_regs[0],  r_dbg_regs[1],  r_dbg_regs[2],  r_dbg_regs[3],
                    r_dbg_regs[4],  r_dbg_regs[5],  r_dbg_regs[6],  r_dbg_regs[7]);
                $display("A0=%x %x %x %x %x %x %x %x",
                    r_dbg_regs[8],  r_dbg_regs[9],  r_dbg_regs[10], r_dbg_regs[11],
                    r_dbg_regs[12], r_dbg_regs[13], r_dbg_regs[14], r_dbg_regs[15]);
                $display("USP=%x SSP=%x SR=%x XNZVC=%b\n",
                    w_dbg_usp_reg, w_dbg_ssp_reg, w_dbg_sr_reg, w_dbg_sr_reg[4:0]);
            end
        end
    end
    */
    
`endif
    
    // ========================================================================
    // ACIA-A at $A000 / $A002 (Load port)
    // ========================================================================
    
    wire w_acia_a_cs = (w_cpu_addr[15:13] == 3'b101) ? w_cpu_bena[1] : 1'b0;
    
    acia_6850 U_acia_6850_a
    (
        // Clock and reset
        .reset    (rst),
        .clk      (clk),
        .e_clk    (r_eclk[3]),
        // CPU bus
        .cs       (w_acia_a_cs),
        .rw_n     (w_cpu_rw_n),
        .rs       (w_cpu_addr[1]),
        .data_in  (w_cpu_wdata[15:8]),
        .data_out (w_aciaa_data_out),
        .data_en  (w_aciaa_data_en),
        .irq_n    (w_irq_1_n),
        // I/Os
        .txclk    (r_ser_clk),
        .rxclk    (r_ser_clk),
        .rxdata   (r_uart0_rxd[2]),
        .cts_n    (uart0_cts_n),
        .dcd_n    (uart0_dcd_n),
        .txdata   (w_uart0_txd),
        .rts_n    (uart0_rts_n)
    );
    
    always@(posedge clk) r_uart0_rxd <= { r_uart0_rxd[1:0], uart0_rxd };
    always@(posedge clk) r_uart0_txd <= { r_uart0_txd[1:0], w_uart0_txd };
    
    assign uart0_txd = r_uart0_txd[2];
    
    // ========================================================================
    // ACIA-B at $C000 / $C002 (Terminal)
    // ========================================================================
    
    wire w_acia_b_cs = (w_cpu_addr[15:13] == 3'b110) ? w_cpu_bena[1] : 1'b0;
    
    acia_6850 U_acia_6850_b
    (
        // Clock and reset
        .reset    (rst),
        .clk      (clk),
        .e_clk    (r_eclk[3]),
        // CPU bus
        .cs       (w_acia_b_cs),
        .rw_n     (w_cpu_rw_n),
        .rs       (w_cpu_addr[1]),
        .data_in  (w_cpu_wdata[15:8]),
        .data_out (w_aciab_data_out),
        .data_en  (w_aciab_data_en),
        .irq_n    (w_irq_2_n),
        // I/Os
        .txclk    (r_ser_clk),
        .rxclk    (r_ser_clk),
        .rxdata   (r_uart1_rxd[2]),
        .cts_n    (uart1_cts_n),
        .dcd_n    (uart1_dcd_n),
        .txdata   (w_uart1_txd),
        .rts_n    (uart1_rts_n)
    );
    
    always@(posedge clk) r_uart1_rxd <= { r_uart1_rxd[1:0], uart1_rxd };
    always@(posedge clk) r_uart1_txd <= { r_uart1_txd[1:0], w_uart1_txd };
    
    assign uart1_txd = r_uart1_txd[2];
    
    // ========================================================================
    // Serial clock (60.000 MHz -> 2.000 MHz)
    // ========================================================================
    // The ACIAs can run at CLK/1 (2 Mb/s), CLK/16 (125 Kb/s) or CLK/64 (31.25 Kb/s)
    
    always@(posedge rst or posedge clk) begin : SERIAL_CLOCK
    
        if (rst) begin
            r_ser_ctr <= 4'd1;
            r_ser_clk <= 1'b0;
        end
        else begin
            // divide by 30 (15 cycles low, 15 cycles high)
            if (&r_ser_ctr) begin
                r_ser_ctr <= 4'd1;
            end
            else begin
                r_ser_ctr <= r_ser_ctr + 4'd1;
            end
            r_ser_clk <= r_ser_clk ^ (&r_ser_ctr);
        end
    end
    
    // ========================================================================
    // E clock (CPU clock divided by 10)
    // ========================================================================
    
    always@(posedge rst or posedge clk) begin : E_CLOCK
    
        if (rst) begin
            r_eclk <= 10'b0000000001;
        end
        else if (clk_ena) begin
            r_eclk <= { r_eclk[8:0], r_eclk[9] };
        end
    end
    
    // ========================================================================
    // Interrupts levels with priority encoding
    // ========================================================================
    
    always@(posedge rst or posedge clk) begin : IRQ_LEVEL
        reg [3:1] v_irq;
    
        if (rst) begin
            r_cpu_ipl_n <= 3'b111;
        end
        else if (clk_ena) begin
            v_irq[3] = ~w_irq_3_n;
            v_irq[2] = ~w_irq_2_n;
            v_irq[1] = ~w_irq_1_n;
            casez (v_irq)
                3'b??1 : r_cpu_ipl_n <= 3'b110; // Level #1 from ACIA-A
                3'b?10 : r_cpu_ipl_n <= 3'b101; // Level #2 from ACIA-B
                3'b100 : r_cpu_ipl_n <= 3'b100; // Level #3 (not used)
                3'b000 : r_cpu_ipl_n <= 3'b111; // No interrupts
            endcase
        end
    end
    
    assign w_irq_3_n = 1'b1;
    
    // ========================================================================
    // Data acknowledge
    // ========================================================================
    
    always@(posedge rst or posedge clk) begin : DTACK_GEN
    
        if (rst) begin
            r_rden_dly <= 1'b0;
            r_q_acia   <= 8'h00;
        end
        else begin
            // Read latencies
            r_rden_dly <= w_cpu_rden & ~w_cpu_vpa              // ROM/RAM read
                        | w_cpu_rden &  w_cpu_vpa & r_eclk[3]; // ACIAs read
            // Peripheral data bus
            if (r_eclk[3]) begin
                // MSB (even addresses)
                r_q_acia <= w_aciaa_data_out & {8{w_acia_a_cs}}  // ACIA-A
                          | w_aciab_data_out & {8{w_acia_b_cs}}; // ACIA-B
            end
        end
    end
    assign w_cpu_dtack = w_cpu_wren & ~w_cpu_vpa             // RAM write
                       | w_cpu_wren &  w_cpu_vpa & r_eclk[3] // ACIAs write
                       | r_rden_dly;                         // ROM/RAM, ACIAs read
    
    // ========================================================================
    // Read data multiplexing
    // ========================================================================
    
    always@(*) begin : RD_DATA_MUX
        case (w_cpu_addr[15:13])
            // $0000 - $1FFF : 8KB ROM
            3'b000 : w_cpu_rdata = w_q_rom;
            // $2000 - $3FFF : 8KB ROM
            3'b001 : w_cpu_rdata = w_q_rom;
            // $4000 - $5FFF : 8KB RAM
            3'b010 : w_cpu_rdata = w_q_ram;
            // $6000 - $7FFF : 8KB RAM
            3'b011 : w_cpu_rdata = w_q_ram;
            // $8000 - $9FFF : Empty
            3'b100 : w_cpu_rdata = 16'h0000;
            // $A000 - $BFFF : ACIA-A
            3'b101 : w_cpu_rdata = { r_q_acia, 8'h00 };
            // $C000 - $DFFF : ACIA-B
            3'b110 : w_cpu_rdata = { r_q_acia, 8'h00 };
            // $E000 - $FFFF : Empty
            3'b111 : w_cpu_rdata = 16'h0000;
        endcase
    end
    
    // ========================================================================
    // 16 KB ROM at $0000 - $3FFF
    // ========================================================================
    
    onchip_rom
    #(
        .ADDR_WIDTH    (14),
        .INIT_FILE_MEM ("rom_vubug.mem"),
        .INIT_FILE_MIF ("rom_vubug.mif")
    )
    U_onchip_rom
    (
        .clock         (clk),
        .address       (w_cpu_addr[13:1]),
        .q             (w_q_rom)
    );
    
    // ========================================================================
    // 16 KB RAM at $4000 - $7FFF
    // ========================================================================
    
    onchip_ram
    #(
        .ADDR_WIDTH    (14)
    )
    U_onchip_ram
    (
        .clock         (clk),
        .wren          (w_ram_wren),
        .byteena       (w_cpu_bena),
        .address       (w_cpu_addr[13:1]),
        .data          (w_cpu_wdata),
        .q             (w_q_ram)
    );

endmodule

