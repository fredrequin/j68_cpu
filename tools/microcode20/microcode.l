%option never-interactive
%{
#include <stdio.h>
#include <string.h>
#include "microcode.parser.h"

#ifndef YY_NO_UNISTD_H
#define YY_NO_UNISTD_H
#endif

extern int line_num;

%}

%start COMMENT
%%

<INITIAL>[ \t] { /* Skip spaces and tabs */ }
<INITIAL>"//".* { /* Skip line comments */ }
<INITIAL>"/*" { BEGIN(COMMENT); /* Comment block starts */ }
<COMMENT>"*/" { BEGIN(INITIAL); /* Comment block ends */ }
<COMMENT>. { /* Ignore comments */ }
"\x0d\n"|"\n" { line_num++; /* Count lines */ return '\n'; }

<INITIAL>"FTI"     { yylval.txt = (char *)0; return TOK_FTI; }
<INITIAL>"LDI"     { yylval.txt = (char *)0; return TOK_LDI; }
<INITIAL>"FTE"     { yylval.txt = (char *)0; return TOK_FTE; }
<INITIAL>"LDE"     { yylval.txt = (char *)0; return TOK_LDE; }
<INITIAL>"LDL"     { yylval.txt = (char *)0; return TOK_LDL; }
<INITIAL>"STL"     { yylval.txt = (char *)0; return TOK_STL; }
<INITIAL>"WRL"     { yylval.txt = (char *)0; return TOK_WRL; }
<INITIAL>"LDH"     { yylval.txt = (char *)0; return TOK_LDH; }
<INITIAL>"STH"     { yylval.txt = (char *)0; return TOK_STH; }
<INITIAL>"WRH"     { yylval.txt = (char *)0; return TOK_WRH; }
<INITIAL>"LDB"     { yylval.txt = (char *)0; return TOK_LDB; }
<INITIAL>"STB"     { yylval.txt = (char *)0; return TOK_STB; }
<INITIAL>"WRB"     { yylval.txt = (char *)0; return TOK_WRB; }
<INITIAL>"FTW"     { yylval.txt = (char *)0; return TOK_FTW; }
<INITIAL>"LDW"     { yylval.txt = (char *)0; return TOK_LDW; }
<INITIAL>"STW"     { yylval.txt = (char *)0; return TOK_STW; }
<INITIAL>"WRW"     { yylval.txt = (char *)0; return TOK_WRW; }

<INITIAL>"LOOPT"   { yylval.txt = (char *)0; return TOK_LOOPT; }
<INITIAL>"LOOP16"  { yylval.txt = (char *)0; return TOK_LOOP16; }
<INITIAL>"ENDLOOP" { yylval.txt = (char *)0; return TOK_ENDLOOP; }
<INITIAL>"CALL"    { yylval.txt = (char *)0; return TOK_CALL; }
<INITIAL>"CALLN"   { yylval.txt = (char *)0; return TOK_CALLN; }
<INITIAL>"JUMP"    { yylval.txt = (char *)0; return TOK_JUMP; }
<INITIAL>"JUMPN"   { yylval.txt = (char *)0; return TOK_JUMPN; }
<INITIAL>"RTS"     { yylval.txt = (char *)0; return TOK_RTS; }
<INITIAL>"LIT"     { yylval.txt = (char *)0; return TOK_LIT; }
<INITIAL>"FLAG"    { yylval.txt = (char *)0; return TOK_FLAG; }

<INITIAL>"DROP"    { yylval.txt = (char *)0; return TOK_DROP; }
<INITIAL>"NIP"     { yylval.txt = (char *)0; return TOK_NIP; }
<INITIAL>"SWAP"    { yylval.txt = (char *)0; return TOK_SWAP; }
<INITIAL>"DUP"     { yylval.txt = (char *)0; return TOK_DUP; }
<INITIAL>"OVER"    { yylval.txt = (char *)0; return TOK_OVER; }
<INITIAL>"ADDB"    { yylval.txt = (char *)0; return TOK_ADDB; }
<INITIAL>"ADDW"    { yylval.txt = (char *)0; return TOK_ADDW; }
<INITIAL>"ADDL"    { yylval.txt = (char *)0; return TOK_ADDL; }
<INITIAL>"ADDCB"   { yylval.txt = (char *)0; return TOK_ADDCB; }
<INITIAL>"ADDCW"   { yylval.txt = (char *)0; return TOK_ADDCW; }
<INITIAL>"ADDCL"   { yylval.txt = (char *)0; return TOK_ADDCL; }
<INITIAL>"SUBB"    { yylval.txt = (char *)0; return TOK_SUBB; }
<INITIAL>"SUBW"    { yylval.txt = (char *)0; return TOK_SUBW; }
<INITIAL>"SUBL"    { yylval.txt = (char *)0; return TOK_SUBL; }
<INITIAL>"SUBCB"   { yylval.txt = (char *)0; return TOK_SUBCB; }
<INITIAL>"SUBCW"   { yylval.txt = (char *)0; return TOK_SUBCW; }
<INITIAL>"SUBCL"   { yylval.txt = (char *)0; return TOK_SUBCL; }
<INITIAL>"SUB2B"   { yylval.txt = (char *)0; return TOK_SUB2B; }
<INITIAL>"SUB2W"   { yylval.txt = (char *)0; return TOK_SUB2W; }
<INITIAL>"SUB2L"   { yylval.txt = (char *)0; return TOK_SUB2L; }
<INITIAL>"SUBC2B"  { yylval.txt = (char *)0; return TOK_SUBC2B; }
<INITIAL>"SUBC2W"  { yylval.txt = (char *)0; return TOK_SUBC2W; }
<INITIAL>"SUBC2L"  { yylval.txt = (char *)0; return TOK_SUBC2L; }
<INITIAL>"NEGB"    { yylval.txt = (char *)0; return TOK_NEGB; }
<INITIAL>"NEGW"    { yylval.txt = (char *)0; return TOK_NEGW; }
<INITIAL>"NEGL"    { yylval.txt = (char *)0; return TOK_NEGL; }
<INITIAL>"NEGCB"   { yylval.txt = (char *)0; return TOK_NEGCB; }
<INITIAL>"NEGCW"   { yylval.txt = (char *)0; return TOK_NEGCW; }
<INITIAL>"NEGCL"   { yylval.txt = (char *)0; return TOK_NEGCL; }
<INITIAL>"DECW"    { yylval.txt = (char *)0; return TOK_DECW; }
<INITIAL>"EXTW"    { yylval.txt = (char *)0; return TOK_EXTW; }
<INITIAL>"ANDB"    { yylval.txt = (char *)0; return TOK_ANDB; }
<INITIAL>"ANDW"    { yylval.txt = (char *)0; return TOK_ANDW; }
<INITIAL>"ANDL"    { yylval.txt = (char *)0; return TOK_ANDL; }
<INITIAL>"ORB"     { yylval.txt = (char *)0; return TOK_ORB; }
<INITIAL>"ORW"     { yylval.txt = (char *)0; return TOK_ORW; }
<INITIAL>"ORL"     { yylval.txt = (char *)0; return TOK_ORL; }
<INITIAL>"XORB"    { yylval.txt = (char *)0; return TOK_XORB; }
<INITIAL>"XORW"    { yylval.txt = (char *)0; return TOK_XORW; }
<INITIAL>"XORL"    { yylval.txt = (char *)0; return TOK_XORL; }
<INITIAL>"MSKB"    { yylval.txt = (char *)0; return TOK_MSKB; }
<INITIAL>"MSKW"    { yylval.txt = (char *)0; return TOK_MSKW; }
<INITIAL>"MSKL"    { yylval.txt = (char *)0; return TOK_MSKL; }
<INITIAL>"BANDB"   { yylval.txt = (char *)0; return TOK_BANDB; }
<INITIAL>"BANDW"   { yylval.txt = (char *)0; return TOK_BANDW; }
<INITIAL>"BANDL"   { yylval.txt = (char *)0; return TOK_BANDL; }
<INITIAL>"BORB"    { yylval.txt = (char *)0; return TOK_BORB; }
<INITIAL>"BORW"    { yylval.txt = (char *)0; return TOK_BORW; }
<INITIAL>"BORL"    { yylval.txt = (char *)0; return TOK_BORL; }
<INITIAL>"BXORB"   { yylval.txt = (char *)0; return TOK_BXORB; }
<INITIAL>"BXORW"   { yylval.txt = (char *)0; return TOK_BXORW; }
<INITIAL>"BXORL"   { yylval.txt = (char *)0; return TOK_BXORL; }
<INITIAL>"BMSKB"   { yylval.txt = (char *)0; return TOK_BMSKB; }
<INITIAL>"BMSKW"   { yylval.txt = (char *)0; return TOK_BMSKW; }
<INITIAL>"BMSKL"   { yylval.txt = (char *)0; return TOK_BMSKL; }
<INITIAL>"NOTB"    { yylval.txt = (char *)0; return TOK_NOTB; }
<INITIAL>"NOTW"    { yylval.txt = (char *)0; return TOK_NOTW; }
<INITIAL>"NOTL"    { yylval.txt = (char *)0; return TOK_NOTL; }
<INITIAL>"TSTB"    { yylval.txt = (char *)0; return TOK_TSTB; }
<INITIAL>"TSTW"    { yylval.txt = (char *)0; return TOK_TSTW; }
<INITIAL>"TSTL"    { yylval.txt = (char *)0; return TOK_TSTL; }
<INITIAL>"LSHB"    { yylval.txt = (char *)0; return TOK_LSHB; }
<INITIAL>"LSHW"    { yylval.txt = (char *)0; return TOK_LSHW; }
<INITIAL>"LSHL"    { yylval.txt = (char *)0; return TOK_LSHL; }
<INITIAL>"RSHB"    { yylval.txt = (char *)0; return TOK_RSHB; }
<INITIAL>"RSHW"    { yylval.txt = (char *)0; return TOK_RSHW; }
<INITIAL>"RSHL"    { yylval.txt = (char *)0; return TOK_RSHL; }
<INITIAL>"MUL"     { yylval.txt = (char *)0; return TOK_MUL; }
<INITIAL>"DIV"     { yylval.txt = (char *)0; return TOK_DIV; }
<INITIAL>"NOP"     { yylval.txt = (char *)0; return TOK_NOP; }

<INITIAL>"T_SR"    { yylval.txt = (char *)0; return TOK_T_SR; }
<INITIAL>"S_SR"    { yylval.txt = (char *)0; return TOK_S_SR; }
<INITIAL>"A_SR"    { yylval.txt = (char *)0; return TOK_A_SR; }
<INITIAL>"I_SR"    { yylval.txt = (char *)0; return TOK_I_SR; }
<INITIAL>"B_SR"    { yylval.txt = (char *)0; return TOK_B_SR; }
<INITIAL>"X_SR"    { yylval.txt = (char *)0; return TOK_X_SR; }
<INITIAL>"N_SR"    { yylval.txt = (char *)0; return TOK_N_SR; }
<INITIAL>"V_SR"    { yylval.txt = (char *)0; return TOK_V_SR; }
<INITIAL>"CIN"     { yylval.txt = (char *)0; return TOK_CIN; }
<INITIAL>"CLR"     { yylval.txt = (char *)0; return TOK_CLR; }
<INITIAL>"C_ADD"   { yylval.txt = (char *)0; return TOK_C_ADD; }
<INITIAL>"C_FLG"   { yylval.txt = (char *)0; return TOK_C_FLG; }
<INITIAL>"Z_FLG"   { yylval.txt = (char *)0; return TOK_Z_FLG; }
<INITIAL>"N_FLG"   { yylval.txt = (char *)0; return TOK_N_FLG; }
<INITIAL>"G_FLG"   { yylval.txt = (char *)0; return TOK_G_FLG; }
<INITIAL>"N_B"     { yylval.txt = (char *)0; return TOK_N_B; }
<INITIAL>"N_W"     { yylval.txt = (char *)0; return TOK_N_W; }
<INITIAL>"T0"      { yylval.txt = (char *)0; return TOK_T0; }
<INITIAL>"T7"      { yylval.txt = (char *)0; return TOK_T7; }
<INITIAL>"T15"     { yylval.txt = (char *)0; return TOK_T15; }
<INITIAL>"N0"      { yylval.txt = (char *)0; return TOK_N0; }
<INITIAL>"N7"      { yylval.txt = (char *)0; return TOK_N7; }
<INITIAL>"N15"     { yylval.txt = (char *)0; return TOK_N15; }
<INITIAL>"EA1_4"   { yylval.txt = (char *)0; return TOK_EA1_4; }
<INITIAL>"EA1_7"   { yylval.txt = (char *)0; return TOK_EA1_7; }
<INITIAL>"EXT_11"  { yylval.txt = (char *)0; return TOK_EXT11; }

<INITIAL>"EA1L"    { yylval.txt = (char *)0; return TOK_EA1L; }
<INITIAL>"EA1H"    { yylval.txt = (char *)0; return TOK_EA1H; }
<INITIAL>"EA2L"    { yylval.txt = (char *)0; return TOK_EA2L; }
<INITIAL>"EA2H"    { yylval.txt = (char *)0; return TOK_EA2H; }
<INITIAL>"PCL"     { yylval.txt = (char *)0; return TOK_PCL; }
<INITIAL>"PCH"     { yylval.txt = (char *)0; return TOK_PCH; }
<INITIAL>"PC"      { yylval.txt = (char *)0; return TOK_PC; }
<INITIAL>"CPUS"    { yylval.txt = (char *)0; return TOK_CPUS; }
<INITIAL>"VECL"    { yylval.txt = (char *)0; return TOK_VECL; }
<INITIAL>"VECH"    { yylval.txt = (char *)0; return TOK_VECH; }
<INITIAL>"VEC"     { yylval.txt = (char *)0; return TOK_VEC; }
<INITIAL>"LSHR"    { yylval.txt = (char *)0; return TOK_LSHR; }
<INITIAL>"ACCL"    { yylval.txt = (char *)0; return TOK_ACCL; }
<INITIAL>"ACCH"    { yylval.txt = (char *)0; return TOK_ACCH; }
<INITIAL>"IMMR"    { yylval.txt = (char *)0; return TOK_IMMR; }
<INITIAL>"DECJ"    { yylval.txt = (char *)0; return TOK_DECJ; }
<INITIAL>"EA1J"    { yylval.txt = (char *)0; return TOK_EA1J; }
<INITIAL>"EA2J"    { yylval.txt = (char *)0; return TOK_EA2J; }
<INITIAL>"EA1B"    { yylval.txt = (char *)0; return TOK_EA1B; }
<INITIAL>"EA2B"    { yylval.txt = (char *)0; return TOK_EA2B; }
<INITIAL>"SR"      { yylval.txt = (char *)0; return TOK_SR; }
<INITIAL>"T"       { yylval.txt = (char *)0; return TOK_RT; }
<INITIAL>"N"       { yylval.txt = (char *)0; return TOK_RN; }
<INITIAL>"DL"      { yylval.txt = (char *)0; return TOK_RDL; }
<INITIAL>"DH"      { yylval.txt = (char *)0; return TOK_RDH; }
<INITIAL>"AL"      { yylval.txt = (char *)0; return TOK_RAL; }
<INITIAL>"AH"      { yylval.txt = (char *)0; return TOK_RAH; }
<INITIAL>"RL"      { yylval.txt = (char *)0; return TOK_RL; }
<INITIAL>"RH"      { yylval.txt = (char *)0; return TOK_RH; }
<INITIAL>"EA1"     { yylval.txt = (char *)0; return TOK_EA1; }
<INITIAL>"EA2"     { yylval.txt = (char *)0; return TOK_EA2; }
<INITIAL>"CNT"     { yylval.txt = (char *)0; return TOK_CNT; }
<INITIAL>"EXT"     { yylval.txt = (char *)0; return TOK_EXT; }
<INITIAL>"VBRL"    { yylval.txt = (char *)0; return TOK_VBRL; }
<INITIAL>"VBRH"    { yylval.txt = (char *)0; return TOK_VBRH; }
<INITIAL>"TMP1L"   { yylval.txt = (char *)0; return TOK_TMP1L; }
<INITIAL>"TMP2L"   { yylval.txt = (char *)0; return TOK_TMP2L; }
<INITIAL>"TMP1H"   { yylval.txt = (char *)0; return TOK_TMP1H; }
<INITIAL>"TMP2H"   { yylval.txt = (char *)0; return TOK_TMP2H; }
<INITIAL>"USPL"    { yylval.txt = (char *)0; return TOK_USPL; }
<INITIAL>"USPH"    { yylval.txt = (char *)0; return TOK_USPH; }
<INITIAL>"SSPL"    { yylval.txt = (char *)0; return TOK_SSPL; }
<INITIAL>"SSPH"    { yylval.txt = (char *)0; return TOK_SSPH; }
<INITIAL>"A7L"     { yylval.txt = (char *)0; return TOK_A7L; }
<INITIAL>"A7H"     { yylval.txt = (char *)0; return TOK_A7H; }

<INITIAL>"ORG"     { yylval.txt = (char *)0; return TOK_ORG; }
<INITIAL>"TABLE"   { yylval.txt = (char *)0; return TOK_TABLE; }

<INITIAL>[\-*#01]{5} {
  int mask = 0;
  int i;
  int j;

  /* XNZVC flags mask */
  for (i = 0, j = 9; i < 5; i++, j-=2)
  {
    switch(yytext[i])
    {
      case '*':
      {
        mask |= (1 << j);
        break;
      }
      case '0':
      {
        mask |= (2 << j);
        break;
      }
      case '1':
      {
        mask |= (3 << j);
        break;
      }
      case '#':
      {
        mask |= (5 << j);
        break;
      }
    }
    if (j == 7) j--;
  }
  yylval.val = mask;
  return TOK_MASK;
}

<INITIAL>[\[\]\.\-+()#,:=] { /* Separators */ return yytext[0]; }

<INITIAL>[0-9]+ {
  /* Decimal number */
  sscanf(yytext, "%d", &yylval.val);
  return TOK_NUMBER;
}

<INITIAL>"$"[0-9a-fA-F]+ {
  /* Hexadecimal number */
  sscanf(yytext, "$%x", &yylval.val);
  return TOK_NUMBER;
}

<INITIAL>[a-zA-Z][a-zA-Z0-9_]* {
  /* Identifier */
  yylval.txt = (char *)malloc(strlen(yytext)+1);
  strcpy(yylval.txt, yytext);
  return TOK_IDENT;
}

%%

void yyerror(char *s){
  fprintf(stderr,"%s at \"%s\" in line %d.\n\n", s, yytext, line_num);
}
