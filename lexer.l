 /***************************************************************/
 /* This module is the lex specification of the lexical         */
 /* analyzer.			                                */
 /* It is able to recognize the following tokens:		*/
 /* - ID: a sequence of letters and digits beginning with a     */
 /*	  letter, and possibly containing one or more           */
 /*       occurrences of "/".                                   */
 /*       The pointer to the symbol table bucket 	        */
 /*       associated with the identifier is returned in yylval; */
 /*	  keywords are treated as special identifiers           */
 /*	  (to limit the automaton space complexity),	        */
 /*	  each of which has a corresponding token;		*/
 /*       (see also the symbol table handler)                   */
 /* - NUMCONST: (unused) a sequence of digits; its numerical    */
 /*		value is returned in yylval;			*/
 /* - CHARCONST: a character other than single quote sorrounded */
 /*		 by single quotes; the character itself is	*/
 /*		 returned in yylval;				*/
 /* - STRINGCONST: a sequence of characters, all lying in a	*/
 /*		   line and different from single quote,	*/
 /*		   sorrounded by single quotes; the pointer to	*/
 /*		   the first character of the string is		*/
 /*		   returned in yylval;				*/
 /* - EXPRDELIM: the symbol ';;'				*/
 /* - One character tokens: '=', '(' ')' '\' and '#'. 		*/
 /*   The character itself is passed to the parser.             */
 /*                                                             */
 /* Comments must be enclosed in "{" and "}".                   */
 /***************************************************************/


 /***************************************************************/
 /* 1. Inclusion of header files.				*/
 /***************************************************************/

%{
#include "bohm.h"
#include "y.tab.h"

#include <stdlib.h>
#include <string.h>
%}


 /***************************************************************/
 /* 2. Inclusion of declarations that are being imported.	*/
 /***************************************************************/


 /***************************************************************/
 /* 3. Definitions of variables and functions.                  */
 /***************************************************************/

%{
int lines, astringlen;

static int to_nat_s(char *s);
%}

 /***************************************************************/
 /* 4. Regular definitions.					*/
 /***************************************************************/

letter			[A-Za-z\_]
digit			[0-9]
illegal_char		[^A-Za-z0-9 \t\n\/;.=()#\\+<>\-\*\[\],\_]
id			{letter}(\/|{letter}|{digit})*
num			{digit}+
blanks			(" ")+
one_char_token          [=()\\.#+<>\-\*\[\],\|]
comment                 [^\}]*\}
string                  [^\"]*\"

 /***************************************************************/
 /* 5. Start Conditions.					*/
 /***************************************************************/

%option nounput
%option noinput

%start com
%start str              

 /***************************************************************/
 /* 6. Rules.							*/
 /***************************************************************/

%%

<com>{comment}     {
                        /* comment */
                        if (loading_mode == 1) ECHO; 
                        BEGIN 0;
                   }

"{"                {
                        /* comment beginning */
                        if (loading_mode == 1) ECHO; 
                        BEGIN com;
                   }

<str>{string}      {
                        if (loading_mode == 1) ECHO;
                        BEGIN 0;
                        astringlen=strlen(yytext);
                        yylval.astring=malloc(astringlen);
                        strncpy(yylval.astring,yytext,astringlen-1);
                        yylval.astring[astringlen-1]=0;
                        return ASTRING;
                    }
\"                 {
                        if (loading_mode == 1) ECHO;
                        BEGIN str;
                   }

{blanks}	   {
			/* sequence of blanks */
                        if (loading_mode == 1) ECHO; 
		   }

\t		   {
			/* tab */
                        if (loading_mode == 1) ECHO; 
		   }

\n		   {
			/* newline */
                        if (loading_mode == 1) ECHO; 
                        lines++;
		   }

{id}		   {
			/* identifier */
                        if (loading_mode == 1) ECHO;
			search_bucket(&(yylval.st_bucket),
				       yytext);
			return(yylval.st_bucket->token);
		   }

{num}		   {
			/* integer */
                        if (loading_mode == 1) ECHO; 
			yylval.num_const = to_nat_s(yytext);
			return(NUMCONST);
		   }

{one_char_token}   {
			/* one-character token */
                        if (loading_mode == 1) ECHO; 
			return(yytext[0]);
		   }


";;"		   {
			/* end of expression  */
                        if (loading_mode == 1) ECHO; 
			return(EXPRDELIM);
		}

"=="		   {
                        if (loading_mode == 1) ECHO; 
			return(EQUAL);
		}

"<="		   {
                        if (loading_mode == 1) ECHO; 
			return(LEQUAL);
		}

">="		   {
                        if (loading_mode == 1) ECHO; 
			return(MEQUAL);
		}
"<>"		   {
                        if (loading_mode == 1) ECHO; 
			return(NOTEQUAL);
		}


{illegal_char}	{
			/* detection of an illegal character */
                        if (loading_mode == 1) ECHO; 
			signal_error("lexical error: illegal character");
                }

%%

#define MAXINT 2147483647

/* The following function turns a given string of digits into a natural */
/* and checks for presence of overflow. */
static int to_nat_s(char *s)
{
	long long n;

	for (n = 0; (n <= MAXINT) && (*s != '\0'); s++)
		n = 10 * n + (*s - '0');

	if (n > MAXINT)
		signal_error("lexical error: numerical constant overflow");

	return n;
}
