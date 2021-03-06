;                 VUBug:  AN M68000 MONITOR PROGRAM
; 
; I.  Introduction.
; 
;      VUBug is a primitive single user monitor program designed
; to interface the user to the "Raymatic" M68000 development board
; designed by Raymond Carr at Vanderbilt University in 1988.  The
; monitor program itself was originally written by Edward M. Carter
; also while at Vanderbilt in 1983.  This documentation relates to
; the 1988 version of the program, about two thirds of which is new.
; The new stuff was added by Russell G. Brown, then of Vanderbilt, but
; lately of Cornell Computer Science.  It allows the user to perform
; such operations as are necessary to develop and debug M68000
; assembly programs in conjunction with a host computer running
; an M68000 assembler which is capable of generating object code in
; the Motorola S-record format.  Some functions provided by VUBUG
; are load from host, dump memory, disassemble memory, and run at
; address.  Feel free to distribute this source and documentation,
; but make sure that the copyright and like information stays on it.
; Also, please make sure that any modified version of this program
; which you may distribute is obviously marked as being modified.
; 
; 
; II.  Running VUBug
; 
;      VUbug comes up running as soon as power is applied to the
; system.  It asserts its presence by printing the following
; message:
; 
;      M68000 Monitor VUBug Version 4.0 27 April, 1988
; 
; 
;      !_
; 
; If there is anything wrong with the system RAM, it will instead
; respond
; 
;      RAM Error!!!!
; 
; Assuming that a RAM error doesn't happen, you can now begin
; entering commands.
; 
; 
; III.  Getting Started
; 
;      The first thing that you will want to do is to load and
; execute an assembly language program using VUBug.  The following
; is an example interactive execution session:
; 
; 1.   Turn on the system.  The VUBug boot message prints at the
;      terminal.
; 2.   Type 'e'.  VUBug responds "Terminal Mode:".
; 3.   Log into the host system.  Enter vi and type in the
;      following program:
; 
;               org     $4400
;               move.l  #$00000004,d0
;               movea.l #$000019ca,a3
;               adda.w  d0,a3
;               move.l  a3,d0
;               trap    #$06
;               trap    #$0
;               end
; 
;           4.   Write and quit from vi.  Assemble the program by
; typing
; 
;               mas68k -l <progname>.
; 
;      where progname is the name of your sample program. 5.
; Examine the listing file produced by mas68k to see the source
;      and object code together.  The listing file is called
;      <progname.l>.
; 6.   Type 'cat <progname.o>' but DO NOT! type a carriage return.
; 7.   type ctrl-L.  VUBug will exit terminal mode, feed a
;      carriage return to the host, and accept an Srec format object
;      file.
; 8.   You are now back in VUBug.  Type 'a 4400'.  You will see an
;      assembly listing which is equivalent to your source code,
;      except that it has values substituted for all labels.  There
;      will be a number of garbage lines following the program.
;      disregard these.
; 9.   Type 'g 4400'.  This is the command meaning "go at $4400".
;      VUBug responds with the following:
; 
;               Program:
; 
;               000019ce
;               !
; 
;      This is approximately how all debugging sessions should
; begin.  Once you have become more familiar with VUBug, you will
; learn shortcuts and enhancements, but the commands already used
; will serve for a start.
; 
; 
; IV.  VUBug Commands
; 
;      This section contains the full, alphabetic listing of the
; commands provided in VUBug.  For information on how to get help
; for commands while in VUBug, see the section on 'h'.
; 
; 
; 
;      A - Assembly Listing
; 
;      A provides a source code listing of memory locations
;      specified in one of the following ways:
; 
;               A<cr>           List 20 instructions from last
;                               examined address.
;               A xxxx          List 20 instructions from address
;                               xxxx.
;               A xxxx,yyyy     List from xxxx to yyyy.
; 
;      B - Set/Remove Breakpoints
; 
;      B permits the setting and removing of breakpoints in a user
;      program.  B is invoked as follows:
; 
;               B<cr>           List all breakpoints.
;               B+xxxx          Add a breakpoint at address xxxx.
;               B-xxxx          Remove a breakpoint at xxxx.
;               B#              Remove all breakpoints.
; 
; 
; 
;      C - Copy Memory
; 
;      C allows the copying of a data block from one location to
;      another.  It is called using:
; 
;               C xxxx=yyyy,zzzz.
; 
;      This copies memory from a block which starts at yyyy and
;      ends at zzzz to a block starting at xxxx.  NOTE:  the copy
;      routine works from bottom to top.  Therefore care must be
;      taken when copying between blocks that share address space.
; 
; 
; 
;      D - Dump Memory
; 
;      D is used to provide a hex dump of memory.  Memory is
;      printed out in lines consisting of an address, 16 hex
;      values, and the ascii representation of such of those
;      values as have printable characters.  The format for
;      calling D is as follows:
; 
;               D<cr>           Dump 64 bytes from last examined
;                               location.
;               D xxxx          Dump 64 bytes from xxxx.
;               D xxxx,yyyy     Dump bytes from xxxx to yyyy.
; 
; 
; 
;      E - Enter terminal emulator mode
; 
;      When E is entered, VUBug enters a passthrough mode in which
;      any key entered at the keyboard is passed through to the
;      host, and vice versa.  This is true for all characters
;      except for ctrl-X, which causes VUBug to exit terminal
;      emulator mode, and ctrl-L, which is the same as ctrl-X,
;      except that it causes VUBug to enter load mode.  E is
;      invoked as follows:
; 
;               E<cr>
; 
;      G - Start user program
; 
;      G is the VUBug command to start a user program running.  A
;      user program which is properly designed to end will have as
;      its last executed line
; 
;               trap    #$00
; 
;      G is called in one of the following ways:
; 
;               G<cr>           Go from start address in the last
;                               executed L command.
;               <cr>            Same as G<cr>.
;               G xxxx          Go from address xxxx.
; 
; 
; 
;      H - Print help messages.
; 
;      H is used to print a simple message (consisting mostly of
;      instruction syntax) to the terminal.  It is called with:
; 
;               H<cr>           Prints a list of commands for
;                               which help is available.
;               Hx              Prints the long help message for
;                               command x.  If x is nonexistant,
;                               Hx acts like H<cr>.
; 
; 
; 
;      L - Load user program from host
; 
;      L causes VUBug to accept an S-record format object file
;      from the host.  It is called in one of the following ways:
; 
;               L<cr>           Load from host with no offset.
;               ctrl-L          Same as L<cr> but invoked from
;                               emulator mode.
;               L xxxx          Load from host with offset xxxx.
; 
;      M - Enter memory update mode
; 
;      M invokes a submode of VUBug in which modifications to
;      memory locations can be made.  M is invoked as follows:
; 
;               M<cr>           Start memory mode.
;               M xxxx          Start memory mode at xxxx.
; 
;      Memory mode subcommands are the following:
; 
;               .xxxx           Set pointer to location xxxx.
;               =xx             Update current location to xx.
;               ,xx             Increment pointer, then update.
;               +               Increment pointer.
;               -               Decrement pointer
;               <cr>            Print current pointer and value.
; 
;      Typing any other character in memory update mode causes an
;      exit back into VUBug proper.
; 
; 
; 
;      P - Prototype commands in RAM
; 
;      P allows the user to create new command subroutines in RAM
;      and call them without having to burn new ROMs.  This is
;      significant in that ordinarily user programs cannot make
;      use of the interrupt routines and other subroutines
;      provided in VUBug.  P is set up to allow a user routine to
;      make use of these subroutines.  It is invoked as follows:
; 
;               Px xxxx         Load address xxxx for prototype
;                               command x.
;               Px<cr>          Execute prototype command x.
; 
;      Note that x must be a 1, 2, or 3.
; 
;      R - Enter register examine/update mode
; 
;      R invokes a submode of VUBug in which registers may be
;      examined and changed.  It is called in the following way:
; 
;               R<cr>           Start register mode.
;               R xx            Start mode at register xx,
;                               where xx is one of:
;                                       SR/_sr - status register,
;                                       PC/_pc - program counter,
;                                       dx - data register 0 - 7,
;                                       ax - address reg. 0 - 7.
; 
;      Register examine/update commands are as follows:
; 
;               .xx             Set pointer to register xx.
;               =xxxxxxxx       Set current register to xxxxxxxx.
;               <cr>            Print all registers.
; 
;      Any other character entered in register submode causes an
;      exit to VUBug.
; 
; 
; 
;      S - Single step mode
; 
;      In single step mode, a Go command causes VUBug to execute a
;      single instruction and then return to the prompt, allowing
;      registers to be examined and changed between instructions.
;      S is called in one of two ways:
; 
;               S+              Turn on single step mode.
;               S-              Turn off single step mode.
; 
; 
; 
;      T - Trace mode
; 
;      In trace mode, a Go command causes VUBug to execute a
;      program, printing out the PC after each instruction.  This
;      permits tracing of a program's path.  It is called as
;      follows:
; 
;               T+              Turn on trace mode.
;               T-              Turn off trace mode. V.
; 
;      U - Upload user program from terminal
; 
;      U allows VUBug to upload an S-record format object file
;      from the terminal.  This allows the user to connect the
;      68000 board to a microcomputer, using it as both terminal
;      and host.  Upload is invoked with one of the following
;      commands:
; 
;               U<cr>           Upload from terminal with no offset.
;               U xxxx          Upload from terminal with offset xxxx.
; 
; 
; V.   Troubleshooting
; 
;      There is not a whole lot that can go wrong with VUBug.
; Most of the possible difficulties actually have their roots in
; hardware.  If a RAM error is indicated at boot-up time, then one
; of the system RAM chips needs replacing.  If no boot-up message
; is printed, then something is wrong with one of the following:
; the terminal, the terminal cable, the ACIAs on the development
; board, the system RAM, or the VUBug ROM.
; 
;      If an error is found in VUBug's performance, the thing to
; do is to document carefully when and where the bug appears, and
; report the problem to the nearest digital electronics professor.
; 
; 
; VI.  Caveats
; 
;      A number of things should be taken into account when using
; VUBug.  Most of these have to do with the memory map.  Number
; one is that hitting the reset button invokes the RAM test program
; which CLEARS THE RAM!  For this reason, ctrl-C should be used to
; recover control from a lost program.
; 
;      The memory map for the board looks like this:
; 
;               0000 - 3FFF     System ROM
;               4000 - 43FF     System RAM
;               4400 - 7FFF     User RAM
;               8000 - 803E     PI/T (68230) registers EVEN ONLY!
;               A000            Load Port Status Register
;               A002            Load Port Data Register
;               C000            Terminal Port Status Register
;               C002            Terminal Port Data Register
; 
;      Note that the PI/T and ACIA registers are on even only
; locations.  Attempting to write to a peripheral chip on an odd
; location will lock up the system.  Similarly, writing to system
; RAM can cause unexpected results, up to and including locking
; up the system.
; 
; VII. Conclusion
; 
;      VUBug 4.0, mas68k, and the Raymatic development board form
; an effective development environment for M68000 assembly
; language programs.  While they cannot substitute for
; professional development/analysis systems, it is nevertheless
; possible to complete considerable software endeavors with a
; reasonable minimum of difficulty.
; 
; ----------------------------CUT HERE-------------------------------------------
; 
;       NOTES   : PORTED TO PC BY DAVE GOODMAN
;               : PORTED TO RAYMATIC 68K BOARD BY RUSSELL G. BROWN
;       ASSEMBLE: mas68k -l vubug.68k
;               : ASSEMBLER WILL TAKE FILE vubug.68k AND
;               : WILL CREATE vubug.o, vubug.l
;       VER 3.0 : VUBUG VER 3.0 PORTEd TO PC FOR ASSEMBLE USING a68K 9/84
;       VER 3.1 : VUBUG VER 3.1 FIXED FOR VU68K BOARD 10/86
;       VER 4.0 : VUBUG VER 4.0 PORTED TO RAYMATIC 68K BOARD 4/88
;*******************************************
;*                                         *
;********         V U B U G         ********
;*                                         *
;* Copyright (C) 1983, 1988                *
;*               Vanderbilt Univ.          *
;*               Comp. Sci. dept.          *
;*               PO Box 1679               *
;*               Station B                 *
;*               Nashville, Tenn.          *
;*                          37235          *
;*                                         *
;*       author:                           *
;*              Edward M. Carter           *
;*                                         *
;*******************************************
;*                                         *
;* This software was prepared for distri-  *
;* bution by Russell G. Brown.  Please     *
;* note that it is being distributed at    *
;* the request of several readers of the   *
;* usenet newsgroup comp.sys.m68k.  It has *
;* no warranty of any sort, at all.  I     *
;* think that the code is fairly self      *
;* explanatory.  Good luck in modifying    *
;* it to work on whatever application you  *
;* may have.                               *
;*******************************************
;*                                         *
;* although the information contained here-*
;* in, as well as any information provided *
;* relative thereto, has been carefully re-*
;* viewed and is believed correct, Vander- *
;* bilt University assumes no liability    *
;* arising out of its application or use,  *
;* neither does it convey any license under*
;* its patent rights nor the rights of     *
;* others.                                 *
;*                                         *
;*******************************************
;*                                         *
;* The commands supported are as follows:  *
;*                                         *
;*         m - examine/update memory       *
;*         l - load program from host      *
;*         u - load program from terminal  *
;*         d - display blocks of memory    *
;*         t - single-step a program       *
;*         s - single-step                 *
;*         g - start a user mode program   *
;*         <cr> - short g command          *
;*         b - set/remove breakpoints      *
;*         r - examine/update registers    *
;*         p - prototype commands          *
;*         e - terminal emulator mode      *
;*         c - copy memory blocks          *
;*         x - print help messages         *
;*                                         *
;* Sub-command under each of these commands*
;* are shown in the source code for each   *
;* command.                                *
;*                                         *
;*******************************************

;
; Queue structure
;
head    equ     $0000
tail    equ     $0002
count   equ     $0004
queue   equ     $0006

;
; Breakpoint structure
;
instr   equ     $0000
iloc    equ     $0002

;
;Terminal port
;
ttyst   equ     $0000c000
ttyd    equ     $0000c002

;
;Load port
;
lpst    equ     $0000a000
lpd     equ     $0000a002

;
; The following is the exception vector
; table for the monitor. There should be
; no further "org"s to address contained
; herein as this will destroy the vector
; for iterrupts, breakpoints...
;
        org     $00000000               ;Reset Vector
        dc.l    stack                   ;system stack
        dc.l    start                   ;initial pc
        dc.l    abhlr                   ;bus error
        dc.l    abhlr                   ;address error
        dc.l    bhlr                    ;illegal instruction vector
        dc.l    ghlr                    ;zero divide
        dc.l    ghlr                    ;chk
        dc.l    ghlr                    ;trapv
        dc.l    phlr                    ;privileged instruction trap
        dc.l    thlr                    ;trace handler
        dc.l    bhlr                    ;emulator trap 1010
        dc.l    bhlr                    ;emulator trap 1111
        org     $0000003C
        dc.l    ghlr                    ;uninitialized interrupt
        org     $00000060
        dc.l    ghlr                    ;spurious interrupt
        dc.l    lpint                   ;download-line vector
        dc.l    inint                   ;terminal vector
        dc.l    uav3                    ;user auto-vectors
        dc.l    uav4
        dc.l    uav5
        dc.l    uav6
        dc.l    uav7
        dc.l    texit                   ;TRAP #0 : exit
        dc.l    tgetb                   ;TRAP #1 : getb
        dc.l    tgetw                   ;TRAP #2 : getw
        dc.l    tgetl                   ;TRAP #3 : getl
        dc.l    twrtb                   ;TRAP #4 : wrtb
        dc.l    twrtw                   ;TRAP #5 : wrtw
        dc.l    twrtl                   ;TRAP #6 : wrtl
        dc.l    tgetc                   ;TRAP #7 : getc
        dc.l    twrts                   ;TRAP #8 : wrts
        dc.l    twrtc                   ;TRAP #9 : wrtc
        dc.l    tcrlf                   ;TRAP #10 : crlf
utrpb:  dc.l    utrapb                  ;user trap vectors
utrpc:  dc.l    utrapc
utrpd:  dc.l    utrapd
utrpe:  dc.l    utrape
utrpf:  dc.l    utrapf

;+++++++++++++++++++++++++++++++++++++++++
;                                        +
;            Start of monitor            +
;                                        +
;+++++++++++++++++++++++++++++++++++++++++

        org     $000000C0
        
csc     equ     $1b45           ;clear screen (h-19)
cr      equ     $0d
lf      equ     $0a
nul     equ     $00

howdy:  dc.w    csc
        dc.b    "M68000 Monitor VUBUG "
        dc.b    "Version 4.0 11 Aug 88"
rnn0:   dc.b    cr,lf,lf,nul
bcomm:  dc.b    ": Bad Command"
        dc.b    cr,lf,nul
;
; These are seven user interrupt vectors
; which must remain at address $0100.
; Please ensure that they do
;
vect1:  dc.l    userv1
vect2:  dc.l    userv2
vect3:  dc.l    userv3
vect4:  dc.l    userv4
vect5:  dc.l    userv5
ssri:   dc.w    $2000           ;supervisor SR
ssrn:   dc.w    $2700           ;same w/o interrupts
prmp:   dc.b    cr,lf
        dc.b    '!'             ; command promdt
        dc.b    nul
start:  move.b  #$03,ttyst              ;setup ports
        move.b  #$03,lpst
        move.b  #$15,ttyst
        move.b  #$15,lpst
        move.w  #$ffff,d0               ;load $ffff for first memory test
        movea.w #$4000,a0               ;start at $4000
        move.w  #$1fff,d2               ;$2000 words of ram
;        move.w  #$1f,d2                 ;$2000 words of ram
mt1:    move.w  d0,(a0)                 ;store value
        move.w  (a0)+,d1                ;load it back
        cmp.w   d0,d1
        bne     memerr                  ;if not the same, memory error.
        dbf     d2,mt1
        move.w  #$0000,d0               ;load $0000 for second mem test
        movea.w #$4000,a0
        move.w  #$1fff,d2
;        move.w  #$1f,d2
mt2:    move.w  d0,(a0)
        move.w  (a0)+,d1
        bne     memerr                  ;if not zero, memory error.
        dbf     d2,mt2
        bra     gwan
memerr: lea     memnot,a0               ;RAM doesn't work right.
        bsr     writs
        bra     gwan
memnot: dc.b    "RAM ERROR!!!!"
        dc.b    cr,lf,nul
gwan:   lea     ibuff,a1                ;setup buffers
        move.w  #$0000,head(a1)
        move.w  #$ffff,tail(a1)
        move.w  #$0000,count(a1)
        lea     lbuff,a1
        move.w  #$0,head(a1)            ;set queue for lp
        move.w  #$ffff,tail(a1)
        move.w  #0,count(a1)
        move.w  #0,exam                 ;initialize control variables
        move.b  #0,ctrls
        move.b  #0,bkptf
        moveq   #$4,d0                  ;clear breakpoint table
        lea     bktab,a1
slp:    move.l  #0,(a1)+
        dbf     d0,slp
        move.w  #0,_sr                  ;clear register save area
        move.l  #$10,d0
        lea     _pc,a0
slp1:   move.l  #0,(a0)+
        dbf     d0,slp1
        lea     ustck,a0                ;set user stack pointer
        move.l  a0,ar7
        lea     sarea,a0                ;clear system stack
        moveq   #$3f,d0
slp2:   move.l  #0,(a0)+
        dbf     d0,slp2
done:   move.w  ssri,sr                 ;enable interrupts at CPU
        lea     howdy,a0                ;say hello
        bsr     writs
        move.b  #$95,ttyst              ;enable interrupts from ports
        move.b  #$95,lpst
        bset    #$00,echo               ;turn on terminal echo
        bra     comm                    ;enter command loop
;
; Generalized write facility writes 1 byte
; passed in d0 to tty.
;
writ:   btst    #0,ctrls                ;Is ctrl-s active
        beq     cwrit                   ;no, so write it
        stop    #$2000                  ;yes, so wait on next character
        bra     writ                    ;when awakened try to echo
cwrit:  move.b  d0,ttyd                 ;write the character to port
writa:  move.b  ttyst,d0                ;sample control register till done
        btst    #$1,d0
        beq     writa
        rts
;
; Generalized write facility writes 1 byte
; passed in d0 to serial port.
;
writu:  move.b  d0,lpd                  ;write it
writp:  move.b  lpst,d0                 ;wait for completion
        btst    #$1,d0
        beq     writp
        rts
;
; Generalized routine to write a string which
; must terminate in a null
;
writs:  move.b  (a0)+,d0                ;a0 is address of string
        beq     dwrts
        bsr     writ
        bra     writs
dwrts:  rts
;
;Generalized routine to write
;a word, byte or long word.
;
writb:  move.w  #$1,t1                  ;t1 is the number of bytes
        bra     wr
writw:  move.w  #$3,t1
        bra     wr
writl:  move.w  #$7,t1
wr:     movem.l d1/d2/a0/a6,-(a7)       ;save registers d1,d2,a0,a6
        move.w  t1,d2                   ;set count
        move.b  #$00,t5+1               ;set a null at end
        lea     t5+1,a6                 ;use temps as a stack
alp:    move.b  d0,d1                   ;make each hex digit a
        and.b   #$0f,d1                 ;writable ascii byte
        cmp.b   #$0a,d1                 ;check for abcdef
        blt     or3
        or.b    #$40,d1
        sub.b   #$09,d1
        bra     m1
or3:    or.b    #$30,d1                 ;set high-order bits
m1:     move.b  d1,-(a6)                ;put on stack
        lsr.l   #$4,d0                  ;get next hex digit
        dbf     d2,alp
        movea.w a6,a0                   ;write the stack with writs
        bsr     writs
        movem.l (a7)+,d1/d2/a0/a6       ;restore registers d1,d2,a0,a6
        rts
;
; Interrupt handler for the keyboard
; interrupt. It simply stashes the input
; character in a buffer pointed to by a1.
;
inint:  move.w  ssrn,sr                 ;disable interrupts
        movem.l d0-d2/a1/a2,-(a7)       ;save registers d0,d1,d2,a1,a2
        move.b  ttyd,d1                 ;get the character
        andi.b  #$7f,d1                 ;mask out the parity, if any
        btst    #$3,bkptf               ;In emulator mode ?
        beq     incmp                   ;No, so continue
        cmp.b   #$0c,d1                 ;ctrl-l ?
        beq     inld                    ;yes, so load
        cmp.b   #$18,d1                 ;No, is it a ctrl-x ?
        bne     inwru                   ;No, so write it
inld:   bclr    #$3,bkptf               ;Exit emulator mode
        lea     emudn,a1                ;set up return
        move.l  a1,$16(a7)              ;put return deep in stack
        cmp.b   #$0c,d1                 ;ctrl-l ?
        bne     out                     ;No
        bra     incmp                   ;check for ctrl-s or q
inwru:  move.b  d1,d0                   ;write to host
        bsr     writu
        bra     out
incmp:  cmp.b   #$03,d1                 ;check for ctrl-c
        beq     rstrt
        cmp.b   #$13,d1                 ;check for ctrl-s
        bne     ctrlq
        move.b  #$1,ctrls
        bra     out
ctrlq:  cmp.b   #$11,d1                 ;check for ctrl-q
        bne     c1
        move.b  #$0,ctrls
        bra     out
c1:     lea     ibuff,a1                ;get buffer address
        cmpi.b  #$10,count(a1)          ;overflow ?
        blt     cont                    ;No
        bra     out                     ;Yes, so ignore character
cont:   addq.b  #$1,tail(a1)            ;add chacter to buffer
        addq.b  #$1,count(a1)           ;add 1 to count
        andi.b  #$0f,tail(a1)           ;modulo-16
        move.w  tail(a1),d2             ;get offset of new entry
        ror.w   #$08,d2                 ;in lower 8 bits of d2
        andi.w  #$ff,d2                 ;mask off what's left
        lea     queue(a1),a1            ;get address of queue
        move.b  d1,$0(a1,d2.w)          ;move byte into buffer
        btst    #$00,echo               ;is the echo turned on?
        beq     out                     ;if not, skip the echo,
        move.b  d1,d0                   ;else setup for echo
        bsr     writ
out:    movem.l (a7)+,d0-d2/a1/a2       ;reset registers d0,d1,d2,a1,a2
        rte
;
; Interrupt handler for the load port.
; It stashes the character in the buffer
; pointed to by a1.
;
lpint:  move.w  ssrn,sr                 ;same as above but less complex
        movem.l d0-d2/a1/a2,-(a7)       ;registers d0,d1,d2,a1,a2
        move.b  lpd,d1
        andi.b  #$7f,d1
        btst    #$3,bkptf
        beq     lplea
        move.b  d1,d0                   ;echo for emulator mode
        bsr     writ
        bra     lout
lplea:  lea     lbuff,a1                ;queue a character
        cmpi.b  #$10,count(a1)
        blt     lcont
        bra     out
lcont:  addq.b  #$1,tail(a1)
        addq.b  #$1,count(a1)
        andi.b  #$0f,tail(a1)
        move.w  tail(a1),d2
        ror.w   #$08,d2
        andi.w  #$ff,d2
        lea     queue(a1),a1
        move.b  d1,$0(a1,d2.w)
lout:   movem.l (a7)+,d0-d2/a1/a2       ;regs d0,d1,d2,a1,a2
        rte
;
; Lgch - get a character from the serial port
; queue. If none available then wait for one
;
;
lgch:   movem.l d2/a1/a2,-(a7)          ;save registers d2,a1,a2
lagn:   ori.w   #$0700,sr               ;diable interrupts
        lea     lbuff,a1                ;point at buffer
        move.w  count(a1),t1            ;see if there is a cahracter
        beq     lwait                   ;No, so wait
        move.w  head(a1),d2             ;Yes, find it and update
        ror.w   #$08,d2
        andi.w  #$00ff,d2
        addq.b  #$1,head(a1)
        subq.b  #$1,count(a1)
        andi.b  #$0f,head(a1)
        lea     queue(a1),a1            ;Return character
        move.b  $0(a1,d2.w),d0
        andi.w  #$f8ff,sr               ;enable interrupts and
        movem.l (a7)+,d2/a1/a2          ;regs d2,a1/a2
        rts
lwait:  stop    #$2000
        bra     lagn
;
; Rstrt - restart from control c
;
rstrt:  movem.l (a7)+,d0/d1/a1/a2       ;rest regs d0,d1,a1,a2 frm intrpt hndlr
        movem.l d0-d7/a0-a7,dr0         ;save registers d0-a7
        move.l  usp,a0                  ;save user stack pointer
        move.l  a0,ar7
        move.w  (a7)+,_sr               ;save status register from stack
        move.l  (a7)+,_pc               ;save program counter from stack
        bset    #$00,echo               ;turn on terminal echo
        pea     comm                    ;fake a return to command loop
        move.w  ssri,-(a7)              ;fake a new status register
        rte
;
; Getch - get a character from the input
; queue. If none available then wait for it
;
getch:  movem.l d2/a1/a2,-(a7)          ;same as lgch above d2,a1,a2
tryag:  ori.w   #$0700,sr
        lea     ibuff,a1
        move.w  count(a1),t1
        beq     wait
        moveq   #$0,d0
        move.w  head(a1),d2
        ror.w   #$08,d2
        andi.w  #$00ff,d2
        addq.b  #$1,head(a1)
        subq.b  #$1,count(a1)
        andi.b  #$0f,head(a1)
        lea     queue(a1),a1
        move.b  $0(a1,d2.w),d0
        andi.w  #$f8ff,sr
        movem.l (a7)+,d2/a1/a2          ;regs d2,a1,a2
        rts
wait:   stop    #$2000
        bra     tryag
;
; CRLF - write a carriage return and
; line feed.
;
cf:     dc.b    cr,lf,nul,nul
crlf:   lea     cf,a0
        bsr     writs
        rts
;
; Generalized number fetcher
;
getb:   move.w  #$1,t1                  ;t1 is byte count
        bra     gb
getw:   move.w  #$3,t1
        bra     gb
getl:   move.w  #$7,t1
gb:     movem.l d1/d2,-(a7)             ;save registers d1,d2
        move.w  t1,d2
        moveq   #$0,d1
blp:    jsr     (a0)                    ;a0 is address of which..
                                        ;routine to use for getting, i.e.
                                        ;serial or terminal port
        cmp.b   #$3a,d0                 ;check for abcdef
        blt     n1
        add.b   #$09,d0
n1:     and.b   #$0f,d0
        asl.l   #$4,d1                  ;place in next hex didgit
        or.b    d0,d1
        dbf     d2,blp
        move.l  d1,d0                   ;setup return in d0
        movem.l (a7)+,d1/d2             ;restore registers d1,d2
        rts
;
; command interpreter
;
ctab:   dc.w    $4d00           ;m - memory update
        dc.w    mem
        dc.w    $4c00           ;l - load from host (S-format)
        dc.w    load
        dc.w    $0c00           ;ctrl-l - load from host (S-format)
        dc.w    lnoof
        dc.w    $5500           ;u - upload program from terminal port
        dc.w    uload
        dc.w    $4400           ;d - dump contents of memory
        dc.w    dump
        dc.w    $5300           ;s - single step
        dc.w    singl
        dc.w    $5400           ;t - trace a program's path
        dc.w    trace
        dc.w    $4700           ;g - start user program
        dc.w    go
        dc.w    $0d00           ;<cr> - short g command
        dc.w    ggo
        dc.w    $4500           ;e - enter terminal emulator mode
        dc.w    emul
        dc.w    $4200           ;b - set/remove breakpoints
        dc.w    bkpt
        dc.w    $4300           ;c - copy memory blocks
        dc.w    copy
        dc.w    $5200           ;r - display/modify registers
        dc.w    regs
        dc.w    $5000           ;p - prototype commands
        dc.w    proto
        dc.w    $4800           ;h - display help messages
        dc.w    help
        dc.w    $4100           ;a - assembly listing
        dc.w    assem
;
; Structure of each entry is command
; (com) and address of servicing routine
; (code)
;
com     =       $0
code    =       $2
comm:   lea     prmp,a0                 ;write prompt
        bsr     writs
        bsr     getch                   ;get command from buffer
        and.b   #$5f,d0                 ;make upper-case
        lea     ctab-4,a2               ;set-up search of ctab
        moveq   #$0f,d2                 ;count is one less
clp:    addq.w  #4,a2
        cmp.b   com(a2),d0
        dbeq    d2,clp
        bne     bad                     ;search fails
        movea.w code(a2),a2             ;get address for success
        jsr     (a2)                    ;go to it
        bra     comm                    ;loop back for next command
bad:    lea     bcomm,a0                ;say it's bad and return
        bsr     writs
        bra     comm
;
; Copy - Copy memory blocks
;
;***************************************
;*                                     *
;* Copy is invoked as follows:         *
;*                                     *
;*          c xxxx=yyyy,zzzz           *
;*                                     *
;* Copy locations yyyy thru zzzz to    *
;* locations xxxx and upward.          *
;*                                     *
;***************************************
;
cdmes:  dc.b    lf,cr
        dc.b    "Copied",0
ctom:   dc.b    " to ",0
cform:  dc.b    " for ",0
cbyt:   dc.b    " bytes",0
        dc.b    nul
copy:   bsr     getch                   ;get past blank
        lea     getch,a0                ;setup for terminal input
        bsr     getw                    ;get target address
        move.l  d0,d2                   ;save it
        movea.w d0,a2
        bsr     getch                   ;get past =
        bsr     getw                    ;get start address
        move.l  d0,d3                   ;save it
        movea.w d0,a3                   ;again
        bsr     getch                   ;get past ,
        bsr     getw                    ;get ending address
        sub.l   d3,d0                   ;calculate byte count
        move.l  d0,d4                   ;save it
        addq.b  #$1,d4
colp:   move.b  (a3)+,(a2)+             ;start moving
        dbf     d0,colp
        lea     cdmes,a0                ;say we're done
        bsr     writs
        move.l  d3,d0
        bsr     writw
        lea     ctom,a0
        bsr     writs
        move.l  d2,d0
        bsr     writw
        lea     cform,a0
        bsr     writs
        move.l  d4,d0
        bsr     writw
        lea     cbyt,a0
        bsr     writs
        rts
;
; Mem - memory update
;
;*******************************************
;*                                         *
;* Memory sub-commands are as follows:     *
;*                                         *
;*          m<cr> - start memory mode      *
;*          m xxxx - start m mode at loca- *
;*                     tion xxxx          *
;*          .xxxx - set pointer to location*
;*                  xxxx                   *
;*          =xx - update current location  *
;*                to xx                    *
;*          ,xx - increment location and   *
;*                update it to xx          *
;*          + - increment location         *
;*          - - decrement location         *
;*          <cr> - print current location  *
;*                 and value               *
;*                                         *
;*******************************************
;
mtab:   dc.w    $2e00           ;.
        dc.w    mdot
        dc.w    $3d00           ;=
        dc.w    mequ
        dc.w    $2c00           ;,
        dc.w    mcom
        dc.w    $2b00           ;+
        dc.w    mplu
        dc.w    $2d00           ;-
        dc.w    mmin
        dc.w    $0d00           ;<CR>
        dc.w    mloc
mmes:   dc.b    lf,lf,cr
        dc.b    "Memory Mode",0
mprmp:  dc.b    lf,cr,':',nul
meqm:   dc.b    " == ",0
mem:    bsr     getch                   ;get delimiter
        cmp.b   #$0d,d0                 ;if <cr> then enter m
        beq     mnoad
        lea     getch,a0                ;else get the address
        bsr     getw
        bra     mplp                    ;set the address
mnoad:  moveq   #$0,d0                  ;start with no address
mplp:   move.w  d0,exam                 ;set the address
        lea     mmes,a0                 ;load message
        bsr     writs
mlp:    lea     mprmp,a0                ;write memory prompt
        bsr     writs
        bsr     getch                   ;enter memory command loop
        moveq   #$5,d2                  ;set for search
        lea     mtab-4,a0
mmlp:   addq.w  #$4,a0                  ;search loop like comm
        cmp.b   (a0),d0
        dbeq    d2,mmlp
        bne     mexit                   ;exit if not found
        movea.w $2(a0),a0               ;get routine address
        jsr     (a0)                    ;go to it
        bra     mlp                     ;stay in memory loop
mexit:  rts
mdot:   lea     getch,a0                ;handle setting of address
        bsr     getw                    ;get address
        move.w  d0,exam                 ;set in p[ointer
        bsr     mloc                    ;print address and value
        rts
mequ:   lea     getch,a0                ;handle new value at pointer
        bsr     getb                    ;get new value
        movea.w exam,a0                 ;set address
        move.b  d0,(a0)                 ;move new value
        bsr     mloc                    ;write new value
        rts
mcom:   addq.w  #$1,exam                ;handle pointer increment by ,
        bsr     mequ                    ;write new address and value
        rts
mplu:   addq.w  #$1,exam                ;increment pointer
        bsr     mloc                    ;write val
        rts
mmin:   subq.w  #$1,exam                ;decrement pointer
        bsr     mloc
        rts
mloc:   bsr     crlf                    ;write address and value
        move.w  exam,d0                 ;write address
        bsr     writw
        lea     meqm,a0
        bsr     writs
        movea.w exam,a0
        move.b  (a0),d0                 ;write value
        bsr     writb
        rts
;
; Regs - Modify/examine registers
;
;***************************************
;*                                     *
;* Register subcommands are as follows:*
;*                                     *
;*      r<cr> - start register mode    *
;*      r xx - start r mode at register*
;*        xx. Where xx :               *
;*            SR/_sr - status register *
;*            PC/_pc - program counter *
;*            d0 - d7 - data registers *
;*            a0 - a7 - address regs.  *
;*     .xx - set pointer to register   *
;*     =xxxxxxxx - update current reg- *
;*                 ister to xxxxxxxx   *
;*     <cr> - print all registers      *
;*                                     *
;***************************************
;
rtab:   dc.w    $2e00           ;.
        dc.w    rdot
        dc.w    $3d00           ;=
        dc.w    requ
        dc.w    $0d00           ;<cr>
        dc.w    rall
rtab1:  dc.w    $cb00           ;internal name/offset
        dc.b    "SR"                    ;print name
        dc.w    $9c02
        dc.b    "PC"
        dc.w    $d006
        dc.b    "d0"
        dc.w    $d10a
        dc.b    "d1"
        dc.w    $d20e
        dc.b    "d2"
        dc.w    $d312
        dc.b    "d3"
        dc.w    $d416
        dc.b    "d4"
        dc.w    $d51a
        dc.b    "d5"
        dc.w    $d61e
        dc.b    "d6"
        dc.w    $d722
        dc.b    "d7"
        dc.w    $a026
        dc.b    "a0"
        dc.w    $a12a
        dc.b    "a1"
        dc.w    $a22e
        dc.b    "a2"
        dc.w    $a332
        dc.b    "a3"
        dc.w    $a436
        dc.b    "a4"
        dc.w    $a53a
        dc.b    "a5"
        dc.w    $a63e
        dc.b    "a6"
        dc.w    $a742
        dc.b    "a7"
rmes:   dc.b    lf,lf,cr
        dc.b    "Register Mode",0
rprmp:  dc.b    lf,cr,':',nul
reqm:   dc.b    " == ",0
regs:   bsr     getch                   ;get delimiter
        cmp.b   #$0d,d0                 ;if <cr> then start at sr
        beq     rnoad
        lea     getch,a0                ;else set for terminal input
        bsr     getb                    ;get register name
        bsr     raddr                   ;set address
        bra     rplp                    ;set register pointer
rnoad:  lea     rtab1,a3                ;set default pointer value
        move.w  a3,rexam
rplp:   lea     rmes,a0                 ;say hello
        bsr     writs
        bsr     rloc                    ;write starting loc value
rlp:    lea     rprmp,a0                ;write register prompt
        bsr     writs
        bsr     getch                   ;get command
        moveq   #$2,d2                  ;set for search
        lea     rtab-4,a0
rmlp:   addq.w  #$4,a0                  ;search
        cmp.b   (a0),d0
        dbeq    d2,rmlp
        bne     rexit                   ;exit if not found
        movea.w $2(a0),a0               ;found it so go to it
        jsr     (a0)
        bra     rlp                     ;go again
rexit:  rts
rdot:   lea     getch,a0                ;set register pointer
        bsr     getb
        bsr     raddr                   ;set input address
        bsr     rloc                    ;write register and value
        rts
requ:   lea     getch,a0                ;set new value
        movea.w rexam,a3
        moveq   #$0,d1                  ;clear d1
        move.b  $1(a3),d1               ;get offset
        beq     requs                   ;branch if sr is reg
        bsr     getl                    ;get new value
        lea     _sr,a4                  ;find save area offset
        adda.l  d1,a4                   ;add offset
        move.l  d0,(a4)                 ;move in new value
        bra     requr                   ;print it
requs:  bsr     getw                    ;same as above but for sr (word vs. long
        move.w  d0,_sr
requr:  bsr     rloc                    ;write new value
        rts
rall:   lea     rtab1-4,a3              ;write all registers
        moveq   #$11,d2                 ;set count
ralp:   addq.w  #$4,a3                  ;loop
        move.w  a3,rexam
        bsr     rloc
        dbf     d2,ralp
        rts
raddr:  move.w  #$11,d4                 ;find offset in save area
        lea     rtab1-4,a3
radlp:  addq.w  #$4,a3
        cmp.b   (a3),d0
        dbeq    d4,radlp
        bne     rexit
        move.w  a3,rexam                ;set register pointer
        rts
rloc:   bsr     crlf                    ;print register name and value
        movea.w rexam,a4
        move.b  $2(a4),d0               ;write name
        bsr     writ
        move.b  $3(a4),d0
        bsr     writ
        lea     reqm,a0
        bsr     writs
        moveq   #$0,d0
        move.b  $1(a4),d0               ;write value
        beq     rpsr                    ;branch if sr
        lea     _sr,a0                  ;find offset
        adda.l  d0,a0                   ;add offset
        move.l  (a0),d0                 ;move in new value
        bsr     writl
        bra     rrts
rpsr:   move.w  _sr,d0                  ;write sr value
        bsr     writw
rrts:   rts
;
; Load - Load data from host
;
;****************************************
;*                                      *
;* Load is invoked as follows:          *
;*                                      *
;*       l<cr> - load from host with no *
;*               offset                 *
;*       <ff> - same as l<cr> but used  *
;*              only exiting emulator   *
;*       l xxxx - load with offset xxxx *
;*                                      *
;****************************************
;
lmes:   dc.b    lf,cr
        dc.b    "Load...",0
slmes:  dc.b    lf,cr
        dc.b    "User PC == ",0
elmes:  dc.b    lf,cr
        dc.b    "Load done...",0
        dc.b    nul

load:   bsr     getch                   ;get delimiter
        cmp.b   #$0d,d0                 ;if <cr> then no offset
        beq     lnoof
        lea     getch,a0                ;get offset
        bsr     getw
        move.l  d0,_pc                  ;save load point for go command
        bra     ld1
lnoof:  move.l  #$0,_pc
ld1:    lea     lbuff,a1                ;point at lpbuff
        move.w  #$0,head(a1)            ;set queue for lp
        move.w  #$ffff,tail(a1)
        move.w  #$0,count(a1)
        lea     lmes,a0                 ;print starting message
        bsr     writs
        move.b  #$0d,d0                 ;load a <cr>
        bsr     writu                   ;send it to the host
        lea     lgch,a0                 ;set up for host load routine
llp:    jsr     (a0)                    ;get S
        cmp.b   #$53,d0
        bne     llp                     ;No - start over
        jsr     (a0)                    ;get 1 or 9
        cmp.b   #$39,d0                 ;9 - then done
        beq     ldone
        cmp.b   #$31,d0                 ;1 - then another record
        bne     llp
        bsr     getb                    ;get byte count
        move.l  d0,d1
        subq.b  #$4,d1                  ;remove count for check
        bsr     getw
        add.l   _pc,d0                  ;add offset
        movea.w d0,a1                   ;save starting address
lblp:   bsr     getb                    ;get actual data byte
        move.b  d0,(a1)+                ;move to memory
        dbf     d1,lblp                 ;loop for count
        bsr     getw                    ;gobble up check and crlf
        bra     llp                     ;try another record
ldone:  jsr     (a0)                    ;gobble up byte count
        jsr     (a0)
        bsr     getw                    ;get address from end macro
        add.l   _pc,d0                  ;add offset
        move.l  d0,d1                   ;save it
        move.l  d0,_pc                  ;set starting address for go
        move.w  #$0,_sr                 ;set status register
        move.l  #$10,d0
        lea     dr0,a1
lreg:   move.l  #$0,(a1)+
        dbf     d0,lreg
        movea.l a0,a2                   ;save the port location in a2
        lea     ustck,a0
        move.l  a0,ar7                  ;set user stack
        lea     slmes,a0                ;write message
        bsr     writs
        move.l  d1,d0
        bsr     writw                   ;write starting address
        move.l  #$03,d1                 ;gobble up last four bytes
        movea.l a2,a0                   ;restore the port location to a0
ll2:    jsr     (a0)
        dbf     d1,ll2
        lea     elmes,a0                ;send last message
        bsr     writs
        bset    #$00,echo               ;turn terminal echo back on
        rts
;
; Upload - upload program from terminal port
;
;****************************************
;*                                      *
;* Upload is invoked as follows:        *
;*                                      *
;*       u<cr> - load from terminal     *
;*               with no offset         *
;*       u xxxx - load with offset xxxx *
;*                                      *
;****************************************
;
uload:  bsr     getch                   ;same as above, except that it
        cmp.b   #$0d,d0                 ;uses the terminal port for the
        beq     ulnoof                  ;load.
        lea     getch,a0
        bsr     getw
        move.l  d0,_pc
        bra     uld1
ulnoof: move.l  #$0,_pc
uld1:   lea     ibuff,a1
        move.w  #$0,head(a1)
        move.w  #$ffff,tail(a1)
        move.w  #$0,count(a1)
        lea     lmes,a0
        bsr     writs
        move.b  #$0d,d0
        bsr     writu
        lea     getch,a0
        bclr    #$00,echo
        bra     llp                     ;goes to the load routine above
;
; e - Enter terminal emulator mode          *
;
;********************************************
;*                                          *
;* Invoke emulator mode as follows          *
;*                                          *
;*       e                                  *
;*                                          *
;*    NOTE: That in this mode any char-     *
;*    except a ctrl-x may be sent to the    *
;*    host. Ctrl-x is the escape sequence   *
;*    for getting out of terminal emulator  *
;*    mode. Ctrl-l does the same thing      *
;*    except a load (l) command is put      *
;*    in the command buffer.                *
;*                                          *
;********************************************
;
emmes:  dc.b    lf,cr
        dc.b    "Exit terminal mode",0
enmes:  dc.b    lf,cr
        dc.b    "Terminal mode:"
        dc.b    lf,cr,nul
emul:   lea     enmes,a0                ;write message
        bsr     writs
        bset    #$3,bkptf               ;set emulator mode
emu1:   stop    #$2000                  ;wait for interrupt
                                        ;if interrupted the handlers
                                        ;will buffer and echo input
        bra     emu1
emudn:  lea     emmes,a0                ;entered from interrupt handler
        bsr     writs
        rts
;
; Proto - Prototype command in ram
;
;******************************************
;*                                        *
;* Prototype commands are invoked:        *
;*                                        *
;*      px xxxx - load address xxxx for   *
;*                prototype command x.    *
;*      px<cr> - execute prototype com-   *
;*               mand x.                  *
;*                                        *
;*      NOTE: x must be a 1, 2, or 3      *
;*                                        *
;******************************************
;
pmess:  dc.b    lf,cr
        dc.b    "Prototype ",0
pm1:    dc.b    "running:"
        dc.b    lf,cr,nul
pm2:    dc.b    "installed"
        dc.b    cr,nul,nul
proto:  bsr     getch                   ;get prototype number
        move.l  d0,d1                   ;save number
        andi.b  #$0f,d1                 ;strip leading hex digit
        subq.b  #$1,d1                  ;normalize to 0
        lsl.l   #$1,d1                  ;multiply by 2
        lea     ptab,a1                 ;set starting address
        adda.l  d1,a1                   ;add offset
        bsr     getch                   ;get delimiter
        cmp.b   #$0d,d0                 ;if <cr> then do command
        beq     prun
        lea     getch,a0                ;else install in table
        bsr     getw                    ;get address
        move.w  d0,(a1)                 ;move in address
        lea     pmess,a0
        bsr     writs
        lea     pm2,a0
        bsr     writs
        bra     prts
prun:   movea.w (a1),a1                 ;run prototype command
        lea     pmess,a0
        bsr     writs
        lea     pm1,a0
        bsr     writs
        jsr     (a1)                    ;go do it
prts:   rts
;
; Bkpt - Set/Remove breakpoints
;
;
;**********************************************
;*                                            *
;* Breakpoint is invoked as follows:          *
;*                                            *
;*         b<cr> - display breakpoints        *
;*         b+xxxx - add a breakpoint at xxxx  *
;*         b-xxxx - delete breakpoint at xxxx *
;*         b# - delete all breakpoints        *
;*                                            *
;**********************************************
;
brmes:  dc.b    lf,cr
        dc.b    "Bkpts removed",0
bdmes:  dc.b    lf,cr
        dc.b    "Bkpts at:"
        dc.b    lf,cr,nul
bpmes:  dc.b    lf,cr
        dc.b    "Bkpt added at ",0
bmmes:  dc.b    lf,cr
        dc.b    "Bkpt deleted at ",0
bbmes:  dc.b    lf,cr
        dc.b    "Bkpt error",0
        dc.b    nul
bkin:   dc.w    $FFFF                   ;instruction constant
bkpt:   bsr     getch                   ;get delimiter
        cmp.b   #$0d,d0                 ;if <cr> then print all bkpts
        beq     bdis
        cmp.b   #$2b,d0                 ;if + then add a bkpt
        beq     bpls
        cmp.b   #$2d,d0                 ;if - then delete a bkpt
        beq     bmin
        cmp.b   #$23,d0                 ;if # then delete all bkpts
        bne     bbad                    ;else its a bad message
brem:   moveq   #$4,d1                  ;remove all bkpts
        lea     bktab-4,a1              ;set for loop
blp1:   adda.w  #$4,a1
        movea.w iloc(a1),a0             ;get address from table
        cmpa.w  #$00,a0                 ;if 0 then not an entry
        beq     bno
        move.w  instr(a1),(a0)          ;else move instr back
        move.l  #$0,instr(a1)           ;clear table entry
bno:    dbf     d1,blp1                 ;loop
        bclr    #$0,bkptf               ;clear bkpt if in one
        btst    #$2,bkptf               ;In trace ?
        bne     brno                    ;Yes.
        andi.w  #$7fff,_sr              ;else clear trace bit
brno:   lea     brmes,a0                ;say done
        bsr     writs
        bra     brts
bdis:   lea     bdmes,a0                ;handle display all bkpts
        bsr     writs
        lea     bktab-4,a1              ;set loop
        moveq   #$4,d1
bdlp:   adda.w  #$4,a1                  ;loop
        move.w  iloc(a1),d0             ;get bkpt
        beq     belp                    ;if 0 then not an entry
        bsr     writw
        bsr     crlf
belp:   dbf     d1,bdlp                 ;loop
        bra     brts
bpls:   lea     bktab-4,a1              ;add a bkpt
        moveq   #$4,d1                  ;set for loop
        lea     getch,a0                ;setup to get address
        bsr     getw
bl2:    adda.w  #$4,a1                  ;loop
        cmp.w   iloc(a1),d0             ;found entry already in table ?
        bne     bmo                     ;yes
        movea.w d0,a2                   ;reset it for insurance
        move.w  bkin,(a2)               ;set instruction
        bra     bfnd                    ;exit for found
bmo:    move.w  iloc(a1),d2             ;move to set condition codes
        dbeq    d1,bl2                  ;exit if 0 entry found
        bne     bbad                    ;if exit is on count and not 0 then error
        move.w  d0,iloc(a1)             ;move in address
        movea.w d0,a2                   ;point at location
        move.w  (a2),instr(a1)          ;get instruction into table
        move.w  bkin,(a2)               ;set bkpt instruction
bfnd:   lea     bpmes,a0                ;load message
        bsr     writs
        move.l  a2,d0
        bsr     writw
        bclr    #$1,bkptf               ;clear in-single flag
        btst    #$2,bkptf               ;In trace ?
        bne     brts                    ;Yes
        andi.w  #$7fff,_sr              ;clear trace bit
        bra     brts
bmin:   lea     bktab-4,a1              ;delete a breakpoint entry
        moveq   #$4,d1                  ;setup for search
        lea     getch,a0                ;setup for terminal input
        bsr     getw
bl3:    adda.w  #$4,a1                  ;loop
        cmp.w   iloc(a1),d0             ;Is this the one ?
        dbeq    d1,bl3                  ;if yes then exit else loop
        bne     bbad                    ;Exit on count ?
        movea.w d0,a2                   ;no, so get address
        move.w  instr(a1),(a2)          ;return instruction
        move.l  #$0,instr(a1)           ;clear table entry
        btst    #$0,bkptf               ;In breakpoint ?
        beq     bok                     ;No
        cmp.l   _pc,d0                  ;Yes, This breakpoint ?
        bne     bok                     ;No
        bclr    #$0,bkptf               ;Yes, so clear handling it
        btst    #$2,bkptf               ;In trace ?
        bne     bok                     ;Yes
        andi.w  #$7fff,_sr              ;else clear trace flag
bok:    lea     bmmes,a0                ;load message
        bsr     writs
        move.l  a2,d0                   ;print address
        bsr     writw
        bra     brts
bbad:   lea     bbmes,a0                ;error handler
        bsr     writs
brts:   rts
;
; dump - dump memory
;
;*****************************************
;*                                       *
;*    dump is invoked as follows:        *
;*                                       *
;*    d<cr> - dump the next 64 bytes from*
;*            last examined location     *
;*    d xxxx<cr> - dump the next 64 bytes*
;*                 from address xxxx     *
;*    d xxxx,yyyy - dump the bytes bet-  *
;*                  ween xxxx and yyyy   *
;*                                       *
;*****************************************
;
dmes:   dc.b    lf,lf,cr
        dc.b    "Memory dump"
        dc.b    lf,cr,nul
dhed:   dc.b    lf,cr
        dc.b    "      0  1  2  3"
        dc.b    "  4  5  6  7  8  9  a"
        dc.b    "  B  C  d  E  F"
dcr:    dc.b    lf,cr,nul
dump:   lea     getch,a0                ;set for terminal input
        bsr     getch                   ;get delimiter
        cmp.b   #$0d,d0                 ;if <cr> then dump from pointer
        bne     dexam                   ;else get address
        movea.w exam,a1                 ;get exam
        movea.w a1,a2                   ;save it for ending address
        adda.w  #$40,a2                 ;add 64 for length of dump
        bra     dgo                     ;go do it
dexam:  bsr     getw                    ;get starting address
        movea.w d0,a1
        bsr     getch                   ;get delimiter
        cmp.b   #$2c,d0                 ;if , the get ending address
        bne     dcom
        bsr     getw                    ;get address
        movea.w d0,a2                   ;save it
        bra     dgo                     ;go dump
dcom:   movea.w a1,a2                   ;default to 64 byte dump
        adda.w  #$40,a2
dgo:    lea     dmes,a0                 ;do the dump
        bsr     writs
        lea     dhed,a0                 ;print header
        bsr     writs
        move.l  a1,d0                   ;set starting address at 16 byte boundary
        and.b   #$f0,d0
        movea.w d0,a1
        move.l  a2,d0                   ;round ending address to boundary
        or.b    #$0f,d0
        movea.w d0,a2
        moveq   #$0f,d1                 ;move byte count to register
dl1:    move.l  a1,d0                   ;write starting address
        bsr     writw
        movea.w a1,a3                   ;save starting address
dflp:   moveq   #$20,d0                 ;write a space
        bsr     writ
        move.b  (a1)+,d0                ;get next byte
        bsr     writb                   ;write it
        dbf     d1,dflp                 ;loop
        moveq   #$0f,d1                 ;reset byte count
        movea.w a3,a1                   ;refetch starting address
        moveq   #$20,d0                 ;write a space
        bsr     writ
dslp:   move.b  (a1)+,d0                ;write the byte representation
        cmp.b   #$20,d0                 ;if not printable then a dot
        bge     dok
        move.b  #$2e,d0                 ;move in the dot
        bra     dwrt
dok:    cmp.b   #$7f,d0                 ;printable again ?
        blt     dwrt                    ;yes
        move.b  #$2e,d0                 ;no, move in a dot
dwrt:   bsr     writ                    ;write it
        dbf     d1,dslp                 ;line done ?
        lea     dcr,a0                  ;yes, so cr-lf
        bsr     writs
        moveq   #$10,d1                 ;reset byte count
        cmpa.l  a1,a2                   ;done ?
        dblt    d1,dl1                  ;NO, so loop
        move.w  a1,exam                 ;yes, so update exam
        rts
;
; Trace - Set trace mode
;
;*****************************************
;*                                       *
;* Invoke trace as follows:              *
;*                                       *
;*       t+ - trace a program's path     *
;*       t- - turn off trace             *
;*                                       *
;*****************************************
;
tmes:   dc.b    lf,cr
        dc.b    "Trace ",0
tonm:   dc.b    "on",0
toffm:  dc.b    "off",0
trace:  bsr     getch                   ;get command
        move.l  d0,d1                   ;save it
        lea     tmes,a0                 ;write message
        bsr     writs
        cmp.b   #$2b,d1                 ;Is it a + ?
        beq     ton                     ;yes
        btst    #$0,bkptf               ;In breakpoint ?
        bne     tclr                    ;Yes, so don't clear trace
        andi.w  #$7fff,_sr              ;clear trace
tclr:   bclr    #$2,bkptf               ;turn-off in-trace flag
        lea     toffm,a0                ;load off message
        bra     tdone                   ;exit
ton:    ori.w   #$8000,_sr              ;set trace bit
        bclr    #$1,bkptf               ;clear single step
        bset    #$2,bkptf               ;set in-trace flag
        lea     tonm,a0                 ;write message
tdone:  bsr     writs
        rts
;
; Single - set single step
;
;*****************************************
;*                                       *
;* Invoke single step as follows:        *
;*                                       *
;*       s+ - turn on single step        *
;*       s- - turn off single step       *
;*                                       *
;*****************************************
;
smes:   dc.b    lf,cr
        dc.b    "Single step",0
sonm:   dc.b    " on ",0
soffm:  dc.b    " off ",0
        dc.b    nul
singl:  bsr     getch                   ;get command
        move.l  d0,d1                   ;save it
        lea     smes,a0                 ;write message
        bsr     writs
        cmp.b   #$2b,d1                 ;+ ?
        beq     son                     ;yes
        btst    #$0,bkptf               ;In breakpoint ?
        bne     sclr                    ;Yes, so don't clear trace
        andi.w  #$7fff,_sr              ;clear trace bit
sclr:   bclr    #$1,bkptf               ;turn-off in-single flag
        lea     soffm,a0                ;write off message
        bsr     writs
        bra     sdone                   ;exit
son:    bclr    #$0,bkptf               ;clear in-bkpt flag
        bset    #$1,bkptf               ;set in-single flag
        bclr    #$2,bkptf               ;clear in-trace flag
        lea     sonm,a0                 ;write message
        bsr     writs
        bsr     brem                    ;remove all breakpoints for single
        ori.w   #$8000,_sr              ;set trace bit
sdone:  rts
;
; Go - Start user program
;
;*****************************************
;*                                       *
;* Invoke go as follows:                 *
;*                                       *
;*      g<cr> - go from start address in *
;*              last load                *
;*      <cr> - same as g<cr>             *
;*      g xxxx - go from address xxxx    *
;*                                       *
;*****************************************
;
gmes:   dc.w    csc
        dc.b    "Program:"
        dc.b    lf,lf,cr,nul
go:     bsr     getch                   ;get seperator
        cmp.b   #$0d,d0                 ;if CR then
        beq     ggo                     ;start from default
gget:   lea     getch,a0                ;else get start addr
        bsr     getw                    ;as given in comm.
        move.l  d0,_pc                  ;set for return
ggo:    btst    #$1,bkptf               ;single set ?
        bne     gnom                    ;Yes so no message
        lea     gmes,a0                 ;write message
        bsr     writs
gnom:   addq.w  #$4,a7                  ;pop the stack
        movem.l dr0,d0-d7/a0-a6         ;get saved values d0-a6
        move.l  a7,t1                   ;save system stack pointer
        movea.l ar7,a7                  ;get saved user stack pointer
        move.l  a7,usp                  ;reset the user stack
        movea.l t1,a7                   ;reset system stack
gbmov:  move.l  _pc,-(a7)               ;set up return pc
        andi.w  #$f8ff,_sr              ;enable interrupts
        move.w  _sr,-(a7)               ;set up return sr
        rte

;++++++++++++++++++++++++++++++++++++++++
;+                                      +
;+     End of commands, Start Handlers  +
;+                                      +
;++++++++++++++++++++++++++++++++++++++++
;
; Generic trap handler
;
ghmes:  dc.b    lf,cr
        dc.b    "Trap at ",0
        dc.b    nul
ghlr:   movem.l d0-d7/a0-a7,dr0         ;save all registers d0-a7
        move.l  usp,a6                  ;get user stack pointer
        move.l  a6,ar7                  ;and save it
        move.w  (a7)+,_sr               ;save current SR
        move.l  (a7)+,_pc               ;save current return value
        pea     comm                    ;set for return to comm
        move.w  ssri,-(a7)              ;enable interrupts on return
ghpr:   lea     ghmes,a0                ;wx message
ghpr1:  bsr     writs
        move.l  _pc,d0
        bsr     writl
        rte
;
; Breakpoint handler
;
bhmes:  dc.b    lf,cr
        dc.b    "Breakpoint at ",0
binin:  dc.b    lf,cr
        dc.b    "Bad Instruction at ",0
        dc.b    nul
bhlr:   move.w  ssrn,sr                 ;disable interrupts
        movem.l d0-d7/a0-a7,dr0         ;save registers d0-a7
        move.l  usp,a6                  ;get and save user stack pointer
        move.l  a6,ar7
        move.w  (a7)+,_sr               ;save status register
        move.l  (a7)+,_pc               ;save program counter
        pea     comm                    ;set for return to comm
        move.w  ssri,-(a7)              ;enable interrupts on return
        movea.l _pc,a0                  ;get pc on interrupt
        cmpi.w  #$ffff,(a0)             ;was interrupt caused by bkpt instruction ?
        beq     bsnd                    ;Yes
        lea     binin,a0                ;No, invalid instruction
        bra     ghpr1                   ;go wx message
bsnd:   lea     bhmes,a0                ;wx bkpt message
        bsr     writs
        move.l  _pc,d0
        bsr     writw
        bsr     crlf
        lea     bktab-4,a1              ;find the breakpoint entry
        move.l  #$4,d1                  ;maximum of 5
        move.l  _pc,d0                  ;this is where it happened
bhl:    adda.w  #$4,a1
        cmp.w   iloc(a1),d0             ;is this the entry ?
        dbeq    d1,bhl                  ;loop if not
        bne     bhrte                   ;not found so quit
        movea.w d0,a2                   ;point at it
        move.w  instr(a1),(a2)          ;move instruction back in
        ori.w   #$8000,_sr              ;set trace mode on
        bset    #$0,bkptf               ;set in-bkpt flag
bhrte:  rte
;
; Trace handler
;
tlocm:  dc.b    lf,cr
        dc.b    "PC == ",0
        dc.b    nul
thlr:   move.w  ssrn,sr                 ;disable interrupts
        move.l  a0,ar0                  ;save used registers
        move.l  d0,dr0
        move.l  a1,ar1
        move.l  d1,dr1
        move.l  a2,ar2
        move.l  d2,dr2
        btst    #$0,bkptf               ;Handling a breakpoint ?
        beq     treal                   ;No, so its a real trace
        movea.l _pc,a0                  ;Yes, find where it occurred
        move.w  bkin,(a0)               ;reset the bkpt instruction
        bclr    #$0,bkptf               ;clear in progress bkpt
        btst    #$2,bkptf               ;In trace mode
        bne     treal                   ;yes, go trace it
thma0:  andi.w  #$7fff,(a7)             ;No, so clear the trace bit
        bra     trte
treal:  move.l  $2(a7),_pc              ;Not (just) a bkpt but trace or single
        btst    #$1,bkptf               ;Trace ?
        beq     trpr                    ;Yes
        movem.l d0-d7/a0-a7,dr0         ;No,single-step d0-a7
        move.l  usp,a6                  ;save registers and stack pointer
        move.l  a6,ar7
        move.w  (a7)+,_sr               ;save status register
        move.l  (a7)+,_pc               ;save pc
        pea     comm                    ;fake return to comm
        move.w  ssri,-(a7)              ;enable interrupts on return
trpr:   lea     tlocm,a0                ;wx message
        bsr     writs
        move.l  _pc,d0
        bsr     writl
        bsr     crlf
        move.l  _pc,a1                  ;load the current address
        bsr     ass1                    ;wx the disassembled instruction
trte:   movea.l ar0,a0                  ;restore used registers
        move.l  dr0,d0
        movea.l ar1,a1
        move.l  dr1,d1
        movea.l ar2,a2
        move.l  dr2,d2
tr:     rte
;
; Privilege Violation Handler
;
; See generic handler for details
;
prmes:  dc.b    lf,cr
        dc.b    "Privilege Error at ",0
phlr:   movem.l d0-d7/a0-a7,dr0         ;regs d0-a7
        move.l  usp,a6
        move.l  a6,ar7
        move.w  (a7)+,_sr
        move.l  (a7)+,_pc
        pea     comm
        move.w  ssri,-(a7)
prpr:   lea     prmes,a0
        bra     ghpr1
;
; address error/bus error trap
;
abmes:  dc.b    lf,cr
        dc.b    "address error at ",0
abhlr:  movem.l d0-d7/a0-a7,dr0         ;regs d0-a7
        move.l  usp,a6
        move.l  a6,ar7                  ;same as above but...
        move.w  $8(a7),_sr              ;status register is deeper in stack
        move.l  $a(a7),_pc              ;also pc
        pea     comm
        move.w  ssri,-(a7)
abpr:   lea     abmes,a0
        bra     ghpr1
;
; Macro instruction handlers
;
;
; Exit
;
texit:  movem.l d0-d7/a0-a7,dr0         ;save register values d0-a7
        move.l  usp,a6                  ;save user stack pointer
        move.l  a6,ar7
        move.w  (a7)+,_sr               ;save status register
        move.l  (a7)+,_pc               ;save pc
        lea     stack,a7                ;reset system mode stack
        pea     comm                    ;fake return to comm
        move.w  ssri,-(a7)              ;ditto for status
        rte
;
; Getb
;
tgetb:  lea     getch,a0
        bsr     getb
        rte
;
; Getw
;
tgetw:  lea     getch,a0
        bsr     getw
        rte
;
; Getl
;
tgetl:  lea     getch,a0
        bsr     getl
        rte
;
; Wrtb
;
twrtb:  bsr     writb
        rte
;
; Wrtw
;
twrtw:  bsr     writw
        rte
;
; Wrtl
;
twrtl:  bsr     writl
        rte
;
; Getc
;
tgetc:  bsr     getch
        rte
;
; Wrts
;
twrts:  bsr     writs
        rte
;
; Wrtc
;
twrtc:  bsr     writ
        rte
;
; Crlf
;
tcrlf:  bsr     crlf
        rte
;
; Help - display help messages
;
;*****************************************
;*                                       *
;* Invoke help as follows:               *
;*                                       *
;*      h<cr> - print list of available  *
;*              help                     *
;*      hx - print help message for x    *
;*                                       *
;*****************************************
hlph:   dc.b   " H - display help messages"
        dc.b    cr,lf,nul
hlph1:  dc.b   " Invoke help as follows:"
        dc.b    cr,lf
        dc.b   "      h<cr> - print list of available help"
        dc.b    cr,lf
        dc.b   "      hx - print help message for x"
        dc.b    cr,lf,nul

hlpc:   dc.b   " C - Copy memory blocks"
        dc.b    cr,lf,nul
hlpc1:  dc.b   " Copy is invoked as follows:"
        dc.b    cr,lf
        dc.b   "          c xxxx=yyyy,zzzz"
        dc.b    cr,lf
        dc.b   " Copy locations yyyy thru zzzz to"
        dc.b    cr,lf
        dc.b   " locations xxxx and upward."
        dc.b    cr,lf,nul

hlpm:   dc.b   " M - memory update"
        dc.b    cr,lf,nul
hlpm1:  dc.b   " Memory sub-commands are as follows:"
        dc.b    cr,lf
        dc.b    cr,lf
        dc.b   "          m<cr> - start memory mode"
        dc.b    cr,lf
        dc.b   "          m xxxx - start m mode at location xxxx"
        dc.b    cr,lf
        dc.b   "          .xxxx - set pointer to location xxxx"
        dc.b    cr,lf
        dc.b   "          =xx - update current location to xx"
        dc.b    cr,lf
        dc.b   "          ,xx - increment location and update it to xx"
        dc.b    cr,lf
        dc.b   "          + - increment location"
        dc.b    cr,lf
        dc.b   "          - - decrement location"
        dc.b    cr,lf
        dc.b   "          <cr> - print current location and value"
        dc.b    cr,lf,nul

hlpr:   dc.b   " R - Modify/examine registers"
        dc.b    cr,lf,nul
hlpr1:  dc.b   " Register subcommands are as follows:"
        dc.b    cr,lf
        dc.b    cr,lf
        dc.b   "      r<cr> - start register mode"
        dc.b    cr,lf
        dc.b   "      r xx - start r mode at register xx. Where xx :"
        dc.b    cr,lf
        dc.b   "            SR/_sr - status register"
        dc.b    cr,lf
        dc.b   "            PC/_pc - program counter"
        dc.b    cr,lf
        dc.b   "            d0 - d7 - data registers"
        dc.b    cr,lf
        dc.b   "            a0 - a7 - address regs."
        dc.b    cr,lf
        dc.b   "     .xx - set pointer to register"
        dc.b    cr,lf
        dc.b   "     =xxxxxxxx - update current register to xxxxxxxx"
        dc.b    cr,lf
        dc.b   "     <cr> - print all registers"
        dc.b    cr,lf,nul

hlpl:   dc.b   " L - Load data from host"
        dc.b    cr,lf,nul
hlpu:   dc.b   " U - Load data from terminal port"
        dc.b    cr,lf,nul
hlpl1:  dc.b   " Load is invoked as follows:"
        dc.b    cr,lf
        dc.b   "       l<cr> - load from host with no offset"
        dc.b    cr,lf
        dc.b   "       <ff> - same as l<cr> but used from emulator mode"
        dc.b    cr,lf
        dc.b   "       l xxxx - load with offset xxxx"
        dc.b    cr,lf,cr,lf
        dc.b   " Upload is invoked as follows:"
        dc.b    cr,lf
        dc.b    "      u<cr> - load from terminal with no offset"
        dc.b    cr,lf
        dc.b    "      u xxxx - load from terminal with offset xxxx"
        dc.b    cr,lf,nul

hlpe:   dc.b   " E - Enter terminal emulator mode"
        dc.b    cr,lf,nul
hlpe1:  dc.b   " Invoke emulator mode as follows"
        dc.b    cr,lf
        dc.b    cr,lf
        dc.b   "       e"
        dc.b    cr,lf
        dc.b   "    NOTE: That in this mode any character except"
        dc.b    cr,lf
        dc.b   "    a ctrl-x may be sent to the host. Ctrl-x is the"
        dc.b    cr,lf
        dc.b   "    escape sequence for getting out of terminal emulator"
        dc.b    cr,lf
        dc.b   "    mode. Ctrl-l does the same thing except a load (l)"
        dc.b    cr,lf
        dc.b   "    command is put in the command buffer."
        dc.b    cr,lf,nul

hlpp:   dc.b   " P - Prototype commands in RAM"
        dc.b    cr,lf,nul
hlpp1:  dc.b   " Prototype commands are invoked:"
        dc.b    cr,lf
        dc.b   "      px xxxx - load address xxxx for prototype command x."
        dc.b    cr,lf
        dc.b   "      px<cr> - execute prototype command x."
        dc.b    cr,lf
        dc.b    cr,lf
        dc.b   "      NOTE: x must be a 1, 2, or 3"
        dc.b    cr,lf,nul

hlpb:   dc.b   " B - Set/Remove breakpoints"
        dc.b    cr,lf,nul
hlpb1:  dc.b   " Breakpoint is invoked as follows:"
        dc.b    cr,lf
        dc.b   "         b<cr> - display breakpoints"
        dc.b    cr,lf
        dc.b   "         b+xxxx - add a breakpoint at xxxx"
        dc.b    cr,lf
        dc.b   "         b-xxxx - delete breakpoint at xxxx"
        dc.b    cr,lf
        dc.b   "         b# - delete all breakpoints"
        dc.b    cr,lf,nul

hlpd:   dc.b   " D - dump memory"
        dc.b    cr,lf,nul
hlpd1:  dc.b   "    dump is invoked as follows:"
        dc.b    cr,lf
        dc.b    cr,lf
        dc.b   "    d<cr> - dump the next 64 bytes from last examined location"
        dc.b    cr,lf
        dc.b   "    d xxxx<cr> - dump the next 64 bytes from address xxxx"
        dc.b    cr,lf
        dc.b   "    d xxxx,yyyy - dump the bytes between xxxx and yyyy"
        dc.b    cr,lf,nul

hlpa:   dc.b   " A - Assembly listing"
        dc.b    cr,lf,nul
hlpa1:  dc.b   "    disassembly is invoked as follows:"
        dc.b    cr,lf
        dc.b    cr,lf
        dc.b   "    a<cr> - list the next 20 instructions from last location"
        dc.b    cr,lf
        dc.b   "    a xxxx<cr> - list the next 20 instructions from address xxxx"
        dc.b    cr,lf
        dc.b   "    a xxxx,yyyy - list the instructions between xxxx and yyyy"
        dc.b    cr,lf,nul

hlpt:   dc.b   " T - Set trace mode"
        dc.b    cr,lf,nul
hlpt1:  dc.b   " Invoke trace as follows:"
        dc.b    cr,lf
        dc.b    cr,lf
        dc.b   "       t+ - trace a program's path"
        dc.b    cr,lf
        dc.b   "       t- - turn off trace"
        dc.b    cr,lf,nul

hlps:   dc.b   " S - set single step"
        dc.b    cr,lf,nul
hlps1:  dc.b   " Invoke single step as follows:"
        dc.b    cr,lf
        dc.b    cr,lf
        dc.b   "       s+ - turn on single step"
        dc.b    cr,lf
        dc.b   "       s- - turn off single step"
        dc.b    cr,lf,nul

hlpg:   dc.b   " G - Start user program"
        dc.b    cr,lf,nul
hlpg1:  dc.b   " Invoke go as follows:"
        dc.b    cr,lf
        dc.b    cr,lf
        dc.b   "      g<cr> - go from start address in last load"
        dc.b    cr,lf
        dc.b   "      <cr> - same as g<cr>"
        dc.b    cr,lf
        dc.b   "      g xxxx - go from address xxxx "
        dc.b    cr,lf,nul

htab:   dc.w    $4800           ;h - help
        dc.w    hlph,hlph1
        dc.w    $4d00           ;m - memory
        dc.w    hlpm,hlpm1
        dc.w    $4c00           ;l - load
        dc.w    hlpl,hlpl1
        dc.w    $5500           ;u - upload
        dc.w    hlpu,hlpl1
        dc.w    $4400           ;d - dump
        dc.w    hlpd,hlpd1
        dc.w    $5300           ;s - single step
        dc.w    hlps,hlps1
        dc.w    $5400           ;t - trace program
        dc.w    hlpt,hlpt1
        dc.w    $4700           ;g - start user program
        dc.w    hlpg,hlpg1
        dc.w    $4500           ;e - emulate mode
        dc.w    hlpe,hlpe1
        dc.w    $4200           ;b - breakpoints
        dc.w    hlpb,hlpb1
        dc.w    $4300           ;c - copy
        dc.w    hlpc,hlpc1
        dc.w    $5200           ;r - register modify
        dc.w    hlpr,hlpr1
        dc.w    $5000           ;p - prototype commands
        dc.w    hlpp,hlpp1
        dc.w    $4100           ;a - assembly listing
        dc.w    hlpa,hlpa1
;
; Structure of entry is topic (top),
; address of short message (hshort),
; and address of long message (hlong).
;
help:   bsr     getch           ;get argument
        andi.b  #$5f,d0         ;make it uppercase
        cmpi.b  #$0d,d0         ;is it a carriage return?
        bne     htopic          ;no, so decode topic
hall:   bsr     crlf
        bsr     crlf
        moveq   #$0d,d1         ;load total # topics - 1
        lea     htab+2,a1       ;load location of short help
shlp:   movea.w (a1),a0         ;copy help location to a0
        bsr     writs           ;write a short help message
        addq.w  #$06,a1         ;increment to next help message
        dbf     d1,shlp         ;if not last message, print another one
        rts
htopic: lea     htab,a1         ;set up search of ctab
        moveq   #$0d,d1         ;load total # topics - 1
lhlp:   cmp.b   (a1),d0         ;is the topic equal to the table value?
        beq     hprn            ;if so, print the short and long helps
        addq.w  #$06,a1         ;else go to the next table location
        dbf     d1,lhlp         ;if not finished, try again
        bra     hall            ;if not one of these, print all shorts
hprn:   bsr     crlf
        bsr     crlf
        addq.w  #$02,a1         ;increment a2 to short help location
        movea.w (a1)+,a0        ;transfer address to a0
        bsr     writs           ;write the short message
        bsr     crlf            ;feed an extra line
        movea.w (a1),a0         ;transfer long help address to a0
        bsr     writs           ;write the long message
        rts

;
; assem - assembly listing
;
;****************************************
;*                                      *
;*      assem is invoked as follows:    *
;*                                      *
;*      a<cr> - disassemble the next    *
;*              20 instructions from    *
;*              last examined location  *
;*      a xxxx<cr> - disassemble 20     *
;*              instructions from xxxx  *
;*      a xxxx,yyyy - disassemble all   *
;*              instructions from xxxx  *
;*              to yyyy                 *
;*                                      *
;****************************************

ames:   dc.b    lf,lf,cr
        dc.b    "assembly listing:"
        dc.b    lf,cr,nul,nul
assem:  lea     getch,a0        ;set for terminal input
        bsr     getch           ;get delimiter
        cmp.b   #$0d,d0         ;if <cr> then list from pointer
        bne     aexam           ;else get address
        movea.w exam,a1         ;get exam
        lea     ames,a0         ;write message
        bsr     writs
        move.b  #$13,d2         ;load 19 into d2
ass20:  bsr     ass1            ;list a single instruction
        dbf     d2,ass20        ;if not finished, decrement and go again
        move.w  a1,exam         ;save new examination pointer
        rts
aexam:  bsr     getw            ;get starting address
        movea.w d0,a1
        bsr     getch           ;get delimiter
        cmpi.b  #$2c,d0         ;if , then get ending address
        bne     acom
        bsr     getw            ;get address
        move.w  d0,aend         ;save it
        lea     ames,a0         ;write message
        bsr     writs
assxy:  bsr     ass1            ;list a single instruction
        cmpa.w  aend,a1         ;reached the end of the range yet?
        ble     assxy           ;if not, do it again
        move.w  a1,exam         ;save new examination pointer
        rts
acom:   lea     ames,a0         ;write message
        bsr     writs
        move.b  #$13,d2         ;load 19 into d2
        bra     ass20           ;jump to dump 20 routine

ass1:   move.w  a1,d0           ;load the address
        bsr     writw           ;print it out
        bsr     spc
        bsr     spc
        move.w  (a1)+,d0        ;load the instruction word
        move.w  d0,d1           ;make a copy
        rol.w   #$06,d0         ;get a longword offset for
        and.w   #$003c,d0       ;the instruction group (most sig. 4 bits)
        lea     grtab,a2        ;load the address of the group table
        adda.w  d0,a2           ;add the group offset
        movea.l (a2),a2         ;get the actual address
        jsr     (a2)            ;jump to the appropriate subroutine
        rts                     ;exit

disend: bra     crlf            ;send crlf after instruction
        rts                     ;return from instruction subroutine

grtab:  dc.l    gr0
        dc.l    gr1
        dc.l    gr2
        dc.l    gr3
        dc.l    gr4
        dc.l    gr5
        dc.l    gr6
        dc.l    gr7
        dc.l    gr8
        dc.l    gr9
        dc.l    gra
        dc.l    grb
        dc.l    grc
        dc.l    grd
        dc.l    gre
        dc.l    grf

gr0:    move.w  d1,d0
        cmpi.w  #$023c,d0       ;is it ANDIccr?
        bne     ANDIsr          ;no.
        lea     mANDI,a0        ;yes, print
        bsr     writs           ;write it
        bsr     spc
        bsr     pound
        bsr     dollar
        move.w  (a1)+,d0        ;load the operand
        bsr     writb           ;write it
        bsr     comma
        lea     mccr,a0         ;load "ccr"
        bsr     writs
        bra     disend
ANDIsr: cmpi.w  #$027c,d0       ;is it ANDIsr?
        bne     EORIcr          ;no.
        lea     mANDI,a0        ;yes, print
        bsr     writs           ;write it
        bsr     spc
        bsr     pound
        bsr     dollar
        move.w  (a1)+,d0        ;load the operand
        bsr     writw           ;write it
        bsr     comma
        lea     msr,a0          ;load "sr"
        bsr     writs
        bra     disend
EORIcr: cmpi.w  #$0a3c,d0       ;is it EORIccr?
        bne     EORIsr          ;no.
        lea     mEORI,a0        ;yes, print
        bsr     writs           ;write it
        bsr     spc
        bsr     pound
        bsr     dollar
        move.w  (a1)+,d0        ;load the operand
        bsr     writb           ;write it
        bsr     comma
        lea     mccr,a0         ;load "ccr"
        bsr     writs
        bra     disend
EORIsr: cmpi.w  #$0a7c,d0       ;is it EORIsr?
        bne     ORIccr          ;no.
        lea     mEORI,a0        ;yes, print
        bsr     writs
        bsr     spc
        bsr     pound
        bsr     dollar
        move.w  (a1)+,d0        ;load the operand
        bsr     writw           ;write it
        bsr     comma
        lea     msr,a0          ;load "sr"
        bsr     writs           ;write it
        bra     disend
ORIccr: cmpi.w  #$003c,d0       ;is it ORIccr?
        bne     ORIsr           ;no.
        lea     mORI,a0         ;yes, print
        bsr     writs           ;write it
        bsr     spc
        bsr     pound
        bsr     dollar
        move.w  (a1)+,d0        ;load the operand
        bsr     writb           ;write it
        bsr     comma
        lea     mccr,a0         ;load "ccr"
        bsr     writs
        bra     disend
ORIsr:  cmpi.w  #$007c,d0       ;is it ORIsr?
        bne     ADDI            ;no.
        lea     mORI,a0         ;yes, print
        bsr     writs           ;write it
        bsr     spc
        bsr     pound
        bsr     dollar
        move.w  (a1)+,d0        ;load the operand
        bsr     writw           ;write it
        bsr     comma
        lea     msr,a0          ;load "sr"
        bsr     writs
        bra     disend
ADDI:   andi.w  #$0f00,d0       ;mask operation bits
        cmpi.w  #$0600,d0       ;is it ADDI?
        bne     ANDI            ;no.
        lea     mADDI,a0        ;yes, print
        bsr     writs           ;write it
        bra     iops            ;go print operands
ANDI:   cmpi.w  #$0200,d0       ;is it ANDI?
        bne     CMPI            ;no.
        lea     mANDI,a0        ;yes, print
        bsr     writs           ;write it
        bra     iops            ;go print operands
CMPI:   cmpi.w  #$0c00,d0       ;is it CMPI?
        bne     EORI            ;no.
        lea     mCMPI,a0        ;yes, print
        bsr     writs           ;write it
        bra     iops            ;go print operands
EORI:   cmpi.w  #$0a00,d0       ;is it EORI?
        bne     ORI             ;no.
        lea     mEORI,a0        ;yes, print
        bsr     writs           ;write it
        bra     iops            ;go print operands
ORI:    cmpi.w  #$0000,d0       ;is it ORI?
        bne     SUBI            ;no.
        lea     mORI,a0         ;yes, print
        bsr     writs           ;write it
        bra     iops            ;go print operands
SUBI:   cmpi.w  #$0400,d0       ;is it SUBI?
        bne     MOVEP           ;no.
        lea     mSUBI,a0        ;yes, print
        bsr     writs           ;write it
iops:   move.w  d1,d0
        andi.w  #$00c0,d0       ;check the size to see if it is legal
        cmpi.w  #$00c0,d0       ;is it size 11?
        bne     lops            ;if not, it is legal
        bsr     spc           ;if so, it is not legal
        bsr     spc
        bra     ILLEG
lops:   bsr     dot
        move.w  d1,d0
        bsr     findsiz         ;print the operand size
        bsr     spc
        bsr     pound
        bsr     dollar
        cmpi.b  #$62,siz        ;is byte?
        bne     iopsw           ;no
        move.w  (a1)+,d0        ;yes
        bsr     writb
        bra     iopsc
iopsw:  cmpi.b  #$77,siz        ;is word?
        bne     iopsl           ;no
        move.w  (a1)+,d0        ;yes
        bsr     writw
        bra     iopsc
iopsl:  move.l  (a1)+,d0        ;size long
        bsr     writl
iopsc:  bsr     comma
        move.w  d1,d0
        bsr     writea          ;write the operand
        bra     disend
MOVEP:  move.w  d1,d0
        andi.w  #$0138,d0       ;mask MOVEP bits
        cmpi.w  #$0108,d0       ;is it a MOVEP?
        bne     bitop           ;if not, it's a bit operation
        lea     mMOVEP,a0       ;load "MOVEP"
        bsr     writs           ;write it
        bsr     dot
        move.w  d1,d0
        andi.w  #$0040,d0       ;word or longword
        bne     movepl          ;longword
        move.b  #$77,d0         ;load a 'W'
        bsr     writ            ;write it
        bra     moveps          ;go write operands
movepl: move.b  #$6C,d0         ;load an 'L'
        bsr     writ            ;write it
moveps: bsr     spc
        move.w  d1,d0
        andi.w  #$0080,d0       ;mask direction bit
        beq     movepr          ;if zero, move to reg
        move.w  d1,d0
        andi.w  #$0e00,d0       ;mask data reg
        rol.w   #$07,d0         ;get into rightmost bits
        bsr     wdreg           ;write it
        bsr     comma
        bsr     lparen
        move.w  (a1)+,d0
        bsr     writw           ;write the address
        bsr     comma
        move.w  d1,d0
        andi.w  #$0007,d0       ;mask address reg
        bsr     wareg           ;write it
        bsr     rparen
        bra     disend
movepr: move.w  d1,d0
        bsr     lparen
        move.w  (a1)+,d0
        bsr     writw           ;write the address
        bsr     comma
        move.w  d1,d0
        andi.w  #$0007,d0       ;mask address reg
        bsr     wareg           ;write it
        bsr     rparen
        bsr     comma
        move.w  d1,d0
        andi.w  #$0e00,d0       ;mask data reg
        rol.w   #$07,d0         ;get into rightmost bits
        bsr     wdreg           ;write it
        bra     disend
bitop:  move.w  d1,d0
        andi.w  #$0f00,d0       ;mask the subgroup bits
        cmpi.w  #$0e00,d0       ;and make sure this is not illegal, since
        beq     ILLEG           ;a non-MOVEP 00001110xxxxxxxx is invalid
        move.w  d1,d0
        andi.w  #$00c0,d0       ;mask bitop select bits
        bne     BCHG            ;it's not BTST
        lea     mBTST,a0        ;load "BTST"
        bsr     writs           ;write it
        bra     bitop2          ;go print operands
BCHG:   cmpi.w  #$0040,d0
        bne     BCLR            ;it's not BCHG
        lea     mBCHG,a0        ;load "BCHG"
        bsr     writs           ;write it
        bra     bitop2          ;go print operands
BCLR:   cmpi.w  #$0080,d0
        bne     BSET            ;it's not BCLR
        lea     mBCLR,a0        ;load "BCLR"
        bsr     writs           ;write it
        bra     bitop2          ;go print operands
BSET:   lea     mBSET,a0        ;load "BSET"
        bsr     writs           ;write it
bitop2: bsr     spc
        move.w  d1,d0
        andi.w  #$0100,d0       ;is it reg or immediate operand?
        bne     bitopr          ;if nonzero, it's a reg operand
        bsr     pound
        move.w  (a1)+,d0        ;get the bit number
        andi.b  #$07,d0         ;modulo 8
        bsr     writb           ;write it
        bsr     comma
        move.w  d1,d0
        bsr     writea          ;write the destination operand
        bra     disend
bitopr: move.w  d1,d0
        andi.w  #$0e00,d0       ;mask off the reg number
        rol.w   #$07,d0         ;get it into rightmost bits
        bsr     wdreg           ;write it
        bsr     comma
        move.w  d1,d0
        bsr     writea          ;write the destination operand
        bra     disend

gr1:    move.b  #$62,siz        ;make MOVE a byte operation
        bra     MOVE            ;go parse the command type
gr2:    move.b  #$6c,siz        ;make MOVE a word operation
        bra     MOVE            ;go parse the command type
gr3:    move.b  #$77,siz        ;make MOVE a long operation
MOVE:   move.w  d1,d0
        andi.w  #$01c0,d0       ;mask the destination opmode
        cmpi.w  #$0040,d0       ;is it MOVEA?
        beq     MOVEA           ;if so, go do MOVEA
        lea     mMOVE,a0        ;load "MOVE"
        bsr     writs           ;write it
        bsr     dot
        bsr     findend         ;write the size
        bsr     spc
        move.w  d1,d0
        bsr     writea          ;write source operand
        bsr     comma
        move.w  d1,d0
        ror.w   #$01,d0         ;these rols and rors make dest. op. std.
        rol.b   #$03,d0
        ror.w   #$08,d0
        ror.b   #$03,d0
        ror.w   #$05,d0         ;dest. op. now looks like source op.
        bsr     writea          ;write it
        bra     disend
MOVEA:  move.b  siz,d0          ;load the size.
        cmpi.b  #$42,d0         ;is it a byte?
        beq     ILLEG           ;if so, this is not a valid instruction
        lea     mMOVEA,a0       ;load "MOVEA"
        bsr     writs           ;write it
        bsr     dot
        bsr     findend         ;write the size
        bsr     spc
        move.w  d1,d0
        bsr     writea          ;write source operand
        bsr     comma
        move.w  d1,d0
        rol.w   #$07,d0         ;get destination into rightmost
        andi.w  #$07,d0         ;mask off the destination bits
        bsr     wareg           ;write it
        bra     disend

gr4:    move.w  d1,d0
NOP:    cmpi.w  #$4e71,d0       ;is it a NOP?
        bne     RESET           ;no
        lea     mNOP,a0         ;yes, print
        bsr     writs           ;write it
        bra     disend
RESET:  cmpi.w  #$4e70,d0       ;is it RESET?
        bne     RTE             ;no
        lea     mRESET,a0       ;yes, print
        bsr     writs           ;write it
        bra     disend
RTE:    cmpi.w  #$4e73,d0       ;is it RTE?
        bne     RTR             ;no
        lea     mRTE,a0         ;yes, print
        bsr     writs           ;write it
        bra     disend
RTR:    cmpi.w  #$4e77,d0       ;is it RTR?
        bne     RTS             ;no
        lea     mRTR,a0         ;yes, print
        bsr     writs           ;write it
        bra     disend
RTS:    cmpi.w  #$4e75,d0       ;is it RTS?
        bne     STOP            ;no
        lea     mRTS,a0         ;yes, print
        bsr     writs           ;write it
        bra     disend
STOP:   cmpi.w  #$4e72,d0       ;is it STOP?
        bne     TRAPV           ;no
        lea     mSTOP,a0        ;yes, print
        bsr     writs           ;write it
        bsr     spc
        bsr     pound
        bsr     dollar
        move.w  (a1)+,d0        ;load data word
        bsr     writw           ;write it
        bra     disend
TRAPV:  cmpi.w  #$4e76,d0       ;is it TRAPV?
        bne     JMP             ;no
        lea     mTRAPV,a0       ;yes, print
        bsr     writs           ;write it
        bra     disend
JMP:    andi.w  #$0fc0,d0       ;mask bits for one <ea> operations
        cmpi.w  #$0ec0,d0       ;is it JMP?
        bne     JSR             ;no
        move.w  d1,d0
        andi.w  #$0038,d0       ;check to see if it's a valid mode
        beq     ILLEG
        cmpi.w  #$0008,d0       ;these are not
        beq     ILLEG
        cmpi.w  #$0018,d0       ;valid modes with
        beq     ILLEG
        cmpi.w  #$0020,d0       ;this instruction
        beq     ILLEG
        lea     mJMP,a0         ;yes, print
        bsr     writs
        bra     gtea0           ;go write operand
JSR:    cmpi.w  #$0e80,d0       ;is it JSR?
        bne     MOVtc           ;no
        move.w  d1,d0
        andi.w  #$0038,d0       ;check to see if it's a valid mode
        beq     ILLEG
        cmpi.w  #$0008,d0       ;these are not
        beq     ILLEG
        cmpi.w  #$0018,d0       ;valid modes with
        beq     ILLEG
        cmpi.w  #$0020,d0       ;this instruction
        beq     ILLEG
        lea     mJSR,a0         ;yes, print
        bsr     writs
        bra     gtea0           ;go write operand
MOVtc:  cmpi.w  #$04c0,d0       ;is it MOVEtoccr?
        bne     MOVfc           ;no
        move.w  d1,d0
        andi.w  #$0038,d0       ;check to see if it's a valid mode
        cmpi.w  #$0008,d0       ;these are not
        beq     ILLEG
        lea     mMOVE,a0        ;yes, print
        bsr     writs
        bsr     spc
        move.w  d1,d0
        bsr     writea          ;write the source operand
        bsr     comma
        lea     mccr,a0         ;load "ccr"
        bsr     writs
        bra     disend
MOVfc:  cmpi.w  #$02c0,d0       ;is it MOVEfromccr?
        bne     MOVts           ;no
        move.w  d1,d0
        andi.w  #$0038,d0       ;check to see if it's a valid mode
        cmpi.w  #$0008,d0       ;these are not
        beq     ILLEG
        lea     mMOVE,a0        ;yes, print
        bsr     writs
        bsr     spc
        lea     mccr,a0         ;load "ccr"
        bsr     writs           ;write it
        bsr     comma
        move.w  d1,d0
        bsr     writea          ;write the operand
        bra     disend
MOVts:  cmpi.w  #$06c0,d0       ;is it MOVEtosr?
        bne     MOVfs           ;no
        move.w  d1,d0
        andi.w  #$0038,d0       ;check to see if it's a valid mode
        cmpi.w  #$0008,d0       ;these are not
        beq     ILLEG
        lea     mMOVE,a0        ;yes, print
        bsr     writs
        bsr     spc
        move.w  d1,d0
        bsr     writea          ;write the source operand
        bsr     comma
        lea     msr,a0          ;load "sr"
        bsr     writs
        bra     disend
MOVfs:  cmpi.w  #$00c0,d0       ;is it MOVEfromsr?
        bne     NBCD            ;no
        move.w  d1,d0
        andi.w  #$0038,d0       ;check to see if it's a valid mode
        cmpi.w  #$0008,d0       ;these are not
        beq     ILLEG
        lea     mMOVE,a0        ;yes, print
        bsr     writs
        bsr     spc
        lea     msr,a0          ;load "sr"
        bsr     writs
        bsr     comma
        move.w  d1,d0
        bsr     writea          ;write the operand
        bra     disend
NBCD:   cmpi.w  #$0800,d0       ;is it NBCD?
        bne     PEA             ;no
        move.w  d1,d0
        andi.w  #$0038,d0       ;check to see if it's a valid mode
        cmpi.w  #$0008,d0       ;these are not
        beq     ILLEG
        lea     mNBCD,a0        ;yes, print
        bsr     writs
        bra     gtea0           ;go write operand
PEA:    cmpi.w  #$0840,d0       ;is it PEA?
        bne     TAS             ;no
        move.w  d1,d0
        andi.w  #$0038,d0       ;check to see if it's a valid mode
        beq     SWAP
        cmpi.w  #$0008,d0       ;these are not
        beq     ILLEG
        cmpi.w  #$0018,d0       ;valid modes with
        beq     ILLEG
        cmpi.w  #$0020,d0       ;this instruction
        beq     ILLEG
        lea     mPEA,a0         ;yes, print
        bsr     writs
        bra     gtea0           ;go write operand
TAS:    cmpi.w  #$0AC0,d0       ;is it TAS?
        bne     CLR             ;no
        move.w  d1,d0
        andi.w  #$0038,d0       ;check to see if a valid mode
        cmpi.w  #$0008,d0       ;these are not
        beq     ILLEG
        cmpi.w  #$0038,d0       ;special modes
        bne     tasok
        move.w  d1,d0
        andi.w  #$0006,d0
        bne     ILLEG           ;certain of them are bad
tasok:  lea     mTAS,a0         ;yes, print
        bsr     writs
gtea0:  bsr     spc
        move.w  d1,d0
        bsr     writea          ;write the operand
        bra     disend
CLR:    andi.w  #$0f00,d0       ;mask <ea> + <size> operations
        cmpi.w  #$0200,d0       ;is it clr?
        bne     NEG             ;no
        move.w  d1,d0
        andi.w  #$0038,d0       ;check to see if it's a valid mode
        cmpi.w  #$0008,d0       ;these are not
        beq     ILLEG
        lea     mCLR,a0         ;yes, print
        bsr     writs
        bra     gtea1           ;go write operand
NEG:    cmpi.w  #$0400,d0       ;is it NEG?
        bne     NEGX            ;no
        move.w  d1,d0
        andi.w  #$0038,d0       ;check to see if it's a valid mode
        cmpi.w  #$0008,d0       ;these are not
        beq     ILLEG
        lea     mNEG,a0         ;yes, print
        bsr     writs
        bra     gtea1           ;go write operand
NEGX:   cmpi.w  #$0000,d0       ;is it NEGX?
        bne     NOT             ;no
        move.w  d1,d0
        andi.w  #$0038,d0       ;check to see if it's a valid mode
        cmpi.w  #$0008,d0       ;these are not
        beq     ILLEG
        lea     mNEGX,a0        ;yes, print
        bsr     writs
        bra     gtea1           ;go write operand
NOT:    cmpi.w  #$0600,d0       ;is it NOT?
        bne     TST             ;no
        move.w  d1,d0
        andi.w  #$0038,d0       ;check to see if it's a valid mode
        cmpi.w  #$0008,d0       ;these are not
        beq     ILLEG
        lea     mNOT,a0         ;yes, print
        bsr     writs
        bra     gtea1           ;go write operand
TST:    cmpi.w  #$0A00,d0       ;is it TST?
        bne     BKPT            ;no
        move.w  d1,d0
        andi.w  #$0038,d0       ;check to see if it's a valid mode
        cmpi.w  #$0008,d0       ;these are not
        beq     ILLEG
        lea     mTST,a0         ;yes, print
        bsr     writs
gtea1:  bsr     dot
        move.w  d1,d0
        bsr     findsiz         ;print the operand length
        bsr     spc
        move.w  d1,d0
        bsr     writea          ;print the operand
        bra     disend
BKPT:   move.w  d1,d0
        andi.w  #$fff8,d0       ;mask out the operand
        cmpi.w  #$4848,d0       ;is it BKPT?
        bne     LINK            ;no
        lea     mBKPT,a0        ;yes, print
        bsr     writs           ;write it
        bsr     spc
        move.w  d1,d0
        andi.w  #$0007,d0       ;mask BKPT number
        addi.b  #$30,d0         ;make it an ascii numeral
        bsr     writ            ;write it
        bra     disend
LINK:   move.w  d1,d0
        andi.w  #$0f00,d0       ;look at bits 8-11
        cmpi.w  #$0e00,d0       ;is it an E?
        bne     SWAP            ;no
        move.w  d1,d0
        andi.w  #$fff8,d0       ;mask off reg number
        cmpi.w  #$4e50,d0       ;is it a LINK?
        bne     MOVEsp          ;no
        lea     mLINK,a0        ;load "LINK"
        bsr     writs           ;write it
        bsr     spc
        move.w  d1,d0
        andi.w  #$0007,d0       ;mask reg bits
        bsr     wareg           ;write it
        bsr     comma
        bsr     pound
        bsr     dollar
        move.w  (a1)+,d0        ;load displacement
        bsr     writw           ;write it
        bra     disend
MOVEsp: move.w  d1,d0
        andi.w  #$fff0,d0       ;mask off operand bits
        cmpi.w  #$4e60,d0       ;is it MOVEusp?
        bne     TRAP            ;no
        lea     mMOVE,a0        ;yes, so load "MOVE"
        bsr     writs           ;write it
        bsr     spc
        move.w  d1,d0
        andi.w  #$0008,d0       ;mask direction bit
        bne     MOVEts          ;if zero, move to usp
        move.w  d1,d0
        andi.w  #$0007,d0       ;mask reg bits
        bsr     wareg           ;write it
        bsr     comma
        lea     musp,a0         ;load "usp"
        bsr     writs           ;write it
        bra     disend
MOVEts: lea     musp,a0         ;load "usp"
        bsr     writs           ;write it
        bsr     comma
        move.w  d1,d0
        andi.w  #$0007,d0       ;mask reg bits
        bsr     wareg           ;write it
        bra     disend
TRAP:   move.w  d1,d0
        andi.w  #$fff0,d0       ;mask operand if TRAP
        cmpi.w  #$4e40,d0       ;is it TRAP?
        bne     SWAP            ;no
        lea     mTRAP,a0        ;yes
        bsr     writs
        bsr     spc
        bsr     pound
        bsr     dollar
        move.b  d1,d0
        andi.b  #$0f,d0         ;mask off trap number
        bsr     writb           ;write it
        bra     disend
SWAP:   move.w  d1,d0
        andi.w  #$fff8,d0       ;mask off operand if SWAP
        cmpi.w  #$4840,d0       ;is it SWAP?
        bne     UNLK            ;no
        lea     mSWAP,a0        ;load "swap"
        bsr     writs           ;write it
        bsr     spc
        move.w  d1,d0
        andi.w  #$0007,d0       ;mask off the reg bits
        bsr     wdreg           ;write the reg
        bra     disend
UNLK:   cmpi.w  #$4e58,d0       ;is it UNLK?
        bne     LEA             ;no
        lea     mUNLK,a0        ;load "UNLK"
        bsr     writs           ;write it
        bsr     spc
        move.w  d1,d0
        andi.w  #$0007,d0       ;mask off reg number
        bsr     wareg           ;write it
        bra     disend
LEA:    move.w  d1,d0
        andi.w  #$f1c0,d0       ;mask for lea
        cmpi.w  #$41c0,d0       ;is it LEA?
        bne     CHK             ;no
        move.w  d1,d0
        andi.w  #$0038,d0       ;check to see if it's a valid mode
        beq     ILLEG
        cmpi.w  #$0008,d0       ;these are not
        beq     ILLEG
        cmpi.w  #$0018,d0       ;valid modes with
        beq     ILLEG
        cmpi.w  #$0020,d0       ;this instruction
        beq     ILLEG
        lea     mLEA,a0         ;load "LEA"
        bsr     writs           ;write it
        bsr     spc
        move.w  d1,d0
        bsr     writea          ;write source op
        bsr     comma
        move.w  d1,d0
        andi.w  #$0e00,d0       ;mask reg number
        rol.w   #$07,d0         ;get reg in rightmost bits
        bsr     wareg           ;write it
        bra     disend
CHK:    cmpi.w  #$4180,d0       ;is it CHK?
        bne     EXT             ;no
        move.w  d1,d0
        andi.w  #$0038,d0       ;check to see if it's a valid mode
        cmpi.w  #$0008,d0       ;these are not
        beq     ILLEG
        lea     mCHK,a0         ;load "CHK"
        bsr     writs           ;write it
        move.b  #$77,siz        ;size is word
        bsr     spc
        move.w  d1,d0
        bsr     writea          ;write source operand
        bsr     comma
        move.w  d1,d0
        andi.w  #$0e00,d0       ;mask reg number
        rol.w   #$07,d0         ;get into rightmost bits
        bsr     wdreg           ;write it
        bra     disend
EXT:    move.w  d1,d0
        andi.w  #$ffb8,d0       ;mask all pertinent bits
        cmpi.w  #$4880,d0       ;is it EXT?
        bne     MOVEC           ;no
        lea     mEXT,a0         ;yes, load "EXT"
        bsr     writs           ;write it
        bsr     dot
        move.w  d1,d0
        andi.w  #$0040,d0       ;mask the size bit
        bne     lext            ;size long
        move.b  #$77,d0         ;size word, load 'W'
        bsr     writ            ;write it
        bra     ext1
lext:   move.b  #$6c,d0         ;load 'L'
        bsr     writ            ;write it
ext1:   bsr     spc
        move.w  d1,d0
        andi.w  #$0007,d0       ;mask the reg number
        bsr     wdreg           ;write it
        bra     disend
MOVEC:  move.w  d1,d0
        andi.w  #$fffe,d0       ;mask in appropriate bits
        cmpi.w  #$4e7b,d0       ;is it a MOVEC?
        bne     MOVEM           ;no
        lea     mCOPOUT,a0      ;yes, so load "COPOUT"
        bsr     writs           ;write it
        move.w  (a1)+,d0        ;compensate for the operand word
        bra     disend
MOVEM:  move.w  d1,d0
        andi.w  #$fb80,d0       ;mask bits
        cmpi.w  #$4880,d0       ;is it MOVEM?
        bne     ILLEG           ;no
        lea     mMOVEM,a0       ;yes, load "MOVEM"
        bsr     writs
        bsr     dot
        move.w  d1,d0
        andi.w  #$0040,d0       ;mask MOVEM size bit
        bne     MOVEMl          ;if nonzero, longword operand
        move.b  #$77,d0         ;load 'W'
        move.b  d0,siz          ;save size as 'W'
        bsr     writ            ;write it
        bsr     spc
        bra     MOVEMo          ;go write operands
MOVEMl: move.b  #$6c,d0         ;load 'L'
        move.b  d0,siz          ;save size as 'L'
        bsr     writ            ;write it
        bsr     spc
MOVEMo: move.w  d1,d0
        andi.w  #$0400,d0       ;which direction?
        bne     MOVEMr          ;to reg
        bsr     dollar
        move.w  (a1)+,d0        ;load the reg list
        bsr     writw           ;write it
        bsr     comma
        move.w  d1,d0
        bsr     writea          ;write the address
        bra     disend
MOVEMr: move.w  (a1)+,t1        ;save the reg list
        move.w  d1,d0
        bsr     writea          ;write the address
        bsr     comma
        bsr     dollar
        move.w  t1,d0           ;reload the reg list
        bsr     writw           ;write it
        bra     disend
ILLEG:  lea     mILLEG,a0       ;yes, print
        bsr     writs           ;write it
        bra     disend

gr5:    move.w  d1,d0           ;refresh the instruction word
        and.w   #$00c0,d0       ;mask bits 6-7
        cmp.w   #$00c0,d0       ;DBcc/Scc?
        bne     addq            ;no
        move.w  d1,d0           ;yes
        andi.w  #$0038,d0       ;mask DB/S bit
        cmpi.w  #$0008,d0       ;DBcc?
        bne     Sxx             ;no
        move.b  #$64,d0         ;load D into d0
        bsr     writ            ;write it
        move.b  #$62,d0         ;load B into d0
        bsr     writ            ;write it
        move.w  d1,d0           ;refresh
        bsr     findcon         ;print condition
        bsr     spc
        move.w  d1,d0           ;refresh
        andi.w  #$0007,d0       ;mask out reg
        bsr     wdreg           ;write reg
        bsr     comma
        clr.w   d0              ;zero d0 so wdis looks for word disp.
        bsr     wdis            ;print the address
        bra     disend

Sxx:    move.b  #$72,d0         ;load S into d0
        bsr     writ            ;write it
        move.w  d1,d0           ;refresh
        bsr     findcon         ;print condition
        bsr     spc
        move.w  d1,d0
        bsr     writea          ;write operand
        bra     disend

findcon:lea     contab,a0       ;load location of beginning of table
        andi.w  #$0f00,d0       ;mask off the condition
        ror.w   #$07,d0         ;make condition a word offset
        adda.w  d0,a0           ;add to table location to get ascii
        move.b  (a0)+,d0        ;load the first byte
        bsr     writ            ;write it
        move.b  (a0)+,d0        ;load the second byte
        bsr     writ            ;write it
        rts

contab: dc.b    "t "
        dc.b    "f "
        dc.b    "hi"
        dc.b    "ls"
        dc.b    "cc"
        dc.b    "cs"
        dc.b    "ne"
        dc.b    "eq"
        dc.b    "vc"
        dc.b    "vs"
        dc.b    "pl"
        dc.b    "mi"
        dc.b    "ge"
        dc.b    "lt"
        dc.b    "gt"
        dc.b    "le"

addq:   move.w  d1,d0
        andi.w  #$0100,d0       ;addq/subq
        bne     subq
        lea     mADDQ,a0        ;load "addq"
        bra     qwrit
subq:   lea     mSUBQ,a0        ;load "subq"
qwrit:  bsr     writs           ;write it
        bsr     dot
        move.w  d1,d0
        bsr     findsiz         ;write size of operand
        bsr     spc
        bsr     pound
        bsr     dollar
        move.w  d1,d0
        andi.w  #$0e00,d0       ;mask data
        rol.w   #$07,d0         ;get into rightmost bits
        bne     q8              ;if nonzero, range is 1-7
        move.b  #$08,d0         ;if zero, range is 8
q8:     bsr     writb           ;write byte
        bsr     comma
        move.w  d1,d0
        bsr     writea          ;write dest
        bra     disend

gr6:    move.w  d1,d0
        andi.w  #$0f00,d0       ;mask the cond bit
        bne     BSR             ;not BRA
        lea     mBRA,a0         ;load "bra"
        bsr     writs           ;write it
        bra     Bccw            ;go write operand
BSR:    cmp.w   #$0100,d0       ;BSR?
        bne     Bcc             ;no
        lea     mBSR,a0         ;load "bsr"
        bsr     writs           ;write it
        bra     Bccw            ;go write operand
Bcc:    move.b  #$62,d0         ;load a B
        bsr     writ            ;write it
        move.w  d1,d0
        bsr     findcon         ;print the condition
Bccw:   bsr     spc
        move.w  d1,d0
        bsr     wdis            ;write the address
        bra     disend

gr7:    move.w  d1,d0
        andi.w  #$0100,d0       ;check to make sure
        bne     ILLEG
        lea     mMOVEQ,a0       ;load "MOVEQ"
        bsr     writs           ;write it
        bsr     spc
        bsr     pound
        bsr     dollar
        move.b  d1,d0           ;load data
        bsr     writb           ;write it
        bsr     comma
        move.w  d1,d0
        andi.w  #$0e00,d0       ;mask off the reg bits
        rol.w   #$07,d0         ;get into rightmost bits
        bsr     wdreg           ;write it
        bra     disend

gr8:    move.w  d1,d0
        andi.w  #$01f0,d0       ;mask for SBCD.
        cmpi.w  #$0100,d0       ;is it SBCD?
        bne     DIVS
        lea     mSBCD,a0        ;load "SBCD"
xBCD:   bsr     writs           ;write it
        move.w  d1,d0
        andi.w  #$0008,d0       ;mask reg/memory bit
        beq     sbcdrg          ;reg to reg op
        bsr     spc
        bsr     minus
        bsr     lparen
        move.w  d1,d0
        andi.w  #$0007,d0       ;mask source reg
        bsr     wareg           ;print it
        bsr     rparen
        bsr     comma
        bsr     minus
        bsr     lparen
        move.w  d1,d0
        andi.w  #$0e00,d0       ;mask destination reg
        rol.w   #$07,d0         ;get into rightmost bits
        bsr     wareg           ;print it
        bsr     rparen
        bra     disend
sbcdrg: bsr     spc
        move.w  d1,d0
        andi.w  #$0007,d0       ;mask source reg
        bsr     wdreg
        bsr     comma
        move.w  d1,d0
        andi.w  #$0e00,d0       ;mask destination reg
        rol.w   #$07,d0         ;get into rightmost bits
        bsr     wdreg           ;print it
        bra     disend

DIVS:   move.w  d1,d0
        andi.w  #$00c0,d0       ;mask mode bits
        cmpi.w  #$00c0,d0       ;is this a DIV operation
        bne     OR              ;no.
        move.w  d1,d0           ;yes.
        andi.w  #$0100,d0       ;mask the sign bit
        beq     DIVU            ;it's unsigned divide
        lea     mDIVS,a0        ;load "DIVS"
        bsr     writs           ;write it
        bra     divprt          ;go decode the rest of the command
DIVU:   lea     mDIVU,a0        ;load "DIVU"
        bsr     writs           ;write it
divprt: bsr     spc
        move.w  d1,d0
        bsr     writea
        bsr     comma
        move.w  d1,d0
        andi.w  #$0e00,d0       ;mask data reg
        rol.w   #$07,d0         ;get into rightmost bits
        bsr     wdreg           ;print it
        bra     disend

OR:     lea     mOR,a0          ;load "OR"
ANDent: bsr     writs           ;write it
        bsr     dot
        move.w  d1,d0
        bsr     findsiz         ;print operand size
        bsr     spc
        move.w  d1,d0
        andi.w  #$0100,d0       ;find destination
        beq     ordreg          ;if zero, data reg
        move.w  d1,d0
        andi.w  #$0e00,d0       ;mask the reg bits
        rol.w   #$07,d0         ;get into rightmost bits
        bsr     wdreg           ;and print it
        bsr     comma
        move.w  d1,d0
        bsr     writea          ;write the destination
        bra     disend
ordreg: move.w  d1,d0
        bsr     writea          ;write the source
        bsr     comma
        move.w  d1,d0
        andi.w  #$0e00,d0       ;mask the reg bits
        rol.w   #$07,d0         ;get into rightmost bits
        bsr     wdreg           ;and print it
        bra     disend

gr9:    lea     mSUB,a0         ;load "SUB"
        bsr     writs           ;write it
ax:     move.w  d1,d0
        andi.w  #$00c0,d0       ;mask the size bits
        cmpi.w  #$00c0,d0       ;is it ADDA or SUBA?
        bne     SUB             ;no
        move.b  #$61,d0         ;yes, so load an 'A'
        bsr     writ            ;write it
        bsr     dot
        move.w  d1,d0
        andi.w  #$0100,d0       ;mask size bit
        bne     SUBAl           ;if set, longword operand
        move.b  #$77,d0         ;load 'W'
        bsr     writ            ;write it
        bra     axa             ;go print operands
SUBAl:  move.b  #$6c,d0         ;load 'L'
        bsr     writ            ;write it
        bra     axa             ;go print operands
SUB:    move.w  d1,d0
        andi.w  #$0130,d0       ;mask appropriate bits
        cmpi.w  #$0100,d0       ;is it ADDX or SUBX?
        beq     SUBX            ;yes
        bsr     dot             ;no, so continue
        move.w  d1,d0
        bsr     findsiz         ;print the size of the operand
axa:    bsr     spc
        move.w  d1,d0
        andi.w  #$00c0,d0       ;mask the size bits
        cmpi.w  #$00c0,d0       ;is it ADDA or SUBA
        beq     subea1          ;if so, <ea> is first operand
        move.w  d1,d0
        andi.w  #$0100,d0       ;mask direction bit
        bne     subea2          ;if bit is set, <ea> is last operand
        move.w  d1,d0
        bsr     writea          ;write the first operand
        bsr     comma
        move.w  d1,d0
        andi.w  #$0e00,d0       ;mask the reg bits
        rol.w   #$07,d0         ;get into rightmost bits
        bsr     wdreg           ;print it
        bra     disend
subea1: move.w  d1,d0
        bsr     writea          ;write the first operand
        bsr     comma
        move.w  d1,d0
        andi.w  #$0e00,d0       ;mask the reg bits
        rol.w   #$07,d0         ;get into rightmost bits
        bsr     wareg           ;print it
        bra     disend
subea2: move.w  d1,d0
        andi.w  #$0e00,d0       ;mask the reg bits
        rol.w   #$07,d0         ;get into rightmost bits
        bsr     wdreg           ;print it
        bsr     comma
        move.w  d1,d0
        bsr     writea          ;write second operand
        bra     disend

SUBX:   move.b  #$78,d0         ;load an 'X'
        bsr     writ            ;write it
        bsr     dot
        move.w  d1,d0
        bsr     findsiz         ;write the operand length
        bsr     spc
        move.w  d1,d0
        andi.w  #$0008,d0       ;mask reg/memory bit
        beq     SUBXdr          ;reg to reg op
        bsr     minus
        bsr     lparen
        move.w  d1,d0
        andi.w  #$0007,d0       ;mask source reg
        bsr     wareg           ;print it
        bsr     rparen
        bsr     comma
        bsr     minus
        bsr     lparen
        move.w  d1,d0
        andi.w  #$0e00,d0       ;mask destination reg
        rol.w   #$07,d0         ;get into rightmost bits
        bsr     wareg           ;print it
        bsr     rparen
        bra     disend
SUBXdr: move.w  d1,d0
        andi.w  #$0007,d0       ;mask source reg
        bsr     wdreg
        bsr     comma
        move.w  d1,d0
        andi.w  #$0e00,d0       ;mask destination reg
        rol.w   #$07,d0         ;get into rightmost bits
        bsr     wdreg           ;print it
        bra     disend

gra:    bra     ILLEG           ;not a valid instruction

grb:    move.w  d1,d0
        andi.w  #$00c0,d0       ;mask size bits
        cmpi.w  #$00c0,d0       ;size = 11 ?
        bne     CMP             ;no.
        lea     mCMPA,a0        ;yes, so load "CMPA"
        bsr     writs           ;write it
        bsr     dot
        move.w  d1,d0
        andi.w  #$0100,d0       ;mask CMPA size bit
        bne     CMPAl           ;if nonzero, longword operand
        move.b  #$77,d0         ;load 'W'
        move.b  d0,siz          ;save size as 'W'
        bsr     writ            ;write it
        bra     CMPAop          ;go write operands
CMPAl:  move.b  #$6c,d0         ;load 'L'
        move.b  d0,siz          ;save size as 'L'
        bsr     writ            ;write it
CMPAop: bsr     spc
        move.w  d1,d0
        bsr     writea          ;go write source operand
        bsr     comma
        move.w  d1,d0
        andi.w  #$0e00,d0       ;mask reg number
        rol.w   #$07,d0         ;get into rightmost bits
        bsr     wareg           ;write it
        bra     disend
CMP:    move.w  d1,d0
        andi.w  #$0100,d0       ;mask CMP/CMPM bit
        bne     CMPM            ;if nonzero, it's CMPM
        lea     mCMP,a0         ;load "CMP"
        bsr     writs           ;write it
        bsr     dot
        move.w  d1,d0
        bsr     findsiz         ;write size of operand
        bsr     spc
        move.w  d1,d0
        bsr     writea          ;write source operand
        bsr     comma
        move.w  d1,d0
        andi.w  #$0e00,d0       ;mask reg number
        rol.w   #$07,d0         ;get into rightmost bits
        bsr     wdreg           ;write it
        bra     disend
CMPM:   move.w  d1,d0
        andi.w  #$0038,d0       ;mask mode bits
        cmpi.w  #$0008,d0       ;is it address reg mode?
        bne     EOR             ;if not, it's an EOR
        lea     mCMPM,a0        ;load "CMPM"
        bsr     writs           ;write it
        bsr     dot
        move.w  d1,d0
        bsr     findsiz         ;write the operand size
        bsr     spc
        bsr     lparen
        move.w  d1,d0
        andi.w  #$0007,d0       ;mask source reg bits
        bsr     wareg           ;write it
        bsr     rparen
        bsr     plus
        bsr     comma
        bsr     lparen
        move.w  d1,d0
        andi.w  #$0e00,d0       ;mask destination reg bits
        rol.w   #$07,d0         ;get into rightmost bits
        bsr     wareg           ;write it
        bsr     rparen
        bsr     plus
        bra     disend
EOR:    lea     mEOR,a0         ;load "EOR"
        bsr     writs           ;write it
        bsr     dot
        move.w  d1,d0
        bsr     findsiz         ;write operand size
        bsr     spc
        move.w  d1,d0
        andi.w  #$0e00,d0       ;mask reg number
        rol.w   #$07,d0         ;get into rightmost bits
        bsr     wdreg           ;write it
        bsr     comma
        move.w  d1,d0
        bsr     writea          ;write destination
        bra     disend

grc:    move.w  d1,d0
        andi.w  #$01f0,d0       ;mask for ABCD
        cmpi.w  #$0100,d0       ;is it ABCD?
        bne     MULS            ;no.
        lea     mABCD,a0        ;load "ABCD"
        bra     xBCD            ;go print everything
MULS:   move.w  d1,d0
        andi.w  #$00c0,d0       ;mask mode bits
        cmpi.w  #$00c0,d0       ;is this a MUL operation?
        bne     EXG             ;no.
        move.w  d1,d0           ;yes.
        andi.w  #$0100,d0       ;mask the sign bit
        beq     MULU            ;it's unsigned multiply
        lea     mMULS,a0        ;load "MULS"
        bsr     writs           ;write it
        bra     divprt          ;go decode the rest of the command
MULU:   lea     mMULU,a0        ;load "MULU"
        bsr     writs           ;write it
        bra     divprt          ;go decode the rest of the command
EXG:    move.w  d1,d0
        andi.w  #$0130,d0       ;mask for EXG
        cmpi.w  #$0100,d0       ;is it EXG?
        bne     AND             ;no.
        lea     mEXG,a0         ;yes, print
        bsr     writs           ;write it
        bsr     spc
        move.w  d1,d0
        andi.w  #$00f8,d0       ;mask op-mode bits
        cmpi.w  #$0040,d0       ;is it Di,Dj?
        bne     EXGaa           ;no
        move.w  d1,d0
        andi.w  #$0e00,d0       ;mask source reg number
        rol.w   #$07,d0         ;get into rightmost bits
        bsr     wdreg           ;write it
        bsr     comma
        move.w  d1,d0
        andi.w  #$0007,d0       ;mask destination reg number
        bsr     wdreg           ;write it
        bra     disend
EXGaa:  cmpi.w  #$0048,d0       ;is it Ai,Aj?
        bne     EXGda           ;no
        move.w  d1,d0
        andi.w  #$0e00,d0       ;mask source reg number
        rol.w   #$07,d0         ;get into rightmost bits
        bsr     wareg           ;write it
        bsr     comma
        move.w  d1,d0
        andi.w  #$0007,d0       ;mask destination reg number
        bsr     wareg           ;write it
        bra     disend
EXGda:  cmpi.w  #$0088,d0       ;is it Di,Aj?
        bne     ILLEG
        move.w  d1,d0
        andi.w  #$0e00,d0       ;mask source reg number
        rol.w   #$07,d0         ;get into rightmost bits
        bsr     wdreg           ;write it
        bsr     comma
        move.w  d1,d0
        andi.w  #$0007,d0       ;mask destination reg number
        bsr     wareg           ;write it
        bra     disend
AND:    lea     mAND,a0         ;load "AND"
        bra     ANDent          ;go write the operation

grd:    lea     mADD,a0         ;load "ADD"
        bsr     writs           ;write it, then find out which ADD
        bra     ax              ;go find out which ADD it is

gre:    move.w  d1,d0
        move.w  d1,t1           ;save an extra copy of opcode
        andi.w  #$00c0,d0       ;is this an <ea> instruction?
        cmpi.w  #$00c0,d0
        bne     fshf            ;if not, find out which shift
        move.w  d1,d0           ;else adjust the saved opcode
        ror.w   #$06,d0         ;rightward by six bits to allow proper
        move.w  d0,t1           ;decoding of the shift type
fshf:   move.w  t1,d0           ;load the properly adjusted opcode
        andi.w  #$0018,d0       ;mask operation bits of adjusted opcode
        bne     LS              ;not AS
        lea     mAS,a0          ;load "AS"
        bra     lr              ;find the direction
LS:     cmpi.w  #$0008,d0       ;is it LS?
        bne     ROX             ;no
        lea     mLS,a0          ;yes, so load "LS"
        bra     lr              ;find the direction
ROX:    cmpi.w  #$0010,d0       ;is it ROX?
        bne     RO              ;no
        lea     mROX,a0         ;yes, so load "ROX"
        bra     lr
RO:     lea     mRO,a0          ;load "RO"
lr:     bsr     writs           ;write the operation
        move.w  d1,d0
        andi.w  #$0100,d0       ;mask the direction bit
        bne     lsh             ;left shift if bit set
        move.b  #$72,d0         ;load 'r'
        bra     shtyp           ;go find the shift type
lsh:    move.b  #$6c,d0         ;load 'l'
shtyp:  bsr     writ            ;write the direction
        move.w  d1,d0
        andi.w  #$00c0,d0       ;mask the size bits
        cmpi.w  #$00c0,d0       ;is the size 11?
        bne     regsh           ;if not, it's a reg shift
        bsr     spc
        move.w  d1,d0
        bsr     writea          ;write the operand
        bra     disend
regsh:  bsr     dot
        move.w  d1,d0
        bsr     findsiz         ;print the operand length
        bsr     spc
        move.w  d1,d0
        andi.w  #$0020,d0       ;mask the immediate/reg bit
        beq     immsh           ;if bit clear, it's an immediate shift
        move.w  d1,d0
        andi.w  #$0e00,d0       ;mask the count reg
        rol.w   #$07,d0         ;get into rightmost bits
        bsr     wdreg           ;write count reg
        bsr     comma
        move.w  d1,d0
        andi.w  #$0007,d0       ;mask destination reg
        bsr     wdreg           ;write destination reg
        bra     disend
immsh:  bsr     spc
        bsr     pound
        bsr     dollar
        move.w  d1,d0
        andi.w  #$0e00,d0       ;mask the count bits
        rol.w   #$07,d0         ;get into rightmost bits
        bne     sh17            ;if not zero, 1-7 bit shift
        move.b  #$08,d0         ;if zero, 8 bit shift
sh17:   bsr     writb           ;write it
        bsr     comma
        move.w  d1,d0
        andi.w  #$0007,d0       ;mask the reg bits
        bsr     wdreg           ;write the destination reg
        bra     disend

grf:    bra     ILLEG           ;not a valid instruction

;
;       message table -- the ascii strings for the instructions
;
mCOPOUT: dc.b   "COPOUT",0
mABCD:   dc.b   "abcd",0
mADD:    dc.b   "add",0
mADDA:   dc.b   "adda",0
mADDI:   dc.b   "addi",0
mADDQ:   dc.b   "addq",0
mADDX:   dc.b   "addx",0
mAND:    dc.b   "and",0
mANDI:   dc.b   "andi",0
mAS:     dc.b   "as",0
mBCHG:   dc.b   "bchg",0
mBCLR:   dc.b   "bclr",0
mBKPT:   dc.b   "bkpt",0
mBRA:    dc.b   "bra",0
mBSET:   dc.b   "bset",0
mBSR:    dc.b   "bsr",0
mBTST:   dc.b   "btst",0
mCHK:    dc.b   "chk",0
mCLR:    dc.b   "clr",0
mCMP:    dc.b   "cmp",0
mCMPA:   dc.b   "cmpa",0
mCMPI:   dc.b   "cmpi",0
mCMPM:   dc.b   "cmpm",0
mDIVS:   dc.b   "divs",0
mDIVU:   dc.b   "divu",0
mEOR:    dc.b   "eor",0
mEORI:   dc.b   "eori",0
mEORIcr: dc.b   "eoriccr",0
mEXG:    dc.b   "exg",0
mEXT:    dc.b   "ext",0
mILLEG:  dc.b   "ILLEGAL",0
mJMP:    dc.b   "jmp",0
mJSR:    dc.b   "jsr",0
mLEA:    dc.b   "lea",0
mLINK:   dc.b   "link",0
mLS:     dc.b   "ls",0
mMOVE:   dc.b   "move",0
mMOVEA:  dc.b   "movea",0
mMOVEC:  dc.b   "movec",0
mMOVEM:  dc.b   "movem",0
mMOVEP:  dc.b   "movep",0
mMOVEQ:  dc.b   "moveq",0
mMULS:   dc.b   "muls",0
mMULU:   dc.b   "mulu",0
mNBCD:   dc.b   "nbcd",0
mNEG:    dc.b   "neg",0
mNEGX:   dc.b   "negx",0
mNOP:    dc.b   "nop",0
mNOT:    dc.b   "not",0
mOR:     dc.b   "or",0
mORI:    dc.b   "ori",0
mPEA:    dc.b   "pea",0
mRESET:  dc.b   "reset",0
mRO:     dc.b   "ro",0
mROX:    dc.b   "rox",0
mRTE:    dc.b   "rte",0
mRTR:    dc.b   "rtr",0
mRTS:    dc.b   "rts",0
mSBCD:   dc.b   "sbcd",0
mSTOP:   dc.b   "stop",0
mSUB:    dc.b   "sub",0
mSUBA:   dc.b   "suba",0
mSUBI:   dc.b   "subi",0
mSUBQ:   dc.b   "subq",0
mSUBX:   dc.b   "subx",0
mSWAP:   dc.b   "swap",0
mTAS:    dc.b   "tas",0
mTRAP:   dc.b   "trap",0
mTRAPV:  dc.b   "trapv",0
mTST:    dc.b   "tst",0
mUNLK:   dc.b   "unlk",0
mccr:    dc.b   "ccr",0
msr:     dc.b   "sr",0
musp:    dc.b   "usp",0

spc:    move.b  #$20,d0         ;load a spc
        bsr     writ            ;write it
        rts

comma:  move.b  #$2c,d0         ;load a comma
        bsr     writ            ;write it
        rts

lparen: move.b  #$28,d0         ;load a left parenthesis
        bsr     writ            ;write it
        rts

rparen: move.b  #$29,d0         ;load a right parenthesis
        bsr     writ            ;write it
        rts

pound:  move.b  #$23,d0         ;load a pound sign
        bsr     writ            ;write it
        rts

dot:    move.b  #$2e,d0         ;load a period
        bsr     writ            ;write it
        rts

plus:   move.b  #$2b,d0         ;load a plus
        bsr     writ            ;write it
        rts

minus:  move.b  #$2d,d0         ;load a minus
        bsr     writ            ;write it
        rts

dollar: move.b  #$24,d0         ;load a dollar sign
        bsr     writ            ;write it
        rts

findsiz:andi.w  #$00c0,d0       ;mask out the size bits
        bne     wsize           ;if nonzero, it's not a byte
        move.b  #$62,siz        ;set size to byte
        bra     findend
wsize:  cmpi.w  #$0040,d0       ;is it a word operand?
        bne     lsize           ;no.
        move.b  #$77,siz        ;set size to word
        bra     findend
lsize:  move.b  #$6c,siz        ;set size to longword
findend:move.b  siz,d0
        bsr     writ            ;write the size
        rts

wareg:  swap    d0              ;save the reg number in upper 16 bits
        move.b  #$61,d0         ;load 'a'
        bsr     writ            ;write it
        swap    d0              ;restore the reg number
        ori.b   #$30,d0         ;add offset to get digit
        bsr     writ            ;write it
        rts

wdreg:  swap    d0              ;save the reg number in upper 16 bits
        move.b  #$64,d0         ;load 'a'
        bsr     writ            ;write it
        swap    d0              ;restore the reg number
        ori.b   #$30,d0         ;add offset to get digit
        bsr     writ            ;write it
        rts

mPC:    dc.b    "pc",0
mIAM:   dc.b    "ILLEGAL ADDRESS MODE",0
writea: move.b  d0,writm        ;save the important part of the opcode
        andi.b  #$38,d0         ;mask off all but the mode bits
        bne     mode1           ;if zero, it's data reg direct
        move.b  writm,d0
        andi.b  #$07,d0         ;mask the reg number
        bsr     wdreg           ;write the data reg
        bra     eaout
mode1:  cmpi.b  #$08,d0         ;is it address reg direct?
        bne     mode2           ;no
        move.b  writm,d0        ;yes
        andi.b  #$07,d0         ;mask reg number
        bsr     wareg           ;write address reg
        bra     eaout
mode2:  cmpi.b  #$10,d0         ;is it address reg indirect?
        bne     mode3           ;no
        bsr     lparen          ;yes
        move.b  writm,d0
        andi.b  #$07,d0         ;mask reg number
        bsr     wareg           ;write address reg
        bsr     rparen
        bra     eaout
mode3:  cmpi.b  #$18,d0         ;is it postincrement?
        bne     mode4           ;no
        bsr     lparen          ;yes
        move.b  writm,d0
        andi.b  #$07,d0         ;mask reg number
        bsr     wareg           ;write address reg
        bsr     rparen
        bsr     plus
        bra     eaout
mode4:  cmpi.b  #$20,d0         ;is it predecrement?
        bne     mode5           ;no
        bsr     minus           ;yes
        bsr     lparen
        move.b  writm,d0
        andi.b  #$07,d0         ;mask reg number
        bsr     wareg           ;write address reg
        bsr     rparen
        bra     eaout
mode5:  cmpi.b  #$28,d0         ;is it reg indirect w/ displacement?
        bne     mode6           ;no
        bsr     dollar
        move.w  (a1)+,d0        ;yes, so load 16 bit displacement
        bsr     writw           ;write it
        bsr     lparen
        move.b  writm,d0
        andi.b  #$07,d0         ;mask reg number
        bsr     wareg           ;write address reg
        bsr     rparen
        bra     eaout
mode6:  cmpi.b  #$30,d0         ;is it reg indirect w/ index?
        bne     mode7           ;no
        bsr     dollar
        move.w  (a1),d0         ;load the index word
        bsr     writb           ;write the 8 bit displacement
        bsr     lparen
        move.b  writm,d0
        andi.b  #$07,d0         ;mask reg number
        bsr     wareg           ;write address reg
        bsr     comma
m6ad:   move.w  (a1),d0         ;load index word again
        bpl     m6d             ;if MSB of index word is 0, data reg
        rol.w   #$04,d0         ;rotate reg number into rightmost bits
        andi.w  #$0007,d0       ;mask reg number
        bsr     wareg           ;write address reg
        bra     m6no
m6d:    rol.w   #$04,d0         ;rotate reg number into rightmost bits
        andi.w  #$0007,d0       ;mask reg number
        bsr     wdreg           ;write data reg
m6no:   bsr     dot
        move.w  (a1)+,d0        ;load the index reg a final time
        andi.w  #$0800,d0       ;mask the length bit
        bne     m6l             ;if nonzero, long reg index
        move.b  #$77,d0         ;load 'w'
        bsr     writ            ;write it
        bsr     rparen
        bra     eaout
m6l:    move.b  #$6c,d0         ;load 'l'
        bsr     writ            ;write it
        bsr     rparen
        bra     eaout
mode7:  move.b  writm,d0        ;mode seven, so decode reg number
        andi.w  #$07,d0         ;mask reg number
        bne     m71             ;if zero, absolute.w
        bsr     dollar
        move.w  (a1)+,d0        ;move the address into d0
        bsr     writw           ;write it
        bra     eaout
m71:    cmpi.b  #$01,d0         ;is it absolute.l?
        bne     m72             ;no
        bsr     dollar
        move.l  (a1)+,d0        ;yes, so move the address into d0
        bsr     writl           ;write it
        bra     eaout
m72:    cmpi.b  #$02,d0         ;is it relative w/ displacement?
        bne     m73             ;no
        bsr     dollar
        move.w  (a1)+,d0        ;yes, so load displacement into d0
        bsr     writw           ;write it
        bsr     lparen
        lea     mPC,a0          ;load "PC"
        bsr     writs           ;write it
        bsr     rparen
        bra     eaout
m73:    cmpi.b  #$03,d0         ;is it relative w/ index?
        bne     m74             ;no
        bsr     dollar
        move.w  (a1),d0         ;load the index word
        bsr     writb           ;write the 8 bit displacement
        bsr     lparen
        lea     mPC,a0          ;load "PC"
        bsr     writs           ;write it
        bsr     comma
        bra     m6ad            ;go to reg. indir. routine to finish
m74:    cmpi.b  #$04,d0         ;is it immediate?
        bne     m75             ;no
        bsr     pound
        bsr     dollar
        move.b  siz,d0          ;load the size byte
        cmpi.b  #$62,d0         ;is it byte data?
        bne     m74w            ;no
        move.w  (a1)+,d0        ;yes, so load immediate data
        bsr     writb           ;write byte data
        bra     eaout
m74w:   cmpi.b  #$77,d0         ;is it word data?
        bne     m74l            ;no
        move.w  (a1)+,d0        ;yes, so load immediate data
        bsr     writw           ;write word data
        bra     eaout
m74l:   move.l  (a1)+,d0        ;load long immediate data
        bsr     writl           ;write long data
        bra     eaout
m75:    lea     mIAM,a0         ;load illegal mode message
        bsr     writs           ;write it
eaout:  rts

wdis:   swap    d0              ;save opcode in upper 16 so we can
        bsr     dollar          ;hexidecimalize the displacement
        swap    d0              ;get it back in lower 16
        move.l  a1,d1           ;copy current address to d1
        tst.b   d0              ;is displacement zero?
        beq     wdisw           ;if so, word displacement
        andi.l  #$00ff,d0       ;mask off the displacement
        ext.w   d0              ;sign extend the displacement
        ext.l   d0              ;to word size
        add.l   d0,d1           ;add 8-bit displacement to address
        move.l  d1,d0           ;copy into d0
        bsr     writl           ;write address
        bra     wdiso
wdisw:  move.w  (a1)+,d0        ;load the displacement word
        ext.l   d0              ;sign extend it
        add.l   d0,d1           ;add displacement
        move.l  d1,d0           ;copy to d0
        bsr     writl
wdiso:  rts
;
;************************************
;*                                  *
;*       Monitor data area          *
;*                                  *
;************************************
;
        org     $00004000
utrapb: ds.l    1
utrapc: ds.l    1
utrapd: ds.l    1
utrape: ds.l    1
utrapf: ds.l    1

userv1: ds.l    1
userv2: ds.l    1
userv3: ds.l    1
userv4: ds.l    1
userv5: ds.l    1

uav3:   ds.l    1
uav4:   ds.l    1
uav5:   ds.l    1
uav6:   ds.l    1
uav7:   ds.l    1

sarea:  ds.w    128                     ;system stack
stack   =       *
bktab:  ds.w    10                      ;breakpoint table
_sr:    ds.w    1                   ;register save area
_pc:    ds.l    1
dr0:    ds.l    1
dr1:    ds.l    1
dr2:    ds.l    1
dr3:    ds.l    1
dr4:    ds.l    1
dr5:    ds.l    1
dr6:    ds.l    1
dr7:    ds.l    1
ar0:    ds.l    1
ar1:    ds.l    1
ar2:    ds.l    1
ar3:    ds.l    1
ar4:    ds.l    1
ar5:    ds.l    1
ar6:    ds.l    1
ar7:    ds.l    1
ptab:   ds.w    3                       ;prototype table
rexam:  ds.w    1                       ;register examination pointer
exam:   ds.w    1                       ;memory examination pointer
t1:     ds.w    1                       ;temporary work area
t2:     ds.w    1
t3:     ds.w    1
t4:     ds.w    1
t5:     ds.w    1
ctrls:  ds.w    1                       ;ctrl-s,ctrl-q flag
bkptf   equ     *-1                     ;breakpoint flag
lbuff:  ds.w    11                      ;load buffer
ibuff:  ds.w    11                      ;terminal buffer
users:  ds.w    128                     ;users stack area
ustck   equ     *
aend:   ds.w    1
siz:    ds.w    1
writm:  ds.w    1
echo:   ds.w    1                       ;terminal port echo flag

