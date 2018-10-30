%{
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

%}

%union {
  char *txt;
  int   val;
}

%token <txt> TOK_JUMPN
%token <txt> TOK_JUMP
%token <txt> TOK_CALLN
%token <txt> TOK_CALL
%token <txt> TOK_RTS
%token <txt> TOK_LIT
%token <txt> TOK_FLAG
%token <txt> TOK_BIT
%token <txt> TOK_LOOPT
%token <txt> TOK_LOOP16
%token <txt> TOK_ENDLOOP
%token <txt> TOK_DROP
%token <txt> TOK_NIP
%token <txt> TOK_SWAP
%token <txt> TOK_DUP
%token <txt> TOK_OVER
%token <txt> TOK_ADDB
%token <txt> TOK_ADDW
%token <txt> TOK_ADDL
%token <txt> TOK_ADDCB
%token <txt> TOK_ADDCW
%token <txt> TOK_ADDCL
%token <txt> TOK_SUBB
%token <txt> TOK_SUBW
%token <txt> TOK_SUBL
%token <txt> TOK_SUBCB
%token <txt> TOK_SUBCW
%token <txt> TOK_SUBCL
%token <txt> TOK_SUB2B
%token <txt> TOK_SUB2W
%token <txt> TOK_SUB2L
%token <txt> TOK_SUBC2B
%token <txt> TOK_SUBC2W
%token <txt> TOK_SUBC2L
%token <txt> TOK_NEGB
%token <txt> TOK_NEGW
%token <txt> TOK_NEGL
%token <txt> TOK_NEGCB
%token <txt> TOK_NEGCW
%token <txt> TOK_NEGCL
%token <txt> TOK_DECW
%token <txt> TOK_EXTW
%token <txt> TOK_ANDB
%token <txt> TOK_ANDW
%token <txt> TOK_ANDL
%token <txt> TOK_ORB
%token <txt> TOK_ORW
%token <txt> TOK_ORL
%token <txt> TOK_XORB
%token <txt> TOK_XORW
%token <txt> TOK_XORL
%token <txt> TOK_MSKB
%token <txt> TOK_MSKW
%token <txt> TOK_MSKL
%token <txt> TOK_BANDB
%token <txt> TOK_BANDW
%token <txt> TOK_BANDL
%token <txt> TOK_BORB
%token <txt> TOK_BORW
%token <txt> TOK_BORL
%token <txt> TOK_BXORB
%token <txt> TOK_BXORW
%token <txt> TOK_BXORL
%token <txt> TOK_BMSKB
%token <txt> TOK_BMSKW
%token <txt> TOK_BMSKL
%token <txt> TOK_NOTB
%token <txt> TOK_NOTW
%token <txt> TOK_NOTL
%token <txt> TOK_TSTB
%token <txt> TOK_TSTW
%token <txt> TOK_TSTL
%token <txt> TOK_LSHB
%token <txt> TOK_LSHW
%token <txt> TOK_LSHL
%token <txt> TOK_RSHB
%token <txt> TOK_RSHW
%token <txt> TOK_RSHL
%token <txt> TOK_MUL
%token <txt> TOK_DIV
%token <txt> TOK_NOP

%token <txt> TOK_LDB
%token <txt> TOK_STB
%token <txt> TOK_WRB
%token <txt> TOK_FTW
%token <txt> TOK_LDW
%token <txt> TOK_STW
%token <txt> TOK_WRW
%token <txt> TOK_LDI
%token <txt> TOK_FTI
%token <txt> TOK_LDE
%token <txt> TOK_FTE
%token <txt> TOK_LDL
%token <txt> TOK_STL
%token <txt> TOK_WRL
%token <txt> TOK_LDH
%token <txt> TOK_STH
%token <txt> TOK_WRH
%token <txt> TOK_PC
%token <txt> TOK_VEC

%token <txt> TOK_EA1
%token <txt> TOK_EA2
%token <txt> TOK_CNT
%token <txt> TOK_EXT

%token <txt> TOK_T_SR
%token <txt> TOK_S_SR
%token <txt> TOK_A_SR
%token <txt> TOK_I_SR
%token <txt> TOK_B_SR
%token <txt> TOK_X_SR
%token <txt> TOK_N_SR
%token <txt> TOK_V_SR
%token <txt> TOK_CIN
%token <txt> TOK_CLR
%token <txt> TOK_C_ADD
%token <txt> TOK_C_FLG
%token <txt> TOK_Z_FLG
%token <txt> TOK_N_FLG
%token <txt> TOK_G_FLG
%token <txt> TOK_N_B
%token <txt> TOK_N_W
%token <txt> TOK_T0
%token <txt> TOK_T7
%token <txt> TOK_T15
%token <txt> TOK_N0
%token <txt> TOK_N7
%token <txt> TOK_N15
%token <txt> TOK_EA1_4
%token <txt> TOK_EA1_7
%token <txt> TOK_EXT11

%token <txt> TOK_EA1L
%token <txt> TOK_EA1H
%token <txt> TOK_EA2L
%token <txt> TOK_EA2H
%token <txt> TOK_PCL
%token <txt> TOK_PCH
%token <txt> TOK_VECL
%token <txt> TOK_VECH
%token <txt> TOK_CPUS
%token <txt> TOK_LSHR
%token <txt> TOK_ACCL
%token <txt> TOK_ACCH
%token <txt> TOK_IMMR
%token <txt> TOK_DECJ
%token <txt> TOK_EA1J
%token <txt> TOK_EA2J
%token <txt> TOK_EA1B
%token <txt> TOK_EA2B
%token <txt> TOK_SR
%token <txt> TOK_RT
%token <txt> TOK_RN
%token <val> TOK_MASK
%token <val> TOK_NUMBER
%token <txt> TOK_IDENT
%token <txt> TOK_RAL
%token <txt> TOK_RDL
%token <txt> TOK_RAH
%token <txt> TOK_RDH
%token <txt> TOK_RL
%token <txt> TOK_RH
%token <txt> TOK_A7L
%token <txt> TOK_A7H
%token <txt> TOK_USPL
%token <txt> TOK_USPH
%token <txt> TOK_SSPL
%token <txt> TOK_SSPH
%token <txt> TOK_TMP1L
%token <txt> TOK_TMP1H
%token <txt> TOK_TMP2L
%token <txt> TOK_TMP2H
%token <txt> TOK_VBRL
%token <txt> TOK_VBRH
%token <txt> TOK_ORG
%token <txt> TOK_TABLE

%%

input : /* empty */
      | input line
      ;

line  : '\n'
      | expr '\n'
      ;

expr  : org
      | table
      | label
      | jump
      | lit
      | flg
      | loop
      | alu
      | mem
      | reg
      ;

label : TOK_IDENT ':' { lbl_decl($1, rom_addr); }
      ;

table : TOK_TABLE TOK_IDENT ',' TOK_IDENT ',' TOK_IDENT ',' TOK_NUMBER
      {
        int lbl0;
        int lbl1;
        int lbl2;

        lbl0 = lbl_use($2, rom_addr);
        lbl1 = lbl_use($4, rom_addr);
        lbl2 = lbl_use($6, rom_addr);
        jmp_data[jmp_idx][0] = lbl0;
        jmp_data[jmp_idx][1] = lbl1 - lbl0;
        jmp_data[jmp_idx][2] = lbl2 - lbl0;
        switch ($8)
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
      };

org   : TOK_ORG TOK_NUMBER { rom_addr = $2 & (ROM_SIZE - 1); }

jump  : TOK_JUMPN cond ',' TOK_IDENT
      {
        int lbl;

        lbl = lbl_use($4, rom_addr);
        rom_data[rom_addr] = OPC_JUMPN | $<val>2 | (lbl & 0x7FF);
        sprintf(buf, "JUMPN %s,%s", cc_str[$<val>2 >> 12], $4);
        strncpy(&rom_instr[rom_addr * 32], buf, 31);
        rom_addr++;
      }
      | TOK_JUMPN cond ',' TOK_NUMBER
      {
        rom_data[rom_addr] = OPC_JUMPN | $<val>2 | ($4 & 0x7FF);
        sprintf(buf, "JUMPN %s,%04X", cc_str[$<val>2 >> 12], $4);
        strncpy(&rom_instr[rom_addr * 32], buf, 31);
        rom_addr++;
      }
      | TOK_JUMP cond ',' TOK_IDENT
      {
        int lbl;

        lbl = lbl_use($4, rom_addr);
        rom_data[rom_addr] = OPC_JUMP | $<val>2 | (lbl & 0x7FF);
        sprintf(buf, "JUMP %s,%s", cc_str[$<val>2 >> 12], $4);
        strncpy(&rom_instr[rom_addr * 32], buf, 31);
        rom_addr++;
      }
      | TOK_JUMP cond ',' TOK_NUMBER
      {
        rom_data[rom_addr] = OPC_JUMP | $<val>2 | ($4 & 0x7FF);
        sprintf(buf, "JUMP %s,%04X", cc_str[$<val>2 >> 12], $4);
        strncpy(&rom_instr[rom_addr * 32], buf, 31);
        rom_addr++;
      }
      | TOK_CALLN cond ',' TOK_IDENT
      {
        int lbl;

        lbl = lbl_use($4, rom_addr);
        rom_data[rom_addr] = OPC_CALLN | $<val>2 | (lbl & 0x7FF);
        sprintf(buf, "CALLN %s,%s", cc_str[$<val>2 >> 12], $4);
        strncpy(&rom_instr[rom_addr * 32], buf, 31);
        rom_addr++;
      }
      | TOK_CALLN cond ',' TOK_NUMBER
      {
        rom_data[rom_addr] = OPC_CALLN | $<val>2 | ($4 & 0x7FF);
        sprintf(buf, "CALLN %s,%04X", cc_str[$<val>2 >> 12], $4);
        strncpy(&rom_instr[rom_addr * 32], buf, 31);
        rom_addr++;
      }
      | TOK_CALL cond ',' TOK_IDENT
      {
        int lbl;

        lbl = lbl_use($4, rom_addr);
        rom_data[rom_addr] = OPC_CALL | $<val>2 | (lbl & 0x7FF);
        sprintf(buf, "CALL %s,%s", cc_str[$<val>2 >> 12], $4);
        strncpy(&rom_instr[rom_addr * 32], buf, 31);
        rom_addr++;
      }
      | TOK_CALL cond ',' TOK_NUMBER
      {
        rom_data[rom_addr] = OPC_CALL | $<val>2 | ($4 & 0x7FF);
        sprintf(buf, "CALL %s,%04X", cc_str[$<val>2 >> 12], $4);
        strncpy(&rom_instr[rom_addr * 32], buf, 31);
        rom_addr++;
      }
      | TOK_JUMP TOK_IDENT
      {
        int lbl;

        lbl = lbl_use($2, rom_addr);
        rom_data[rom_addr] = OPC_JUMP | CC_TRUE | (lbl & 0x7FF);
        sprintf(buf, "JUMP %s", $2);
        strncpy(&rom_instr[rom_addr * 32], buf, 31);
        rom_addr++;
      }
      | TOK_JUMP TOK_NUMBER
      {
        rom_data[rom_addr] = OPC_JUMP | CC_TRUE | ($2 & 0x7FF);
        sprintf(buf, "JUMP %04X", $2);
        strncpy(&rom_instr[rom_addr * 32], buf, 31);
        rom_addr++;
      }
      | TOK_CALL TOK_IDENT
      {
        int lbl;

        lbl = lbl_use($2, rom_addr);
        rom_data[rom_addr] = OPC_CALL | CC_TRUE | (lbl & 0x7FF);
        sprintf(buf, "CALL %s", $2);
        strncpy(&rom_instr[rom_addr * 32], buf, 31);
        rom_addr++;
      }
      | TOK_CALL TOK_NUMBER
      {
        rom_data[rom_addr] = OPC_CALL | CC_TRUE | ($2 & 0x7FF);
        sprintf(buf, "CALL %04X", $2);
        strncpy(&rom_instr[rom_addr * 32], buf, 31);
        rom_addr++;
      }
      | TOK_JUMP TOK_IDENT '(' TOK_RT ')'
      {
        int lbl;

        lbl = lbl_use($2, rom_addr);
        rom_data[rom_addr] = OPC_JUMP | CC_IND | (lbl & 0x7FF);
        sprintf(buf, "JUMP %s(T)", $2);
        strncpy(&rom_instr[rom_addr * 32], buf, 31);
        rom_addr++;
      }
      | TOK_JUMP TOK_NUMBER '(' TOK_RT ')'
      {
        rom_data[rom_addr] = OPC_JUMP | CC_IND | ($2 & 0x7FF);
        sprintf(buf, "JUMP %04X(T)", $2);
        strncpy(&rom_instr[rom_addr * 32], buf, 31);
        rom_addr++;
      }
      | TOK_CALL TOK_IDENT '(' TOK_RT ')'
      {
        int lbl;

        lbl = lbl_use($2, rom_addr);
        rom_data[rom_addr] = OPC_CALL | CC_IND | (lbl & 0x7FF);
        sprintf(buf, "CALL %s(T)", $2);
        strncpy(&rom_instr[rom_addr * 32], buf, 31);
        rom_addr++;
      }
      | TOK_CALL TOK_NUMBER '(' TOK_RT ')'
      {
        rom_data[rom_addr] = OPC_CALL | CC_IND | ($2 & 0x7FF);
        sprintf(buf, "CALL %04X(T)", $2);
        strncpy(&rom_instr[rom_addr * 32], buf, 31);
        rom_addr++;
      }
      ;

cond  : TOK_Z_FLG { $<val>$ = CC_Z_FLG;  }
      | TOK_N_FLG { $<val>$ = CC_N_FLG;  }
      | TOK_G_FLG { $<val>$ = CC_G_FLG;  }
      | TOK_T0    { $<val>$ = CC_T0;     }
      | TOK_EA1_4 { $<val>$ = CC_EA1_4;  }
      | TOK_EA1_7 { $<val>$ = CC_EA1_7;  }
      | TOK_EXT11 { $<val>$ = CC_EXT_11; }
      | TOK_V_SR  { $<val>$ = CC_V_SR;   }
      | TOK_N_SR  { $<val>$ = CC_N_SR;   }
      | TOK_B_SR  { $<val>$ = CC_B_SR;   }
      | TOK_I_SR  { $<val>$ = CC_I_SR;   }
      | TOK_A_SR  { $<val>$ = CC_A_SR;   }
      | TOK_S_SR  { $<val>$ = CC_S_SR;   }
      | TOK_T_SR  { $<val>$ = CC_T_SR;   }
      ;

lit   : litop TOK_RTS
      {
        rom_data[rom_addr] = $<val>1 | OPC_RTS;
        strcat(buf, "; RTS");
        strncpy(&rom_instr[rom_addr * 32], buf, 31);
        rom_addr++;
      }
      | litop
      {
        rom_data[rom_addr] = $<val>1;
        strncpy(&rom_instr[rom_addr * 32], buf, 31);
        rom_addr++;
      }
      ;

litop : TOK_LIT '#' TOK_NUMBER
      {
        $<val>$ = OPC_LIT | ($3 & 0xFFFF);
        sprintf(buf, "LIT #%04X", $3 & 0xFFFF);
      }
      | TOK_LIT '#' TOK_IDENT
      {
        int lbl;

        lbl = lbl_use($3, rom_addr);
        $<val>$ = OPC_LIT | (lbl & 0xFFFF);
        sprintf(buf, "LIT #%s", $3);
      }
      ;

flg   : flgop TOK_RTS
      {
        rom_data[rom_addr] = $<val>1 | OPC_RTS;
        strcat(buf, "; RTS");
        strncpy(&rom_instr[rom_addr * 32], buf, 31);
        rom_addr++;
      }
      | flgop
      {
        rom_data[rom_addr] = $<val>1;
        strncpy(&rom_instr[rom_addr * 32], buf, 31);
        rom_addr++;
      }
      ;

flgop : TOK_FLAG TOK_MASK cin
      {
        int m, i, v;

        $<val>$ = OPC_FLAG | $<val>2 | $<val>3;
        sprintf(buf, "FLAG -----,CIN=%s", flg_str[($<val>3 >> 11) & 15]);
        m = $<val>2;
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
      }
      ;

cin   : /* empty */               { $<val>$ = CIN_KEEP;  }
      | ',' TOK_CIN '=' TOK_CLR   { $<val>$ = CIN_CLR;   }
      | ',' TOK_CIN '=' TOK_C_ADD { $<val>$ = CIN_C_ADD; }
      | ',' TOK_CIN '=' TOK_C_FLG { $<val>$ = CIN_C_FLG; }
      | ',' TOK_CIN '=' TOK_X_SR  { $<val>$ = CIN_X_SR;  }
      | ',' TOK_CIN '=' TOK_N_B   { $<val>$ = CIN_N_B;   }
      | ',' TOK_CIN '=' TOK_N_W   { $<val>$ = CIN_N_W;   }
      | ',' TOK_CIN '=' TOK_N_SR  { $<val>$ = CIN_N_SR;  }
      | ',' TOK_CIN '=' TOK_T0    { $<val>$ = CIN_T0;    }
      | ',' TOK_CIN '=' TOK_T7    { $<val>$ = CIN_T7;    }
      | ',' TOK_CIN '=' TOK_T15   { $<val>$ = CIN_T15;   }
      | ',' TOK_CIN '=' TOK_N0    { $<val>$ = CIN_N0;    }
      | ',' TOK_CIN '=' TOK_N7    { $<val>$ = CIN_N7;    }
      | ',' TOK_CIN '=' TOK_N15   { $<val>$ = CIN_N15;  }
      ;

loop  : TOK_LOOP16
      {
        loop_addr = rom_addr;
        rom_data[rom_addr] = OPC_LOOP;
        strcpy(&rom_instr[rom_addr * 32], "LOOP #16");
        rom_addr++;
      }
      | TOK_LOOPT
      {
        loop_addr = rom_addr;
        rom_data[rom_addr] = OPC_LOOP | 0x0800;
        strcpy(&rom_instr[rom_addr * 32], "LOOP T");
        rom_addr++;
      }
      | TOK_ENDLOOP
      {
        if (loop_addr != -1)
        {
          rom_data[loop_addr] |= ((rom_addr - 1) & 0x7FF);
          loop_addr = -1;
        }
      }
      ;

alu   : aluop '.' TOK_RTS
      {
        rom_data[rom_addr] = $<val>1 | ALU_CCUPD | OPC_RTS;
        strcat(buf, ".; RTS");
        strncpy(&rom_instr[rom_addr * 32], buf, 31);
        rom_addr++;
      }
      | aluop TOK_RTS
      {
        rom_data[rom_addr] = $<val>1 | OPC_RTS;
        strcat(buf, "; RTS");
        strncpy(&rom_instr[rom_addr * 32], buf, 31);
        rom_addr++;
      }
      | aluop '.'
      {
        rom_data[rom_addr] = $<val>1 | ALU_CCUPD;
        strcat(buf, ".");
        strncpy(&rom_instr[rom_addr * 32], buf, 31);
        rom_addr++;
      }
      | aluop
      {
        rom_data[rom_addr] = $<val>1;
        strncpy(&rom_instr[rom_addr * 32], buf, 31);
        rom_addr++;
      }
      ;

aluop : TOK_DROP   { $<val>$ = ALU_DROP;   strcpy(buf, "DROP");  }
      | TOK_NIP    { $<val>$ = ALU_NIP;    strcpy(buf, "NIP");   }
      | TOK_SWAP   { $<val>$ = ALU_SWAP;   strcpy(buf, "SWAP");  }
      | TOK_DUP    { $<val>$ = ALU_DUP;    strcpy(buf, "DUP");   }
      | TOK_OVER   { $<val>$ = ALU_OVER;   strcpy(buf, "OVER");  }
      | TOK_ADDB   { $<val>$ = ALU_ADDB;   strcpy(buf, "ADDB");  }
      | TOK_ADDW   { $<val>$ = ALU_ADDW;   strcpy(buf, "ADDW");  }
      | TOK_ADDL   { $<val>$ = ALU_ADDL;   strcpy(buf, "ADDL");  }
      | TOK_ADDCB  { $<val>$ = ALU_ADDCB;  strcpy(buf, "ADDCB"); }
      | TOK_ADDCW  { $<val>$ = ALU_ADDCW;  strcpy(buf, "ADDCW"); }
      | TOK_ADDCL  { $<val>$ = ALU_ADDCL;  strcpy(buf, "ADDCL"); }
      | TOK_SUBB   { $<val>$ = ALU_SUBB;   strcpy(buf, "SUBB");  }
      | TOK_SUBW   { $<val>$ = ALU_SUBW;   strcpy(buf, "SUBW");  }
      | TOK_SUBL   { $<val>$ = ALU_SUBL;   strcpy(buf, "SUBL");  }
      | TOK_SUBCB  { $<val>$ = ALU_SUBCB;  strcpy(buf, "SUBCB"); }
      | TOK_SUBCW  { $<val>$ = ALU_SUBCW;  strcpy(buf, "SUBCW"); }
      | TOK_SUBCL  { $<val>$ = ALU_SUBCL;  strcpy(buf, "SUBCL"); }
      | TOK_SUB2B  { $<val>$ = ALU_SUB2B;  strcpy(buf, "SUBB");  }
      | TOK_SUB2W  { $<val>$ = ALU_SUB2W;  strcpy(buf, "SUBW");  }
      | TOK_SUB2L  { $<val>$ = ALU_SUB2L;  strcpy(buf, "SUBL");  }
      | TOK_SUBC2B { $<val>$ = ALU_SUBC2B; strcpy(buf, "SUBCB"); }
      | TOK_SUBC2W { $<val>$ = ALU_SUBC2W; strcpy(buf, "SUBCW"); }
      | TOK_SUBC2L { $<val>$ = ALU_SUBC2L; strcpy(buf, "SUBCL"); }
      | TOK_NEGB   { $<val>$ = ALU_NEGB;   strcpy(buf, "NEGB");  }
      | TOK_NEGW   { $<val>$ = ALU_NEGW;   strcpy(buf, "NEGW");  }
      | TOK_NEGL   { $<val>$ = ALU_NEGL;   strcpy(buf, "NEGL");  }
      | TOK_NEGCB  { $<val>$ = ALU_NEGCB;  strcpy(buf, "NEGCB"); }
      | TOK_NEGCW  { $<val>$ = ALU_NEGCW;  strcpy(buf, "NEGCW"); }
      | TOK_NEGCL  { $<val>$ = ALU_NEGCL;  strcpy(buf, "NEGCL"); }
      | TOK_DECW   { $<val>$ = ALU_DECW;   strcpy(buf, "DECW");  }
      | TOK_EXTW   { $<val>$ = ALU_EXTW;   strcpy(buf, "EXTW");  }
      | TOK_ANDB   { $<val>$ = ALU_ANDB;   strcpy(buf, "ANDB");  }
      | TOK_ANDW   { $<val>$ = ALU_ANDW;   strcpy(buf, "ANDW");  }
      | TOK_ANDL   { $<val>$ = ALU_ANDL;   strcpy(buf, "ANDL");  }
      | TOK_ORB    { $<val>$ = ALU_ORB;    strcpy(buf, "ORB");   }
      | TOK_ORW    { $<val>$ = ALU_ORW;    strcpy(buf, "ORW");   }
      | TOK_ORL    { $<val>$ = ALU_ORL;    strcpy(buf, "ORL");   }
      | TOK_XORB   { $<val>$ = ALU_XORB;   strcpy(buf, "XORB");  }
      | TOK_XORW   { $<val>$ = ALU_XORW;   strcpy(buf, "XORW");  }
      | TOK_XORL   { $<val>$ = ALU_XORL;   strcpy(buf, "XORL");  }
      | TOK_MSKB   { $<val>$ = ALU_MSKB;   strcpy(buf, "MSKB");  }
      | TOK_MSKW   { $<val>$ = ALU_MSKW;   strcpy(buf, "MSKW");  }
      | TOK_MSKL   { $<val>$ = ALU_MSKL;   strcpy(buf, "MSKL");  }
      | TOK_BANDB  { $<val>$ = ALU_BANDB;  strcpy(buf, "BANDB"); }
      | TOK_BANDW  { $<val>$ = ALU_BANDW;  strcpy(buf, "BANDW"); }
      | TOK_BANDL  { $<val>$ = ALU_BANDL;  strcpy(buf, "BANDL"); }
      | TOK_BORB   { $<val>$ = ALU_BORB;   strcpy(buf, "BORB");  }
      | TOK_BORW   { $<val>$ = ALU_BORW;   strcpy(buf, "BORW");  }
      | TOK_BORL   { $<val>$ = ALU_BORL;   strcpy(buf, "BORL");  }
      | TOK_BXORB  { $<val>$ = ALU_BXORB;  strcpy(buf, "BXORB"); }
      | TOK_BXORW  { $<val>$ = ALU_BXORW;  strcpy(buf, "BXORW"); }
      | TOK_BXORL  { $<val>$ = ALU_BXORL;  strcpy(buf, "BXORL"); }
      | TOK_BMSKB  { $<val>$ = ALU_BMSKB;  strcpy(buf, "BMSKB"); }
      | TOK_BMSKW  { $<val>$ = ALU_BMSKW;  strcpy(buf, "BMSKW"); }
      | TOK_BMSKL  { $<val>$ = ALU_BMSKL;  strcpy(buf, "BMSKL"); }
      | TOK_NOTB   { $<val>$ = ALU_NOTB;   strcpy(buf, "NOTB");  }
      | TOK_NOTW   { $<val>$ = ALU_NOTW;   strcpy(buf, "NOTW");  }
      | TOK_NOTL   { $<val>$ = ALU_NOTL;   strcpy(buf, "NOTL");  }
      | TOK_TSTB   { $<val>$ = ALU_TSTB;   strcpy(buf, "TSTB");  }
      | TOK_TSTW   { $<val>$ = ALU_TSTW;   strcpy(buf, "TSTW");  }
      | TOK_TSTL   { $<val>$ = ALU_TSTL;   strcpy(buf, "TSTL");  }
      | TOK_LSHB   { $<val>$ = ALU_LSHB;   strcpy(buf, "LSHB");  }
      | TOK_LSHW   { $<val>$ = ALU_LSHW;   strcpy(buf, "LSHW");  }
      | TOK_LSHL   { $<val>$ = ALU_LSHL;   strcpy(buf, "LSHL");  }
      | TOK_RSHB   { $<val>$ = ALU_RSHB;   strcpy(buf, "RSHB");  }
      | TOK_RSHW   { $<val>$ = ALU_RSHW;   strcpy(buf, "RSHW");  }
      | TOK_RSHL   { $<val>$ = ALU_RSHL;   strcpy(buf, "RSHL");  }
      | TOK_MUL    { $<val>$ = ALU_MUL;    strcpy(buf, "MUL");   }
      | TOK_DIV    { $<val>$ = ALU_DIV;    strcpy(buf, "DIV");   }
      | TOK_NOP    { $<val>$ = ALU_NOP;    strcpy(buf, "NOP");   }
      ;

mem   : memop '.' TOK_RTS
      {
        rom_data[rom_addr] = $<val>1 | ALU_CCUPD | OPC_RTS;
        strcat(buf, ".; RTS");
        strncpy(&rom_instr[rom_addr * 32], buf, 31);
        rom_addr++;
      }
      | memop TOK_RTS
      {
        rom_data[rom_addr] = $<val>1 | OPC_RTS;
        strcat(buf, "; RTS");
        strncpy(&rom_instr[rom_addr * 32], buf, 31);
        rom_addr++;
      }
      | memop '.'
      {
        rom_data[rom_addr] = $<val>1 | ALU_CCUPD;
        strcat(buf, ".");
        strncpy(&rom_instr[rom_addr * 32], buf, 31);
        rom_addr++;
      }
      | memop
      {
        rom_data[rom_addr] = $<val>1;
        strncpy(&rom_instr[rom_addr * 32], buf, 31);
        rom_addr++;
      }
      ;

memop : TOK_LDB '(' TOK_EA1 ')'     { $<val>$ = MEM_EA1_B_LD;                strcpy(buf, "LDB (EA1)"); }
      | TOK_LDB '(' TOK_EA1 ')' '+' { $<val>$ = MEM_EA1_B_LD | MEM_POST_INC; strcpy(buf, "LDB (EA1)+"); }
      | TOK_LDB '-' '(' TOK_EA1 ')' { $<val>$ = MEM_EA1_B_LD | MEM_PRE_DEC;  strcpy(buf, "LDB -(EA1)"); }
      | TOK_LDB '+' '(' TOK_EA1 ')' { $<val>$ = MEM_EA1_B_LD | MEM_PRE_INC;  strcpy(buf, "LDB +(EA1)"); }
      | TOK_LDW '(' TOK_EA1 ')'     { $<val>$ = MEM_EA1_W_LD;                strcpy(buf, "LDW (EA1)"); }
      | TOK_LDW '(' TOK_EA1 ')' '+' { $<val>$ = MEM_EA1_W_LD | MEM_POST_INC; strcpy(buf, "LDW (EA1)+"); }
      | TOK_LDW '-' '(' TOK_EA1 ')' { $<val>$ = MEM_EA1_W_LD | MEM_PRE_DEC;  strcpy(buf, "LDW -(EA1)"); }
      | TOK_LDW '+' '(' TOK_EA1 ')' { $<val>$ = MEM_EA1_W_LD | MEM_PRE_INC;  strcpy(buf, "LDW +(EA1)"); }
      | TOK_LDH '(' TOK_EA1 ')'     { $<val>$ = MEM_EA1_H_LD;                strcpy(buf, "LDH (EA1)"); }
      | TOK_LDH '(' TOK_EA1 ')' '+' { $<val>$ = MEM_EA1_H_LD | MEM_POST_INC; strcpy(buf, "LDH (EA1)+"); }
      | TOK_LDH '-' '(' TOK_EA1 ')' { $<val>$ = MEM_EA1_H_LD | MEM_PRE_DEC;  strcpy(buf, "LDH -(EA1)"); }
      | TOK_LDH '+' '(' TOK_EA1 ')' { $<val>$ = MEM_EA1_H_LD | MEM_PRE_INC;  strcpy(buf, "LDH +(EA1)"); }
      | TOK_LDL '(' TOK_EA1 ')'     { $<val>$ = MEM_EA1_L_LD;                strcpy(buf, "LDL (EA1)"); }
      | TOK_LDL '(' TOK_EA1 ')' '+' { $<val>$ = MEM_EA1_L_LD | MEM_POST_INC; strcpy(buf, "LDL (EA1)+"); }
      | TOK_LDL '-' '(' TOK_EA1 ')' { $<val>$ = MEM_EA1_L_LD | MEM_PRE_DEC;  strcpy(buf, "LDL -(EA1)"); }
      | TOK_LDL '+' '(' TOK_EA1 ')' { $<val>$ = MEM_EA1_L_LD | MEM_PRE_INC;  strcpy(buf, "LDL +(EA1)"); }
      | TOK_LDB '(' TOK_EA2 ')'     { $<val>$ = MEM_EA2_B_LD;                strcpy(buf, "LDB (EA2)"); }
      | TOK_LDB '(' TOK_EA2 ')' '+' { $<val>$ = MEM_EA2_B_LD | MEM_POST_INC; strcpy(buf, "LDB (EA2)+"); }
      | TOK_LDB '-' '(' TOK_EA2 ')' { $<val>$ = MEM_EA2_B_LD | MEM_PRE_DEC;  strcpy(buf, "LDB -(EA2)"); }
      | TOK_LDB '+' '(' TOK_EA2 ')' { $<val>$ = MEM_EA2_B_LD | MEM_PRE_INC;  strcpy(buf, "LDB +(EA2)"); }
      | TOK_LDW '(' TOK_EA2 ')'     { $<val>$ = MEM_EA2_W_LD;                strcpy(buf, "LDW (EA2)"); }
      | TOK_LDW '(' TOK_EA2 ')' '+' { $<val>$ = MEM_EA2_W_LD | MEM_POST_INC; strcpy(buf, "LDW (EA2)+"); }
      | TOK_LDW '-' '(' TOK_EA2 ')' { $<val>$ = MEM_EA2_W_LD | MEM_PRE_DEC;  strcpy(buf, "LDW -(EA2)"); }
      | TOK_LDW '+' '(' TOK_EA2 ')' { $<val>$ = MEM_EA2_W_LD | MEM_PRE_INC;  strcpy(buf, "LDW +(EA2)"); }
      | TOK_STB '(' TOK_EA1 ')'     { $<val>$ = MEM_EA1_B_ST;                strcpy(buf, "STB (EA1)"); }
      | TOK_STB '(' TOK_EA1 ')' '+' { $<val>$ = MEM_EA1_B_ST | MEM_POST_INC; strcpy(buf, "STB (EA1)+"); }
      | TOK_STB '-' '(' TOK_EA1 ')' { $<val>$ = MEM_EA1_B_ST | MEM_PRE_DEC;  strcpy(buf, "STB -(EA1)"); }
      | TOK_STB '+' '(' TOK_EA1 ')' { $<val>$ = MEM_EA1_B_ST | MEM_PRE_INC;  strcpy(buf, "STB +(EA1)"); }
      | TOK_STW '(' TOK_EA1 ')'     { $<val>$ = MEM_EA1_W_ST;                strcpy(buf, "STW (EA1)"); }
      | TOK_STW '(' TOK_EA1 ')' '+' { $<val>$ = MEM_EA1_W_ST | MEM_POST_INC; strcpy(buf, "STW (EA1)+"); }
      | TOK_STW '-' '(' TOK_EA1 ')' { $<val>$ = MEM_EA1_W_ST | MEM_PRE_DEC;  strcpy(buf, "STW -(EA1)"); }
      | TOK_STW '+' '(' TOK_EA1 ')' { $<val>$ = MEM_EA1_W_ST | MEM_PRE_INC;  strcpy(buf, "STW +(EA1)"); }
      | TOK_STH '(' TOK_EA1 ')'     { $<val>$ = MEM_EA1_H_ST;                strcpy(buf, "STH (EA1)"); }
      | TOK_STH '(' TOK_EA1 ')' '+' { $<val>$ = MEM_EA1_H_ST | MEM_POST_INC; strcpy(buf, "STH (EA1)+"); }
      | TOK_STH '-' '(' TOK_EA1 ')' { $<val>$ = MEM_EA1_H_ST | MEM_PRE_DEC;  strcpy(buf, "STH -(EA1)"); }
      | TOK_STH '+' '(' TOK_EA1 ')' { $<val>$ = MEM_EA1_H_ST | MEM_PRE_INC;  strcpy(buf, "STH +(EA1)"); }
      | TOK_STL '(' TOK_EA1 ')'     { $<val>$ = MEM_EA1_L_ST;                strcpy(buf, "STL (EA1)"); }
      | TOK_STL '(' TOK_EA1 ')' '+' { $<val>$ = MEM_EA1_L_ST | MEM_POST_INC; strcpy(buf, "STL (EA1)+"); }
      | TOK_STL '-' '(' TOK_EA1 ')' { $<val>$ = MEM_EA1_L_ST | MEM_PRE_DEC;  strcpy(buf, "STL -(EA1)"); }
      | TOK_STL '+' '(' TOK_EA1 ')' { $<val>$ = MEM_EA1_L_ST | MEM_PRE_INC;  strcpy(buf, "STL +(EA1)"); }
      | TOK_STB '(' TOK_EA2 ')'     { $<val>$ = MEM_EA2_B_ST;                strcpy(buf, "STB (EA2)"); }
      | TOK_STB '(' TOK_EA2 ')' '+' { $<val>$ = MEM_EA2_B_ST | MEM_POST_INC; strcpy(buf, "STB (EA2)+"); }
      | TOK_STB '-' '(' TOK_EA2 ')' { $<val>$ = MEM_EA2_B_ST | MEM_PRE_DEC;  strcpy(buf, "STB -(EA2)"); }
      | TOK_STB '+' '(' TOK_EA2 ')' { $<val>$ = MEM_EA2_B_ST | MEM_PRE_INC;  strcpy(buf, "STB +(EA2)"); }
      | TOK_STW '(' TOK_EA2 ')'     { $<val>$ = MEM_EA2_W_ST;                strcpy(buf, "STW (EA2)"); }
      | TOK_STW '(' TOK_EA2 ')' '+' { $<val>$ = MEM_EA2_W_ST | MEM_POST_INC; strcpy(buf, "STW (EA2)+"); }
      | TOK_STW '-' '(' TOK_EA2 ')' { $<val>$ = MEM_EA2_W_ST | MEM_PRE_DEC;  strcpy(buf, "STW -(EA2)"); }
      | TOK_STW '+' '(' TOK_EA2 ')' { $<val>$ = MEM_EA2_W_ST | MEM_PRE_INC;  strcpy(buf, "STW +(EA2)"); }
      | TOK_LDW '(' TOK_VEC ')' '+' { $<val>$ = MEM_VEC_LD | MEM_POST_INC;   strcpy(buf, "LDW (VEC)+"); }
      | TOK_LDI '(' TOK_PC ')' '+'  { $<val>$ = MEM_INS_LD;                  strcpy(buf, "LDI (PC)+"); }
      | TOK_LDE '(' TOK_PC ')' '+'  { $<val>$ = MEM_EXT_LD;                  strcpy(buf, "LDE (PC)+"); }
      | TOK_LDW '(' TOK_PC ')' '+'  { $<val>$ = MEM_IMM_LD;                  strcpy(buf, "LDW (PC)+"); }
      | TOK_FTI '(' TOK_PC ')' '+'  { $<val>$ = MEM_INS_FT;                  strcpy(buf, "FTI (PC)+"); }
      | TOK_FTE '(' TOK_PC ')' '+'  { $<val>$ = MEM_EXT_FT;                  strcpy(buf, "FTE (PC)+"); }
      | TOK_FTW '(' TOK_PC ')' '+'  { $<val>$ = MEM_IMM_FT;                  strcpy(buf, "FTW (PC)+"); }
      ;

reg   : regop '.' TOK_RTS
      {
        rom_data[rom_addr] = $<val>1 | ALU_CCUPD | OPC_RTS;
        strcat(buf, ".; RTS");
        strncpy(&rom_instr[rom_addr * 32], buf, 31);
        rom_addr++;
      }
      | regop TOK_RTS
      {
        rom_data[rom_addr] = $<val>1 | OPC_RTS;
        strcat(buf, "; RTS");
        strncpy(&rom_instr[rom_addr * 32], buf, 31);
        rom_addr++;
      }
      | regop '.'
      {
        rom_data[rom_addr] = $<val>1 | ALU_CCUPD;
        strcat(buf, ".");
        strncpy(&rom_instr[rom_addr * 32], buf, 31);
        rom_addr++;
      }
      | regop
      {
        rom_data[rom_addr] = $<val>1;
        strncpy(&rom_instr[rom_addr * 32], buf, 31);
        rom_addr++;
      }
      ;

regop : TOK_LDB TOK_RDL '[' TOK_EA1 ']' { $<val>$ = CPU_REG_B_LD | CREG_DL | RIDX_EA1; strcpy(buf, "LDB DL[EA1]"); }
      | TOK_LDB TOK_RAL '[' TOK_EA1 ']' { $<val>$ = CPU_REG_B_LD | CREG_AL | RIDX_EA1; strcpy(buf, "LDB AL[EA1]"); }
      | TOK_LDB TOK_RL  '[' TOK_EA1 ']' { $<val>$ = CPU_REG_B_LD | CREG_RL | RIDX_EA1; strcpy(buf, "LDB RL[EA1]"); }
      | TOK_LDB TOK_RDL '[' TOK_EA2 ']' { $<val>$ = CPU_REG_B_LD | CREG_DL | RIDX_EA2; strcpy(buf, "LDB DL[EA2]"); }
      | TOK_LDB TOK_RAL '[' TOK_EA2 ']' { $<val>$ = CPU_REG_B_LD | CREG_AL | RIDX_EA2; strcpy(buf, "LDB AL[EA2]"); }
      | TOK_LDB TOK_RL  '[' TOK_EA2 ']' { $<val>$ = CPU_REG_B_LD | CREG_RL | RIDX_EA2; strcpy(buf, "LDB RL[EA2]"); }
      | TOK_LDB TOK_RL  '[' TOK_CNT ']' { $<val>$ = CPU_REG_B_LD | CREG_RL | RIDX_CNT; strcpy(buf, "LDB RL[CNT]"); }
      | TOK_LDB TOK_RDL '[' TOK_EXT ']' { $<val>$ = CPU_REG_B_LD | CREG_DL | RIDX_EXT; strcpy(buf, "LDB DL[EXT]"); }
      | TOK_LDB TOK_RAL '[' TOK_EXT ']' { $<val>$ = CPU_REG_B_LD | CREG_AL | RIDX_EXT; strcpy(buf, "LDB AL[EXT]"); }
      | TOK_LDB TOK_RL  '[' TOK_EXT ']' { $<val>$ = CPU_REG_B_LD | CREG_RL | RIDX_EXT; strcpy(buf, "LDB RL[EXT]"); }
      | TOK_LDB TOK_VBRL                { $<val>$ = CPU_REG_B_LD | CREG_VBRL;          strcpy(buf, "LDB VBRL");    }
      | TOK_LDB TOK_TMP1L               { $<val>$ = CPU_REG_B_LD | CREG_TMP1L;         strcpy(buf, "LDB TMPL1");   }
      | TOK_LDB TOK_TMP2L               { $<val>$ = CPU_REG_B_LD | CREG_TMP2L;         strcpy(buf, "LDB TMPL2");   }
      | TOK_LDB TOK_USPL                { $<val>$ = CPU_REG_B_LD | CREG_USPL;          strcpy(buf, "LDB USPL");    }
      | TOK_LDB TOK_SSPL                { $<val>$ = CPU_REG_B_LD | CREG_SSPL;          strcpy(buf, "LDB SSPL");    }
      | TOK_LDB TOK_RDH '[' TOK_EA1 ']' { $<val>$ = CPU_REG_B_LD | CREG_DH | RIDX_EA1; strcpy(buf, "LDB DH[EA1]"); }
      | TOK_LDB TOK_RAH '[' TOK_EA1 ']' { $<val>$ = CPU_REG_B_LD | CREG_AH | RIDX_EA1; strcpy(buf, "LDB AH[EA1]"); }
      | TOK_LDB TOK_RH  '[' TOK_EA1 ']' { $<val>$ = CPU_REG_B_LD | CREG_RH | RIDX_EA1; strcpy(buf, "LDB RH[EA1]"); }
      | TOK_LDB TOK_RDH '[' TOK_EA2 ']' { $<val>$ = CPU_REG_B_LD | CREG_DH | RIDX_EA2; strcpy(buf, "LDB DH[EA2]"); }
      | TOK_LDB TOK_RAH '[' TOK_EA2 ']' { $<val>$ = CPU_REG_B_LD | CREG_AH | RIDX_EA2; strcpy(buf, "LDB AH[EA2]"); }
      | TOK_LDB TOK_RH  '[' TOK_EA2 ']' { $<val>$ = CPU_REG_B_LD | CREG_RH | RIDX_EA2; strcpy(buf, "LDB RH[EA2]"); }
      | TOK_LDB TOK_RH  '[' TOK_CNT ']' { $<val>$ = CPU_REG_B_LD | CREG_RH | RIDX_CNT; strcpy(buf, "LDB RH[CNT]"); }
      | TOK_LDB TOK_RDH '[' TOK_EXT ']' { $<val>$ = CPU_REG_B_LD | CREG_DH | RIDX_EXT; strcpy(buf, "LDB DH[EXT]"); }
      | TOK_LDB TOK_RAH '[' TOK_EXT ']' { $<val>$ = CPU_REG_B_LD | CREG_AH | RIDX_EXT; strcpy(buf, "LDB AH[EXT]"); }
      | TOK_LDB TOK_RH  '[' TOK_EXT ']' { $<val>$ = CPU_REG_B_LD | CREG_RH | RIDX_EXT; strcpy(buf, "LDB RH[EXT]"); }
      | TOK_LDB TOK_VBRH                { $<val>$ = CPU_REG_B_LD | CREG_VBRH;          strcpy(buf, "LDB VBRH");    }
      | TOK_LDB TOK_TMP1H               { $<val>$ = CPU_REG_B_LD | CREG_TMP1H;         strcpy(buf, "LDB TMP1H");   }
      | TOK_LDB TOK_TMP2H               { $<val>$ = CPU_REG_B_LD | CREG_TMP2H;         strcpy(buf, "LDB TMP2H");   }
      | TOK_LDB TOK_USPH                { $<val>$ = CPU_REG_B_LD | CREG_USPH;          strcpy(buf, "LDB USPH");    }
      | TOK_LDB TOK_SSPH                { $<val>$ = CPU_REG_B_LD | CREG_SSPH;          strcpy(buf, "LDB SSPH");    }
      | TOK_LDW TOK_RDL '[' TOK_EA1 ']' { $<val>$ = CPU_REG_W_LD | CREG_DL | RIDX_EA1; strcpy(buf, "LDW DL[EA1]"); }
      | TOK_LDW TOK_RAL '[' TOK_EA1 ']' { $<val>$ = CPU_REG_W_LD | CREG_AL | RIDX_EA1; strcpy(buf, "LDW AL[EA1]"); }
      | TOK_LDW TOK_RL  '[' TOK_EA1 ']' { $<val>$ = CPU_REG_W_LD | CREG_RL | RIDX_EA1; strcpy(buf, "LDW RL[EA1]"); }
      | TOK_LDW TOK_A7L                 { $<val>$ = CPU_REG_W_LD | CREG_A7L;           strcpy(buf, "LDW A7L");     }
      | TOK_LDW TOK_RDL '[' TOK_EA2 ']' { $<val>$ = CPU_REG_W_LD | CREG_DL | RIDX_EA2; strcpy(buf, "LDW DL[EA2]"); }
      | TOK_LDW TOK_RAL '[' TOK_EA2 ']' { $<val>$ = CPU_REG_W_LD | CREG_AL | RIDX_EA2; strcpy(buf, "LDW AL[EA2]"); }
      | TOK_LDW TOK_RL  '[' TOK_EA2 ']' { $<val>$ = CPU_REG_W_LD | CREG_RL | RIDX_EA2; strcpy(buf, "LDW RL[EA2]"); }
      | TOK_LDW TOK_RL  '[' TOK_CNT ']' { $<val>$ = CPU_REG_W_LD | CREG_RL | RIDX_CNT; strcpy(buf, "LDW RL[CNT]"); }
      | TOK_LDW TOK_RDL '[' TOK_EXT ']' { $<val>$ = CPU_REG_W_LD | CREG_DL | RIDX_EXT; strcpy(buf, "LDW DL[EXT]"); }
      | TOK_LDW TOK_RAL '[' TOK_EXT ']' { $<val>$ = CPU_REG_W_LD | CREG_AL | RIDX_EXT; strcpy(buf, "LDW AL[EXT]"); }
      | TOK_LDW TOK_RL  '[' TOK_EXT ']' { $<val>$ = CPU_REG_W_LD | CREG_RL | RIDX_EXT; strcpy(buf, "LDW RL[EXT]"); }
      | TOK_LDW TOK_VBRL                { $<val>$ = CPU_REG_W_LD | CREG_VBRL;          strcpy(buf, "LDW VBRL");    }
      | TOK_LDW TOK_TMP1L               { $<val>$ = CPU_REG_W_LD | CREG_TMP1L;         strcpy(buf, "LDW TMP1L");   }
      | TOK_LDW TOK_TMP2L               { $<val>$ = CPU_REG_W_LD | CREG_TMP2L;         strcpy(buf, "LDW TMP2L");   }
      | TOK_LDW TOK_USPL                { $<val>$ = CPU_REG_W_LD | CREG_USPL;          strcpy(buf, "LDW USPL");    }
      | TOK_LDW TOK_SSPL                { $<val>$ = CPU_REG_W_LD | CREG_SSPL;          strcpy(buf, "LDW SSPL");    }
      | TOK_LDW TOK_RDH '[' TOK_EA1 ']' { $<val>$ = CPU_REG_W_LD | CREG_DH | RIDX_EA1; strcpy(buf, "LDW DH[EA1]"); }
      | TOK_LDW TOK_RAH '[' TOK_EA1 ']' { $<val>$ = CPU_REG_W_LD | CREG_AH | RIDX_EA1; strcpy(buf, "LDW AH[EA1]"); }
      | TOK_LDW TOK_RH  '[' TOK_EA1 ']' { $<val>$ = CPU_REG_W_LD | CREG_RH | RIDX_EA1; strcpy(buf, "LDW RH[EA1]"); }
      | TOK_LDW TOK_A7H                 { $<val>$ = CPU_REG_W_LD | CREG_A7H;           strcpy(buf, "LDW A7H"); }
      | TOK_LDW TOK_RDH '[' TOK_EA2 ']' { $<val>$ = CPU_REG_W_LD | CREG_DH | RIDX_EA2; strcpy(buf, "LDW DH[EA2]"); }
      | TOK_LDW TOK_RAH '[' TOK_EA2 ']' { $<val>$ = CPU_REG_W_LD | CREG_AH | RIDX_EA2; strcpy(buf, "LDW AH[EA2]"); }
      | TOK_LDW TOK_RH  '[' TOK_EA2 ']' { $<val>$ = CPU_REG_W_LD | CREG_RH | RIDX_EA2; strcpy(buf, "LDW RH[EA2]"); }
      | TOK_LDW TOK_RH  '[' TOK_CNT ']' { $<val>$ = CPU_REG_W_LD | CREG_RH | RIDX_CNT; strcpy(buf, "LDW RH[CNT]"); }
      | TOK_LDW TOK_RDH '[' TOK_EXT ']' { $<val>$ = CPU_REG_W_LD | CREG_DH | RIDX_EXT; strcpy(buf, "LDW DH[EXT]"); }
      | TOK_LDW TOK_RAH '[' TOK_EXT ']' { $<val>$ = CPU_REG_W_LD | CREG_AH | RIDX_EXT; strcpy(buf, "LDW AH[EXT]"); }
      | TOK_LDW TOK_RH  '[' TOK_EXT ']' { $<val>$ = CPU_REG_W_LD | CREG_RH | RIDX_EXT; strcpy(buf, "LDW RH[EXT]"); }
      | TOK_LDW TOK_VBRH                { $<val>$ = CPU_REG_W_LD | CREG_VBRH;          strcpy(buf, "LDW VBRH");    }
      | TOK_LDW TOK_TMP1H               { $<val>$ = CPU_REG_W_LD | CREG_TMP1H;         strcpy(buf, "LDW TMP1H");   }
      | TOK_LDW TOK_TMP2H               { $<val>$ = CPU_REG_W_LD | CREG_TMP2H;         strcpy(buf, "LDW TMP2H");   }
      | TOK_LDW TOK_USPH                { $<val>$ = CPU_REG_W_LD | CREG_USPH;          strcpy(buf, "LDW USPH");    }
      | TOK_LDW TOK_SSPH                { $<val>$ = CPU_REG_W_LD | CREG_SSPH;          strcpy(buf, "LDW SSPH");    }
      | TOK_STB TOK_RDL '[' TOK_EA1 ']' { $<val>$ = CPU_REG_B_ST | CREG_DL | RIDX_EA1; strcpy(buf, "STB DL[EA1]"); }
      | TOK_STB TOK_RAL '[' TOK_EA1 ']' { $<val>$ = CPU_REG_B_ST | CREG_AL | RIDX_EA1; strcpy(buf, "STB AL[EA1]"); }
      | TOK_STB TOK_RL  '[' TOK_EA1 ']' { $<val>$ = CPU_REG_B_ST | CREG_RL | RIDX_EA1; strcpy(buf, "STB RL[EA1]"); }
      | TOK_STB TOK_RDL '[' TOK_EA2 ']' { $<val>$ = CPU_REG_B_ST | CREG_DL | RIDX_EA2; strcpy(buf, "STB DL[EA2]"); }
      | TOK_STB TOK_RAL '[' TOK_EA2 ']' { $<val>$ = CPU_REG_B_ST | CREG_AL | RIDX_EA2; strcpy(buf, "STB AL[EA2]"); }
      | TOK_STB TOK_RL  '[' TOK_EA2 ']' { $<val>$ = CPU_REG_B_ST | CREG_RL | RIDX_EA2; strcpy(buf, "STB RL[EA2]"); }
      | TOK_STB TOK_RL  '[' TOK_CNT ']' { $<val>$ = CPU_REG_B_ST | CREG_RL | RIDX_CNT; strcpy(buf, "STB RL[CNT]"); }
      | TOK_STB TOK_RDL '[' TOK_EXT ']' { $<val>$ = CPU_REG_B_ST | CREG_DL | RIDX_EXT; strcpy(buf, "STB DL[EXT]"); }
      | TOK_STB TOK_RAL '[' TOK_EXT ']' { $<val>$ = CPU_REG_B_ST | CREG_AL | RIDX_EXT; strcpy(buf, "STB AL[EXT]"); }
      | TOK_STB TOK_RL  '[' TOK_EXT ']' { $<val>$ = CPU_REG_B_ST | CREG_RL | RIDX_EXT; strcpy(buf, "STB RL[EXT]"); }
      | TOK_STB TOK_VBRL                { $<val>$ = CPU_REG_B_ST | CREG_VBRL;          strcpy(buf, "STB VBRL");    }
      | TOK_STB TOK_TMP1L               { $<val>$ = CPU_REG_B_ST | CREG_TMP1L;         strcpy(buf, "STB TMP1L");   }
      | TOK_STB TOK_TMP2L               { $<val>$ = CPU_REG_B_ST | CREG_TMP2L;         strcpy(buf, "STB TMP2L");   }
      | TOK_STB TOK_USPL                { $<val>$ = CPU_REG_B_ST | CREG_USPL;          strcpy(buf, "STB USPL");    }
      | TOK_STB TOK_SSPL                { $<val>$ = CPU_REG_B_ST | CREG_SSPL;          strcpy(buf, "STB SSPL");    }
      | TOK_STB TOK_RDH '[' TOK_EA1 ']' { $<val>$ = CPU_REG_B_ST | CREG_DH | RIDX_EA1; strcpy(buf, "STB DH[EA1]"); }
      | TOK_STB TOK_RAH '[' TOK_EA1 ']' { $<val>$ = CPU_REG_B_ST | CREG_AH | RIDX_EA1; strcpy(buf, "STB AH[EA1]"); }
      | TOK_STB TOK_RH  '[' TOK_EA1 ']' { $<val>$ = CPU_REG_B_ST | CREG_RH | RIDX_EA1; strcpy(buf, "STB RH[EA1]"); }
      | TOK_STB TOK_RDH '[' TOK_EA2 ']' { $<val>$ = CPU_REG_B_ST | CREG_DH | RIDX_EA2; strcpy(buf, "STB DH[EA2]"); }
      | TOK_STB TOK_RAH '[' TOK_EA2 ']' { $<val>$ = CPU_REG_B_ST | CREG_AH | RIDX_EA2; strcpy(buf, "STB AH[EA2]"); }
      | TOK_STB TOK_RH  '[' TOK_EA2 ']' { $<val>$ = CPU_REG_B_ST | CREG_RH | RIDX_EA2; strcpy(buf, "STB RH[EA2]"); }
      | TOK_STB TOK_RH  '[' TOK_CNT ']' { $<val>$ = CPU_REG_B_ST | CREG_RH | RIDX_CNT; strcpy(buf, "STB RH[CNT]"); }
      | TOK_STB TOK_RDH '[' TOK_EXT ']' { $<val>$ = CPU_REG_B_ST | CREG_DH | RIDX_EXT; strcpy(buf, "STB DH[EXT]"); }
      | TOK_STB TOK_RAH '[' TOK_EXT ']' { $<val>$ = CPU_REG_B_ST | CREG_AH | RIDX_EXT; strcpy(buf, "STB AH[EXT]"); }
      | TOK_STB TOK_RH  '[' TOK_EXT ']' { $<val>$ = CPU_REG_B_ST | CREG_RH | RIDX_EXT; strcpy(buf, "STB RH[EXT]"); }
      | TOK_STB TOK_VBRH                { $<val>$ = CPU_REG_B_ST | CREG_VBRH;          strcpy(buf, "STB VBRH");    }
      | TOK_STB TOK_TMP1H               { $<val>$ = CPU_REG_B_ST | CREG_TMP1H;         strcpy(buf, "STB TMP1H");   }
      | TOK_STB TOK_TMP2H               { $<val>$ = CPU_REG_B_ST | CREG_TMP2H;         strcpy(buf, "STB TMP2H");   }
      | TOK_STB TOK_USPH                { $<val>$ = CPU_REG_B_ST | CREG_USPH;          strcpy(buf, "STB USPH");    }
      | TOK_STB TOK_SSPH                { $<val>$ = CPU_REG_B_ST | CREG_SSPH;          strcpy(buf, "STB SSPH");    }
      | TOK_STW TOK_RDL '[' TOK_EA1 ']' { $<val>$ = CPU_REG_W_ST | CREG_DL | RIDX_EA1; strcpy(buf, "STW DL[EA1]"); }
      | TOK_STW TOK_RAL '[' TOK_EA1 ']' { $<val>$ = CPU_REG_W_ST | CREG_AL | RIDX_EA1; strcpy(buf, "STW AL[EA1]"); }
      | TOK_STW TOK_RL  '[' TOK_EA1 ']' { $<val>$ = CPU_REG_W_ST | CREG_RL | RIDX_EA1; strcpy(buf, "STW RL[EA1]"); }
      | TOK_STW TOK_A7L                 { $<val>$ = CPU_REG_W_ST | CREG_A7L;           strcpy(buf, "STW A7L");     }
      | TOK_STW TOK_RDL '[' TOK_EA2 ']' { $<val>$ = CPU_REG_W_ST | CREG_DL | RIDX_EA2; strcpy(buf, "STW DL[EA2]"); }
      | TOK_STW TOK_RAL '[' TOK_EA2 ']' { $<val>$ = CPU_REG_W_ST | CREG_AL | RIDX_EA2; strcpy(buf, "STW AL[EA2]"); }
      | TOK_STW TOK_RL  '[' TOK_EA2 ']' { $<val>$ = CPU_REG_W_ST | CREG_RL | RIDX_EA2; strcpy(buf, "STW RL[EA2]"); }
      | TOK_STW TOK_RL  '[' TOK_CNT ']' { $<val>$ = CPU_REG_W_ST | CREG_RL | RIDX_CNT; strcpy(buf, "STW RL[CNT]"); }
      | TOK_STW TOK_RDL '[' TOK_EXT ']' { $<val>$ = CPU_REG_W_ST | CREG_DL | RIDX_EXT; strcpy(buf, "STW DL[EXT]"); }
      | TOK_STW TOK_RAL '[' TOK_EXT ']' { $<val>$ = CPU_REG_W_ST | CREG_AL | RIDX_EXT; strcpy(buf, "STW AL[EXT]"); }
      | TOK_STW TOK_RL  '[' TOK_EXT ']' { $<val>$ = CPU_REG_W_ST | CREG_RL | RIDX_EXT; strcpy(buf, "STW RL[EXT]"); }
      | TOK_STW TOK_VBRL                { $<val>$ = CPU_REG_W_ST | CREG_VBRL;          strcpy(buf, "STW VBRL");    }
      | TOK_STW TOK_TMP1L               { $<val>$ = CPU_REG_W_ST | CREG_TMP1L;         strcpy(buf, "STW TMP1L");   }
      | TOK_STW TOK_TMP2L               { $<val>$ = CPU_REG_W_ST | CREG_TMP2L;         strcpy(buf, "STW TMP2L");   }
      | TOK_STW TOK_USPL                { $<val>$ = CPU_REG_W_ST | CREG_USPL;          strcpy(buf, "STW USPL");    }
      | TOK_STW TOK_SSPL                { $<val>$ = CPU_REG_W_ST | CREG_SSPL;          strcpy(buf, "STW SSPL");    }
      | TOK_STW TOK_RDH '[' TOK_EA1 ']' { $<val>$ = CPU_REG_W_ST | CREG_DH | RIDX_EA1; strcpy(buf, "STW DH[EA1]"); }
      | TOK_STW TOK_RAH '[' TOK_EA1 ']' { $<val>$ = CPU_REG_W_ST | CREG_AH | RIDX_EA1; strcpy(buf, "STW AH[EA1]"); }
      | TOK_STW TOK_RH  '[' TOK_EA1 ']' { $<val>$ = CPU_REG_W_ST | CREG_RH | RIDX_EA1; strcpy(buf, "STW RH[EA1]"); }
      | TOK_STW TOK_A7H                 { $<val>$ = CPU_REG_W_ST | CREG_A7H;           strcpy(buf, "STW A7H");     }
      | TOK_STW TOK_RDH '[' TOK_EA2 ']' { $<val>$ = CPU_REG_W_ST | CREG_DH | RIDX_EA2; strcpy(buf, "STW DH[EA2]"); }
      | TOK_STW TOK_RAH '[' TOK_EA2 ']' { $<val>$ = CPU_REG_W_ST | CREG_AH | RIDX_EA2; strcpy(buf, "STW AH[EA2]"); }
      | TOK_STW TOK_RH  '[' TOK_EA2 ']' { $<val>$ = CPU_REG_W_ST | CREG_RH | RIDX_EA2; strcpy(buf, "STW RH[EA2]"); }
      | TOK_STW TOK_RH  '[' TOK_CNT ']' { $<val>$ = CPU_REG_W_ST | CREG_RH | RIDX_CNT; strcpy(buf, "STW RH[CNT]"); }
      | TOK_STW TOK_RDH '[' TOK_EXT ']' { $<val>$ = CPU_REG_W_ST | CREG_DH | RIDX_EXT; strcpy(buf, "STW DH[EXT]"); }
      | TOK_STW TOK_RAH '[' TOK_EXT ']' { $<val>$ = CPU_REG_W_ST | CREG_AH | RIDX_EXT; strcpy(buf, "STW AH[EXT]"); }
      | TOK_STW TOK_RH  '[' TOK_EXT ']' { $<val>$ = CPU_REG_W_ST | CREG_RH | RIDX_EXT; strcpy(buf, "STW RH[EXT]"); }
      | TOK_STW TOK_VBRH                { $<val>$ = CPU_REG_W_ST | CREG_VBRH;          strcpy(buf, "STW VBRH"); }
      | TOK_STW TOK_TMP1H               { $<val>$ = CPU_REG_W_ST | CREG_TMP1H;         strcpy(buf, "STW TMP1H"); }
      | TOK_STW TOK_TMP2H               { $<val>$ = CPU_REG_W_ST | CREG_TMP2H;         strcpy(buf, "STW TMP2H"); }
      | TOK_STW TOK_USPH                { $<val>$ = CPU_REG_W_ST | CREG_USPH;          strcpy(buf, "STW USPH"); }
      | TOK_STW TOK_SSPH                { $<val>$ = CPU_REG_W_ST | CREG_SSPH;          strcpy(buf, "STW SSPH"); }
      | TOK_WRB TOK_RDL '[' TOK_EA1 ']' { $<val>$ = CPU_REG_B_WR | CREG_DL | RIDX_EA1; strcpy(buf, "WRB DL[EA1]"); }
      | TOK_WRB TOK_RAL '[' TOK_EA1 ']' { $<val>$ = CPU_REG_B_WR | CREG_AL | RIDX_EA1; strcpy(buf, "WRB AL[EA1]"); }
      | TOK_WRB TOK_RL  '[' TOK_EA1 ']' { $<val>$ = CPU_REG_B_WR | CREG_RL | RIDX_EA1; strcpy(buf, "WRB RL[EA1]"); }
      | TOK_WRB TOK_RDL '[' TOK_EA2 ']' { $<val>$ = CPU_REG_B_WR | CREG_DL | RIDX_EA2; strcpy(buf, "WRB DL[EA2]"); }
      | TOK_WRB TOK_RAL '[' TOK_EA2 ']' { $<val>$ = CPU_REG_B_WR | CREG_AL | RIDX_EA2; strcpy(buf, "WRB AL[EA2]"); }
      | TOK_WRB TOK_RL  '[' TOK_EA2 ']' { $<val>$ = CPU_REG_B_WR | CREG_RL | RIDX_EA2; strcpy(buf, "WRB RL[EA2]"); }
      | TOK_WRB TOK_RL  '[' TOK_CNT ']' { $<val>$ = CPU_REG_B_WR | CREG_RL | RIDX_CNT; strcpy(buf, "WRB RL[CNT]"); }
      | TOK_WRB TOK_RDL '[' TOK_EXT ']' { $<val>$ = CPU_REG_B_WR | CREG_DL | RIDX_EXT; strcpy(buf, "WRB DL[EXT]"); }
      | TOK_WRB TOK_RAL '[' TOK_EXT ']' { $<val>$ = CPU_REG_B_WR | CREG_AL | RIDX_EXT; strcpy(buf, "WRB AL[EXT]"); }
      | TOK_WRB TOK_RL  '[' TOK_EXT ']' { $<val>$ = CPU_REG_B_WR | CREG_RL | RIDX_EXT; strcpy(buf, "WRB RL[EXT]"); }
      | TOK_WRB TOK_VBRL                { $<val>$ = CPU_REG_B_WR | CREG_VBRL;          strcpy(buf, "WRB VBRL");    }
      | TOK_WRB TOK_TMP1L               { $<val>$ = CPU_REG_B_WR | CREG_TMP1L;         strcpy(buf, "WRB TMP1L");   }
      | TOK_WRB TOK_TMP2L               { $<val>$ = CPU_REG_B_WR | CREG_TMP2L;         strcpy(buf, "WRB TMP2L");   }
      | TOK_WRB TOK_USPL                { $<val>$ = CPU_REG_B_WR | CREG_USPL;          strcpy(buf, "WRB USPL");    }
      | TOK_WRB TOK_SSPL                { $<val>$ = CPU_REG_B_WR | CREG_SSPL;          strcpy(buf, "WRB SSPL");    }
      | TOK_WRB TOK_RDH '[' TOK_EA1 ']' { $<val>$ = CPU_REG_B_WR | CREG_DH | RIDX_EA1; strcpy(buf, "WRB DH[EA1]"); }
      | TOK_WRB TOK_RAH '[' TOK_EA1 ']' { $<val>$ = CPU_REG_B_WR | CREG_AH | RIDX_EA1; strcpy(buf, "WRB AH[EA1]"); }
      | TOK_WRB TOK_RH  '[' TOK_EA1 ']' { $<val>$ = CPU_REG_B_WR | CREG_RH | RIDX_EA1; strcpy(buf, "WRB RH[EA1]"); }
      | TOK_WRB TOK_RDH '[' TOK_EA2 ']' { $<val>$ = CPU_REG_B_WR | CREG_DH | RIDX_EA2; strcpy(buf, "WRB DH[EA2]"); }
      | TOK_WRB TOK_RAH '[' TOK_EA2 ']' { $<val>$ = CPU_REG_B_WR | CREG_AH | RIDX_EA2; strcpy(buf, "WRB AH[EA2]"); }
      | TOK_WRB TOK_RH  '[' TOK_EA2 ']' { $<val>$ = CPU_REG_B_WR | CREG_RH | RIDX_EA2; strcpy(buf, "WRB RH[EA2]"); }
      | TOK_WRB TOK_RH  '[' TOK_CNT ']' { $<val>$ = CPU_REG_B_WR | CREG_RH | RIDX_CNT; strcpy(buf, "WRB RH[CNT]"); }
      | TOK_WRB TOK_RDH '[' TOK_EXT ']' { $<val>$ = CPU_REG_B_WR | CREG_DH | RIDX_EXT; strcpy(buf, "WRB DH[EXT]"); }
      | TOK_WRB TOK_RAH '[' TOK_EXT ']' { $<val>$ = CPU_REG_B_WR | CREG_AH | RIDX_EXT; strcpy(buf, "WRB AH[EXT]"); }
      | TOK_WRB TOK_RH  '[' TOK_EXT ']' { $<val>$ = CPU_REG_B_WR | CREG_RH | RIDX_EXT; strcpy(buf, "WRB RH[EXT]"); }
      | TOK_WRB TOK_VBRH                { $<val>$ = CPU_REG_B_WR | CREG_VBRH;          strcpy(buf, "WRB VBRH");    }
      | TOK_WRB TOK_TMP1H               { $<val>$ = CPU_REG_B_WR | CREG_TMP1H;         strcpy(buf, "WRB TMP1H");   }
      | TOK_WRB TOK_TMP2H               { $<val>$ = CPU_REG_B_WR | CREG_TMP2H;         strcpy(buf, "WRB TMP2H");   }
      | TOK_WRB TOK_USPH                { $<val>$ = CPU_REG_B_WR | CREG_USPH;          strcpy(buf, "WRB USPH");    }
      | TOK_WRB TOK_SSPH                { $<val>$ = CPU_REG_B_WR | CREG_SSPH;          strcpy(buf, "WRB SSPH");    }
      | TOK_WRW TOK_RDL '[' TOK_EA1 ']' { $<val>$ = CPU_REG_W_WR | CREG_DL | RIDX_EA1; strcpy(buf, "WRW DL[EA1]"); }
      | TOK_WRW TOK_RAL '[' TOK_EA1 ']' { $<val>$ = CPU_REG_W_WR | CREG_AL | RIDX_EA1; strcpy(buf, "WRW AL[EA1]"); }
      | TOK_WRW TOK_RL  '[' TOK_EA1 ']' { $<val>$ = CPU_REG_W_WR | CREG_RL | RIDX_EA1; strcpy(buf, "WRW RL[EA1]"); }
      | TOK_WRW TOK_A7L                 { $<val>$ = CPU_REG_W_WR | CREG_A7L;           strcpy(buf, "WRW A7L");     }
      | TOK_WRW TOK_RDL '[' TOK_EA2 ']' { $<val>$ = CPU_REG_W_WR | CREG_DL | RIDX_EA2; strcpy(buf, "WRW DL[EA2]"); }
      | TOK_WRW TOK_RAL '[' TOK_EA2 ']' { $<val>$ = CPU_REG_W_WR | CREG_AL | RIDX_EA2; strcpy(buf, "WRW AL[EA2]"); }
      | TOK_WRW TOK_RL  '[' TOK_EA2 ']' { $<val>$ = CPU_REG_W_WR | CREG_RL | RIDX_EA2; strcpy(buf, "WRW RL[EA2]"); }
      | TOK_WRW TOK_RL  '[' TOK_CNT ']' { $<val>$ = CPU_REG_W_WR | CREG_RL | RIDX_CNT; strcpy(buf, "WRW RL[CNT]"); }
      | TOK_WRW TOK_RDL '[' TOK_EXT ']' { $<val>$ = CPU_REG_W_WR | CREG_DL | RIDX_EXT; strcpy(buf, "WRW DL[EXT]"); }
      | TOK_WRW TOK_RAL '[' TOK_EXT ']' { $<val>$ = CPU_REG_W_WR | CREG_AL | RIDX_EXT; strcpy(buf, "WRW AL[EXT]"); }
      | TOK_WRW TOK_RL  '[' TOK_EXT ']' { $<val>$ = CPU_REG_W_WR | CREG_RL | RIDX_EXT; strcpy(buf, "WRW RL[EXT]"); }
      | TOK_WRW TOK_VBRL                { $<val>$ = CPU_REG_W_WR | CREG_VBRL;          strcpy(buf, "WRW VBRL");    }
      | TOK_WRW TOK_TMP1L               { $<val>$ = CPU_REG_W_WR | CREG_TMP1L;         strcpy(buf, "WRW TMP1L");   }
      | TOK_WRW TOK_TMP2L               { $<val>$ = CPU_REG_W_WR | CREG_TMP2L;         strcpy(buf, "WRW TMP2L");   }
      | TOK_WRW TOK_USPL                { $<val>$ = CPU_REG_W_WR | CREG_USPL;          strcpy(buf, "WRW USPL");    }
      | TOK_WRW TOK_SSPL                { $<val>$ = CPU_REG_W_WR | CREG_SSPL;          strcpy(buf, "WRW SSPL");    }
      | TOK_WRW TOK_RDH '[' TOK_EA1 ']' { $<val>$ = CPU_REG_W_WR | CREG_DH | RIDX_EA1; strcpy(buf, "WRW DH[EA1]"); }
      | TOK_WRW TOK_RAH '[' TOK_EA1 ']' { $<val>$ = CPU_REG_W_WR | CREG_AH | RIDX_EA1; strcpy(buf, "WRW AH[EA1]"); }
      | TOK_WRW TOK_RH  '[' TOK_EA1 ']' { $<val>$ = CPU_REG_W_WR | CREG_RH | RIDX_EA1; strcpy(buf, "WRW RH[EA1]"); }
      | TOK_WRW TOK_A7H                 { $<val>$ = CPU_REG_W_WR | CREG_A7H;           strcpy(buf, "WRW A7H");     }
      | TOK_WRW TOK_RDH '[' TOK_EA2 ']' { $<val>$ = CPU_REG_W_WR | CREG_DH | RIDX_EA2; strcpy(buf, "WRW DH[EA2]"); }
      | TOK_WRW TOK_RAH '[' TOK_EA2 ']' { $<val>$ = CPU_REG_W_WR | CREG_AH | RIDX_EA2; strcpy(buf, "WRW AH[EA2]"); }
      | TOK_WRW TOK_RH  '[' TOK_EA2 ']' { $<val>$ = CPU_REG_W_WR | CREG_RH | RIDX_EA2; strcpy(buf, "WRW RH[EA2]"); }
      | TOK_WRW TOK_RH  '[' TOK_CNT ']' { $<val>$ = CPU_REG_W_WR | CREG_RH | RIDX_CNT; strcpy(buf, "WRW RH[CNT]"); }
      | TOK_WRW TOK_RDH '[' TOK_EXT ']' { $<val>$ = CPU_REG_W_WR | CREG_DH | RIDX_EXT; strcpy(buf, "WRW DH[EXT]"); }
      | TOK_WRW TOK_RAH '[' TOK_EXT ']' { $<val>$ = CPU_REG_W_WR | CREG_AH | RIDX_EXT; strcpy(buf, "WRW AH[EXT]"); }
      | TOK_WRW TOK_RH  '[' TOK_EXT ']' { $<val>$ = CPU_REG_W_WR | CREG_RH | RIDX_EXT; strcpy(buf, "WRW RH[EXT]"); }
      | TOK_WRW TOK_VBRH                { $<val>$ = CPU_REG_W_WR | CREG_VBRH;          strcpy(buf, "WRW VBRH"); }
      | TOK_WRW TOK_TMP1H               { $<val>$ = CPU_REG_W_WR | CREG_TMP1H;         strcpy(buf, "WRW TMP1H"); }
      | TOK_WRW TOK_TMP2H               { $<val>$ = CPU_REG_W_WR | CREG_TMP2H;         strcpy(buf, "WRW TMP2H"); }
      | TOK_WRW TOK_USPH                { $<val>$ = CPU_REG_W_WR | CREG_USPH;          strcpy(buf, "WRW USPH"); }
      | TOK_WRW TOK_SSPH                { $<val>$ = CPU_REG_W_WR | CREG_SSPH;          strcpy(buf, "WRW SSPH"); }
      | TOK_LDW TOK_EA1L                { $<val>$ = IO_REG_W_LD  | IREG_EA1L;          strcpy(buf, "LDW EA1L"); }
      | TOK_LDW TOK_EA1H                { $<val>$ = IO_REG_W_LD  | IREG_EA1H;          strcpy(buf, "LDW EA1H"); }
      | TOK_LDW TOK_EA2L                { $<val>$ = IO_REG_W_LD  | IREG_EA2L;          strcpy(buf, "LDW EA2L"); }
      | TOK_LDW TOK_EA2H                { $<val>$ = IO_REG_W_LD  | IREG_EA2H;          strcpy(buf, "LDW EA2H"); }
      | TOK_LDW TOK_PCL                 { $<val>$ = IO_REG_W_LD  | IREG_PCL;           strcpy(buf, "LDW PCL"); }
      | TOK_LDW TOK_PCH                 { $<val>$ = IO_REG_W_LD  | IREG_PCH;           strcpy(buf, "LDW PCH"); }
      | TOK_LDW TOK_VECL                { $<val>$ = IO_REG_W_LD  | IREG_VECL;          strcpy(buf, "LDW VECL"); }
      | TOK_LDW TOK_CPUS                { $<val>$ = IO_REG_W_LD  | IREG_CPUS;          strcpy(buf, "LDW CPUS"); }
      | TOK_LDW TOK_IMMR                { $<val>$ = IO_REG_W_LD  | IREG_IMM;           strcpy(buf, "LDW IMM"); }
      | TOK_LDW TOK_LSHR                { $<val>$ = IO_REG_W_LD  | IREG_LSHR;          strcpy(buf, "LDW LSHR"); }
      | TOK_LDW TOK_ACCL                { $<val>$ = IO_REG_W_LD  | IREG_ACCL;          strcpy(buf, "LDW ACCL"); }
      | TOK_LDW TOK_ACCH                { $<val>$ = IO_REG_W_LD  | IREG_ACCH;          strcpy(buf, "LDW ACCH"); }
      | TOK_LDW TOK_DECJ                { $<val>$ = IO_REG_W_LD  | IREG_DECJ;          strcpy(buf, "LDW DECJ"); }
      | TOK_LDW TOK_EA1J                { $<val>$ = IO_REG_W_LD  | IREG_EA1J;          strcpy(buf, "LDW EA1J"); }
      | TOK_LDW TOK_EA2J                { $<val>$ = IO_REG_W_LD  | IREG_EA2J;          strcpy(buf, "LDW EA2J"); }
      | TOK_LDW TOK_SR                  { $<val>$ = IO_REG_W_LD  | IREG_SR;            strcpy(buf, "LDW SR"); }
      | TOK_LDB TOK_SR                  { $<val>$ = IO_REG_B_LD  | IREG_SR;            strcpy(buf, "LDB SR"); }
      | TOK_STW TOK_EA1L                { $<val>$ = IO_REG_W_ST  | IREG_EA1L;          strcpy(buf, "STW EA1L"); }
      | TOK_STW TOK_EA1H                { $<val>$ = IO_REG_W_ST  | IREG_EA1H;          strcpy(buf, "STW EA1H"); }
      | TOK_STW TOK_EA2L                { $<val>$ = IO_REG_W_ST  | IREG_EA2L;          strcpy(buf, "STW EA2L"); }
      | TOK_STW TOK_EA2H                { $<val>$ = IO_REG_W_ST  | IREG_EA2H;          strcpy(buf, "STW EA2H"); }
      | TOK_STW TOK_PCL                 { $<val>$ = IO_REG_W_ST  | IREG_PCL;           strcpy(buf, "STW PCL"); }
      | TOK_STW TOK_PCH                 { $<val>$ = IO_REG_W_ST  | IREG_PCH;           strcpy(buf, "STW PCH"); }
      | TOK_STW TOK_VECL                { $<val>$ = IO_REG_W_ST  | IREG_VECL;          strcpy(buf, "STW VECL"); }
      | TOK_STW TOK_VECH                { $<val>$ = IO_REG_W_ST  | IREG_VECH;          strcpy(buf, "STW VECH"); }
      | TOK_STW TOK_LSHR                { $<val>$ = IO_REG_W_ST  | IREG_LSHR;          strcpy(buf, "STW LSHR"); }
      | TOK_STW TOK_ACCL                { $<val>$ = IO_REG_W_ST  | IREG_ACCL;          strcpy(buf, "STW ACCL"); }
      | TOK_STW TOK_ACCH                { $<val>$ = IO_REG_W_ST  | IREG_ACCH;          strcpy(buf, "STW ACCH"); }
      | TOK_STW TOK_SR                  { $<val>$ = IO_REG_W_ST  | IREG_SR;            strcpy(buf, "STW SR"); }
      | TOK_STB TOK_SR                  { $<val>$ = IO_REG_B_ST  | IREG_SR;            strcpy(buf, "STB SR"); }
      | TOK_WRW TOK_EA1L                { $<val>$ = IO_REG_W_WR  | IREG_EA1L;          strcpy(buf, "WRW EA1L"); }
      | TOK_WRW TOK_EA1H                { $<val>$ = IO_REG_W_WR  | IREG_EA1H;          strcpy(buf, "WRW EA1H"); }
      | TOK_WRW TOK_EA2L                { $<val>$ = IO_REG_W_WR  | IREG_EA2L;          strcpy(buf, "WRW EA2L"); }
      | TOK_WRW TOK_EA2H                { $<val>$ = IO_REG_W_WR  | IREG_EA2H;          strcpy(buf, "WRW EA2H"); }
      | TOK_WRW TOK_PCL                 { $<val>$ = IO_REG_W_WR  | IREG_PCL;           strcpy(buf, "WRW PCL"); }
      | TOK_WRW TOK_PCH                 { $<val>$ = IO_REG_W_WR  | IREG_PCH;           strcpy(buf, "WRW PCH"); }
      | TOK_WRW TOK_VECL                { $<val>$ = IO_REG_W_WR  | IREG_VECL;          strcpy(buf, "WRW VECL"); }
      | TOK_WRW TOK_VECH                { $<val>$ = IO_REG_W_WR  | IREG_VECH;          strcpy(buf, "WRW VECH"); }
      | TOK_WRW TOK_LSHR                { $<val>$ = IO_REG_W_WR  | IREG_LSHR;          strcpy(buf, "WRW LSHR"); }
      | TOK_WRW TOK_ACCL                { $<val>$ = IO_REG_W_WR  | IREG_ACCL;          strcpy(buf, "WRW ACCL"); }
      | TOK_WRW TOK_ACCH                { $<val>$ = IO_REG_W_WR  | IREG_ACCH;          strcpy(buf, "WRW ACCH"); }
      | TOK_WRW TOK_SR                  { $<val>$ = IO_REG_W_WR  | IREG_SR;            strcpy(buf, "WRW SR"); }
      | TOK_WRB TOK_SR                  { $<val>$ = IO_REG_B_WR  | IREG_SR;            strcpy(buf, "WRB SR"); }
      ;

%%

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
