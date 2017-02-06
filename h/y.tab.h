/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    EXPRDELIM = 257,
    ID = 258,
    NUMCONST = 259,
    EQUAL = 260,
    LEQUAL = 261,
    MEQUAL = 262,
    NOTEQUAL = 263,
    EOFKW = 264,
    LETKW = 400,
    INKW = 401,
    INSPECTKW = 402,
    QUITKW = 403,
    LOADKW = 404,
    LETRECKW = 405,
    TRUEKW = 406,
    FALSEKW = 407,
    IFKW = 408,
    THENKW = 409,
    ELSEKW = 410,
    ANDKW = 411,
    ORKW = 412,
    NOTKW = 413,
    DIVKW = 414,
    MODKW = 415,
    CONSKW = 416,
    HEADKW = 417,
    TAILKW = 418,
    TESTNILKW = 419,
    DEFKW = 420,
    SHAREKW = 421,
    NILKW = 422,
    GARBAGEKW = 423,
    OPTIONKW = 424,
    INFOKW = 425,
    SAVEKW = 426,
    ASTRING = 427,
    NEG = 429
  };
#endif
/* Tokens.  */
#define EXPRDELIM 257
#define ID 258
#define NUMCONST 259
#define EQUAL 260
#define LEQUAL 261
#define MEQUAL 262
#define NOTEQUAL 263
#define EOFKW 264
#define LETKW 400
#define INKW 401
#define INSPECTKW 402
#define QUITKW 403
#define LOADKW 404
#define LETRECKW 405
#define TRUEKW 406
#define FALSEKW 407
#define IFKW 408
#define THENKW 409
#define ELSEKW 410
#define ANDKW 411
#define ORKW 412
#define NOTKW 413
#define DIVKW 414
#define MODKW 415
#define CONSKW 416
#define HEADKW 417
#define TAILKW 418
#define TESTNILKW 419
#define DEFKW 420
#define SHAREKW 421
#define NILKW 422
#define GARBAGEKW 423
#define OPTIONKW 424
#define INFOKW 425
#define SAVEKW 426
#define ASTRING 427
#define NEG 429

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 166 "lambda_parser.y" /* yacc.c:1909  */

		STBUCKET	*st_bucket;
					/* pointer to a symbol */
					/* table bucket */
		int		num_const;
					/* numerical constant */
		TERM		*term;
					/* graph representation */
					/* of the term */
		FORM		*root;
					/* root_form  */
                char            *astring;
                PATTERN         *pattern;
	

#line 148 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
