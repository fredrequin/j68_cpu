
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
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

/* Line 1676 of yacc.c  */
#line 350 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20\\microcode.y"

  char *txt;
  int   val;



/* Line 1676 of yacc.c  */
#line 235 "F:\\Repo_ip_core\\ip_cpu_j68\\tool\\microcode20/microcode.parser.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


