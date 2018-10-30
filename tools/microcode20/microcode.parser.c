
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct lblrec
{
  char  *name;
  int    addr;
  int    type;
  struct lblrec *next;
};

typedef struct lblrec LBLREC;

LBLREC *lbl_tab = (LBLREC *)0;

static LBLREC *lbl_decl(char *name, int addr);
static int lbl_use(char *name, int addr);

#define LBL_DECL (0)
#define LBL_USE  (1)

extern FILE *yyin, *yyout;

int   line_num = 1;

int   jmp_idx = 0;
int   rom_addr = 0;
int   loop_addr = -1;
int  *rom_data;
int   jmp_data[256][4];
char *rom_instr;
char  buf[80];

static const char cc_str[16][6] =
{
  "A_SR",  "Z_FLG", "N_FLG", "G_FLG",
  "T[0]",  "EA4",   "EA7",   "EXT11",
  "V_SR",  "N_SR",  "B_SR",  "I_SR",
  "S_SR",  "T_SR",  "TRUE",  "IND"
};

static const char flg_str[16][6] =
{
  "KEEP",  "CLR",  "C_ADD", "C_FLG",
  "X_SR",  "N_B",  "N_W",   "N_SR",
  "T[0]",  "T[7]", "T[15]", "-",
  "N[0]",  "N[7]", "N[15]", "-"
};

static const char reg_str[8][5] =
{
  "A", "B", "INSW", "EXTW", "EA1B", "EA2B", "SR", ""
};

#define ROM_SIZE       (0x4000)

#define MODE_NONE      (-1)
#define MODE_MIF       (0)
#define MODE_MEM       (1)
#define MODE_VERILOG   (2)
#define MODE_VHDL      (3)

// Opcodes encoding
#define OPC_LOOP       ((int)0x00000)
#define OPC_CALL       ((int)0x20000)
#define OPC_CALLN      ((int)0x20800)
#define OPC_JUMP       ((int)0x30000)
#define OPC_JUMPN      ((int)0x30800)
#define OPC_LIT        ((int)0x40000)
#define OPC_FLAG       ((int)0x60000)
#define OPC_IO         ((int)0x80000)
#define OPC_REG        ((int)0xA0000)
#define OPC_ALU        ((int)0xC0000)
#define OPC_RTS        ((int)0x10000)

// Carry in source for FLAG instruction
#define CIN_KEEP       ((int)0x00000)
#define CIN_CLR        ((int)0x00800)
#define CIN_C_ADD      ((int)0x01000)
#define CIN_C_FLG      ((int)0x01800)
#define CIN_X_SR       ((int)0x02000)
#define CIN_N_B        ((int)0x02800)
#define CIN_N_W        ((int)0x03000)
#define CIN_N_SR       ((int)0x03800)
#define CIN_T0         ((int)0x04000)
#define CIN_T7         ((int)0x04800)
#define CIN_T15        ((int)0x05000)
#define CIN_N0         ((int)0x06000)
#define CIN_N7         ((int)0x06800)
#define CIN_N15        ((int)0x07000)

// Conditions encoding for JUMP and CALL
#define CC_A_SR        ((int)0x00000)
#define CC_Z_FLG       ((int)0x01000)
#define CC_N_FLG       ((int)0x02000)
#define CC_G_FLG       ((int)0x03000)
#define CC_T0          ((int)0x04000)
#define CC_EA1_4       ((int)0x05000)
#define CC_EA1_7       ((int)0x06000)
#define CC_EXT_11      ((int)0x07000)
#define CC_V_SR        ((int)0x08000)
#define CC_N_SR        ((int)0x09000)
#define CC_B_SR        ((int)0x0A000)
#define CC_I_SR        ((int)0x0B000)
#define CC_S_SR        ((int)0x0C000)
#define CC_T_SR        ((int)0x0D000)
#define CC_TRUE        ((int)0x0E000)
#define CC_IND         ((int)0x0F000)

// B source select for ALU
#define BSRC_ADD_NUL   ((int)0x00000)
#define BSRC_ADD_ONES  ((int)0x00001)
#define BSRC_ADD_N     ((int)0x00002)
#define BSRC_ADD_CN    ((int)0x00003)
#define BSRC_LOG_NUL   ((int)0x00000)
#define BSRC_LOG_IO    ((int)0x00001)
#define BSRC_LOG_N     ((int)0x00002)
#define BSRC_LOG_CN    ((int)0x00003)

// A source select for ALU
#define ASRC_ADD_NUL   ((int)0x00000)
#define ASRC_ADD_ONES  ((int)0x00004)
#define ASRC_ADD_T     ((int)0x00008)
#define ASRC_ADD_CT    ((int)0x0000C)
#define ASRC_LOG_NUL   ((int)0x00000)
#define ASRC_LOG_IMM   ((int)0x00004)
#define ASRC_LOG_T     ((int)0x00008)
#define ASRC_LOG_RAM   ((int)0x0000C)

// ALU operation select
#define OP_ADD         ((int)0x00000)
#define OP_ADDC        ((int)0x00010)
#define OP_SUB         ((int)0x00020)
#define OP_SUBC        ((int)0x00030)
#define OP_AND         ((int)0x00040)
#define OP_OR          ((int)0x00050)
#define OP_XOR         ((int)0x00060)
#define OP_NOT         ((int)0x00070)
#define OP_BAND        ((int)0x00140)
#define OP_BOR         ((int)0x00150)
#define OP_BXOR        ((int)0x00160)
#define OP_BNOT        ((int)0x00170)
#define OP_SHL         ((int)0x00080)
#define OP_SHR         ((int)0x000C0)
#define OP_DIV         ((int)0x000E0)
#define OP_MUL         ((int)0x000F0)

// Operand size select
#define SIZE_B         ((int)0x00000)
#define SIZE_W         ((int)0x00400)
#define SIZE_L         ((int)0x00800)
#define SIZE_H         ((int)0x00C00)

// Data stack pointer update
#define DSTK_NUL       ((int)0x00000)
#define DSTK_INC       ((int)0x01000)
#define DSTK_DEC       ((int)0x03000)

// Special flags
#define ALU_CCUPD      ((int)0x00200)
#define ALU_N_WR       ((int)0x04000)

//               Bits:   19..16   14, 9    13..12  11..10  8..4      3..2         1..0
#define ALU_ADDB       (OPC_ALU|          DSTK_DEC|SIZE_B|OP_ADD |ASRC_ADD_T  |BSRC_ADD_N   )
#define ALU_ADDW       (OPC_ALU|          DSTK_DEC|SIZE_W|OP_ADD |ASRC_ADD_T  |BSRC_ADD_N   )
#define ALU_ADDL       (OPC_ALU|          DSTK_DEC|SIZE_L|OP_ADD |ASRC_ADD_T  |BSRC_ADD_N   )
#define ALU_ADDCB      (OPC_ALU|          DSTK_DEC|SIZE_B|OP_ADDC|ASRC_ADD_T  |BSRC_ADD_N   )
#define ALU_ADDCW      (OPC_ALU|          DSTK_DEC|SIZE_W|OP_ADDC|ASRC_ADD_T  |BSRC_ADD_N   )
#define ALU_ADDCL      (OPC_ALU|          DSTK_DEC|SIZE_L|OP_ADDC|ASRC_ADD_T  |BSRC_ADD_N   )
#define ALU_SUBB       (OPC_ALU|          DSTK_DEC|SIZE_B|OP_SUB |ASRC_ADD_T  |BSRC_ADD_CN  )
#define ALU_SUBW       (OPC_ALU|          DSTK_DEC|SIZE_W|OP_SUB |ASRC_ADD_T  |BSRC_ADD_CN  )
#define ALU_SUBL       (OPC_ALU|          DSTK_DEC|SIZE_L|OP_SUB |ASRC_ADD_T  |BSRC_ADD_CN  )
#define ALU_SUBCB      (OPC_ALU|          DSTK_DEC|SIZE_B|OP_SUBC|ASRC_ADD_T  |BSRC_ADD_CN  )
#define ALU_SUBCW      (OPC_ALU|          DSTK_DEC|SIZE_W|OP_SUBC|ASRC_ADD_T  |BSRC_ADD_CN  )
#define ALU_SUBCL      (OPC_ALU|          DSTK_DEC|SIZE_L|OP_SUBC|ASRC_ADD_T  |BSRC_ADD_CN  )
#define ALU_SUB2B      (OPC_ALU|          DSTK_DEC|SIZE_B|OP_SUB |ASRC_ADD_CT |BSRC_ADD_N   )
#define ALU_SUB2W      (OPC_ALU|          DSTK_DEC|SIZE_W|OP_SUB |ASRC_ADD_CT |BSRC_ADD_N   )
#define ALU_SUB2L      (OPC_ALU|          DSTK_DEC|SIZE_L|OP_SUB |ASRC_ADD_CT |BSRC_ADD_N   )
#define ALU_SUBC2B     (OPC_ALU|          DSTK_DEC|SIZE_B|OP_SUBC|ASRC_ADD_CT |BSRC_ADD_N   )
#define ALU_SUBC2W     (OPC_ALU|          DSTK_DEC|SIZE_W|OP_SUBC|ASRC_ADD_CT |BSRC_ADD_N   )
#define ALU_SUBC2L     (OPC_ALU|          DSTK_DEC|SIZE_L|OP_SUBC|ASRC_ADD_CT |BSRC_ADD_N   )
#define ALU_NEGB       (OPC_ALU|          DSTK_NUL|SIZE_B|OP_SUB |ASRC_ADD_CT |BSRC_ADD_NUL )
#define ALU_NEGW       (OPC_ALU|          DSTK_NUL|SIZE_W|OP_SUB |ASRC_ADD_CT |BSRC_ADD_NUL )
#define ALU_NEGL       (OPC_ALU|          DSTK_NUL|SIZE_L|OP_SUB |ASRC_ADD_CT |BSRC_ADD_NUL )
#define ALU_NEGCB      (OPC_ALU|          DSTK_NUL|SIZE_B|OP_SUBC|ASRC_ADD_CT |BSRC_ADD_NUL )
#define ALU_NEGCW      (OPC_ALU|          DSTK_NUL|SIZE_W|OP_SUBC|ASRC_ADD_CT |BSRC_ADD_NUL )
#define ALU_NEGCL      (OPC_ALU|          DSTK_NUL|SIZE_L|OP_SUBC|ASRC_ADD_CT |BSRC_ADD_NUL )
#define ALU_DECW       (OPC_ALU|          DSTK_NUL|SIZE_W|OP_ADD |ASRC_ADD_T  |BSRC_ADD_ONES)
#define ALU_EXTW       (OPC_ALU|ALU_N_WR |DSTK_INC|SIZE_W|OP_SUBC|ASRC_ADD_NUL|BSRC_ADD_ONES)
#define ALU_ANDB       (OPC_ALU|          DSTK_DEC|SIZE_B|OP_AND |ASRC_LOG_T  |BSRC_LOG_N   )
#define ALU_ANDW       (OPC_ALU|          DSTK_DEC|SIZE_W|OP_AND |ASRC_LOG_T  |BSRC_LOG_N   )
#define ALU_ANDL       (OPC_ALU|          DSTK_DEC|SIZE_L|OP_AND |ASRC_LOG_T  |BSRC_LOG_N   )
#define ALU_ORB        (OPC_ALU|          DSTK_DEC|SIZE_B|OP_OR  |ASRC_LOG_T  |BSRC_LOG_N   )
#define ALU_ORW        (OPC_ALU|          DSTK_DEC|SIZE_W|OP_OR  |ASRC_LOG_T  |BSRC_LOG_N   )
#define ALU_ORL        (OPC_ALU|          DSTK_DEC|SIZE_L|OP_OR  |ASRC_LOG_T  |BSRC_LOG_N   )
#define ALU_XORB       (OPC_ALU|          DSTK_DEC|SIZE_B|OP_XOR |ASRC_LOG_T  |BSRC_LOG_N   )
#define ALU_XORW       (OPC_ALU|          DSTK_DEC|SIZE_W|OP_XOR |ASRC_LOG_T  |BSRC_LOG_N   )
#define ALU_XORL       (OPC_ALU|          DSTK_DEC|SIZE_L|OP_XOR |ASRC_LOG_T  |BSRC_LOG_N   )
#define ALU_MSKB       (OPC_ALU|          DSTK_DEC|SIZE_B|OP_AND |ASRC_LOG_T  |BSRC_LOG_CN  )
#define ALU_MSKW       (OPC_ALU|          DSTK_DEC|SIZE_W|OP_AND |ASRC_LOG_T  |BSRC_LOG_CN  )
#define ALU_MSKL       (OPC_ALU|          DSTK_DEC|SIZE_L|OP_AND |ASRC_LOG_T  |BSRC_LOG_CN  )
#define ALU_BANDB      (OPC_ALU|          DSTK_DEC|SIZE_B|OP_BAND|ASRC_LOG_T  |BSRC_LOG_N   )
#define ALU_BANDW      (OPC_ALU|          DSTK_DEC|SIZE_W|OP_BAND|ASRC_LOG_T  |BSRC_LOG_N   )
#define ALU_BANDL      (OPC_ALU|          DSTK_DEC|SIZE_L|OP_BAND|ASRC_LOG_T  |BSRC_LOG_N   )
#define ALU_BORB       (OPC_ALU|          DSTK_DEC|SIZE_B|OP_BOR |ASRC_LOG_T  |BSRC_LOG_N   )
#define ALU_BORW       (OPC_ALU|          DSTK_DEC|SIZE_W|OP_BOR |ASRC_LOG_T  |BSRC_LOG_N   )
#define ALU_BORL       (OPC_ALU|          DSTK_DEC|SIZE_L|OP_BOR |ASRC_LOG_T  |BSRC_LOG_N   )
#define ALU_BXORB      (OPC_ALU|          DSTK_DEC|SIZE_B|OP_BXOR|ASRC_LOG_T  |BSRC_LOG_N   )
#define ALU_BXORW      (OPC_ALU|          DSTK_DEC|SIZE_W|OP_BXOR|ASRC_LOG_T  |BSRC_LOG_N   )
#define ALU_BXORL      (OPC_ALU|          DSTK_DEC|SIZE_L|OP_BXOR|ASRC_LOG_T  |BSRC_LOG_N   )
#define ALU_BMSKB      (OPC_ALU|          DSTK_DEC|SIZE_B|OP_BAND|ASRC_LOG_T  |BSRC_LOG_CN  )
#define ALU_BMSKW      (OPC_ALU|          DSTK_DEC|SIZE_W|OP_BAND|ASRC_LOG_T  |BSRC_LOG_CN  )
#define ALU_BMSKL      (OPC_ALU|          DSTK_DEC|SIZE_L|OP_BAND|ASRC_LOG_T  |BSRC_LOG_CN  )
#define ALU_NOTB       (OPC_ALU|          DSTK_NUL|SIZE_B|OP_NOT |ASRC_LOG_T  |BSRC_LOG_N   )
#define ALU_NOTW       (OPC_ALU|          DSTK_NUL|SIZE_W|OP_NOT |ASRC_LOG_T  |BSRC_LOG_N   )
#define ALU_NOTL       (OPC_ALU|          DSTK_NUL|SIZE_L|OP_NOT |ASRC_LOG_T  |BSRC_LOG_N   )
#define ALU_TSTB       (OPC_ALU|ALU_CCUPD|DSTK_NUL|SIZE_B|OP_OR  |ASRC_LOG_T  |BSRC_LOG_NUL )
#define ALU_TSTW       (OPC_ALU|ALU_CCUPD|DSTK_NUL|SIZE_W|OP_OR  |ASRC_LOG_T  |BSRC_LOG_NUL )
#define ALU_TSTL       (OPC_ALU|ALU_CCUPD|DSTK_NUL|SIZE_L|OP_OR  |ASRC_LOG_T  |BSRC_LOG_NUL )
#define ALU_LSHB       (OPC_ALU|ALU_N_WR |DSTK_NUL|SIZE_B|OP_SHL                            )
#define ALU_LSHW       (OPC_ALU|ALU_N_WR |DSTK_NUL|SIZE_W|OP_SHL                            )
#define ALU_LSHL       (OPC_ALU|ALU_N_WR |DSTK_NUL|SIZE_L|OP_SHL                            )
#define ALU_RSHB       (OPC_ALU|ALU_N_WR |DSTK_NUL|SIZE_B|OP_SHR                            )
#define ALU_RSHW       (OPC_ALU|ALU_N_WR |DSTK_NUL|SIZE_W|OP_SHR                            )
#define ALU_RSHL       (OPC_ALU|ALU_N_WR |DSTK_NUL|SIZE_L|OP_SHR                            )
#define ALU_MUL        (OPC_ALU|ALU_N_WR |DSTK_NUL|SIZE_L|OP_MUL                            )
#define ALU_DIV        (OPC_ALU|ALU_N_WR |DSTK_NUL|SIZE_L|OP_DIV                            )
#define ALU_DROP       (OPC_ALU|          DSTK_DEC|SIZE_W|OP_OR  |ASRC_LOG_NUL|BSRC_LOG_N   )
#define ALU_NIP        (OPC_ALU|          DSTK_DEC|SIZE_W|OP_OR  |ASRC_LOG_T  |BSRC_LOG_NUL )
#define ALU_SWAP       (OPC_ALU|ALU_N_WR |DSTK_NUL|SIZE_W|OP_OR  |ASRC_LOG_NUL|BSRC_LOG_N   )
#define ALU_DUP        (OPC_ALU|ALU_N_WR |DSTK_INC|SIZE_W|OP_OR  |ASRC_LOG_T  |BSRC_LOG_NUL )
#define ALU_OVER       (OPC_ALU|ALU_N_WR |DSTK_INC|SIZE_W|OP_OR  |ASRC_LOG_NUL|BSRC_LOG_N   )
#define ALU_NOP        (OPC_ALU|          DSTK_NUL|SIZE_W|OP_OR  |ASRC_LOG_T  |BSRC_LOG_NUL )

// Access types (bits 8..6)
#define MEM_IO_WR      ((int)0x00040)
#define MEM_IO_RD      ((int)0x00080)
#define MEM_EXT_BUS    ((int)0x00100)

// Memory access (bits 3..0)
#define MEM_EA1_PTR    ((int)0x00000)
#define MEM_EA2_PTR    ((int)0x00001)
#define MEM_PC_PTR     ((int)0x00002)
#define MEM_VEC_PTR    ((int)0x00003)
#define MEM_NO_INC     ((int)0x00000)
#define MEM_POST_INC   ((int)0x00004)
#define MEM_PRE_DEC    ((int)0x00008)
#define MEM_PRE_INC    ((int)0x0000C)
#define MEM_INS_DATA   ((int)0x00002)
#define MEM_EXT_DATA   ((int)0x00006)
#define MEM_IMM_DATA   ((int)0x0000A)

// I/O registers (bits 3..0)
#define IREG_EA1L      ((int)0x00000)
#define IREG_EA1H      ((int)0x00001)
#define IREG_EA2L      ((int)0x00002)
#define IREG_EA2H      ((int)0x00003)
#define IREG_PCL       ((int)0x00004)
#define IREG_PCH       ((int)0x00005)
#define IREG_VECL      ((int)0x00006)
#define IREG_VECH      ((int)0x00007)
#define IREG_CPUS      ((int)0x00007)
#define IREG_IMM       ((int)0x00008)
#define IREG_LSHR      ((int)0x00009)
#define IREG_ACCL      ((int)0x0000A)
#define IREG_ACCH      ((int)0x0000B)
#define IREG_DECJ      ((int)0x0000C)
#define IREG_EA1J      ((int)0x0000D)
#define IREG_EA2J      ((int)0x0000E)
#define IREG_SR        ((int)0x0000F)

//               Bits:  19..16    14       13..12  11..10     8          7..6       3..0
#define MEM_EA1_B_LD   (OPC_IO|ALU_N_WR|DSTK_INC|SIZE_B|MEM_EXT_BUS|MEM_IO_RD|MEM_EA1_PTR)
#define MEM_EA1_W_LD   (OPC_IO|ALU_N_WR|DSTK_INC|SIZE_W|MEM_EXT_BUS|MEM_IO_RD|MEM_EA1_PTR)
#define MEM_EA1_H_LD   (OPC_IO|ALU_N_WR|DSTK_INC|SIZE_H|MEM_EXT_BUS|MEM_IO_RD|MEM_EA1_PTR)
#define MEM_EA1_L_LD   (OPC_IO|ALU_N_WR|DSTK_INC|SIZE_L|MEM_EXT_BUS|MEM_IO_RD|MEM_EA1_PTR)
#define MEM_EA2_B_LD   (OPC_IO|ALU_N_WR|DSTK_INC|SIZE_B|MEM_EXT_BUS|MEM_IO_RD|MEM_EA2_PTR)
#define MEM_EA2_W_LD   (OPC_IO|ALU_N_WR|DSTK_INC|SIZE_W|MEM_EXT_BUS|MEM_IO_RD|MEM_EA2_PTR)
#define MEM_EA2_H_LD   (OPC_IO|ALU_N_WR|DSTK_INC|SIZE_H|MEM_EXT_BUS|MEM_IO_RD|MEM_EA2_PTR)
#define MEM_EA2_L_LD   (OPC_IO|ALU_N_WR|DSTK_INC|SIZE_L|MEM_EXT_BUS|MEM_IO_RD|MEM_EA2_PTR)
#define MEM_EA1_B_ST   (OPC_IO|         DSTK_DEC|SIZE_B|MEM_EXT_BUS|MEM_IO_WR|MEM_EA1_PTR)
#define MEM_EA1_W_ST   (OPC_IO|         DSTK_DEC|SIZE_W|MEM_EXT_BUS|MEM_IO_WR|MEM_EA1_PTR)
#define MEM_EA1_H_ST   (OPC_IO|         DSTK_DEC|SIZE_H|MEM_EXT_BUS|MEM_IO_WR|MEM_EA1_PTR)
#define MEM_EA1_L_ST   (OPC_IO|         DSTK_DEC|SIZE_L|MEM_EXT_BUS|MEM_IO_WR|MEM_EA1_PTR)
#define MEM_EA2_B_ST   (OPC_IO|         DSTK_DEC|SIZE_B|MEM_EXT_BUS|MEM_IO_WR|MEM_EA2_PTR)
#define MEM_EA2_W_ST   (OPC_IO|         DSTK_DEC|SIZE_W|MEM_EXT_BUS|MEM_IO_WR|MEM_EA2_PTR)
#define MEM_EA2_H_ST   (OPC_IO|         DSTK_DEC|SIZE_H|MEM_EXT_BUS|MEM_IO_WR|MEM_EA2_PTR)
#define MEM_EA2_L_ST   (OPC_IO|         DSTK_DEC|SIZE_L|MEM_EXT_BUS|MEM_IO_WR|MEM_EA2_PTR)
#define MEM_EA1_B_WR   (OPC_IO|         DSTK_NUL|SIZE_B|MEM_EXT_BUS|MEM_IO_WR|MEM_EA1_PTR)
#define MEM_EA1_W_WR   (OPC_IO|         DSTK_NUL|SIZE_W|MEM_EXT_BUS|MEM_IO_WR|MEM_EA1_PTR)
#define MEM_EA1_H_WR   (OPC_IO|         DSTK_NUL|SIZE_H|MEM_EXT_BUS|MEM_IO_WR|MEM_EA1_PTR)
#define MEM_EA1_L_WR   (OPC_IO|         DSTK_NUL|SIZE_L|MEM_EXT_BUS|MEM_IO_WR|MEM_EA1_PTR)
#define MEM_EA2_B_WR   (OPC_IO|         DSTK_NUL|SIZE_B|MEM_EXT_BUS|MEM_IO_WR|MEM_EA2_PTR)
#define MEM_EA2_W_WR   (OPC_IO|         DSTK_NUL|SIZE_W|MEM_EXT_BUS|MEM_IO_WR|MEM_EA2_PTR)
#define MEM_EA2_H_WR   (OPC_IO|         DSTK_NUL|SIZE_H|MEM_EXT_BUS|MEM_IO_WR|MEM_EA2_PTR)
#define MEM_EA2_L_WR   (OPC_IO|         DSTK_NUL|SIZE_L|MEM_EXT_BUS|MEM_IO_WR|MEM_EA2_PTR)
#define MEM_INS_LD     (OPC_IO|ALU_N_WR|DSTK_INC|SIZE_W|MEM_EXT_BUS|MEM_IO_RD|MEM_INS_DATA)
#define MEM_EXT_LD     (OPC_IO|ALU_N_WR|DSTK_INC|SIZE_W|MEM_EXT_BUS|MEM_IO_RD|MEM_EXT_DATA)
#define MEM_IMM_LD     (OPC_IO|ALU_N_WR|DSTK_INC|SIZE_W|MEM_EXT_BUS|MEM_IO_RD|MEM_IMM_DATA)
#define MEM_INS_FT     (OPC_IO|         DSTK_NUL|SIZE_W|MEM_EXT_BUS|MEM_IO_RD|MEM_INS_DATA)
#define MEM_EXT_FT     (OPC_IO|         DSTK_NUL|SIZE_W|MEM_EXT_BUS|MEM_IO_RD|MEM_EXT_DATA)
#define MEM_IMM_FT     (OPC_IO|         DSTK_NUL|SIZE_W|MEM_EXT_BUS|MEM_IO_RD|MEM_IMM_DATA)
#define MEM_VEC_LD     (OPC_IO|ALU_N_WR|DSTK_INC|SIZE_W|MEM_EXT_BUS|MEM_IO_RD|MEM_VEC_PTR)

//               Bits:  19..16    14     13..12  11..10    7..6
#define IO_REG_B_LD    (OPC_IO|ALU_N_WR|DSTK_INC|SIZE_B|MEM_IO_RD)
#define IO_REG_W_LD    (OPC_IO|ALU_N_WR|DSTK_INC|SIZE_W|MEM_IO_RD)
#define IO_REG_B_ST    (OPC_IO|         DSTK_DEC|SIZE_B|MEM_IO_WR)
#define IO_REG_W_ST    (OPC_IO|         DSTK_DEC|SIZE_W|MEM_IO_WR)
#define IO_REG_B_WR    (OPC_IO|         DSTK_NUL|SIZE_B|MEM_IO_WR)
#define IO_REG_W_WR    (OPC_IO|         DSTK_NUL|SIZE_W|MEM_IO_WR)

// CPU registers (bits 8, 3..0)
#define CREG_DL        ((int)0x00000)
#define CREG_AL        ((int)0x00001)
#define CREG_RL        ((int)0x00002)
#define CREG_A7L       ((int)0x00003)
#define CREG_DH        ((int)0x00100)
#define CREG_AH        ((int)0x00101)
#define CREG_RH        ((int)0x00102)
#define CREG_A7H       ((int)0x00103)
#define CREG_VBRL      ((int)0x0000B)
#define CREG_TMP1L     ((int)0x0000C)
#define CREG_TMP2L     ((int)0x0000D)
#define CREG_USPL      ((int)0x0000E)
#define CREG_SSPL      ((int)0x0000F)
#define CREG_VBRH      ((int)0x0010B)
#define CREG_TMP1H     ((int)0x0010C)
#define CREG_TMP2H     ((int)0x0010D)
#define CREG_USPH      ((int)0x0010E)
#define CREG_SSPH      ((int)0x0010F)

#define RIDX_EA1       ((int)0x00000)
#define RIDX_EA2       ((int)0x00004)
#define RIDX_CNT       ((int)0x00007)
#define RIDX_EXT       ((int)0x00008)

//               Bits:  19..16    14      13..12  11..10    7..6
#define CPU_REG_B_LD   (OPC_REG|ALU_N_WR|DSTK_INC|SIZE_B|MEM_IO_RD)
#define CPU_REG_W_LD   (OPC_REG|ALU_N_WR|DSTK_INC|SIZE_W|MEM_IO_RD)
#define CPU_REG_B_ST   (OPC_REG|         DSTK_DEC|SIZE_B|MEM_IO_WR)
#define CPU_REG_W_ST   (OPC_REG|         DSTK_DEC|SIZE_W|MEM_IO_WR)
#define CPU_REG_B_WR   (OPC_REG|         DSTK_NUL|SIZE_B|MEM_IO_WR)
#define CPU_REG_W_WR   (OPC_REG|         DSTK_NUL|SIZE_W|MEM_IO_WR)



/* Line 189 of yacc.c  */
#line 423 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20/microcode.parser.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TOK_JUMPN = 258,
     TOK_JUMP = 259,
     TOK_CALLN = 260,
     TOK_CALL = 261,
     TOK_RTS = 262,
     TOK_LIT = 263,
     TOK_FLAG = 264,
     TOK_BIT = 265,
     TOK_LOOPT = 266,
     TOK_LOOP16 = 267,
     TOK_ENDLOOP = 268,
     TOK_DROP = 269,
     TOK_NIP = 270,
     TOK_SWAP = 271,
     TOK_DUP = 272,
     TOK_OVER = 273,
     TOK_ADDB = 274,
     TOK_ADDW = 275,
     TOK_ADDL = 276,
     TOK_ADDCB = 277,
     TOK_ADDCW = 278,
     TOK_ADDCL = 279,
     TOK_SUBB = 280,
     TOK_SUBW = 281,
     TOK_SUBL = 282,
     TOK_SUBCB = 283,
     TOK_SUBCW = 284,
     TOK_SUBCL = 285,
     TOK_SUB2B = 286,
     TOK_SUB2W = 287,
     TOK_SUB2L = 288,
     TOK_SUBC2B = 289,
     TOK_SUBC2W = 290,
     TOK_SUBC2L = 291,
     TOK_NEGB = 292,
     TOK_NEGW = 293,
     TOK_NEGL = 294,
     TOK_NEGCB = 295,
     TOK_NEGCW = 296,
     TOK_NEGCL = 297,
     TOK_DECW = 298,
     TOK_EXTW = 299,
     TOK_ANDB = 300,
     TOK_ANDW = 301,
     TOK_ANDL = 302,
     TOK_ORB = 303,
     TOK_ORW = 304,
     TOK_ORL = 305,
     TOK_XORB = 306,
     TOK_XORW = 307,
     TOK_XORL = 308,
     TOK_MSKB = 309,
     TOK_MSKW = 310,
     TOK_MSKL = 311,
     TOK_BANDB = 312,
     TOK_BANDW = 313,
     TOK_BANDL = 314,
     TOK_BORB = 315,
     TOK_BORW = 316,
     TOK_BORL = 317,
     TOK_BXORB = 318,
     TOK_BXORW = 319,
     TOK_BXORL = 320,
     TOK_BMSKB = 321,
     TOK_BMSKW = 322,
     TOK_BMSKL = 323,
     TOK_NOTB = 324,
     TOK_NOTW = 325,
     TOK_NOTL = 326,
     TOK_TSTB = 327,
     TOK_TSTW = 328,
     TOK_TSTL = 329,
     TOK_LSHB = 330,
     TOK_LSHW = 331,
     TOK_LSHL = 332,
     TOK_RSHB = 333,
     TOK_RSHW = 334,
     TOK_RSHL = 335,
     TOK_MUL = 336,
     TOK_DIV = 337,
     TOK_NOP = 338,
     TOK_LDB = 339,
     TOK_STB = 340,
     TOK_WRB = 341,
     TOK_FTW = 342,
     TOK_LDW = 343,
     TOK_STW = 344,
     TOK_WRW = 345,
     TOK_LDI = 346,
     TOK_FTI = 347,
     TOK_LDE = 348,
     TOK_FTE = 349,
     TOK_LDL = 350,
     TOK_STL = 351,
     TOK_WRL = 352,
     TOK_LDH = 353,
     TOK_STH = 354,
     TOK_WRH = 355,
     TOK_PC = 356,
     TOK_VEC = 357,
     TOK_EA1 = 358,
     TOK_EA2 = 359,
     TOK_CNT = 360,
     TOK_EXT = 361,
     TOK_T_SR = 362,
     TOK_S_SR = 363,
     TOK_A_SR = 364,
     TOK_I_SR = 365,
     TOK_B_SR = 366,
     TOK_X_SR = 367,
     TOK_N_SR = 368,
     TOK_V_SR = 369,
     TOK_CIN = 370,
     TOK_CLR = 371,
     TOK_C_ADD = 372,
     TOK_C_FLG = 373,
     TOK_Z_FLG = 374,
     TOK_N_FLG = 375,
     TOK_G_FLG = 376,
     TOK_N_B = 377,
     TOK_N_W = 378,
     TOK_T0 = 379,
     TOK_T7 = 380,
     TOK_T15 = 381,
     TOK_N0 = 382,
     TOK_N7 = 383,
     TOK_N15 = 384,
     TOK_EA1_4 = 385,
     TOK_EA1_7 = 386,
     TOK_EXT11 = 387,
     TOK_EA1L = 388,
     TOK_EA1H = 389,
     TOK_EA2L = 390,
     TOK_EA2H = 391,
     TOK_PCL = 392,
     TOK_PCH = 393,
     TOK_VECL = 394,
     TOK_VECH = 395,
     TOK_CPUS = 396,
     TOK_LSHR = 397,
     TOK_ACCL = 398,
     TOK_ACCH = 399,
     TOK_IMMR = 400,
     TOK_DECJ = 401,
     TOK_EA1J = 402,
     TOK_EA2J = 403,
     TOK_EA1B = 404,
     TOK_EA2B = 405,
     TOK_SR = 406,
     TOK_RT = 407,
     TOK_RN = 408,
     TOK_MASK = 409,
     TOK_NUMBER = 410,
     TOK_IDENT = 411,
     TOK_RAL = 412,
     TOK_RDL = 413,
     TOK_RAH = 414,
     TOK_RDH = 415,
     TOK_RL = 416,
     TOK_RH = 417,
     TOK_A7L = 418,
     TOK_A7H = 419,
     TOK_USPL = 420,
     TOK_USPH = 421,
     TOK_SSPL = 422,
     TOK_SSPH = 423,
     TOK_TMP1L = 424,
     TOK_TMP1H = 425,
     TOK_TMP2L = 426,
     TOK_TMP2H = 427,
     TOK_VBRL = 428,
     TOK_VBRH = 429,
     TOK_ORG = 430,
     TOK_TABLE = 431
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 350 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"

  char *txt;
  int   val;



/* Line 214 of yacc.c  */
#line 642 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20/microcode.parser.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 654 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20/microcode.parser.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   827

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  189
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  21
/* YYNRULES -- Number of rules.  */
#define YYNRULES  438
/* YYNRULES -- Number of states.  */
#define YYNSTATES  777

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   431

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     177,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,   182,     2,     2,     2,     2,
     180,   181,     2,   185,   179,   186,   184,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   178,     2,
       2,   183,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   187,     2,   188,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   176
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     7,     9,    12,    14,    16,    18,
      20,    22,    24,    26,    28,    30,    32,    35,    44,    47,
      52,    57,    62,    67,    72,    77,    82,    87,    90,    93,
      96,    99,   105,   111,   117,   123,   125,   127,   129,   131,
     133,   135,   137,   139,   141,   143,   145,   147,   149,   151,
     154,   156,   160,   164,   167,   169,   173,   174,   179,   184,
     189,   194,   199,   204,   209,   214,   219,   224,   229,   234,
     239,   241,   243,   245,   249,   252,   255,   257,   259,   261,
     263,   265,   267,   269,   271,   273,   275,   277,   279,   281,
     283,   285,   287,   289,   291,   293,   295,   297,   299,   301,
     303,   305,   307,   309,   311,   313,   315,   317,   319,   321,
     323,   325,   327,   329,   331,   333,   335,   337,   339,   341,
     343,   345,   347,   349,   351,   353,   355,   357,   359,   361,
     363,   365,   367,   369,   371,   373,   375,   377,   379,   381,
     383,   385,   387,   389,   391,   393,   395,   397,   401,   404,
     407,   409,   414,   420,   426,   432,   437,   443,   449,   455,
     460,   466,   472,   478,   483,   489,   495,   501,   506,   512,
     518,   524,   529,   535,   541,   547,   552,   558,   564,   570,
     575,   581,   587,   593,   598,   604,   610,   616,   621,   627,
     633,   639,   644,   650,   656,   662,   667,   673,   679,   685,
     691,   697,   703,   709,   715,   721,   727,   731,   734,   737,
     739,   745,   751,   757,   763,   769,   775,   781,   787,   793,
     799,   802,   805,   808,   811,   814,   820,   826,   832,   838,
     844,   850,   856,   862,   868,   874,   877,   880,   883,   886,
     889,   895,   901,   907,   910,   916,   922,   928,   934,   940,
     946,   952,   955,   958,   961,   964,   967,   973,   979,   985,
     988,   994,  1000,  1006,  1012,  1018,  1024,  1030,  1033,  1036,
    1039,  1042,  1045,  1051,  1057,  1063,  1069,  1075,  1081,  1087,
    1093,  1099,  1105,  1108,  1111,  1114,  1117,  1120,  1126,  1132,
    1138,  1144,  1150,  1156,  1162,  1168,  1174,  1180,  1183,  1186,
    1189,  1192,  1195,  1201,  1207,  1213,  1216,  1222,  1228,  1234,
    1240,  1246,  1252,  1258,  1261,  1264,  1267,  1270,  1273,  1279,
    1285,  1291,  1294,  1300,  1306,  1312,  1318,  1324,  1330,  1336,
    1339,  1342,  1345,  1348,  1351,  1357,  1363,  1369,  1375,  1381,
    1387,  1393,  1399,  1405,  1411,  1414,  1417,  1420,  1423,  1426,
    1432,  1438,  1444,  1450,  1456,  1462,  1468,  1474,  1480,  1486,
    1489,  1492,  1495,  1498,  1501,  1507,  1513,  1519,  1522,  1528,
    1534,  1540,  1546,  1552,  1558,  1564,  1567,  1570,  1573,  1576,
    1579,  1585,  1591,  1597,  1600,  1606,  1612,  1618,  1624,  1630,
    1636,  1642,  1645,  1648,  1651,  1654,  1657,  1660,  1663,  1666,
    1669,  1672,  1675,  1678,  1681,  1684,  1687,  1690,  1693,  1696,
    1699,  1702,  1705,  1708,  1711,  1714,  1717,  1720,  1723,  1726,
    1729,  1732,  1735,  1738,  1741,  1744,  1747,  1750,  1753,  1756,
    1759,  1762,  1765,  1768,  1771,  1774,  1777,  1780,  1783
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     190,     0,    -1,    -1,   190,   191,    -1,   177,    -1,   192,
     177,    -1,   195,    -1,   194,    -1,   193,    -1,   196,    -1,
     198,    -1,   200,    -1,   203,    -1,   204,    -1,   206,    -1,
     208,    -1,   156,   178,    -1,   176,   156,   179,   156,   179,
     156,   179,   155,    -1,   175,   155,    -1,     3,   197,   179,
     156,    -1,     3,   197,   179,   155,    -1,     4,   197,   179,
     156,    -1,     4,   197,   179,   155,    -1,     5,   197,   179,
     156,    -1,     5,   197,   179,   155,    -1,     6,   197,   179,
     156,    -1,     6,   197,   179,   155,    -1,     4,   156,    -1,
       4,   155,    -1,     6,   156,    -1,     6,   155,    -1,     4,
     156,   180,   152,   181,    -1,     4,   155,   180,   152,   181,
      -1,     6,   156,   180,   152,   181,    -1,     6,   155,   180,
     152,   181,    -1,   119,    -1,   120,    -1,   121,    -1,   124,
      -1,   130,    -1,   131,    -1,   132,    -1,   114,    -1,   113,
      -1,   111,    -1,   110,    -1,   109,    -1,   108,    -1,   107,
      -1,   199,     7,    -1,   199,    -1,     8,   182,   155,    -1,
       8,   182,   156,    -1,   201,     7,    -1,   201,    -1,     9,
     154,   202,    -1,    -1,   179,   115,   183,   116,    -1,   179,
     115,   183,   117,    -1,   179,   115,   183,   118,    -1,   179,
     115,   183,   112,    -1,   179,   115,   183,   122,    -1,   179,
     115,   183,   123,    -1,   179,   115,   183,   113,    -1,   179,
     115,   183,   124,    -1,   179,   115,   183,   125,    -1,   179,
     115,   183,   126,    -1,   179,   115,   183,   127,    -1,   179,
     115,   183,   128,    -1,   179,   115,   183,   129,    -1,    12,
      -1,    11,    -1,    13,    -1,   205,   184,     7,    -1,   205,
       7,    -1,   205,   184,    -1,   205,    -1,    14,    -1,    15,
      -1,    16,    -1,    17,    -1,    18,    -1,    19,    -1,    20,
      -1,    21,    -1,    22,    -1,    23,    -1,    24,    -1,    25,
      -1,    26,    -1,    27,    -1,    28,    -1,    29,    -1,    30,
      -1,    31,    -1,    32,    -1,    33,    -1,    34,    -1,    35,
      -1,    36,    -1,    37,    -1,    38,    -1,    39,    -1,    40,
      -1,    41,    -1,    42,    -1,    43,    -1,    44,    -1,    45,
      -1,    46,    -1,    47,    -1,    48,    -1,    49,    -1,    50,
      -1,    51,    -1,    52,    -1,    53,    -1,    54,    -1,    55,
      -1,    56,    -1,    57,    -1,    58,    -1,    59,    -1,    60,
      -1,    61,    -1,    62,    -1,    63,    -1,    64,    -1,    65,
      -1,    66,    -1,    67,    -1,    68,    -1,    69,    -1,    70,
      -1,    71,    -1,    72,    -1,    73,    -1,    74,    -1,    75,
      -1,    76,    -1,    77,    -1,    78,    -1,    79,    -1,    80,
      -1,    81,    -1,    82,    -1,    83,    -1,   207,   184,     7,
      -1,   207,     7,    -1,   207,   184,    -1,   207,    -1,    84,
     180,   103,   181,    -1,    84,   180,   103,   181,   185,    -1,
      84,   186,   180,   103,   181,    -1,    84,   185,   180,   103,
     181,    -1,    88,   180,   103,   181,    -1,    88,   180,   103,
     181,   185,    -1,    88,   186,   180,   103,   181,    -1,    88,
     185,   180,   103,   181,    -1,    98,   180,   103,   181,    -1,
      98,   180,   103,   181,   185,    -1,    98,   186,   180,   103,
     181,    -1,    98,   185,   180,   103,   181,    -1,    95,   180,
     103,   181,    -1,    95,   180,   103,   181,   185,    -1,    95,
     186,   180,   103,   181,    -1,    95,   185,   180,   103,   181,
      -1,    84,   180,   104,   181,    -1,    84,   180,   104,   181,
     185,    -1,    84,   186,   180,   104,   181,    -1,    84,   185,
     180,   104,   181,    -1,    88,   180,   104,   181,    -1,    88,
     180,   104,   181,   185,    -1,    88,   186,   180,   104,   181,
      -1,    88,   185,   180,   104,   181,    -1,    85,   180,   103,
     181,    -1,    85,   180,   103,   181,   185,    -1,    85,   186,
     180,   103,   181,    -1,    85,   185,   180,   103,   181,    -1,
      89,   180,   103,   181,    -1,    89,   180,   103,   181,   185,
      -1,    89,   186,   180,   103,   181,    -1,    89,   185,   180,
     103,   181,    -1,    99,   180,   103,   181,    -1,    99,   180,
     103,   181,   185,    -1,    99,   186,   180,   103,   181,    -1,
      99,   185,   180,   103,   181,    -1,    96,   180,   103,   181,
      -1,    96,   180,   103,   181,   185,    -1,    96,   186,   180,
     103,   181,    -1,    96,   185,   180,   103,   181,    -1,    85,
     180,   104,   181,    -1,    85,   180,   104,   181,   185,    -1,
      85,   186,   180,   104,   181,    -1,    85,   185,   180,   104,
     181,    -1,    89,   180,   104,   181,    -1,    89,   180,   104,
     181,   185,    -1,    89,   186,   180,   104,   181,    -1,    89,
     185,   180,   104,   181,    -1,    88,   180,   102,   181,   185,
      -1,    91,   180,   101,   181,   185,    -1,    93,   180,   101,
     181,   185,    -1,    88,   180,   101,   181,   185,    -1,    92,
     180,   101,   181,   185,    -1,    94,   180,   101,   181,   185,
      -1,    87,   180,   101,   181,   185,    -1,   209,   184,     7,
      -1,   209,     7,    -1,   209,   184,    -1,   209,    -1,    84,
     158,   187,   103,   188,    -1,    84,   157,   187,   103,   188,
      -1,    84,   161,   187,   103,   188,    -1,    84,   158,   187,
     104,   188,    -1,    84,   157,   187,   104,   188,    -1,    84,
     161,   187,   104,   188,    -1,    84,   161,   187,   105,   188,
      -1,    84,   158,   187,   106,   188,    -1,    84,   157,   187,
     106,   188,    -1,    84,   161,   187,   106,   188,    -1,    84,
     173,    -1,    84,   169,    -1,    84,   171,    -1,    84,   165,
      -1,    84,   167,    -1,    84,   160,   187,   103,   188,    -1,
      84,   159,   187,   103,   188,    -1,    84,   162,   187,   103,
     188,    -1,    84,   160,   187,   104,   188,    -1,    84,   159,
     187,   104,   188,    -1,    84,   162,   187,   104,   188,    -1,
      84,   162,   187,   105,   188,    -1,    84,   160,   187,   106,
     188,    -1,    84,   159,   187,   106,   188,    -1,    84,   162,
     187,   106,   188,    -1,    84,   174,    -1,    84,   170,    -1,
      84,   172,    -1,    84,   166,    -1,    84,   168,    -1,    88,
     158,   187,   103,   188,    -1,    88,   157,   187,   103,   188,
      -1,    88,   161,   187,   103,   188,    -1,    88,   163,    -1,
      88,   158,   187,   104,   188,    -1,    88,   157,   187,   104,
     188,    -1,    88,   161,   187,   104,   188,    -1,    88,   161,
     187,   105,   188,    -1,    88,   158,   187,   106,   188,    -1,
      88,   157,   187,   106,   188,    -1,    88,   161,   187,   106,
     188,    -1,    88,   173,    -1,    88,   169,    -1,    88,   171,
      -1,    88,   165,    -1,    88,   167,    -1,    88,   160,   187,
     103,   188,    -1,    88,   159,   187,   103,   188,    -1,    88,
     162,   187,   103,   188,    -1,    88,   164,    -1,    88,   160,
     187,   104,   188,    -1,    88,   159,   187,   104,   188,    -1,
      88,   162,   187,   104,   188,    -1,    88,   162,   187,   105,
     188,    -1,    88,   160,   187,   106,   188,    -1,    88,   159,
     187,   106,   188,    -1,    88,   162,   187,   106,   188,    -1,
      88,   174,    -1,    88,   170,    -1,    88,   172,    -1,    88,
     166,    -1,    88,   168,    -1,    85,   158,   187,   103,   188,
      -1,    85,   157,   187,   103,   188,    -1,    85,   161,   187,
     103,   188,    -1,    85,   158,   187,   104,   188,    -1,    85,
     157,   187,   104,   188,    -1,    85,   161,   187,   104,   188,
      -1,    85,   161,   187,   105,   188,    -1,    85,   158,   187,
     106,   188,    -1,    85,   157,   187,   106,   188,    -1,    85,
     161,   187,   106,   188,    -1,    85,   173,    -1,    85,   169,
      -1,    85,   171,    -1,    85,   165,    -1,    85,   167,    -1,
      85,   160,   187,   103,   188,    -1,    85,   159,   187,   103,
     188,    -1,    85,   162,   187,   103,   188,    -1,    85,   160,
     187,   104,   188,    -1,    85,   159,   187,   104,   188,    -1,
      85,   162,   187,   104,   188,    -1,    85,   162,   187,   105,
     188,    -1,    85,   160,   187,   106,   188,    -1,    85,   159,
     187,   106,   188,    -1,    85,   162,   187,   106,   188,    -1,
      85,   174,    -1,    85,   170,    -1,    85,   172,    -1,    85,
     166,    -1,    85,   168,    -1,    89,   158,   187,   103,   188,
      -1,    89,   157,   187,   103,   188,    -1,    89,   161,   187,
     103,   188,    -1,    89,   163,    -1,    89,   158,   187,   104,
     188,    -1,    89,   157,   187,   104,   188,    -1,    89,   161,
     187,   104,   188,    -1,    89,   161,   187,   105,   188,    -1,
      89,   158,   187,   106,   188,    -1,    89,   157,   187,   106,
     188,    -1,    89,   161,   187,   106,   188,    -1,    89,   173,
      -1,    89,   169,    -1,    89,   171,    -1,    89,   165,    -1,
      89,   167,    -1,    89,   160,   187,   103,   188,    -1,    89,
     159,   187,   103,   188,    -1,    89,   162,   187,   103,   188,
      -1,    89,   164,    -1,    89,   160,   187,   104,   188,    -1,
      89,   159,   187,   104,   188,    -1,    89,   162,   187,   104,
     188,    -1,    89,   162,   187,   105,   188,    -1,    89,   160,
     187,   106,   188,    -1,    89,   159,   187,   106,   188,    -1,
      89,   162,   187,   106,   188,    -1,    89,   174,    -1,    89,
     170,    -1,    89,   172,    -1,    89,   166,    -1,    89,   168,
      -1,    86,   158,   187,   103,   188,    -1,    86,   157,   187,
     103,   188,    -1,    86,   161,   187,   103,   188,    -1,    86,
     158,   187,   104,   188,    -1,    86,   157,   187,   104,   188,
      -1,    86,   161,   187,   104,   188,    -1,    86,   161,   187,
     105,   188,    -1,    86,   158,   187,   106,   188,    -1,    86,
     157,   187,   106,   188,    -1,    86,   161,   187,   106,   188,
      -1,    86,   173,    -1,    86,   169,    -1,    86,   171,    -1,
      86,   165,    -1,    86,   167,    -1,    86,   160,   187,   103,
     188,    -1,    86,   159,   187,   103,   188,    -1,    86,   162,
     187,   103,   188,    -1,    86,   160,   187,   104,   188,    -1,
      86,   159,   187,   104,   188,    -1,    86,   162,   187,   104,
     188,    -1,    86,   162,   187,   105,   188,    -1,    86,   160,
     187,   106,   188,    -1,    86,   159,   187,   106,   188,    -1,
      86,   162,   187,   106,   188,    -1,    86,   174,    -1,    86,
     170,    -1,    86,   172,    -1,    86,   166,    -1,    86,   168,
      -1,    90,   158,   187,   103,   188,    -1,    90,   157,   187,
     103,   188,    -1,    90,   161,   187,   103,   188,    -1,    90,
     163,    -1,    90,   158,   187,   104,   188,    -1,    90,   157,
     187,   104,   188,    -1,    90,   161,   187,   104,   188,    -1,
      90,   161,   187,   105,   188,    -1,    90,   158,   187,   106,
     188,    -1,    90,   157,   187,   106,   188,    -1,    90,   161,
     187,   106,   188,    -1,    90,   173,    -1,    90,   169,    -1,
      90,   171,    -1,    90,   165,    -1,    90,   167,    -1,    90,
     160,   187,   103,   188,    -1,    90,   159,   187,   103,   188,
      -1,    90,   162,   187,   103,   188,    -1,    90,   164,    -1,
      90,   160,   187,   104,   188,    -1,    90,   159,   187,   104,
     188,    -1,    90,   162,   187,   104,   188,    -1,    90,   162,
     187,   105,   188,    -1,    90,   160,   187,   106,   188,    -1,
      90,   159,   187,   106,   188,    -1,    90,   162,   187,   106,
     188,    -1,    90,   174,    -1,    90,   170,    -1,    90,   172,
      -1,    90,   166,    -1,    90,   168,    -1,    88,   133,    -1,
      88,   134,    -1,    88,   135,    -1,    88,   136,    -1,    88,
     137,    -1,    88,   138,    -1,    88,   139,    -1,    88,   141,
      -1,    88,   145,    -1,    88,   142,    -1,    88,   143,    -1,
      88,   144,    -1,    88,   146,    -1,    88,   147,    -1,    88,
     148,    -1,    88,   151,    -1,    84,   151,    -1,    89,   133,
      -1,    89,   134,    -1,    89,   135,    -1,    89,   136,    -1,
      89,   137,    -1,    89,   138,    -1,    89,   139,    -1,    89,
     140,    -1,    89,   142,    -1,    89,   143,    -1,    89,   144,
      -1,    89,   151,    -1,    85,   151,    -1,    90,   133,    -1,
      90,   134,    -1,    90,   135,    -1,    90,   136,    -1,    90,
     137,    -1,    90,   138,    -1,    90,   139,    -1,    90,   140,
      -1,    90,   142,    -1,    90,   143,    -1,    90,   144,    -1,
      90,   151,    -1,    86,   151,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   536,   536,   537,   540,   541,   544,   545,   546,   547,
     548,   549,   550,   551,   552,   553,   556,   559,   622,   624,
     634,   641,   651,   658,   668,   675,   685,   692,   702,   709,
     719,   726,   736,   743,   753,   762,   763,   764,   765,   766,
     767,   768,   769,   770,   771,   772,   773,   774,   775,   778,
     785,   793,   798,   808,   815,   823,   887,   888,   889,   890,
     891,   892,   893,   894,   895,   896,   897,   898,   899,   900,
     903,   910,   917,   927,   934,   941,   948,   956,   957,   958,
     959,   960,   961,   962,   963,   964,   965,   966,   967,   968,
     969,   970,   971,   972,   973,   974,   975,   976,   977,   978,
     979,   980,   981,   982,   983,   984,   985,   986,   987,   988,
     989,   990,   991,   992,   993,   994,   995,   996,   997,   998,
     999,  1000,  1001,  1002,  1003,  1004,  1005,  1006,  1007,  1008,
    1009,  1010,  1011,  1012,  1013,  1014,  1015,  1016,  1017,  1018,
    1019,  1020,  1021,  1022,  1023,  1024,  1025,  1028,  1035,  1042,
    1049,  1057,  1058,  1059,  1060,  1061,  1062,  1063,  1064,  1065,
    1066,  1067,  1068,  1069,  1070,  1071,  1072,  1073,  1074,  1075,
    1076,  1077,  1078,  1079,  1080,  1081,  1082,  1083,  1084,  1085,
    1086,  1087,  1088,  1089,  1090,  1091,  1092,  1093,  1094,  1095,
    1096,  1097,  1098,  1099,  1100,  1101,  1102,  1103,  1104,  1105,
    1106,  1107,  1108,  1109,  1110,  1111,  1114,  1121,  1128,  1135,
    1143,  1144,  1145,  1146,  1147,  1148,  1149,  1150,  1151,  1152,
    1153,  1154,  1155,  1156,  1157,  1158,  1159,  1160,  1161,  1162,
    1163,  1164,  1165,  1166,  1167,  1168,  1169,  1170,  1171,  1172,
    1173,  1174,  1175,  1176,  1177,  1178,  1179,  1180,  1181,  1182,
    1183,  1184,  1185,  1186,  1187,  1188,  1189,  1190,  1191,  1192,
    1193,  1194,  1195,  1196,  1197,  1198,  1199,  1200,  1201,  1202,
    1203,  1204,  1205,  1206,  1207,  1208,  1209,  1210,  1211,  1212,
    1213,  1214,  1215,  1216,  1217,  1218,  1219,  1220,  1221,  1222,
    1223,  1224,  1225,  1226,  1227,  1228,  1229,  1230,  1231,  1232,
    1233,  1234,  1235,  1236,  1237,  1238,  1239,  1240,  1241,  1242,
    1243,  1244,  1245,  1246,  1247,  1248,  1249,  1250,  1251,  1252,
    1253,  1254,  1255,  1256,  1257,  1258,  1259,  1260,  1261,  1262,
    1263,  1264,  1265,  1266,  1267,  1268,  1269,  1270,  1271,  1272,
    1273,  1274,  1275,  1276,  1277,  1278,  1279,  1280,  1281,  1282,
    1283,  1284,  1285,  1286,  1287,  1288,  1289,  1290,  1291,  1292,
    1293,  1294,  1295,  1296,  1297,  1298,  1299,  1300,  1301,  1302,
    1303,  1304,  1305,  1306,  1307,  1308,  1309,  1310,  1311,  1312,
    1313,  1314,  1315,  1316,  1317,  1318,  1319,  1320,  1321,  1322,
    1323,  1324,  1325,  1326,  1327,  1328,  1329,  1330,  1331,  1332,
    1333,  1334,  1335,  1336,  1337,  1338,  1339,  1340,  1341,  1342,
    1343,  1344,  1345,  1346,  1347,  1348,  1349,  1350,  1351,  1352,
    1353,  1354,  1355,  1356,  1357,  1358,  1359,  1360,  1361,  1362,
    1363,  1364,  1365,  1366,  1367,  1368,  1369,  1370,  1371
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TOK_JUMPN", "TOK_JUMP", "TOK_CALLN",
  "TOK_CALL", "TOK_RTS", "TOK_LIT", "TOK_FLAG", "TOK_BIT", "TOK_LOOPT",
  "TOK_LOOP16", "TOK_ENDLOOP", "TOK_DROP", "TOK_NIP", "TOK_SWAP",
  "TOK_DUP", "TOK_OVER", "TOK_ADDB", "TOK_ADDW", "TOK_ADDL", "TOK_ADDCB",
  "TOK_ADDCW", "TOK_ADDCL", "TOK_SUBB", "TOK_SUBW", "TOK_SUBL",
  "TOK_SUBCB", "TOK_SUBCW", "TOK_SUBCL", "TOK_SUB2B", "TOK_SUB2W",
  "TOK_SUB2L", "TOK_SUBC2B", "TOK_SUBC2W", "TOK_SUBC2L", "TOK_NEGB",
  "TOK_NEGW", "TOK_NEGL", "TOK_NEGCB", "TOK_NEGCW", "TOK_NEGCL",
  "TOK_DECW", "TOK_EXTW", "TOK_ANDB", "TOK_ANDW", "TOK_ANDL", "TOK_ORB",
  "TOK_ORW", "TOK_ORL", "TOK_XORB", "TOK_XORW", "TOK_XORL", "TOK_MSKB",
  "TOK_MSKW", "TOK_MSKL", "TOK_BANDB", "TOK_BANDW", "TOK_BANDL",
  "TOK_BORB", "TOK_BORW", "TOK_BORL", "TOK_BXORB", "TOK_BXORW",
  "TOK_BXORL", "TOK_BMSKB", "TOK_BMSKW", "TOK_BMSKL", "TOK_NOTB",
  "TOK_NOTW", "TOK_NOTL", "TOK_TSTB", "TOK_TSTW", "TOK_TSTL", "TOK_LSHB",
  "TOK_LSHW", "TOK_LSHL", "TOK_RSHB", "TOK_RSHW", "TOK_RSHL", "TOK_MUL",
  "TOK_DIV", "TOK_NOP", "TOK_LDB", "TOK_STB", "TOK_WRB", "TOK_FTW",
  "TOK_LDW", "TOK_STW", "TOK_WRW", "TOK_LDI", "TOK_FTI", "TOK_LDE",
  "TOK_FTE", "TOK_LDL", "TOK_STL", "TOK_WRL", "TOK_LDH", "TOK_STH",
  "TOK_WRH", "TOK_PC", "TOK_VEC", "TOK_EA1", "TOK_EA2", "TOK_CNT",
  "TOK_EXT", "TOK_T_SR", "TOK_S_SR", "TOK_A_SR", "TOK_I_SR", "TOK_B_SR",
  "TOK_X_SR", "TOK_N_SR", "TOK_V_SR", "TOK_CIN", "TOK_CLR", "TOK_C_ADD",
  "TOK_C_FLG", "TOK_Z_FLG", "TOK_N_FLG", "TOK_G_FLG", "TOK_N_B", "TOK_N_W",
  "TOK_T0", "TOK_T7", "TOK_T15", "TOK_N0", "TOK_N7", "TOK_N15",
  "TOK_EA1_4", "TOK_EA1_7", "TOK_EXT11", "TOK_EA1L", "TOK_EA1H",
  "TOK_EA2L", "TOK_EA2H", "TOK_PCL", "TOK_PCH", "TOK_VECL", "TOK_VECH",
  "TOK_CPUS", "TOK_LSHR", "TOK_ACCL", "TOK_ACCH", "TOK_IMMR", "TOK_DECJ",
  "TOK_EA1J", "TOK_EA2J", "TOK_EA1B", "TOK_EA2B", "TOK_SR", "TOK_RT",
  "TOK_RN", "TOK_MASK", "TOK_NUMBER", "TOK_IDENT", "TOK_RAL", "TOK_RDL",
  "TOK_RAH", "TOK_RDH", "TOK_RL", "TOK_RH", "TOK_A7L", "TOK_A7H",
  "TOK_USPL", "TOK_USPH", "TOK_SSPL", "TOK_SSPH", "TOK_TMP1L", "TOK_TMP1H",
  "TOK_TMP2L", "TOK_TMP2H", "TOK_VBRL", "TOK_VBRH", "TOK_ORG", "TOK_TABLE",
  "'\\n'", "':'", "','", "'('", "')'", "'#'", "'='", "'.'", "'+'", "'-'",
  "'['", "']'", "$accept", "input", "line", "expr", "label", "table",
  "org", "jump", "cond", "lit", "litop", "flg", "flgop", "cin", "loop",
  "alu", "aluop", "mem", "memop", "reg", "regop", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     385,   386,   387,   388,   389,   390,   391,   392,   393,   394,
     395,   396,   397,   398,   399,   400,   401,   402,   403,   404,
     405,   406,   407,   408,   409,   410,   411,   412,   413,   414,
     415,   416,   417,   418,   419,   420,   421,   422,   423,   424,
     425,   426,   427,   428,   429,   430,   431,    10,    58,    44,
      40,    41,    35,    61,    46,    43,    45,    91,    93
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   189,   190,   190,   191,   191,   192,   192,   192,   192,
     192,   192,   192,   192,   192,   192,   193,   194,   195,   196,
     196,   196,   196,   196,   196,   196,   196,   196,   196,   196,
     196,   196,   196,   196,   196,   197,   197,   197,   197,   197,
     197,   197,   197,   197,   197,   197,   197,   197,   197,   198,
     198,   199,   199,   200,   200,   201,   202,   202,   202,   202,
     202,   202,   202,   202,   202,   202,   202,   202,   202,   202,
     203,   203,   203,   204,   204,   204,   204,   205,   205,   205,
     205,   205,   205,   205,   205,   205,   205,   205,   205,   205,
     205,   205,   205,   205,   205,   205,   205,   205,   205,   205,
     205,   205,   205,   205,   205,   205,   205,   205,   205,   205,
     205,   205,   205,   205,   205,   205,   205,   205,   205,   205,
     205,   205,   205,   205,   205,   205,   205,   205,   205,   205,
     205,   205,   205,   205,   205,   205,   205,   205,   205,   205,
     205,   205,   205,   205,   205,   205,   205,   206,   206,   206,
     206,   207,   207,   207,   207,   207,   207,   207,   207,   207,
     207,   207,   207,   207,   207,   207,   207,   207,   207,   207,
     207,   207,   207,   207,   207,   207,   207,   207,   207,   207,
     207,   207,   207,   207,   207,   207,   207,   207,   207,   207,
     207,   207,   207,   207,   207,   207,   207,   207,   207,   207,
     207,   207,   207,   207,   207,   207,   208,   208,   208,   208,
     209,   209,   209,   209,   209,   209,   209,   209,   209,   209,
     209,   209,   209,   209,   209,   209,   209,   209,   209,   209,
     209,   209,   209,   209,   209,   209,   209,   209,   209,   209,
     209,   209,   209,   209,   209,   209,   209,   209,   209,   209,
     209,   209,   209,   209,   209,   209,   209,   209,   209,   209,
     209,   209,   209,   209,   209,   209,   209,   209,   209,   209,
     209,   209,   209,   209,   209,   209,   209,   209,   209,   209,
     209,   209,   209,   209,   209,   209,   209,   209,   209,   209,
     209,   209,   209,   209,   209,   209,   209,   209,   209,   209,
     209,   209,   209,   209,   209,   209,   209,   209,   209,   209,
     209,   209,   209,   209,   209,   209,   209,   209,   209,   209,
     209,   209,   209,   209,   209,   209,   209,   209,   209,   209,
     209,   209,   209,   209,   209,   209,   209,   209,   209,   209,
     209,   209,   209,   209,   209,   209,   209,   209,   209,   209,
     209,   209,   209,   209,   209,   209,   209,   209,   209,   209,
     209,   209,   209,   209,   209,   209,   209,   209,   209,   209,
     209,   209,   209,   209,   209,   209,   209,   209,   209,   209,
     209,   209,   209,   209,   209,   209,   209,   209,   209,   209,
     209,   209,   209,   209,   209,   209,   209,   209,   209,   209,
     209,   209,   209,   209,   209,   209,   209,   209,   209,   209,
     209,   209,   209,   209,   209,   209,   209,   209,   209,   209,
     209,   209,   209,   209,   209,   209,   209,   209,   209,   209,
     209,   209,   209,   209,   209,   209,   209,   209,   209
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     8,     2,     4,
       4,     4,     4,     4,     4,     4,     4,     2,     2,     2,
       2,     5,     5,     5,     5,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     3,     3,     2,     1,     3,     0,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       1,     1,     1,     3,     2,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     2,     2,
       1,     4,     5,     5,     5,     4,     5,     5,     5,     4,
       5,     5,     5,     4,     5,     5,     5,     4,     5,     5,
       5,     4,     5,     5,     5,     4,     5,     5,     5,     4,
       5,     5,     5,     4,     5,     5,     5,     4,     5,     5,
       5,     4,     5,     5,     5,     4,     5,     5,     5,     5,
       5,     5,     5,     5,     5,     5,     3,     2,     2,     1,
       5,     5,     5,     5,     5,     5,     5,     5,     5,     5,
       2,     2,     2,     2,     2,     5,     5,     5,     5,     5,
       5,     5,     5,     5,     5,     2,     2,     2,     2,     2,
       5,     5,     5,     2,     5,     5,     5,     5,     5,     5,
       5,     2,     2,     2,     2,     2,     5,     5,     5,     2,
       5,     5,     5,     5,     5,     5,     5,     2,     2,     2,
       2,     2,     5,     5,     5,     5,     5,     5,     5,     5,
       5,     5,     2,     2,     2,     2,     2,     5,     5,     5,
       5,     5,     5,     5,     5,     5,     5,     2,     2,     2,
       2,     2,     5,     5,     5,     2,     5,     5,     5,     5,
       5,     5,     5,     2,     2,     2,     2,     2,     5,     5,
       5,     2,     5,     5,     5,     5,     5,     5,     5,     2,
       2,     2,     2,     2,     5,     5,     5,     5,     5,     5,
       5,     5,     5,     5,     2,     2,     2,     2,     2,     5,
       5,     5,     5,     5,     5,     5,     5,     5,     5,     2,
       2,     2,     2,     2,     5,     5,     5,     2,     5,     5,
       5,     5,     5,     5,     5,     2,     2,     2,     2,     2,
       5,     5,     5,     2,     5,     5,     5,     5,     5,     5,
       5,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,     0,    71,
      70,    72,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       4,     3,     0,     8,     7,     6,     9,    10,    50,    11,
      54,    12,    13,    76,    14,   150,    15,   209,    48,    47,
      46,    45,    44,    43,    42,    35,    36,    37,    38,    39,
      40,    41,     0,    28,    27,     0,     0,    30,    29,     0,
       0,    56,   412,     0,     0,     0,     0,     0,     0,   223,
     238,   224,   239,   221,   236,   222,   237,   220,   235,     0,
       0,     0,   425,     0,     0,     0,     0,     0,     0,   285,
     300,   286,   301,   283,   298,   284,   299,   282,   297,     0,
       0,     0,   438,     0,     0,     0,     0,     0,     0,   347,
     362,   348,   363,   345,   360,   346,   361,   344,   359,     0,
     396,   397,   398,   399,   400,   401,   402,   403,   405,   406,
     407,   404,   408,   409,   410,   411,     0,     0,     0,     0,
       0,     0,   243,   259,   254,   270,   255,   271,   252,   268,
     253,   269,   251,   267,     0,     0,     0,   413,   414,   415,
     416,   417,   418,   419,   420,   421,   422,   423,   424,     0,
       0,     0,     0,     0,     0,   305,   321,   316,   332,   317,
     333,   314,   330,   315,   331,   313,   329,     0,     0,     0,
     426,   427,   428,   429,   430,   431,   432,   433,   434,   435,
     436,   437,     0,     0,     0,     0,     0,     0,   367,   383,
     378,   394,   379,   395,   376,   392,   377,   393,   375,   391,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    16,    18,     0,     5,
      49,    53,    74,    75,   148,   149,   207,   208,     0,     0,
       0,     0,     0,     0,     0,     0,    51,    52,     0,    55,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    73,   147,   206,    20,    19,     0,     0,    22,
      21,    24,    23,     0,     0,    26,    25,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   151,   167,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   175,   191,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   155,   171,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   179,
     195,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   163,
       0,     0,   187,     0,     0,   159,     0,     0,   183,     0,
       0,     0,    32,    31,    34,    33,     0,   211,   214,   218,
     210,   213,   217,   226,   229,   233,   225,   228,   232,   212,
     215,   216,   219,   227,   230,   231,   234,   152,   168,   154,
     170,   153,   169,   273,   276,   280,   272,   275,   279,   288,
     291,   295,   287,   290,   294,   274,   277,   278,   281,   289,
     292,   293,   296,   176,   192,   178,   194,   177,   193,   335,
     338,   342,   334,   337,   341,   350,   353,   357,   349,   352,
     356,   336,   339,   340,   343,   351,   354,   355,   358,   205,
     241,   245,   249,   240,   244,   248,   257,   261,   265,   256,
     260,   264,   242,   246,   247,   250,   258,   262,   263,   266,
     202,   199,   156,   172,   158,   174,   157,   173,   303,   307,
     311,   302,   306,   310,   319,   323,   327,   318,   322,   326,
     304,   308,   309,   312,   320,   324,   325,   328,   180,   196,
     182,   198,   181,   197,   365,   369,   373,   364,   368,   372,
     381,   385,   389,   380,   384,   388,   366,   370,   371,   374,
     382,   386,   387,   390,   200,   203,   201,   204,   164,   166,
     165,   188,   190,   189,   160,   162,   161,   184,   186,   185,
       0,    60,    63,    57,    58,    59,    61,    62,    64,    65,
      66,    67,    68,    69,     0,     0,    17
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,   101,   102,   103,   104,   105,   106,   132,   107,
     108,   109,   110,   339,   111,   112,   113,   114,   115,   116,
     117
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -176
static const yytype_int16 yypact[] =
{
    -176,     0,  -176,    50,   123,    50,   150,  -175,   -57,  -176,
    -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,
    -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,
    -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,
    -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,
    -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,
    -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,
    -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,
    -176,  -176,   175,   205,   235,   -73,   -33,    55,   151,   -63,
     -38,   -34,    16,   -64,   -37,   -35,   -18,   -55,   -11,    96,
    -176,  -176,    34,  -176,  -176,  -176,  -176,  -176,   249,  -176,
     255,  -176,  -176,    -6,  -176,    -5,  -176,     3,  -176,  -176,
    -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,
    -176,  -176,   113,   103,   124,   128,   152,   158,   159,   180,
     -36,   240,  -176,   167,   259,   263,   267,   271,   275,  -176,
    -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,    51,
     204,   286,  -176,   283,   287,   291,   299,   303,   307,  -176,
    -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,    62,
     302,   318,  -176,   315,   319,   323,   327,   331,   335,  -176,
    -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,   437,
    -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,
    -176,  -176,  -176,  -176,  -176,  -176,   339,   343,   352,   354,
     355,   356,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,
    -176,  -176,  -176,  -176,    82,   360,   364,  -176,  -176,  -176,
    -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,   358,
     359,   362,   363,   366,   367,  -176,  -176,  -176,  -176,  -176,
    -176,  -176,  -176,  -176,  -176,  -176,  -176,    69,   368,   371,
    -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,
    -176,  -176,   370,   372,   374,   375,   376,   378,  -176,  -176,
    -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,
     446,   451,   454,   455,   457,   384,   386,   464,   388,   390,
     466,   391,   392,   470,   394,   395,  -176,  -176,   379,  -176,
    -176,  -176,  -176,   569,  -176,   570,  -176,   571,    49,   427,
     428,    83,    90,   430,   432,   121,  -176,  -176,   468,  -176,
     169,   197,   341,   345,    97,   104,   400,   404,   254,   265,
     349,   353,   357,   361,   145,   162,   406,   407,   295,   309,
     365,   369,   373,   377,   193,   224,   408,   381,   385,   389,
     393,   247,   277,   410,   411,   412,   414,   314,   429,   397,
     401,   405,   409,   325,   329,   415,   416,   431,   433,   413,
     417,   421,   425,   333,   337,   418,   419,   420,   422,   423,
     483,   487,   424,   491,   495,   426,   499,   503,   434,   505,
     506,   456,  -176,  -176,  -176,  -176,  -176,   435,   436,  -176,
    -176,  -176,  -176,   438,   439,  -176,  -176,   440,   441,   442,
     443,   444,   445,   447,   448,   449,   450,   452,   453,   458,
     459,   460,   461,   462,   463,   465,   467,   469,   471,   473,
     478,   479,   480,   481,   475,   476,   477,   482,   484,   485,
     486,   488,   489,   490,   492,   493,   494,   496,   497,   498,
     500,   501,   502,   504,   508,   509,   510,   514,   515,   516,
     511,   512,   513,   517,   518,   519,   520,   521,   522,   523,
     524,   525,   526,   527,   528,   529,   530,   531,   532,   533,
     537,   535,   536,   538,   539,   540,   541,   542,   543,   544,
     545,   546,   547,   548,   549,   550,   551,   552,   553,   554,
     555,   559,   560,   561,   562,   567,   568,   572,   573,   563,
     564,   574,   575,   576,   577,   578,   579,   580,   581,   582,
     583,   584,   585,   586,   587,   588,   589,   590,   591,   565,
     595,   600,   601,   602,   603,   597,   598,   599,   604,   605,
     606,   607,   608,   609,   610,   611,   612,   613,   614,   615,
     616,   617,   618,   619,   620,   624,   625,   626,   627,   628,
     633,   634,   631,   636,   637,   635,   638,   640,   639,   641,
     642,   646,  -176,  -176,  -176,  -176,   298,  -176,  -176,  -176,
    -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,
    -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,
    -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,
    -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,
    -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,
    -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,
    -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,
    -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,
    -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,
    -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,
    -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,
    -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,
    -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,
    -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,
    -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,
    -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,
     472,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,
    -176,  -176,  -176,  -176,   647,   672,  -176
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,   383,  -176,
    -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,
    -176
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
       2,   322,   324,     3,     4,     5,     6,   140,     7,     8,
     326,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,   141,    95,    96,
     200,   201,   202,   203,   204,   205,   206,   199,   207,   208,
     209,   210,   211,   212,   213,   214,   304,   300,   215,   336,
     337,   305,   306,   316,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   225,   226,   227,   228,   229,   230,   231,
     232,   233,   301,   307,   317,   310,   302,   234,   308,   309,
     311,   312,   235,   236,   346,   347,    97,   118,   119,   120,
     121,   122,   313,   123,   124,   356,   357,   314,   315,   125,
     126,   127,   385,   386,   128,    98,    99,   100,   323,   325,
     129,   130,   131,   373,   374,   375,   376,   327,   237,   238,
     239,   240,   241,   242,   243,   244,   303,   245,   246,   247,
     440,   441,   442,   443,   415,   416,   248,   444,   445,   446,
     447,   319,   249,   250,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   263,   264,   265,   266,
     118,   119,   120,   121,   122,   267,   123,   124,   419,   420,
     268,   269,   125,   126,   127,   421,   422,   128,   466,   467,
     468,   469,   318,   129,   130,   131,   320,   118,   119,   120,
     121,   122,   321,   123,   124,   470,   471,   472,   473,   125,
     126,   127,   428,   429,   128,   430,   425,   426,   133,   134,
     129,   130,   131,   329,   270,   271,   272,   273,   274,   275,
     276,   277,   328,   278,   279,   280,   492,   493,   494,   495,
     431,   432,   281,   433,   330,   137,   138,   331,   282,   283,
     284,   285,   286,   287,   288,   289,   290,   291,   292,   293,
     294,   295,   296,   297,   298,   299,   142,   496,   497,   498,
     499,   332,   143,   144,   145,   146,   147,   148,   333,   334,
     149,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     513,   514,   515,   516,   340,   159,   162,   450,   451,   335,
     160,   161,   163,   164,   165,   166,   167,   168,   452,   453,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     517,   518,   519,   520,   348,   179,   182,   135,   136,   139,
     180,   181,   183,   184,   185,   186,   187,   188,   476,   477,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     761,   762,   478,   479,   763,   764,   765,   525,   526,   338,
     766,   767,   768,   769,   770,   771,   772,   773,   541,   542,
     543,   544,   545,   546,   547,   548,   567,   568,   569,   570,
     571,   572,   573,   574,   434,   435,   341,   436,   437,   438,
     342,   439,   454,   455,   343,   456,   457,   458,   344,   459,
     460,   461,   345,   462,   463,   464,   349,   465,   480,   481,
     350,   482,   483,   484,   351,   485,   486,   487,   352,   488,
     489,   490,   358,   491,   501,   502,   353,   503,   504,   505,
     354,   506,   507,   508,   355,   509,   510,   511,   359,   512,
     529,   530,   360,   531,   532,   533,   361,   534,   535,   536,
     362,   537,   538,   539,   363,   540,   555,   556,   364,   557,
     558,   559,   365,   560,   561,   562,   367,   563,   564,   565,
     368,   566,   527,   528,   551,   552,   553,   554,   366,   369,
     377,   370,   371,   372,   378,   379,   380,   395,   387,   381,
     382,   388,   396,   383,   384,   397,   398,   389,   411,   390,
     399,   391,   392,   393,   400,   394,   401,   402,   403,   405,
     404,   406,   407,   408,   409,   410,   412,   413,   414,   417,
     418,   448,   423,   427,   424,   449,   580,   474,   475,   500,
     581,   521,   522,   523,   583,   524,   549,   550,   584,   575,
     576,   577,   586,   578,   579,   582,   587,   585,   589,   590,
       0,     0,   591,     0,     0,   588,   592,   593,     0,   594,
     595,     0,     0,   596,     0,     0,     0,     0,   774,   597,
     598,   599,   600,   601,     0,   602,   603,   604,   605,     0,
     606,   607,     0,     0,     0,     0,   608,   609,   610,   611,
     612,   613,     0,   614,     0,   615,   617,   616,   618,   619,
     620,   621,   622,   623,   624,   625,     0,     0,     0,     0,
     626,     0,   627,   628,   629,     0,   630,   631,   632,     0,
     633,   634,   635,     0,   636,   637,   638,     0,   639,   640,
     641,   645,   642,   643,   644,   646,   647,   648,     0,   649,
     650,   651,     0,     0,     0,   652,   653,   654,   655,   656,
     657,   658,   659,   660,   661,   662,   663,   664,   665,   666,
     667,   668,   669,   670,   671,     0,   672,   673,   674,   675,
     676,   677,   678,   679,   680,   681,   682,   683,   684,   685,
     686,   687,   688,   689,   690,   691,   692,   693,   694,   695,
     718,   698,   699,   696,   697,     0,     0,     0,     0,     0,
       0,     0,   700,   701,   702,   703,   704,   705,   706,   707,
     708,   709,   710,   711,   712,   713,   714,   715,   716,   717,
     719,   720,   721,   722,   723,   724,   725,   726,     0,     0,
       0,     0,   727,   728,   729,   730,   731,   732,   733,   734,
     735,   736,   737,   738,   739,   740,   741,   742,   743,   744,
     745,   746,   747,   748,   749,   750,   751,   752,   753,   755,
     754,   756,   758,   759,   757,   760,   775,   776
};

static const yytype_int16 yycheck[] =
{
       0,     7,     7,     3,     4,     5,     6,   182,     8,     9,
       7,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,   154,    98,    99,
     133,   134,   135,   136,   137,   138,   139,   180,   141,   142,
     143,   144,   145,   146,   147,   148,   180,   180,   151,   155,
     156,   185,   186,   178,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   180,   180,   155,   180,   180,   180,   185,   186,
     185,   186,   185,   186,   103,   104,   156,   107,   108,   109,
     110,   111,   180,   113,   114,   103,   104,   185,   186,   119,
     120,   121,   103,   104,   124,   175,   176,   177,   184,   184,
     130,   131,   132,   101,   102,   103,   104,   184,   133,   134,
     135,   136,   137,   138,   139,   140,   180,   142,   143,   144,
     103,   104,   105,   106,   155,   156,   151,   103,   104,   105,
     106,   177,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     107,   108,   109,   110,   111,   180,   113,   114,   155,   156,
     185,   186,   119,   120,   121,   155,   156,   124,   103,   104,
     105,   106,   156,   130,   131,   132,     7,   107,   108,   109,
     110,   111,     7,   113,   114,   103,   104,   105,   106,   119,
     120,   121,   103,   104,   124,   106,   155,   156,   155,   156,
     130,   131,   132,   180,   133,   134,   135,   136,   137,   138,
     139,   140,   179,   142,   143,   144,   103,   104,   105,   106,
     103,   104,   151,   106,   180,   155,   156,   179,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   151,   103,   104,   105,
     106,   179,   157,   158,   159,   160,   161,   162,   180,   180,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     103,   104,   105,   106,   187,   180,   151,   103,   104,   179,
     185,   186,   157,   158,   159,   160,   161,   162,   103,   104,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     103,   104,   105,   106,   180,   180,   151,     4,     5,     6,
     185,   186,   157,   158,   159,   160,   161,   162,   103,   104,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     112,   113,   103,   104,   116,   117,   118,   103,   104,   179,
     122,   123,   124,   125,   126,   127,   128,   129,   103,   104,
     105,   106,   103,   104,   105,   106,   103,   104,   105,   106,
     103,   104,   105,   106,   103,   104,   187,   106,   103,   104,
     187,   106,   103,   104,   187,   106,   103,   104,   187,   106,
     103,   104,   187,   106,   103,   104,   180,   106,   103,   104,
     187,   106,   103,   104,   187,   106,   103,   104,   187,   106,
     103,   104,   180,   106,   103,   104,   187,   106,   103,   104,
     187,   106,   103,   104,   187,   106,   103,   104,   180,   106,
     103,   104,   187,   106,   103,   104,   187,   106,   103,   104,
     187,   106,   103,   104,   187,   106,   103,   104,   187,   106,
     103,   104,   187,   106,   103,   104,   187,   106,   103,   104,
     187,   106,   103,   104,   103,   104,   103,   104,   101,   187,
     180,   187,   187,   187,   180,   187,   187,   101,   180,   187,
     187,   180,   101,   187,   187,   101,   101,   187,   179,   187,
     103,   187,   187,   187,   180,   187,   180,   103,   180,   103,
     180,   180,   180,   103,   180,   180,     7,     7,     7,   152,
     152,   181,   152,   115,   152,   181,   103,   181,   181,   181,
     103,   181,   181,   181,   103,   181,   181,   181,   103,   181,
     181,   181,   103,   181,   181,   181,   103,   181,   103,   103,
      -1,    -1,   156,    -1,    -1,   181,   181,   181,    -1,   181,
     181,    -1,    -1,   183,    -1,    -1,    -1,    -1,   156,   188,
     188,   188,   188,   188,    -1,   188,   188,   188,   188,    -1,
     188,   188,    -1,    -1,    -1,    -1,   188,   188,   188,   188,
     188,   188,    -1,   188,    -1,   188,   185,   188,   185,   181,
     181,   181,   181,   188,   188,   188,    -1,    -1,    -1,    -1,
     188,    -1,   188,   188,   188,    -1,   188,   188,   188,    -1,
     188,   188,   188,    -1,   188,   188,   188,    -1,   188,   188,
     188,   181,   188,   185,   185,   181,   181,   181,    -1,   188,
     188,   188,    -1,    -1,    -1,   188,   188,   188,   188,   188,
     188,   188,   188,   188,   188,   188,   188,   188,   188,   188,
     188,   188,   185,   188,   188,    -1,   188,   188,   188,   188,
     188,   188,   188,   188,   188,   188,   188,   188,   188,   188,
     188,   188,   188,   188,   185,   185,   185,   185,   181,   181,
     185,   188,   188,   181,   181,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   188,   188,   188,   188,   188,   188,   188,   188,
     188,   188,   188,   188,   188,   188,   188,   188,   188,   188,
     185,   181,   181,   181,   181,   188,   188,   188,    -1,    -1,
      -1,    -1,   188,   188,   188,   188,   188,   188,   188,   188,
     188,   188,   188,   188,   188,   188,   188,   188,   188,   185,
     185,   185,   185,   185,   181,   181,   185,   181,   181,   181,
     185,   181,   181,   181,   185,   179,   179,   155
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   190,     0,     3,     4,     5,     6,     8,     9,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    98,    99,   156,   175,   176,
     177,   191,   192,   193,   194,   195,   196,   198,   199,   200,
     201,   203,   204,   205,   206,   207,   208,   209,   107,   108,
     109,   110,   111,   113,   114,   119,   120,   121,   124,   130,
     131,   132,   197,   155,   156,   197,   197,   155,   156,   197,
     182,   154,   151,   157,   158,   159,   160,   161,   162,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,   180,
     185,   186,   151,   157,   158,   159,   160,   161,   162,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,   180,
     185,   186,   151,   157,   158,   159,   160,   161,   162,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,   180,
     133,   134,   135,   136,   137,   138,   139,   141,   142,   143,
     144,   145,   146,   147,   148,   151,   157,   158,   159,   160,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   172,   173,   174,   180,   185,   186,   133,   134,   135,
     136,   137,   138,   139,   140,   142,   143,   144,   151,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   174,   180,   185,   186,
     133,   134,   135,   136,   137,   138,   139,   140,   142,   143,
     144,   151,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     180,   180,   180,   180,   180,   185,   186,   180,   185,   186,
     180,   185,   186,   180,   185,   186,   178,   155,   156,   177,
       7,     7,     7,   184,     7,   184,     7,   184,   179,   180,
     180,   179,   179,   180,   180,   179,   155,   156,   179,   202,
     187,   187,   187,   187,   187,   187,   103,   104,   180,   180,
     187,   187,   187,   187,   187,   187,   103,   104,   180,   180,
     187,   187,   187,   187,   187,   187,   101,   187,   187,   187,
     187,   187,   187,   101,   102,   103,   104,   180,   180,   187,
     187,   187,   187,   187,   187,   103,   104,   180,   180,   187,
     187,   187,   187,   187,   187,   101,   101,   101,   101,   103,
     180,   180,   103,   180,   180,   103,   180,   180,   103,   180,
     180,   179,     7,     7,     7,   155,   156,   152,   152,   155,
     156,   155,   156,   152,   152,   155,   156,   115,   103,   104,
     106,   103,   104,   106,   103,   104,   106,   103,   104,   106,
     103,   104,   105,   106,   103,   104,   105,   106,   181,   181,
     103,   104,   103,   104,   103,   104,   106,   103,   104,   106,
     103,   104,   106,   103,   104,   106,   103,   104,   105,   106,
     103,   104,   105,   106,   181,   181,   103,   104,   103,   104,
     103,   104,   106,   103,   104,   106,   103,   104,   106,   103,
     104,   106,   103,   104,   105,   106,   103,   104,   105,   106,
     181,   103,   104,   106,   103,   104,   106,   103,   104,   106,
     103,   104,   106,   103,   104,   105,   106,   103,   104,   105,
     106,   181,   181,   181,   181,   103,   104,   103,   104,   103,
     104,   106,   103,   104,   106,   103,   104,   106,   103,   104,
     106,   103,   104,   105,   106,   103,   104,   105,   106,   181,
     181,   103,   104,   103,   104,   103,   104,   106,   103,   104,
     106,   103,   104,   106,   103,   104,   106,   103,   104,   105,
     106,   103,   104,   105,   106,   181,   181,   181,   181,   181,
     103,   103,   181,   103,   103,   181,   103,   103,   181,   103,
     103,   156,   181,   181,   181,   181,   183,   188,   188,   188,
     188,   188,   188,   188,   188,   188,   188,   188,   188,   188,
     188,   188,   188,   188,   188,   188,   188,   185,   185,   181,
     181,   181,   181,   188,   188,   188,   188,   188,   188,   188,
     188,   188,   188,   188,   188,   188,   188,   188,   188,   188,
     188,   188,   188,   185,   185,   181,   181,   181,   181,   188,
     188,   188,   188,   188,   188,   188,   188,   188,   188,   188,
     188,   188,   188,   188,   188,   188,   188,   188,   188,   185,
     188,   188,   188,   188,   188,   188,   188,   188,   188,   188,
     188,   188,   188,   188,   188,   188,   188,   188,   188,   188,
     185,   185,   185,   185,   181,   181,   181,   181,   188,   188,
     188,   188,   188,   188,   188,   188,   188,   188,   188,   188,
     188,   188,   188,   188,   188,   188,   188,   188,   185,   185,
     181,   181,   181,   181,   188,   188,   188,   188,   188,   188,
     188,   188,   188,   188,   188,   188,   188,   188,   188,   188,
     188,   188,   188,   188,   185,   185,   185,   185,   185,   181,
     181,   185,   181,   181,   185,   181,   181,   185,   181,   181,
     179,   112,   113,   116,   117,   118,   122,   123,   124,   125,
     126,   127,   128,   129,   156,   179,   155
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 16:

/* Line 1455 of yacc.c  */
#line 556 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { lbl_decl((yyvsp[(1) - (2)].txt), rom_addr); ;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 560 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    {
        int lbl0;
        int lbl1;
        int lbl2;

        lbl0 = lbl_use((yyvsp[(2) - (8)].txt), rom_addr);
        lbl1 = lbl_use((yyvsp[(4) - (8)].txt), rom_addr);
        lbl2 = lbl_use((yyvsp[(6) - (8)].txt), rom_addr);
        jmp_data[jmp_idx][0] = lbl0;
        jmp_data[jmp_idx][1] = lbl1 - lbl0;
        jmp_data[jmp_idx][2] = lbl2 - lbl0;
        switch ((yyvsp[(8) - (8)].val))
        {
            case 0x0000:
                jmp_data[jmp_idx][3] = 0;
                break;
            case 0x01F5:
                jmp_data[jmp_idx][3] = 1;
                break;
            case 0x01FC:
                jmp_data[jmp_idx][3] = 2;
                break;
            case 0x01FD:
                jmp_data[jmp_idx][3] = 3;
                break;
            case 0x01FE:
                jmp_data[jmp_idx][3] = 4;
                break;
            case 0x01FF:
                jmp_data[jmp_idx][3] = 5;
                break;
            case 0x07CD:
                jmp_data[jmp_idx][3] = 6;
                break;
            case 0x07E4:
                jmp_data[jmp_idx][3] = 7;
                break;
            case 0x07E5:
                jmp_data[jmp_idx][3] = 8;
                break;
            case 0x07EC:
                jmp_data[jmp_idx][3] = 9;
                break;
            case 0x07FD:
                jmp_data[jmp_idx][3] = 10;
                break;
            case 0x09FD:
                jmp_data[jmp_idx][3] = 11;
                break;
            case 0x0FFD:
                jmp_data[jmp_idx][3] = 12;
                break;
            case 0x0FFF:
                jmp_data[jmp_idx][3] = 13;
                break;
            default:
                jmp_data[jmp_idx][3] = 14;
                break;
        }
        if (jmp_idx < 255) jmp_idx++
      ;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 622 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { rom_addr = (yyvsp[(2) - (2)].val) & (ROM_SIZE - 1); ;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 625 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    {
        int lbl;

        lbl = lbl_use((yyvsp[(4) - (4)].txt), rom_addr);
        rom_data[rom_addr] = OPC_JUMPN | (yyvsp[(2) - (4)].val) | (lbl & 0x7FF);
        sprintf(buf, "JUMPN %s,%s", cc_str[(yyvsp[(2) - (4)].val) >> 12], (yyvsp[(4) - (4)].txt));
        strncpy(&rom_instr[rom_addr * 32], buf, 31);
        rom_addr++;
      ;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 635 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    {
        rom_data[rom_addr] = OPC_JUMPN | (yyvsp[(2) - (4)].val) | ((yyvsp[(4) - (4)].val) & 0x7FF);
        sprintf(buf, "JUMPN %s,%04X", cc_str[(yyvsp[(2) - (4)].val) >> 12], (yyvsp[(4) - (4)].val));
        strncpy(&rom_instr[rom_addr * 32], buf, 31);
        rom_addr++;
      ;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 642 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    {
        int lbl;

        lbl = lbl_use((yyvsp[(4) - (4)].txt), rom_addr);
        rom_data[rom_addr] = OPC_JUMP | (yyvsp[(2) - (4)].val) | (lbl & 0x7FF);
        sprintf(buf, "JUMP %s,%s", cc_str[(yyvsp[(2) - (4)].val) >> 12], (yyvsp[(4) - (4)].txt));
        strncpy(&rom_instr[rom_addr * 32], buf, 31);
        rom_addr++;
      ;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 652 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    {
        rom_data[rom_addr] = OPC_JUMP | (yyvsp[(2) - (4)].val) | ((yyvsp[(4) - (4)].val) & 0x7FF);
        sprintf(buf, "JUMP %s,%04X", cc_str[(yyvsp[(2) - (4)].val) >> 12], (yyvsp[(4) - (4)].val));
        strncpy(&rom_instr[rom_addr * 32], buf, 31);
        rom_addr++;
      ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 659 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    {
        int lbl;

        lbl = lbl_use((yyvsp[(4) - (4)].txt), rom_addr);
        rom_data[rom_addr] = OPC_CALLN | (yyvsp[(2) - (4)].val) | (lbl & 0x7FF);
        sprintf(buf, "CALLN %s,%s", cc_str[(yyvsp[(2) - (4)].val) >> 12], (yyvsp[(4) - (4)].txt));
        strncpy(&rom_instr[rom_addr * 32], buf, 31);
        rom_addr++;
      ;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 669 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    {
        rom_data[rom_addr] = OPC_CALLN | (yyvsp[(2) - (4)].val) | ((yyvsp[(4) - (4)].val) & 0x7FF);
        sprintf(buf, "CALLN %s,%04X", cc_str[(yyvsp[(2) - (4)].val) >> 12], (yyvsp[(4) - (4)].val));
        strncpy(&rom_instr[rom_addr * 32], buf, 31);
        rom_addr++;
      ;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 676 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    {
        int lbl;

        lbl = lbl_use((yyvsp[(4) - (4)].txt), rom_addr);
        rom_data[rom_addr] = OPC_CALL | (yyvsp[(2) - (4)].val) | (lbl & 0x7FF);
        sprintf(buf, "CALL %s,%s", cc_str[(yyvsp[(2) - (4)].val) >> 12], (yyvsp[(4) - (4)].txt));
        strncpy(&rom_instr[rom_addr * 32], buf, 31);
        rom_addr++;
      ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 686 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    {
        rom_data[rom_addr] = OPC_CALL | (yyvsp[(2) - (4)].val) | ((yyvsp[(4) - (4)].val) & 0x7FF);
        sprintf(buf, "CALL %s,%04X", cc_str[(yyvsp[(2) - (4)].val) >> 12], (yyvsp[(4) - (4)].val));
        strncpy(&rom_instr[rom_addr * 32], buf, 31);
        rom_addr++;
      ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 693 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    {
        int lbl;

        lbl = lbl_use((yyvsp[(2) - (2)].txt), rom_addr);
        rom_data[rom_addr] = OPC_JUMP | CC_TRUE | (lbl & 0x7FF);
        sprintf(buf, "JUMP %s", (yyvsp[(2) - (2)].txt));
        strncpy(&rom_instr[rom_addr * 32], buf, 31);
        rom_addr++;
      ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 703 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    {
        rom_data[rom_addr] = OPC_JUMP | CC_TRUE | ((yyvsp[(2) - (2)].val) & 0x7FF);
        sprintf(buf, "JUMP %04X", (yyvsp[(2) - (2)].val));
        strncpy(&rom_instr[rom_addr * 32], buf, 31);
        rom_addr++;
      ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 710 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    {
        int lbl;

        lbl = lbl_use((yyvsp[(2) - (2)].txt), rom_addr);
        rom_data[rom_addr] = OPC_CALL | CC_TRUE | (lbl & 0x7FF);
        sprintf(buf, "CALL %s", (yyvsp[(2) - (2)].txt));
        strncpy(&rom_instr[rom_addr * 32], buf, 31);
        rom_addr++;
      ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 720 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    {
        rom_data[rom_addr] = OPC_CALL | CC_TRUE | ((yyvsp[(2) - (2)].val) & 0x7FF);
        sprintf(buf, "CALL %04X", (yyvsp[(2) - (2)].val));
        strncpy(&rom_instr[rom_addr * 32], buf, 31);
        rom_addr++;
      ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 727 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    {
        int lbl;

        lbl = lbl_use((yyvsp[(2) - (5)].txt), rom_addr);
        rom_data[rom_addr] = OPC_JUMP | CC_IND | (lbl & 0x7FF);
        sprintf(buf, "JUMP %s(T)", (yyvsp[(2) - (5)].txt));
        strncpy(&rom_instr[rom_addr * 32], buf, 31);
        rom_addr++;
      ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 737 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    {
        rom_data[rom_addr] = OPC_JUMP | CC_IND | ((yyvsp[(2) - (5)].val) & 0x7FF);
        sprintf(buf, "JUMP %04X(T)", (yyvsp[(2) - (5)].val));
        strncpy(&rom_instr[rom_addr * 32], buf, 31);
        rom_addr++;
      ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 744 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    {
        int lbl;

        lbl = lbl_use((yyvsp[(2) - (5)].txt), rom_addr);
        rom_data[rom_addr] = OPC_CALL | CC_IND | (lbl & 0x7FF);
        sprintf(buf, "CALL %s(T)", (yyvsp[(2) - (5)].txt));
        strncpy(&rom_instr[rom_addr * 32], buf, 31);
        rom_addr++;
      ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 754 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    {
        rom_data[rom_addr] = OPC_CALL | CC_IND | ((yyvsp[(2) - (5)].val) & 0x7FF);
        sprintf(buf, "CALL %04X(T)", (yyvsp[(2) - (5)].val));
        strncpy(&rom_instr[rom_addr * 32], buf, 31);
        rom_addr++;
      ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 762 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CC_Z_FLG;  ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 763 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CC_N_FLG;  ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 764 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CC_G_FLG;  ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 765 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CC_T0;     ;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 766 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CC_EA1_4;  ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 767 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CC_EA1_7;  ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 768 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CC_EXT_11; ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 769 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CC_V_SR;   ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 770 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CC_N_SR;   ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 771 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CC_B_SR;   ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 772 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CC_I_SR;   ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 773 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CC_A_SR;   ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 774 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CC_S_SR;   ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 775 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CC_T_SR;   ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 779 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    {
        rom_data[rom_addr] = (yyvsp[(1) - (2)].val) | OPC_RTS;
        strcat(buf, "; RTS");
        strncpy(&rom_instr[rom_addr * 32], buf, 31);
        rom_addr++;
      ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 786 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    {
        rom_data[rom_addr] = (yyvsp[(1) - (1)].val);
        strncpy(&rom_instr[rom_addr * 32], buf, 31);
        rom_addr++;
      ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 794 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    {
        (yyval.val) = OPC_LIT | ((yyvsp[(3) - (3)].val) & 0xFFFF);
        sprintf(buf, "LIT #%04X", (yyvsp[(3) - (3)].val) & 0xFFFF);
      ;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 799 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    {
        int lbl;

        lbl = lbl_use((yyvsp[(3) - (3)].txt), rom_addr);
        (yyval.val) = OPC_LIT | (lbl & 0xFFFF);
        sprintf(buf, "LIT #%s", (yyvsp[(3) - (3)].txt));
      ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 809 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    {
        rom_data[rom_addr] = (yyvsp[(1) - (2)].val) | OPC_RTS;
        strcat(buf, "; RTS");
        strncpy(&rom_instr[rom_addr * 32], buf, 31);
        rom_addr++;
      ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 816 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    {
        rom_data[rom_addr] = (yyvsp[(1) - (1)].val);
        strncpy(&rom_instr[rom_addr * 32], buf, 31);
        rom_addr++;
      ;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 824 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    {
        int m, i, v;

        (yyval.val) = OPC_FLAG | (yyvsp[(2) - (3)].val) | (yyvsp[(3) - (3)].val);
        sprintf(buf, "FLAG -----,CIN=%s", flg_str[((yyvsp[(3) - (3)].val) >> 11) & 15]);
        m = (yyvsp[(2) - (3)].val);
        for (i = 0; i < 5; i++)
        {
          switch (i)
          {
            case 0: // X
              v = (m >> 9) & 3;
              break;
            case 1: // N
              v = (m >> 7) & 3;
              break;
            case 2: // Z
              v = (m >> 4) & 7;
              break;
            case 3: // V
              v = (m >> 2) & 3;
              break;
            case 4: // C
              v = m & 3;
              break;
            default:
              v = 0;
          }
          switch (v)
          {
            case 0:
            case 4:
            {
              buf[5+i] = '-';
              break;
            }
            case 1:
            {
              buf[5+i] = '*';
              break;
            }
            case 2:
            case 6:
            {
              buf[5+i] = '0';
              break;
            }
            case 3:
            case 7:
            {
              buf[5+i] = '1';
              break;
            }
            case 5:
            {
              buf[5+i] = '#';
              break;
            }
          }
        }
      ;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 887 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CIN_KEEP;  ;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 888 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CIN_CLR;   ;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 889 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CIN_C_ADD; ;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 890 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CIN_C_FLG; ;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 891 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CIN_X_SR;  ;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 892 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CIN_N_B;   ;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 893 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CIN_N_W;   ;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 894 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CIN_N_SR;  ;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 895 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CIN_T0;    ;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 896 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CIN_T7;    ;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 897 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CIN_T15;   ;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 898 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CIN_N0;    ;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 899 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CIN_N7;    ;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 900 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CIN_N15;  ;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 904 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    {
        loop_addr = rom_addr;
        rom_data[rom_addr] = OPC_LOOP;
        strcpy(&rom_instr[rom_addr * 32], "LOOP #16");
        rom_addr++;
      ;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 911 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    {
        loop_addr = rom_addr;
        rom_data[rom_addr] = OPC_LOOP | 0x0800;
        strcpy(&rom_instr[rom_addr * 32], "LOOP T");
        rom_addr++;
      ;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 918 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    {
        if (loop_addr != -1)
        {
          rom_data[loop_addr] |= ((rom_addr - 1) & 0x7FF);
          loop_addr = -1;
        }
      ;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 928 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    {
        rom_data[rom_addr] = (yyvsp[(1) - (3)].val) | ALU_CCUPD | OPC_RTS;
        strcat(buf, ".; RTS");
        strncpy(&rom_instr[rom_addr * 32], buf, 31);
        rom_addr++;
      ;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 935 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    {
        rom_data[rom_addr] = (yyvsp[(1) - (2)].val) | OPC_RTS;
        strcat(buf, "; RTS");
        strncpy(&rom_instr[rom_addr * 32], buf, 31);
        rom_addr++;
      ;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 942 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    {
        rom_data[rom_addr] = (yyvsp[(1) - (2)].val) | ALU_CCUPD;
        strcat(buf, ".");
        strncpy(&rom_instr[rom_addr * 32], buf, 31);
        rom_addr++;
      ;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 949 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    {
        rom_data[rom_addr] = (yyvsp[(1) - (1)].val);
        strncpy(&rom_instr[rom_addr * 32], buf, 31);
        rom_addr++;
      ;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 956 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = ALU_DROP;   strcpy(buf, "DROP");  ;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 957 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = ALU_NIP;    strcpy(buf, "NIP");   ;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 958 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = ALU_SWAP;   strcpy(buf, "SWAP");  ;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 959 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = ALU_DUP;    strcpy(buf, "DUP");   ;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 960 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = ALU_OVER;   strcpy(buf, "OVER");  ;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 961 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = ALU_ADDB;   strcpy(buf, "ADDB");  ;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 962 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = ALU_ADDW;   strcpy(buf, "ADDW");  ;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 963 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = ALU_ADDL;   strcpy(buf, "ADDL");  ;}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 964 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = ALU_ADDCB;  strcpy(buf, "ADDCB"); ;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 965 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = ALU_ADDCW;  strcpy(buf, "ADDCW"); ;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 966 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = ALU_ADDCL;  strcpy(buf, "ADDCL"); ;}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 967 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = ALU_SUBB;   strcpy(buf, "SUBB");  ;}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 968 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = ALU_SUBW;   strcpy(buf, "SUBW");  ;}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 969 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = ALU_SUBL;   strcpy(buf, "SUBL");  ;}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 970 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = ALU_SUBCB;  strcpy(buf, "SUBCB"); ;}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 971 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = ALU_SUBCW;  strcpy(buf, "SUBCW"); ;}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 972 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = ALU_SUBCL;  strcpy(buf, "SUBCL"); ;}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 973 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = ALU_SUB2B;  strcpy(buf, "SUBB");  ;}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 974 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = ALU_SUB2W;  strcpy(buf, "SUBW");  ;}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 975 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = ALU_SUB2L;  strcpy(buf, "SUBL");  ;}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 976 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = ALU_SUBC2B; strcpy(buf, "SUBCB"); ;}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 977 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = ALU_SUBC2W; strcpy(buf, "SUBCW"); ;}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 978 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = ALU_SUBC2L; strcpy(buf, "SUBCL"); ;}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 979 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = ALU_NEGB;   strcpy(buf, "NEGB");  ;}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 980 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = ALU_NEGW;   strcpy(buf, "NEGW");  ;}
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 981 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = ALU_NEGL;   strcpy(buf, "NEGL");  ;}
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 982 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = ALU_NEGCB;  strcpy(buf, "NEGCB"); ;}
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 983 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = ALU_NEGCW;  strcpy(buf, "NEGCW"); ;}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 984 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = ALU_NEGCL;  strcpy(buf, "NEGCL"); ;}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 985 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = ALU_DECW;   strcpy(buf, "DECW");  ;}
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 986 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = ALU_EXTW;   strcpy(buf, "EXTW");  ;}
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 987 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = ALU_ANDB;   strcpy(buf, "ANDB");  ;}
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 988 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = ALU_ANDW;   strcpy(buf, "ANDW");  ;}
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 989 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = ALU_ANDL;   strcpy(buf, "ANDL");  ;}
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 990 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = ALU_ORB;    strcpy(buf, "ORB");   ;}
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 991 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = ALU_ORW;    strcpy(buf, "ORW");   ;}
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 992 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = ALU_ORL;    strcpy(buf, "ORL");   ;}
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 993 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = ALU_XORB;   strcpy(buf, "XORB");  ;}
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 994 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = ALU_XORW;   strcpy(buf, "XORW");  ;}
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 995 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = ALU_XORL;   strcpy(buf, "XORL");  ;}
    break;

  case 117:

/* Line 1455 of yacc.c  */
#line 996 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = ALU_MSKB;   strcpy(buf, "MSKB");  ;}
    break;

  case 118:

/* Line 1455 of yacc.c  */
#line 997 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = ALU_MSKW;   strcpy(buf, "MSKW");  ;}
    break;

  case 119:

/* Line 1455 of yacc.c  */
#line 998 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = ALU_MSKL;   strcpy(buf, "MSKL");  ;}
    break;

  case 120:

/* Line 1455 of yacc.c  */
#line 999 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = ALU_BANDB;  strcpy(buf, "BANDB"); ;}
    break;

  case 121:

/* Line 1455 of yacc.c  */
#line 1000 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = ALU_BANDW;  strcpy(buf, "BANDW"); ;}
    break;

  case 122:

/* Line 1455 of yacc.c  */
#line 1001 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = ALU_BANDL;  strcpy(buf, "BANDL"); ;}
    break;

  case 123:

/* Line 1455 of yacc.c  */
#line 1002 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = ALU_BORB;   strcpy(buf, "BORB");  ;}
    break;

  case 124:

/* Line 1455 of yacc.c  */
#line 1003 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = ALU_BORW;   strcpy(buf, "BORW");  ;}
    break;

  case 125:

/* Line 1455 of yacc.c  */
#line 1004 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = ALU_BORL;   strcpy(buf, "BORL");  ;}
    break;

  case 126:

/* Line 1455 of yacc.c  */
#line 1005 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = ALU_BXORB;  strcpy(buf, "BXORB"); ;}
    break;

  case 127:

/* Line 1455 of yacc.c  */
#line 1006 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = ALU_BXORW;  strcpy(buf, "BXORW"); ;}
    break;

  case 128:

/* Line 1455 of yacc.c  */
#line 1007 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = ALU_BXORL;  strcpy(buf, "BXORL"); ;}
    break;

  case 129:

/* Line 1455 of yacc.c  */
#line 1008 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = ALU_BMSKB;  strcpy(buf, "BMSKB"); ;}
    break;

  case 130:

/* Line 1455 of yacc.c  */
#line 1009 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = ALU_BMSKW;  strcpy(buf, "BMSKW"); ;}
    break;

  case 131:

/* Line 1455 of yacc.c  */
#line 1010 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = ALU_BMSKL;  strcpy(buf, "BMSKL"); ;}
    break;

  case 132:

/* Line 1455 of yacc.c  */
#line 1011 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = ALU_NOTB;   strcpy(buf, "NOTB");  ;}
    break;

  case 133:

/* Line 1455 of yacc.c  */
#line 1012 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = ALU_NOTW;   strcpy(buf, "NOTW");  ;}
    break;

  case 134:

/* Line 1455 of yacc.c  */
#line 1013 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = ALU_NOTL;   strcpy(buf, "NOTL");  ;}
    break;

  case 135:

/* Line 1455 of yacc.c  */
#line 1014 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = ALU_TSTB;   strcpy(buf, "TSTB");  ;}
    break;

  case 136:

/* Line 1455 of yacc.c  */
#line 1015 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = ALU_TSTW;   strcpy(buf, "TSTW");  ;}
    break;

  case 137:

/* Line 1455 of yacc.c  */
#line 1016 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = ALU_TSTL;   strcpy(buf, "TSTL");  ;}
    break;

  case 138:

/* Line 1455 of yacc.c  */
#line 1017 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = ALU_LSHB;   strcpy(buf, "LSHB");  ;}
    break;

  case 139:

/* Line 1455 of yacc.c  */
#line 1018 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = ALU_LSHW;   strcpy(buf, "LSHW");  ;}
    break;

  case 140:

/* Line 1455 of yacc.c  */
#line 1019 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = ALU_LSHL;   strcpy(buf, "LSHL");  ;}
    break;

  case 141:

/* Line 1455 of yacc.c  */
#line 1020 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = ALU_RSHB;   strcpy(buf, "RSHB");  ;}
    break;

  case 142:

/* Line 1455 of yacc.c  */
#line 1021 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = ALU_RSHW;   strcpy(buf, "RSHW");  ;}
    break;

  case 143:

/* Line 1455 of yacc.c  */
#line 1022 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = ALU_RSHL;   strcpy(buf, "RSHL");  ;}
    break;

  case 144:

/* Line 1455 of yacc.c  */
#line 1023 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = ALU_MUL;    strcpy(buf, "MUL");   ;}
    break;

  case 145:

/* Line 1455 of yacc.c  */
#line 1024 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = ALU_DIV;    strcpy(buf, "DIV");   ;}
    break;

  case 146:

/* Line 1455 of yacc.c  */
#line 1025 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = ALU_NOP;    strcpy(buf, "NOP");   ;}
    break;

  case 147:

/* Line 1455 of yacc.c  */
#line 1029 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    {
        rom_data[rom_addr] = (yyvsp[(1) - (3)].val) | ALU_CCUPD | OPC_RTS;
        strcat(buf, ".; RTS");
        strncpy(&rom_instr[rom_addr * 32], buf, 31);
        rom_addr++;
      ;}
    break;

  case 148:

/* Line 1455 of yacc.c  */
#line 1036 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    {
        rom_data[rom_addr] = (yyvsp[(1) - (2)].val) | OPC_RTS;
        strcat(buf, "; RTS");
        strncpy(&rom_instr[rom_addr * 32], buf, 31);
        rom_addr++;
      ;}
    break;

  case 149:

/* Line 1455 of yacc.c  */
#line 1043 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    {
        rom_data[rom_addr] = (yyvsp[(1) - (2)].val) | ALU_CCUPD;
        strcat(buf, ".");
        strncpy(&rom_instr[rom_addr * 32], buf, 31);
        rom_addr++;
      ;}
    break;

  case 150:

/* Line 1455 of yacc.c  */
#line 1050 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    {
        rom_data[rom_addr] = (yyvsp[(1) - (1)].val);
        strncpy(&rom_instr[rom_addr * 32], buf, 31);
        rom_addr++;
      ;}
    break;

  case 151:

/* Line 1455 of yacc.c  */
#line 1057 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = MEM_EA1_B_LD;                strcpy(buf, "LDB (EA1)"); ;}
    break;

  case 152:

/* Line 1455 of yacc.c  */
#line 1058 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = MEM_EA1_B_LD | MEM_POST_INC; strcpy(buf, "LDB (EA1)+"); ;}
    break;

  case 153:

/* Line 1455 of yacc.c  */
#line 1059 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = MEM_EA1_B_LD | MEM_PRE_DEC;  strcpy(buf, "LDB -(EA1)"); ;}
    break;

  case 154:

/* Line 1455 of yacc.c  */
#line 1060 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = MEM_EA1_B_LD | MEM_PRE_INC;  strcpy(buf, "LDB +(EA1)"); ;}
    break;

  case 155:

/* Line 1455 of yacc.c  */
#line 1061 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = MEM_EA1_W_LD;                strcpy(buf, "LDW (EA1)"); ;}
    break;

  case 156:

/* Line 1455 of yacc.c  */
#line 1062 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = MEM_EA1_W_LD | MEM_POST_INC; strcpy(buf, "LDW (EA1)+"); ;}
    break;

  case 157:

/* Line 1455 of yacc.c  */
#line 1063 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = MEM_EA1_W_LD | MEM_PRE_DEC;  strcpy(buf, "LDW -(EA1)"); ;}
    break;

  case 158:

/* Line 1455 of yacc.c  */
#line 1064 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = MEM_EA1_W_LD | MEM_PRE_INC;  strcpy(buf, "LDW +(EA1)"); ;}
    break;

  case 159:

/* Line 1455 of yacc.c  */
#line 1065 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = MEM_EA1_H_LD;                strcpy(buf, "LDH (EA1)"); ;}
    break;

  case 160:

/* Line 1455 of yacc.c  */
#line 1066 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = MEM_EA1_H_LD | MEM_POST_INC; strcpy(buf, "LDH (EA1)+"); ;}
    break;

  case 161:

/* Line 1455 of yacc.c  */
#line 1067 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = MEM_EA1_H_LD | MEM_PRE_DEC;  strcpy(buf, "LDH -(EA1)"); ;}
    break;

  case 162:

/* Line 1455 of yacc.c  */
#line 1068 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = MEM_EA1_H_LD | MEM_PRE_INC;  strcpy(buf, "LDH +(EA1)"); ;}
    break;

  case 163:

/* Line 1455 of yacc.c  */
#line 1069 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = MEM_EA1_L_LD;                strcpy(buf, "LDL (EA1)"); ;}
    break;

  case 164:

/* Line 1455 of yacc.c  */
#line 1070 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = MEM_EA1_L_LD | MEM_POST_INC; strcpy(buf, "LDL (EA1)+"); ;}
    break;

  case 165:

/* Line 1455 of yacc.c  */
#line 1071 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = MEM_EA1_L_LD | MEM_PRE_DEC;  strcpy(buf, "LDL -(EA1)"); ;}
    break;

  case 166:

/* Line 1455 of yacc.c  */
#line 1072 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = MEM_EA1_L_LD | MEM_PRE_INC;  strcpy(buf, "LDL +(EA1)"); ;}
    break;

  case 167:

/* Line 1455 of yacc.c  */
#line 1073 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = MEM_EA2_B_LD;                strcpy(buf, "LDB (EA2)"); ;}
    break;

  case 168:

/* Line 1455 of yacc.c  */
#line 1074 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = MEM_EA2_B_LD | MEM_POST_INC; strcpy(buf, "LDB (EA2)+"); ;}
    break;

  case 169:

/* Line 1455 of yacc.c  */
#line 1075 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = MEM_EA2_B_LD | MEM_PRE_DEC;  strcpy(buf, "LDB -(EA2)"); ;}
    break;

  case 170:

/* Line 1455 of yacc.c  */
#line 1076 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = MEM_EA2_B_LD | MEM_PRE_INC;  strcpy(buf, "LDB +(EA2)"); ;}
    break;

  case 171:

/* Line 1455 of yacc.c  */
#line 1077 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = MEM_EA2_W_LD;                strcpy(buf, "LDW (EA2)"); ;}
    break;

  case 172:

/* Line 1455 of yacc.c  */
#line 1078 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = MEM_EA2_W_LD | MEM_POST_INC; strcpy(buf, "LDW (EA2)+"); ;}
    break;

  case 173:

/* Line 1455 of yacc.c  */
#line 1079 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = MEM_EA2_W_LD | MEM_PRE_DEC;  strcpy(buf, "LDW -(EA2)"); ;}
    break;

  case 174:

/* Line 1455 of yacc.c  */
#line 1080 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = MEM_EA2_W_LD | MEM_PRE_INC;  strcpy(buf, "LDW +(EA2)"); ;}
    break;

  case 175:

/* Line 1455 of yacc.c  */
#line 1081 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = MEM_EA1_B_ST;                strcpy(buf, "STB (EA1)"); ;}
    break;

  case 176:

/* Line 1455 of yacc.c  */
#line 1082 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = MEM_EA1_B_ST | MEM_POST_INC; strcpy(buf, "STB (EA1)+"); ;}
    break;

  case 177:

/* Line 1455 of yacc.c  */
#line 1083 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = MEM_EA1_B_ST | MEM_PRE_DEC;  strcpy(buf, "STB -(EA1)"); ;}
    break;

  case 178:

/* Line 1455 of yacc.c  */
#line 1084 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = MEM_EA1_B_ST | MEM_PRE_INC;  strcpy(buf, "STB +(EA1)"); ;}
    break;

  case 179:

/* Line 1455 of yacc.c  */
#line 1085 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = MEM_EA1_W_ST;                strcpy(buf, "STW (EA1)"); ;}
    break;

  case 180:

/* Line 1455 of yacc.c  */
#line 1086 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = MEM_EA1_W_ST | MEM_POST_INC; strcpy(buf, "STW (EA1)+"); ;}
    break;

  case 181:

/* Line 1455 of yacc.c  */
#line 1087 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = MEM_EA1_W_ST | MEM_PRE_DEC;  strcpy(buf, "STW -(EA1)"); ;}
    break;

  case 182:

/* Line 1455 of yacc.c  */
#line 1088 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = MEM_EA1_W_ST | MEM_PRE_INC;  strcpy(buf, "STW +(EA1)"); ;}
    break;

  case 183:

/* Line 1455 of yacc.c  */
#line 1089 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = MEM_EA1_H_ST;                strcpy(buf, "STH (EA1)"); ;}
    break;

  case 184:

/* Line 1455 of yacc.c  */
#line 1090 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = MEM_EA1_H_ST | MEM_POST_INC; strcpy(buf, "STH (EA1)+"); ;}
    break;

  case 185:

/* Line 1455 of yacc.c  */
#line 1091 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = MEM_EA1_H_ST | MEM_PRE_DEC;  strcpy(buf, "STH -(EA1)"); ;}
    break;

  case 186:

/* Line 1455 of yacc.c  */
#line 1092 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = MEM_EA1_H_ST | MEM_PRE_INC;  strcpy(buf, "STH +(EA1)"); ;}
    break;

  case 187:

/* Line 1455 of yacc.c  */
#line 1093 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = MEM_EA1_L_ST;                strcpy(buf, "STL (EA1)"); ;}
    break;

  case 188:

/* Line 1455 of yacc.c  */
#line 1094 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = MEM_EA1_L_ST | MEM_POST_INC; strcpy(buf, "STL (EA1)+"); ;}
    break;

  case 189:

/* Line 1455 of yacc.c  */
#line 1095 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = MEM_EA1_L_ST | MEM_PRE_DEC;  strcpy(buf, "STL -(EA1)"); ;}
    break;

  case 190:

/* Line 1455 of yacc.c  */
#line 1096 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = MEM_EA1_L_ST | MEM_PRE_INC;  strcpy(buf, "STL +(EA1)"); ;}
    break;

  case 191:

/* Line 1455 of yacc.c  */
#line 1097 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = MEM_EA2_B_ST;                strcpy(buf, "STB (EA2)"); ;}
    break;

  case 192:

/* Line 1455 of yacc.c  */
#line 1098 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = MEM_EA2_B_ST | MEM_POST_INC; strcpy(buf, "STB (EA2)+"); ;}
    break;

  case 193:

/* Line 1455 of yacc.c  */
#line 1099 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = MEM_EA2_B_ST | MEM_PRE_DEC;  strcpy(buf, "STB -(EA2)"); ;}
    break;

  case 194:

/* Line 1455 of yacc.c  */
#line 1100 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = MEM_EA2_B_ST | MEM_PRE_INC;  strcpy(buf, "STB +(EA2)"); ;}
    break;

  case 195:

/* Line 1455 of yacc.c  */
#line 1101 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = MEM_EA2_W_ST;                strcpy(buf, "STW (EA2)"); ;}
    break;

  case 196:

/* Line 1455 of yacc.c  */
#line 1102 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = MEM_EA2_W_ST | MEM_POST_INC; strcpy(buf, "STW (EA2)+"); ;}
    break;

  case 197:

/* Line 1455 of yacc.c  */
#line 1103 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = MEM_EA2_W_ST | MEM_PRE_DEC;  strcpy(buf, "STW -(EA2)"); ;}
    break;

  case 198:

/* Line 1455 of yacc.c  */
#line 1104 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = MEM_EA2_W_ST | MEM_PRE_INC;  strcpy(buf, "STW +(EA2)"); ;}
    break;

  case 199:

/* Line 1455 of yacc.c  */
#line 1105 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = MEM_VEC_LD | MEM_POST_INC;   strcpy(buf, "LDW (VEC)+"); ;}
    break;

  case 200:

/* Line 1455 of yacc.c  */
#line 1106 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = MEM_INS_LD;                  strcpy(buf, "LDI (PC)+"); ;}
    break;

  case 201:

/* Line 1455 of yacc.c  */
#line 1107 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = MEM_EXT_LD;                  strcpy(buf, "LDE (PC)+"); ;}
    break;

  case 202:

/* Line 1455 of yacc.c  */
#line 1108 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = MEM_IMM_LD;                  strcpy(buf, "LDW (PC)+"); ;}
    break;

  case 203:

/* Line 1455 of yacc.c  */
#line 1109 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = MEM_INS_FT;                  strcpy(buf, "FTI (PC)+"); ;}
    break;

  case 204:

/* Line 1455 of yacc.c  */
#line 1110 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = MEM_EXT_FT;                  strcpy(buf, "FTE (PC)+"); ;}
    break;

  case 205:

/* Line 1455 of yacc.c  */
#line 1111 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = MEM_IMM_FT;                  strcpy(buf, "FTW (PC)+"); ;}
    break;

  case 206:

/* Line 1455 of yacc.c  */
#line 1115 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    {
        rom_data[rom_addr] = (yyvsp[(1) - (3)].val) | ALU_CCUPD | OPC_RTS;
        strcat(buf, ".; RTS");
        strncpy(&rom_instr[rom_addr * 32], buf, 31);
        rom_addr++;
      ;}
    break;

  case 207:

/* Line 1455 of yacc.c  */
#line 1122 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    {
        rom_data[rom_addr] = (yyvsp[(1) - (2)].val) | OPC_RTS;
        strcat(buf, "; RTS");
        strncpy(&rom_instr[rom_addr * 32], buf, 31);
        rom_addr++;
      ;}
    break;

  case 208:

/* Line 1455 of yacc.c  */
#line 1129 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    {
        rom_data[rom_addr] = (yyvsp[(1) - (2)].val) | ALU_CCUPD;
        strcat(buf, ".");
        strncpy(&rom_instr[rom_addr * 32], buf, 31);
        rom_addr++;
      ;}
    break;

  case 209:

/* Line 1455 of yacc.c  */
#line 1136 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    {
        rom_data[rom_addr] = (yyvsp[(1) - (1)].val);
        strncpy(&rom_instr[rom_addr * 32], buf, 31);
        rom_addr++;
      ;}
    break;

  case 210:

/* Line 1455 of yacc.c  */
#line 1143 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_LD | CREG_DL | RIDX_EA1; strcpy(buf, "LDB DL[EA1]"); ;}
    break;

  case 211:

/* Line 1455 of yacc.c  */
#line 1144 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_LD | CREG_AL | RIDX_EA1; strcpy(buf, "LDB AL[EA1]"); ;}
    break;

  case 212:

/* Line 1455 of yacc.c  */
#line 1145 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_LD | CREG_RL | RIDX_EA1; strcpy(buf, "LDB RL[EA1]"); ;}
    break;

  case 213:

/* Line 1455 of yacc.c  */
#line 1146 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_LD | CREG_DL | RIDX_EA2; strcpy(buf, "LDB DL[EA2]"); ;}
    break;

  case 214:

/* Line 1455 of yacc.c  */
#line 1147 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_LD | CREG_AL | RIDX_EA2; strcpy(buf, "LDB AL[EA2]"); ;}
    break;

  case 215:

/* Line 1455 of yacc.c  */
#line 1148 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_LD | CREG_RL | RIDX_EA2; strcpy(buf, "LDB RL[EA2]"); ;}
    break;

  case 216:

/* Line 1455 of yacc.c  */
#line 1149 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_LD | CREG_RL | RIDX_CNT; strcpy(buf, "LDB RL[CNT]"); ;}
    break;

  case 217:

/* Line 1455 of yacc.c  */
#line 1150 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_LD | CREG_DL | RIDX_EXT; strcpy(buf, "LDB DL[EXT]"); ;}
    break;

  case 218:

/* Line 1455 of yacc.c  */
#line 1151 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_LD | CREG_AL | RIDX_EXT; strcpy(buf, "LDB AL[EXT]"); ;}
    break;

  case 219:

/* Line 1455 of yacc.c  */
#line 1152 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_LD | CREG_RL | RIDX_EXT; strcpy(buf, "LDB RL[EXT]"); ;}
    break;

  case 220:

/* Line 1455 of yacc.c  */
#line 1153 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_LD | CREG_VBRL;          strcpy(buf, "LDB VBRL");    ;}
    break;

  case 221:

/* Line 1455 of yacc.c  */
#line 1154 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_LD | CREG_TMP1L;         strcpy(buf, "LDB TMPL1");   ;}
    break;

  case 222:

/* Line 1455 of yacc.c  */
#line 1155 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_LD | CREG_TMP2L;         strcpy(buf, "LDB TMPL2");   ;}
    break;

  case 223:

/* Line 1455 of yacc.c  */
#line 1156 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_LD | CREG_USPL;          strcpy(buf, "LDB USPL");    ;}
    break;

  case 224:

/* Line 1455 of yacc.c  */
#line 1157 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_LD | CREG_SSPL;          strcpy(buf, "LDB SSPL");    ;}
    break;

  case 225:

/* Line 1455 of yacc.c  */
#line 1158 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_LD | CREG_DH | RIDX_EA1; strcpy(buf, "LDB DH[EA1]"); ;}
    break;

  case 226:

/* Line 1455 of yacc.c  */
#line 1159 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_LD | CREG_AH | RIDX_EA1; strcpy(buf, "LDB AH[EA1]"); ;}
    break;

  case 227:

/* Line 1455 of yacc.c  */
#line 1160 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_LD | CREG_RH | RIDX_EA1; strcpy(buf, "LDB RH[EA1]"); ;}
    break;

  case 228:

/* Line 1455 of yacc.c  */
#line 1161 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_LD | CREG_DH | RIDX_EA2; strcpy(buf, "LDB DH[EA2]"); ;}
    break;

  case 229:

/* Line 1455 of yacc.c  */
#line 1162 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_LD | CREG_AH | RIDX_EA2; strcpy(buf, "LDB AH[EA2]"); ;}
    break;

  case 230:

/* Line 1455 of yacc.c  */
#line 1163 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_LD | CREG_RH | RIDX_EA2; strcpy(buf, "LDB RH[EA2]"); ;}
    break;

  case 231:

/* Line 1455 of yacc.c  */
#line 1164 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_LD | CREG_RH | RIDX_CNT; strcpy(buf, "LDB RH[CNT]"); ;}
    break;

  case 232:

/* Line 1455 of yacc.c  */
#line 1165 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_LD | CREG_DH | RIDX_EXT; strcpy(buf, "LDB DH[EXT]"); ;}
    break;

  case 233:

/* Line 1455 of yacc.c  */
#line 1166 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_LD | CREG_AH | RIDX_EXT; strcpy(buf, "LDB AH[EXT]"); ;}
    break;

  case 234:

/* Line 1455 of yacc.c  */
#line 1167 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_LD | CREG_RH | RIDX_EXT; strcpy(buf, "LDB RH[EXT]"); ;}
    break;

  case 235:

/* Line 1455 of yacc.c  */
#line 1168 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_LD | CREG_VBRH;          strcpy(buf, "LDB VBRH");    ;}
    break;

  case 236:

/* Line 1455 of yacc.c  */
#line 1169 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_LD | CREG_TMP1H;         strcpy(buf, "LDB TMP1H");   ;}
    break;

  case 237:

/* Line 1455 of yacc.c  */
#line 1170 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_LD | CREG_TMP2H;         strcpy(buf, "LDB TMP2H");   ;}
    break;

  case 238:

/* Line 1455 of yacc.c  */
#line 1171 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_LD | CREG_USPH;          strcpy(buf, "LDB USPH");    ;}
    break;

  case 239:

/* Line 1455 of yacc.c  */
#line 1172 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_LD | CREG_SSPH;          strcpy(buf, "LDB SSPH");    ;}
    break;

  case 240:

/* Line 1455 of yacc.c  */
#line 1173 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_LD | CREG_DL | RIDX_EA1; strcpy(buf, "LDW DL[EA1]"); ;}
    break;

  case 241:

/* Line 1455 of yacc.c  */
#line 1174 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_LD | CREG_AL | RIDX_EA1; strcpy(buf, "LDW AL[EA1]"); ;}
    break;

  case 242:

/* Line 1455 of yacc.c  */
#line 1175 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_LD | CREG_RL | RIDX_EA1; strcpy(buf, "LDW RL[EA1]"); ;}
    break;

  case 243:

/* Line 1455 of yacc.c  */
#line 1176 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_LD | CREG_A7L;           strcpy(buf, "LDW A7L");     ;}
    break;

  case 244:

/* Line 1455 of yacc.c  */
#line 1177 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_LD | CREG_DL | RIDX_EA2; strcpy(buf, "LDW DL[EA2]"); ;}
    break;

  case 245:

/* Line 1455 of yacc.c  */
#line 1178 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_LD | CREG_AL | RIDX_EA2; strcpy(buf, "LDW AL[EA2]"); ;}
    break;

  case 246:

/* Line 1455 of yacc.c  */
#line 1179 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_LD | CREG_RL | RIDX_EA2; strcpy(buf, "LDW RL[EA2]"); ;}
    break;

  case 247:

/* Line 1455 of yacc.c  */
#line 1180 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_LD | CREG_RL | RIDX_CNT; strcpy(buf, "LDW RL[CNT]"); ;}
    break;

  case 248:

/* Line 1455 of yacc.c  */
#line 1181 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_LD | CREG_DL | RIDX_EXT; strcpy(buf, "LDW DL[EXT]"); ;}
    break;

  case 249:

/* Line 1455 of yacc.c  */
#line 1182 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_LD | CREG_AL | RIDX_EXT; strcpy(buf, "LDW AL[EXT]"); ;}
    break;

  case 250:

/* Line 1455 of yacc.c  */
#line 1183 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_LD | CREG_RL | RIDX_EXT; strcpy(buf, "LDW RL[EXT]"); ;}
    break;

  case 251:

/* Line 1455 of yacc.c  */
#line 1184 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_LD | CREG_VBRL;          strcpy(buf, "LDW VBRL");    ;}
    break;

  case 252:

/* Line 1455 of yacc.c  */
#line 1185 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_LD | CREG_TMP1L;         strcpy(buf, "LDW TMP1L");   ;}
    break;

  case 253:

/* Line 1455 of yacc.c  */
#line 1186 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_LD | CREG_TMP2L;         strcpy(buf, "LDW TMP2L");   ;}
    break;

  case 254:

/* Line 1455 of yacc.c  */
#line 1187 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_LD | CREG_USPL;          strcpy(buf, "LDW USPL");    ;}
    break;

  case 255:

/* Line 1455 of yacc.c  */
#line 1188 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_LD | CREG_SSPL;          strcpy(buf, "LDW SSPL");    ;}
    break;

  case 256:

/* Line 1455 of yacc.c  */
#line 1189 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_LD | CREG_DH | RIDX_EA1; strcpy(buf, "LDW DH[EA1]"); ;}
    break;

  case 257:

/* Line 1455 of yacc.c  */
#line 1190 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_LD | CREG_AH | RIDX_EA1; strcpy(buf, "LDW AH[EA1]"); ;}
    break;

  case 258:

/* Line 1455 of yacc.c  */
#line 1191 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_LD | CREG_RH | RIDX_EA1; strcpy(buf, "LDW RH[EA1]"); ;}
    break;

  case 259:

/* Line 1455 of yacc.c  */
#line 1192 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_LD | CREG_A7H;           strcpy(buf, "LDW A7H"); ;}
    break;

  case 260:

/* Line 1455 of yacc.c  */
#line 1193 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_LD | CREG_DH | RIDX_EA2; strcpy(buf, "LDW DH[EA2]"); ;}
    break;

  case 261:

/* Line 1455 of yacc.c  */
#line 1194 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_LD | CREG_AH | RIDX_EA2; strcpy(buf, "LDW AH[EA2]"); ;}
    break;

  case 262:

/* Line 1455 of yacc.c  */
#line 1195 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_LD | CREG_RH | RIDX_EA2; strcpy(buf, "LDW RH[EA2]"); ;}
    break;

  case 263:

/* Line 1455 of yacc.c  */
#line 1196 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_LD | CREG_RH | RIDX_CNT; strcpy(buf, "LDW RH[CNT]"); ;}
    break;

  case 264:

/* Line 1455 of yacc.c  */
#line 1197 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_LD | CREG_DH | RIDX_EXT; strcpy(buf, "LDW DH[EXT]"); ;}
    break;

  case 265:

/* Line 1455 of yacc.c  */
#line 1198 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_LD | CREG_AH | RIDX_EXT; strcpy(buf, "LDW AH[EXT]"); ;}
    break;

  case 266:

/* Line 1455 of yacc.c  */
#line 1199 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_LD | CREG_RH | RIDX_EXT; strcpy(buf, "LDW RH[EXT]"); ;}
    break;

  case 267:

/* Line 1455 of yacc.c  */
#line 1200 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_LD | CREG_VBRH;          strcpy(buf, "LDW VBRH");    ;}
    break;

  case 268:

/* Line 1455 of yacc.c  */
#line 1201 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_LD | CREG_TMP1H;         strcpy(buf, "LDW TMP1H");   ;}
    break;

  case 269:

/* Line 1455 of yacc.c  */
#line 1202 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_LD | CREG_TMP2H;         strcpy(buf, "LDW TMP2H");   ;}
    break;

  case 270:

/* Line 1455 of yacc.c  */
#line 1203 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_LD | CREG_USPH;          strcpy(buf, "LDW USPH");    ;}
    break;

  case 271:

/* Line 1455 of yacc.c  */
#line 1204 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_LD | CREG_SSPH;          strcpy(buf, "LDW SSPH");    ;}
    break;

  case 272:

/* Line 1455 of yacc.c  */
#line 1205 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_ST | CREG_DL | RIDX_EA1; strcpy(buf, "STB DL[EA1]"); ;}
    break;

  case 273:

/* Line 1455 of yacc.c  */
#line 1206 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_ST | CREG_AL | RIDX_EA1; strcpy(buf, "STB AL[EA1]"); ;}
    break;

  case 274:

/* Line 1455 of yacc.c  */
#line 1207 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_ST | CREG_RL | RIDX_EA1; strcpy(buf, "STB RL[EA1]"); ;}
    break;

  case 275:

/* Line 1455 of yacc.c  */
#line 1208 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_ST | CREG_DL | RIDX_EA2; strcpy(buf, "STB DL[EA2]"); ;}
    break;

  case 276:

/* Line 1455 of yacc.c  */
#line 1209 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_ST | CREG_AL | RIDX_EA2; strcpy(buf, "STB AL[EA2]"); ;}
    break;

  case 277:

/* Line 1455 of yacc.c  */
#line 1210 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_ST | CREG_RL | RIDX_EA2; strcpy(buf, "STB RL[EA2]"); ;}
    break;

  case 278:

/* Line 1455 of yacc.c  */
#line 1211 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_ST | CREG_RL | RIDX_CNT; strcpy(buf, "STB RL[CNT]"); ;}
    break;

  case 279:

/* Line 1455 of yacc.c  */
#line 1212 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_ST | CREG_DL | RIDX_EXT; strcpy(buf, "STB DL[EXT]"); ;}
    break;

  case 280:

/* Line 1455 of yacc.c  */
#line 1213 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_ST | CREG_AL | RIDX_EXT; strcpy(buf, "STB AL[EXT]"); ;}
    break;

  case 281:

/* Line 1455 of yacc.c  */
#line 1214 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_ST | CREG_RL | RIDX_EXT; strcpy(buf, "STB RL[EXT]"); ;}
    break;

  case 282:

/* Line 1455 of yacc.c  */
#line 1215 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_ST | CREG_VBRL;          strcpy(buf, "STB VBRL");    ;}
    break;

  case 283:

/* Line 1455 of yacc.c  */
#line 1216 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_ST | CREG_TMP1L;         strcpy(buf, "STB TMP1L");   ;}
    break;

  case 284:

/* Line 1455 of yacc.c  */
#line 1217 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_ST | CREG_TMP2L;         strcpy(buf, "STB TMP2L");   ;}
    break;

  case 285:

/* Line 1455 of yacc.c  */
#line 1218 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_ST | CREG_USPL;          strcpy(buf, "STB USPL");    ;}
    break;

  case 286:

/* Line 1455 of yacc.c  */
#line 1219 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_ST | CREG_SSPL;          strcpy(buf, "STB SSPL");    ;}
    break;

  case 287:

/* Line 1455 of yacc.c  */
#line 1220 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_ST | CREG_DH | RIDX_EA1; strcpy(buf, "STB DH[EA1]"); ;}
    break;

  case 288:

/* Line 1455 of yacc.c  */
#line 1221 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_ST | CREG_AH | RIDX_EA1; strcpy(buf, "STB AH[EA1]"); ;}
    break;

  case 289:

/* Line 1455 of yacc.c  */
#line 1222 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_ST | CREG_RH | RIDX_EA1; strcpy(buf, "STB RH[EA1]"); ;}
    break;

  case 290:

/* Line 1455 of yacc.c  */
#line 1223 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_ST | CREG_DH | RIDX_EA2; strcpy(buf, "STB DH[EA2]"); ;}
    break;

  case 291:

/* Line 1455 of yacc.c  */
#line 1224 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_ST | CREG_AH | RIDX_EA2; strcpy(buf, "STB AH[EA2]"); ;}
    break;

  case 292:

/* Line 1455 of yacc.c  */
#line 1225 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_ST | CREG_RH | RIDX_EA2; strcpy(buf, "STB RH[EA2]"); ;}
    break;

  case 293:

/* Line 1455 of yacc.c  */
#line 1226 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_ST | CREG_RH | RIDX_CNT; strcpy(buf, "STB RH[CNT]"); ;}
    break;

  case 294:

/* Line 1455 of yacc.c  */
#line 1227 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_ST | CREG_DH | RIDX_EXT; strcpy(buf, "STB DH[EXT]"); ;}
    break;

  case 295:

/* Line 1455 of yacc.c  */
#line 1228 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_ST | CREG_AH | RIDX_EXT; strcpy(buf, "STB AH[EXT]"); ;}
    break;

  case 296:

/* Line 1455 of yacc.c  */
#line 1229 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_ST | CREG_RH | RIDX_EXT; strcpy(buf, "STB RH[EXT]"); ;}
    break;

  case 297:

/* Line 1455 of yacc.c  */
#line 1230 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_ST | CREG_VBRH;          strcpy(buf, "STB VBRH");    ;}
    break;

  case 298:

/* Line 1455 of yacc.c  */
#line 1231 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_ST | CREG_TMP1H;         strcpy(buf, "STB TMP1H");   ;}
    break;

  case 299:

/* Line 1455 of yacc.c  */
#line 1232 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_ST | CREG_TMP2H;         strcpy(buf, "STB TMP2H");   ;}
    break;

  case 300:

/* Line 1455 of yacc.c  */
#line 1233 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_ST | CREG_USPH;          strcpy(buf, "STB USPH");    ;}
    break;

  case 301:

/* Line 1455 of yacc.c  */
#line 1234 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_ST | CREG_SSPH;          strcpy(buf, "STB SSPH");    ;}
    break;

  case 302:

/* Line 1455 of yacc.c  */
#line 1235 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_ST | CREG_DL | RIDX_EA1; strcpy(buf, "STW DL[EA1]"); ;}
    break;

  case 303:

/* Line 1455 of yacc.c  */
#line 1236 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_ST | CREG_AL | RIDX_EA1; strcpy(buf, "STW AL[EA1]"); ;}
    break;

  case 304:

/* Line 1455 of yacc.c  */
#line 1237 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_ST | CREG_RL | RIDX_EA1; strcpy(buf, "STW RL[EA1]"); ;}
    break;

  case 305:

/* Line 1455 of yacc.c  */
#line 1238 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_ST | CREG_A7L;           strcpy(buf, "STW A7L");     ;}
    break;

  case 306:

/* Line 1455 of yacc.c  */
#line 1239 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_ST | CREG_DL | RIDX_EA2; strcpy(buf, "STW DL[EA2]"); ;}
    break;

  case 307:

/* Line 1455 of yacc.c  */
#line 1240 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_ST | CREG_AL | RIDX_EA2; strcpy(buf, "STW AL[EA2]"); ;}
    break;

  case 308:

/* Line 1455 of yacc.c  */
#line 1241 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_ST | CREG_RL | RIDX_EA2; strcpy(buf, "STW RL[EA2]"); ;}
    break;

  case 309:

/* Line 1455 of yacc.c  */
#line 1242 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_ST | CREG_RL | RIDX_CNT; strcpy(buf, "STW RL[CNT]"); ;}
    break;

  case 310:

/* Line 1455 of yacc.c  */
#line 1243 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_ST | CREG_DL | RIDX_EXT; strcpy(buf, "STW DL[EXT]"); ;}
    break;

  case 311:

/* Line 1455 of yacc.c  */
#line 1244 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_ST | CREG_AL | RIDX_EXT; strcpy(buf, "STW AL[EXT]"); ;}
    break;

  case 312:

/* Line 1455 of yacc.c  */
#line 1245 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_ST | CREG_RL | RIDX_EXT; strcpy(buf, "STW RL[EXT]"); ;}
    break;

  case 313:

/* Line 1455 of yacc.c  */
#line 1246 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_ST | CREG_VBRL;          strcpy(buf, "STW VBRL");    ;}
    break;

  case 314:

/* Line 1455 of yacc.c  */
#line 1247 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_ST | CREG_TMP1L;         strcpy(buf, "STW TMP1L");   ;}
    break;

  case 315:

/* Line 1455 of yacc.c  */
#line 1248 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_ST | CREG_TMP2L;         strcpy(buf, "STW TMP2L");   ;}
    break;

  case 316:

/* Line 1455 of yacc.c  */
#line 1249 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_ST | CREG_USPL;          strcpy(buf, "STW USPL");    ;}
    break;

  case 317:

/* Line 1455 of yacc.c  */
#line 1250 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_ST | CREG_SSPL;          strcpy(buf, "STW SSPL");    ;}
    break;

  case 318:

/* Line 1455 of yacc.c  */
#line 1251 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_ST | CREG_DH | RIDX_EA1; strcpy(buf, "STW DH[EA1]"); ;}
    break;

  case 319:

/* Line 1455 of yacc.c  */
#line 1252 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_ST | CREG_AH | RIDX_EA1; strcpy(buf, "STW AH[EA1]"); ;}
    break;

  case 320:

/* Line 1455 of yacc.c  */
#line 1253 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_ST | CREG_RH | RIDX_EA1; strcpy(buf, "STW RH[EA1]"); ;}
    break;

  case 321:

/* Line 1455 of yacc.c  */
#line 1254 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_ST | CREG_A7H;           strcpy(buf, "STW A7H");     ;}
    break;

  case 322:

/* Line 1455 of yacc.c  */
#line 1255 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_ST | CREG_DH | RIDX_EA2; strcpy(buf, "STW DH[EA2]"); ;}
    break;

  case 323:

/* Line 1455 of yacc.c  */
#line 1256 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_ST | CREG_AH | RIDX_EA2; strcpy(buf, "STW AH[EA2]"); ;}
    break;

  case 324:

/* Line 1455 of yacc.c  */
#line 1257 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_ST | CREG_RH | RIDX_EA2; strcpy(buf, "STW RH[EA2]"); ;}
    break;

  case 325:

/* Line 1455 of yacc.c  */
#line 1258 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_ST | CREG_RH | RIDX_CNT; strcpy(buf, "STW RH[CNT]"); ;}
    break;

  case 326:

/* Line 1455 of yacc.c  */
#line 1259 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_ST | CREG_DH | RIDX_EXT; strcpy(buf, "STW DH[EXT]"); ;}
    break;

  case 327:

/* Line 1455 of yacc.c  */
#line 1260 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_ST | CREG_AH | RIDX_EXT; strcpy(buf, "STW AH[EXT]"); ;}
    break;

  case 328:

/* Line 1455 of yacc.c  */
#line 1261 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_ST | CREG_RH | RIDX_EXT; strcpy(buf, "STW RH[EXT]"); ;}
    break;

  case 329:

/* Line 1455 of yacc.c  */
#line 1262 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_ST | CREG_VBRH;          strcpy(buf, "STW VBRH"); ;}
    break;

  case 330:

/* Line 1455 of yacc.c  */
#line 1263 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_ST | CREG_TMP1H;         strcpy(buf, "STW TMP1H"); ;}
    break;

  case 331:

/* Line 1455 of yacc.c  */
#line 1264 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_ST | CREG_TMP2H;         strcpy(buf, "STW TMP2H"); ;}
    break;

  case 332:

/* Line 1455 of yacc.c  */
#line 1265 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_ST | CREG_USPH;          strcpy(buf, "STW USPH"); ;}
    break;

  case 333:

/* Line 1455 of yacc.c  */
#line 1266 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_ST | CREG_SSPH;          strcpy(buf, "STW SSPH"); ;}
    break;

  case 334:

/* Line 1455 of yacc.c  */
#line 1267 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_WR | CREG_DL | RIDX_EA1; strcpy(buf, "WRB DL[EA1]"); ;}
    break;

  case 335:

/* Line 1455 of yacc.c  */
#line 1268 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_WR | CREG_AL | RIDX_EA1; strcpy(buf, "WRB AL[EA1]"); ;}
    break;

  case 336:

/* Line 1455 of yacc.c  */
#line 1269 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_WR | CREG_RL | RIDX_EA1; strcpy(buf, "WRB RL[EA1]"); ;}
    break;

  case 337:

/* Line 1455 of yacc.c  */
#line 1270 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_WR | CREG_DL | RIDX_EA2; strcpy(buf, "WRB DL[EA2]"); ;}
    break;

  case 338:

/* Line 1455 of yacc.c  */
#line 1271 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_WR | CREG_AL | RIDX_EA2; strcpy(buf, "WRB AL[EA2]"); ;}
    break;

  case 339:

/* Line 1455 of yacc.c  */
#line 1272 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_WR | CREG_RL | RIDX_EA2; strcpy(buf, "WRB RL[EA2]"); ;}
    break;

  case 340:

/* Line 1455 of yacc.c  */
#line 1273 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_WR | CREG_RL | RIDX_CNT; strcpy(buf, "WRB RL[CNT]"); ;}
    break;

  case 341:

/* Line 1455 of yacc.c  */
#line 1274 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_WR | CREG_DL | RIDX_EXT; strcpy(buf, "WRB DL[EXT]"); ;}
    break;

  case 342:

/* Line 1455 of yacc.c  */
#line 1275 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_WR | CREG_AL | RIDX_EXT; strcpy(buf, "WRB AL[EXT]"); ;}
    break;

  case 343:

/* Line 1455 of yacc.c  */
#line 1276 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_WR | CREG_RL | RIDX_EXT; strcpy(buf, "WRB RL[EXT]"); ;}
    break;

  case 344:

/* Line 1455 of yacc.c  */
#line 1277 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_WR | CREG_VBRL;          strcpy(buf, "WRB VBRL");    ;}
    break;

  case 345:

/* Line 1455 of yacc.c  */
#line 1278 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_WR | CREG_TMP1L;         strcpy(buf, "WRB TMP1L");   ;}
    break;

  case 346:

/* Line 1455 of yacc.c  */
#line 1279 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_WR | CREG_TMP2L;         strcpy(buf, "WRB TMP2L");   ;}
    break;

  case 347:

/* Line 1455 of yacc.c  */
#line 1280 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_WR | CREG_USPL;          strcpy(buf, "WRB USPL");    ;}
    break;

  case 348:

/* Line 1455 of yacc.c  */
#line 1281 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_WR | CREG_SSPL;          strcpy(buf, "WRB SSPL");    ;}
    break;

  case 349:

/* Line 1455 of yacc.c  */
#line 1282 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_WR | CREG_DH | RIDX_EA1; strcpy(buf, "WRB DH[EA1]"); ;}
    break;

  case 350:

/* Line 1455 of yacc.c  */
#line 1283 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_WR | CREG_AH | RIDX_EA1; strcpy(buf, "WRB AH[EA1]"); ;}
    break;

  case 351:

/* Line 1455 of yacc.c  */
#line 1284 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_WR | CREG_RH | RIDX_EA1; strcpy(buf, "WRB RH[EA1]"); ;}
    break;

  case 352:

/* Line 1455 of yacc.c  */
#line 1285 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_WR | CREG_DH | RIDX_EA2; strcpy(buf, "WRB DH[EA2]"); ;}
    break;

  case 353:

/* Line 1455 of yacc.c  */
#line 1286 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_WR | CREG_AH | RIDX_EA2; strcpy(buf, "WRB AH[EA2]"); ;}
    break;

  case 354:

/* Line 1455 of yacc.c  */
#line 1287 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_WR | CREG_RH | RIDX_EA2; strcpy(buf, "WRB RH[EA2]"); ;}
    break;

  case 355:

/* Line 1455 of yacc.c  */
#line 1288 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_WR | CREG_RH | RIDX_CNT; strcpy(buf, "WRB RH[CNT]"); ;}
    break;

  case 356:

/* Line 1455 of yacc.c  */
#line 1289 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_WR | CREG_DH | RIDX_EXT; strcpy(buf, "WRB DH[EXT]"); ;}
    break;

  case 357:

/* Line 1455 of yacc.c  */
#line 1290 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_WR | CREG_AH | RIDX_EXT; strcpy(buf, "WRB AH[EXT]"); ;}
    break;

  case 358:

/* Line 1455 of yacc.c  */
#line 1291 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_WR | CREG_RH | RIDX_EXT; strcpy(buf, "WRB RH[EXT]"); ;}
    break;

  case 359:

/* Line 1455 of yacc.c  */
#line 1292 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_WR | CREG_VBRH;          strcpy(buf, "WRB VBRH");    ;}
    break;

  case 360:

/* Line 1455 of yacc.c  */
#line 1293 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_WR | CREG_TMP1H;         strcpy(buf, "WRB TMP1H");   ;}
    break;

  case 361:

/* Line 1455 of yacc.c  */
#line 1294 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_WR | CREG_TMP2H;         strcpy(buf, "WRB TMP2H");   ;}
    break;

  case 362:

/* Line 1455 of yacc.c  */
#line 1295 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_WR | CREG_USPH;          strcpy(buf, "WRB USPH");    ;}
    break;

  case 363:

/* Line 1455 of yacc.c  */
#line 1296 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_B_WR | CREG_SSPH;          strcpy(buf, "WRB SSPH");    ;}
    break;

  case 364:

/* Line 1455 of yacc.c  */
#line 1297 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_WR | CREG_DL | RIDX_EA1; strcpy(buf, "WRW DL[EA1]"); ;}
    break;

  case 365:

/* Line 1455 of yacc.c  */
#line 1298 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_WR | CREG_AL | RIDX_EA1; strcpy(buf, "WRW AL[EA1]"); ;}
    break;

  case 366:

/* Line 1455 of yacc.c  */
#line 1299 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_WR | CREG_RL | RIDX_EA1; strcpy(buf, "WRW RL[EA1]"); ;}
    break;

  case 367:

/* Line 1455 of yacc.c  */
#line 1300 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_WR | CREG_A7L;           strcpy(buf, "WRW A7L");     ;}
    break;

  case 368:

/* Line 1455 of yacc.c  */
#line 1301 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_WR | CREG_DL | RIDX_EA2; strcpy(buf, "WRW DL[EA2]"); ;}
    break;

  case 369:

/* Line 1455 of yacc.c  */
#line 1302 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_WR | CREG_AL | RIDX_EA2; strcpy(buf, "WRW AL[EA2]"); ;}
    break;

  case 370:

/* Line 1455 of yacc.c  */
#line 1303 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_WR | CREG_RL | RIDX_EA2; strcpy(buf, "WRW RL[EA2]"); ;}
    break;

  case 371:

/* Line 1455 of yacc.c  */
#line 1304 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_WR | CREG_RL | RIDX_CNT; strcpy(buf, "WRW RL[CNT]"); ;}
    break;

  case 372:

/* Line 1455 of yacc.c  */
#line 1305 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_WR | CREG_DL | RIDX_EXT; strcpy(buf, "WRW DL[EXT]"); ;}
    break;

  case 373:

/* Line 1455 of yacc.c  */
#line 1306 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_WR | CREG_AL | RIDX_EXT; strcpy(buf, "WRW AL[EXT]"); ;}
    break;

  case 374:

/* Line 1455 of yacc.c  */
#line 1307 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_WR | CREG_RL | RIDX_EXT; strcpy(buf, "WRW RL[EXT]"); ;}
    break;

  case 375:

/* Line 1455 of yacc.c  */
#line 1308 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_WR | CREG_VBRL;          strcpy(buf, "WRW VBRL");    ;}
    break;

  case 376:

/* Line 1455 of yacc.c  */
#line 1309 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_WR | CREG_TMP1L;         strcpy(buf, "WRW TMP1L");   ;}
    break;

  case 377:

/* Line 1455 of yacc.c  */
#line 1310 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_WR | CREG_TMP2L;         strcpy(buf, "WRW TMP2L");   ;}
    break;

  case 378:

/* Line 1455 of yacc.c  */
#line 1311 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_WR | CREG_USPL;          strcpy(buf, "WRW USPL");    ;}
    break;

  case 379:

/* Line 1455 of yacc.c  */
#line 1312 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_WR | CREG_SSPL;          strcpy(buf, "WRW SSPL");    ;}
    break;

  case 380:

/* Line 1455 of yacc.c  */
#line 1313 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_WR | CREG_DH | RIDX_EA1; strcpy(buf, "WRW DH[EA1]"); ;}
    break;

  case 381:

/* Line 1455 of yacc.c  */
#line 1314 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_WR | CREG_AH | RIDX_EA1; strcpy(buf, "WRW AH[EA1]"); ;}
    break;

  case 382:

/* Line 1455 of yacc.c  */
#line 1315 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_WR | CREG_RH | RIDX_EA1; strcpy(buf, "WRW RH[EA1]"); ;}
    break;

  case 383:

/* Line 1455 of yacc.c  */
#line 1316 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_WR | CREG_A7H;           strcpy(buf, "WRW A7H");     ;}
    break;

  case 384:

/* Line 1455 of yacc.c  */
#line 1317 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_WR | CREG_DH | RIDX_EA2; strcpy(buf, "WRW DH[EA2]"); ;}
    break;

  case 385:

/* Line 1455 of yacc.c  */
#line 1318 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_WR | CREG_AH | RIDX_EA2; strcpy(buf, "WRW AH[EA2]"); ;}
    break;

  case 386:

/* Line 1455 of yacc.c  */
#line 1319 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_WR | CREG_RH | RIDX_EA2; strcpy(buf, "WRW RH[EA2]"); ;}
    break;

  case 387:

/* Line 1455 of yacc.c  */
#line 1320 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_WR | CREG_RH | RIDX_CNT; strcpy(buf, "WRW RH[CNT]"); ;}
    break;

  case 388:

/* Line 1455 of yacc.c  */
#line 1321 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_WR | CREG_DH | RIDX_EXT; strcpy(buf, "WRW DH[EXT]"); ;}
    break;

  case 389:

/* Line 1455 of yacc.c  */
#line 1322 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_WR | CREG_AH | RIDX_EXT; strcpy(buf, "WRW AH[EXT]"); ;}
    break;

  case 390:

/* Line 1455 of yacc.c  */
#line 1323 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_WR | CREG_RH | RIDX_EXT; strcpy(buf, "WRW RH[EXT]"); ;}
    break;

  case 391:

/* Line 1455 of yacc.c  */
#line 1324 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_WR | CREG_VBRH;          strcpy(buf, "WRW VBRH"); ;}
    break;

  case 392:

/* Line 1455 of yacc.c  */
#line 1325 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_WR | CREG_TMP1H;         strcpy(buf, "WRW TMP1H"); ;}
    break;

  case 393:

/* Line 1455 of yacc.c  */
#line 1326 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_WR | CREG_TMP2H;         strcpy(buf, "WRW TMP2H"); ;}
    break;

  case 394:

/* Line 1455 of yacc.c  */
#line 1327 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_WR | CREG_USPH;          strcpy(buf, "WRW USPH"); ;}
    break;

  case 395:

/* Line 1455 of yacc.c  */
#line 1328 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = CPU_REG_W_WR | CREG_SSPH;          strcpy(buf, "WRW SSPH"); ;}
    break;

  case 396:

/* Line 1455 of yacc.c  */
#line 1329 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = IO_REG_W_LD  | IREG_EA1L;          strcpy(buf, "LDW EA1L"); ;}
    break;

  case 397:

/* Line 1455 of yacc.c  */
#line 1330 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = IO_REG_W_LD  | IREG_EA1H;          strcpy(buf, "LDW EA1H"); ;}
    break;

  case 398:

/* Line 1455 of yacc.c  */
#line 1331 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = IO_REG_W_LD  | IREG_EA2L;          strcpy(buf, "LDW EA2L"); ;}
    break;

  case 399:

/* Line 1455 of yacc.c  */
#line 1332 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = IO_REG_W_LD  | IREG_EA2H;          strcpy(buf, "LDW EA2H"); ;}
    break;

  case 400:

/* Line 1455 of yacc.c  */
#line 1333 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = IO_REG_W_LD  | IREG_PCL;           strcpy(buf, "LDW PCL"); ;}
    break;

  case 401:

/* Line 1455 of yacc.c  */
#line 1334 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = IO_REG_W_LD  | IREG_PCH;           strcpy(buf, "LDW PCH"); ;}
    break;

  case 402:

/* Line 1455 of yacc.c  */
#line 1335 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = IO_REG_W_LD  | IREG_VECL;          strcpy(buf, "LDW VECL"); ;}
    break;

  case 403:

/* Line 1455 of yacc.c  */
#line 1336 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = IO_REG_W_LD  | IREG_CPUS;          strcpy(buf, "LDW CPUS"); ;}
    break;

  case 404:

/* Line 1455 of yacc.c  */
#line 1337 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = IO_REG_W_LD  | IREG_IMM;           strcpy(buf, "LDW IMM"); ;}
    break;

  case 405:

/* Line 1455 of yacc.c  */
#line 1338 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = IO_REG_W_LD  | IREG_LSHR;          strcpy(buf, "LDW LSHR"); ;}
    break;

  case 406:

/* Line 1455 of yacc.c  */
#line 1339 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = IO_REG_W_LD  | IREG_ACCL;          strcpy(buf, "LDW ACCL"); ;}
    break;

  case 407:

/* Line 1455 of yacc.c  */
#line 1340 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = IO_REG_W_LD  | IREG_ACCH;          strcpy(buf, "LDW ACCH"); ;}
    break;

  case 408:

/* Line 1455 of yacc.c  */
#line 1341 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = IO_REG_W_LD  | IREG_DECJ;          strcpy(buf, "LDW DECJ"); ;}
    break;

  case 409:

/* Line 1455 of yacc.c  */
#line 1342 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = IO_REG_W_LD  | IREG_EA1J;          strcpy(buf, "LDW EA1J"); ;}
    break;

  case 410:

/* Line 1455 of yacc.c  */
#line 1343 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = IO_REG_W_LD  | IREG_EA2J;          strcpy(buf, "LDW EA2J"); ;}
    break;

  case 411:

/* Line 1455 of yacc.c  */
#line 1344 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = IO_REG_W_LD  | IREG_SR;            strcpy(buf, "LDW SR"); ;}
    break;

  case 412:

/* Line 1455 of yacc.c  */
#line 1345 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = IO_REG_B_LD  | IREG_SR;            strcpy(buf, "LDB SR"); ;}
    break;

  case 413:

/* Line 1455 of yacc.c  */
#line 1346 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = IO_REG_W_ST  | IREG_EA1L;          strcpy(buf, "STW EA1L"); ;}
    break;

  case 414:

/* Line 1455 of yacc.c  */
#line 1347 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = IO_REG_W_ST  | IREG_EA1H;          strcpy(buf, "STW EA1H"); ;}
    break;

  case 415:

/* Line 1455 of yacc.c  */
#line 1348 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = IO_REG_W_ST  | IREG_EA2L;          strcpy(buf, "STW EA2L"); ;}
    break;

  case 416:

/* Line 1455 of yacc.c  */
#line 1349 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = IO_REG_W_ST  | IREG_EA2H;          strcpy(buf, "STW EA2H"); ;}
    break;

  case 417:

/* Line 1455 of yacc.c  */
#line 1350 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = IO_REG_W_ST  | IREG_PCL;           strcpy(buf, "STW PCL"); ;}
    break;

  case 418:

/* Line 1455 of yacc.c  */
#line 1351 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = IO_REG_W_ST  | IREG_PCH;           strcpy(buf, "STW PCH"); ;}
    break;

  case 419:

/* Line 1455 of yacc.c  */
#line 1352 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = IO_REG_W_ST  | IREG_VECL;          strcpy(buf, "STW VECL"); ;}
    break;

  case 420:

/* Line 1455 of yacc.c  */
#line 1353 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = IO_REG_W_ST  | IREG_VECH;          strcpy(buf, "STW VECH"); ;}
    break;

  case 421:

/* Line 1455 of yacc.c  */
#line 1354 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = IO_REG_W_ST  | IREG_LSHR;          strcpy(buf, "STW LSHR"); ;}
    break;

  case 422:

/* Line 1455 of yacc.c  */
#line 1355 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = IO_REG_W_ST  | IREG_ACCL;          strcpy(buf, "STW ACCL"); ;}
    break;

  case 423:

/* Line 1455 of yacc.c  */
#line 1356 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = IO_REG_W_ST  | IREG_ACCH;          strcpy(buf, "STW ACCH"); ;}
    break;

  case 424:

/* Line 1455 of yacc.c  */
#line 1357 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = IO_REG_W_ST  | IREG_SR;            strcpy(buf, "STW SR"); ;}
    break;

  case 425:

/* Line 1455 of yacc.c  */
#line 1358 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = IO_REG_B_ST  | IREG_SR;            strcpy(buf, "STB SR"); ;}
    break;

  case 426:

/* Line 1455 of yacc.c  */
#line 1359 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = IO_REG_W_WR  | IREG_EA1L;          strcpy(buf, "WRW EA1L"); ;}
    break;

  case 427:

/* Line 1455 of yacc.c  */
#line 1360 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = IO_REG_W_WR  | IREG_EA1H;          strcpy(buf, "WRW EA1H"); ;}
    break;

  case 428:

/* Line 1455 of yacc.c  */
#line 1361 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = IO_REG_W_WR  | IREG_EA2L;          strcpy(buf, "WRW EA2L"); ;}
    break;

  case 429:

/* Line 1455 of yacc.c  */
#line 1362 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = IO_REG_W_WR  | IREG_EA2H;          strcpy(buf, "WRW EA2H"); ;}
    break;

  case 430:

/* Line 1455 of yacc.c  */
#line 1363 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = IO_REG_W_WR  | IREG_PCL;           strcpy(buf, "WRW PCL"); ;}
    break;

  case 431:

/* Line 1455 of yacc.c  */
#line 1364 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = IO_REG_W_WR  | IREG_PCH;           strcpy(buf, "WRW PCH"); ;}
    break;

  case 432:

/* Line 1455 of yacc.c  */
#line 1365 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = IO_REG_W_WR  | IREG_VECL;          strcpy(buf, "WRW VECL"); ;}
    break;

  case 433:

/* Line 1455 of yacc.c  */
#line 1366 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = IO_REG_W_WR  | IREG_VECH;          strcpy(buf, "WRW VECH"); ;}
    break;

  case 434:

/* Line 1455 of yacc.c  */
#line 1367 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = IO_REG_W_WR  | IREG_LSHR;          strcpy(buf, "WRW LSHR"); ;}
    break;

  case 435:

/* Line 1455 of yacc.c  */
#line 1368 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = IO_REG_W_WR  | IREG_ACCL;          strcpy(buf, "WRW ACCL"); ;}
    break;

  case 436:

/* Line 1455 of yacc.c  */
#line 1369 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = IO_REG_W_WR  | IREG_ACCH;          strcpy(buf, "WRW ACCH"); ;}
    break;

  case 437:

/* Line 1455 of yacc.c  */
#line 1370 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = IO_REG_W_WR  | IREG_SR;            strcpy(buf, "WRW SR"); ;}
    break;

  case 438:

/* Line 1455 of yacc.c  */
#line 1371 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"
    { (yyval.val) = IO_REG_B_WR  | IREG_SR;            strcpy(buf, "WRB SR"); ;}
    break;



/* Line 1455 of yacc.c  */
#line 5934 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20/microcode.parser.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 1374 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"


static LBLREC *lbl_decl(char *name, int addr)
{
  LBLREC *ptr;
  LBLREC *found = (LBLREC *)0;

  for (ptr = lbl_tab; ptr != (LBLREC *)0; ptr = ptr->next)
  {
    if (strcmp(ptr->name, name) == 0)
    {
      found = ptr;
      if (ptr->type == LBL_USE)
      {
        rom_data[ptr->addr] |= addr;
        ptr->addr = addr;
        ptr->type = LBL_DECL;
      }
    }
  }

  if (found)
  {
    return found;
  }
  else
  {
    ptr = (LBLREC *)malloc(sizeof(LBLREC));
    ptr->name = (char *)malloc(strlen(name) + 1);
    strcpy(ptr->name, name);
    ptr->addr = addr;
    ptr->type = LBL_DECL;
    ptr->next = lbl_tab;
    lbl_tab   = ptr;
    return ptr;
  }
}

static int lbl_use(char *name, int addr)
{
  LBLREC *ptr;
  LBLREC *found = (LBLREC *)0;

  for (ptr = lbl_tab; ptr != (LBLREC *)0; ptr = ptr->next)
  {
    if ((strcmp(ptr->name, name) == 0) && (ptr->type == LBL_DECL))
    {
      found = ptr;
    }
  }

  if (found)
  {
    return found->addr;
  }
  else
  {
    ptr = (LBLREC *)malloc(sizeof(LBLREC));
    ptr->name = (char *)malloc(strlen(name) + 1);
    strcpy(ptr->name, name);
    ptr->addr = addr;
    ptr->type = LBL_USE;
    ptr->next = lbl_tab;
    lbl_tab   = ptr;
    return 0;
  }
}

static void mif_out(FILE *fd, int *rom_data, int rom_size, int bit_st, int nb_bit)
{
  int i, j, v;

  for (i = 512; i <= ROM_SIZE; i *= 2)
  {
    if (rom_size <= i)
    {
      rom_size = i;
      break;
    }
  }

  fprintf(fd, "DEPTH = %d;\n", rom_size);
  fprintf(fd, "WIDTH = %d;\n", nb_bit);
  fputs("ADDRESS_RADIX = HEX;\n", fd);
  fputs("DATA_RADIX = BIN;\n", fd);
  fputs("CONTENT\n", fd);
  fputs("BEGIN\n", fd);
  for (i = 0; i < rom_size; i++)
  {
    fprintf(fd, "%04X : ", i);
    v = rom_data[i];
    for (j = (1 << (bit_st + nb_bit - 1)); j >= (1 << bit_st); j >>= 1)
    {
      if (v &j)
      {
        //putchar('1');
        fputc('1', fd);
      }
      else
      {
        //putchar('0');
        fputc('0', fd);
      }
    }
    //printf("; -- %s\n", &rom_instr[i * 32]);
    fprintf(fd, "; -- %05X %s\n", v, &rom_instr[i * 32]);
  }
  fputs("END;\n", fd);
}

static void jmp_mif_out(void)
{
  int i, j, v;

  printf("DEPTH = 256;\n");
  printf("WIDTH = 36;\n");
  printf("ADDRESS_RADIX = HEX;\n");
  printf("DATA_RADIX = BIN;\n");
  printf("CONTENT\n");
  printf("BEGIN\n");
  for (i = 0; i < 256; i++)
  {
    printf("%04X : ", i);
    v = jmp_data[i][0] & 0xFFF;
    for (j = 0x800; j >= 1; j /= 2)
    {
      if (v &j)
      {
        putchar('1');
      }
      else
      {
        putchar('0');
      }
    }
    v = jmp_data[i][1] & 0x3F;
    for (j = 0x20; j >= 1; j /= 2)
    {
      if (v &j)
      {
        putchar('1');
      }
      else
      {
        putchar('0');
      }
    }
    v = jmp_data[i][2] & 0x3F;
    for (j = 0x20; j >= 1; j /= 2)
    {
      if (v &j)
      {
        putchar('1');
      }
      else
      {
        putchar('0');
      }
    }
    v = jmp_data[i][3] & 0xF;
    for (j = 0x8; j >= 1; j /= 2)
    {
      if (v &j)
      {
        putchar('1');
      }
      else
      {
        putchar('0');
      }
    }
    printf("00000000; -- %03X, +%d, +%d\n", jmp_data[i][0], jmp_data[i][1], jmp_data[i][2]);
  }
  printf("END;\n");
}

static void mem_out(FILE *fd, int *rom_data, int rom_size)
{
  int i, j, v;

  for (i = 512; i <= ROM_SIZE; i *= 2)
  {
    if (rom_size <= i)
    {
      rom_size = i;
      break;
    }
  }

  for (i = 0; i < rom_size; i++)
  {
    v = rom_data[i];
    for (j = 0x80000; j >= 1; j /= 2)
    {
      if (v &j)
        fputc('1', fd);
      else
        fputc('0', fd);
    }
    fputc('\n', fd);
  }
}

static void jmp_mem_out(void)
{
  int i, j, v;

  for (i = 0; i < 256; i++)
  {
    v = jmp_data[i][0] & 0xFFF;
    for (j = 0x800; j >= 1; j /= 2)
    {
      if (v &j)
      {
        putchar('1');
      }
      else
      {
        putchar('0');
      }
    }
    v = jmp_data[i][1] & 0x3F;
    for (j = 0x20; j >= 1; j /= 2)
    {
      if (v &j)
      {
        putchar('1');
      }
      else
      {
        putchar('0');
      }
    }
    v = jmp_data[i][2] & 0x3F;
    for (j = 0x20; j >= 1; j /= 2)
    {
      if (v &j)
      {
        putchar('1');
      }
      else
      {
        putchar('0');
      }
    }
    v = jmp_data[i][3] & 0xF;
    for (j = 0x8; j >= 1; j /= 2)
    {
      if (v &j)
      {
        putchar('1');
      }
      else
      {
        putchar('0');
      }
    }
    printf("00000000 # %03X, +%d, +%d\n", jmp_data[i][0], jmp_data[i][1], jmp_data[i][2]);
  }
}

static void vl_out(FILE *fd, int *rom_data, int rom_size)
{
  int i, j, v, rom_pow2 = 9;

  for (i = 512, j = 9; i <= ROM_SIZE; i *= 2, j++)
  {
    if (rom_size <= i)
    {
      rom_size = i;
      rom_pow2 = j;
      break;
    }
  }

  fputs("module dpram_2048x20\n", fd);
  fputs("(\n", fd);
  fputs("  // Clock & reset\n", fd);
  fputs("  input         reset,\n", fd);
  fputs("  input         clock,\n", fd);
  fputs("  // Port A : micro-instruction fetch\n", fd);
  fputs("  input         rden_a,\n", fd);
  fprintf(fd, "  input  [%2d:0] address_a,\n", rom_pow2-1);
  fputs("  output [19:0] q_a,\n", fd);
  fputs("  // Port B : m68k registers read/write\n", fd);
  fputs("  input   [1:0] wren_b,\n", fd);
  fprintf(fd, "  input  [%2d:0] address_b,\n", rom_pow2-1);
  fputs("  input  [15:0] data_b,\n", fd);
  fputs("  output [15:0] q_b\n", fd);
  fputs(");\n\n", fd);

  fputs("// Inferred block ROM and RAM\n", fd);
  fprintf(fd, "reg  [15:0] r_mem_blk [0:%d];\n\n", rom_size-1);

  fputs("reg  [19:0] r_q_a;\n", fd);
  fputs("reg  [15:0] r_q_b;\n\n", fd);

  fputs("// Port A (read only)\n", fd);
  fputs("always@(posedge reset or posedge clock) begin\n", fd);
  fputs("  if (reset)\n", fd);
  fputs("    r_q_a <= 20'hC0458; // NOP instruction\n", fd);
  fputs("  else if (rden_a) begin\n", fd);
  fputs("    case(address_a)\n", fd);
  for (i = 0; i < rom_size; i++)
  {
    fprintf(fd, "      %d'h%03X : r_q_a <= 20'b", rom_pow2, i);
    v = rom_data[i];
    for (j = (1 << 19); j >= 1; j >>= 1)
    {
      if (v &j)
      {
        fputc('1', fd);
      }
      else
      {
        fputc('0', fd);
      }
    }
    fprintf(fd, "; // %05X %s\n", v, &rom_instr[i * 32]);
  }
  fputs("    endcase\n", fd);
  fputs("  end\n", fd);
  fputs("end\n\n", fd);

  fputs("assign q_a = r_q_a;\n\n", fd);

  fputs("// Port B (read/write)\n", fd);
  fputs("always@(posedge clock) begin\n", fd);
  fputs("  r_q_b <= r_mem_blk[address_b][15:0];\n", fd);
  fputs("  if (wren_b[0]) r_mem_blk[address_b][7:0]  <= data_b[7:0];\n", fd);
  fputs("  if (wren_b[1]) r_mem_blk[address_b][15:8] <= data_b[15:8];\n", fd);
  fputs("end\n\n", fd);

  fputs("assign q_b = r_q_b;\n\n", fd);

  fputs("endmodule\n", fd);

}

static void jmp_vl_out(void)
{
  int i, j, v;

  printf("module decode_rom\n");
  printf("(\n");
  printf("  input         clock,\n");
  printf("  input   [7:0] address,\n");
  printf("  output [35:0] q\n");
  printf(");\n\n");

  printf("reg  [35:0] r_q;\n\n");

  printf("always@(posedge clock) begin\n");
  printf("  case(address)\n");

  for (i = 0; i < 256; i++)
  {
    printf("    8'h%02X : r_q <= 36'b", i);
    v = jmp_data[i][0] & 0xFFF;
    for (j = 0x800; j >= 1; j /= 2)
    {
      if (v &j)
      {
        putchar('1');
      }
      else
      {
        putchar('0');
      }
    }
    putchar('_');

    v = jmp_data[i][1] & 0x3F;
    for (j = 0x20; j >= 1; j /= 2)
    {
      if (v &j)
      {
        putchar('1');
      }
      else
      {
        putchar('0');
      }
    }
    putchar('_');

    v = jmp_data[i][2] & 0x3F;
    for (j = 0x20; j >= 1; j /= 2)
    {
      if (v &j)
      {
        putchar('1');
      }
      else
      {
        putchar('0');
      }
    }
    putchar('_');

    v = jmp_data[i][3] & 0xF;
    for (j = 0x8; j >= 1; j /= 2)
    {
      if (v &j)
      {
        putchar('1');
      }
      else
      {
        putchar('0');
      }
    }
    putchar('_');

    printf("00000000; // %03X, +%d, +%d\n", jmp_data[i][0], jmp_data[i][1], jmp_data[i][2]);
  }
  printf("  endcase\n");
  printf("end\n\n");

  printf("endmodule\n");
}

int main(int argc, char **argv)
{
  FILE *dest;
  FILE *dest_0;
  FILE *dest_1;
  FILE *dest_2;
  FILE *dest_3;
  FILE *dest_4;
  int status;
  int mode;
  int idx;

  if ((argc == 3) || (argc == 4))
  {
    if (argc == 4)
    {
      mode = MODE_NONE;
      if (strcmp("-mif", argv[1]) == 0)  mode = MODE_MIF;
      if (strcmp("-mem", argv[1]) == 0)  mode = MODE_MEM;
      if (strcmp("-vlog", argv[1]) == 0) mode = MODE_VERILOG;
      if (strcmp("-vhdl", argv[1]) == 0) mode = MODE_VHDL;
      if (mode == MODE_NONE) goto usage;
      idx = 2;
    }
    else
    {
      mode = MODE_MIF;
      idx = 1;
    }
    yyin = fopen(argv[idx],"r");
    if (!yyin)
    {
      printf("Cannot open file \"%s\" for reading !!\n", argv[idx]);
      return -1;
    }
    idx++;

    dest = fopen(argv[idx],"w");
    if (!dest)
    {
      printf("Cannot open file \"%s\" for writing !!\n", argv[idx]);
      fclose(yyin);
      return -1;
    }

    if (mode == MODE_MIF)
    {
      dest_0 = fopen("j68_ram_0.mif","w");
      if (!dest)
      {
        printf("Cannot open file \"j68_ram_0.mif\" for writing !!\n");
        fclose(dest);
        fclose(yyin);
        return -1;
      }

      dest_1 = fopen("j68_ram_1.mif","w");
      if (!dest)
      {
        printf("Cannot open file \"j68_ram_1.mif\" for writing !!\n");
        fclose(dest_0);
        fclose(dest);
        fclose(yyin);
        return -1;
      }

      dest_2 = fopen("j68_ram_2.mif","w");
      if (!dest)
      {
        printf("Cannot open file \"j68_ram_2.mif\" for writing !!\n");
        fclose(dest_1);
        fclose(dest_0);
        fclose(dest);
        fclose(yyin);
        return -1;
      }

      dest_3 = fopen("j68_ram_3.mif","w");
      if (!dest)
      {
        printf("Cannot open file \"j68_ram_3.mif\" for writing !!\n");
        fclose(dest_2);
        fclose(dest_1);
        fclose(dest_0);
        fclose(dest);
        fclose(yyin);
        return -1;
      }

      dest_4 = fopen("j68_ram_4.mif","w");
      if (!dest)
      {
        printf("Cannot open file \"j68_ram_4.mif\" for writing !!\n");
        fclose(dest_3);
        fclose(dest_2);
        fclose(dest_1);
        fclose(dest_0);
        fclose(dest);
        fclose(yyin);
        return -1;
      }
    }

    rom_data = (int *)malloc(ROM_SIZE * sizeof(int));
    memset(rom_data, 0, ROM_SIZE * sizeof(int));

    rom_instr = (char *)malloc(ROM_SIZE * 32);

    if (yyout == NULL) yyout = stdout;

    status = yyparse();

    if (mode == MODE_MEM)
    {
      mem_out(dest, rom_data, rom_addr);
      jmp_mem_out();
    }

    if (mode == MODE_MIF)
    {
      mif_out(dest,   rom_data, rom_addr,  0, 20);
      mif_out(dest_0, rom_data, rom_addr,  0, 4);
      mif_out(dest_1, rom_data, rom_addr,  4, 4);
      mif_out(dest_2, rom_data, rom_addr,  8, 4);
      mif_out(dest_3, rom_data, rom_addr, 12, 4);
      mif_out(dest_4, rom_data, rom_addr, 16, 4);
      jmp_mif_out();
    }

    if (mode == MODE_VERILOG)
    {
      vl_out(dest, rom_data, rom_addr);
      jmp_vl_out();
    }

    if (mode == MODE_MIF)
    {
      fclose(dest_4);
      fclose(dest_3);
      fclose(dest_2);
      fclose(dest_1);
      fclose(dest_0);
    }

    fclose(dest);
    fclose(yyin);
  }
  else
  {
usage:
    printf("USAGE : microcode20 [-mif/-mem/-vlog/-vhdl] <source file> <destination file>\n");
    return -1;
  }

  return status;
}

