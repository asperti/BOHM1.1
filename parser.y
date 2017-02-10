 /***************************************************************/
 /* This module is the YACC_specification of the parser.        */
 /* All inputs must be terminated by a double simicolon         */
 /* An input is either a term or a directive.                   */
 /* A term can be a global definition of the kind               */
 /*  - def <identifier> = <expr> in <expr>                      */
 /* or a single expression.                                     */
 /*                                                             */
 /* Expressions are syntactically defined by the following      */
 /* grammar:                                                    */
 /*                                                             */
 /*  <expr> ::= <expr0>                                         */
 /*     |  <expr> < <expr>                                      */
 /*     |  <expr> == <expr>                                     */
 /*     |  <expr> > <expr>                                      */
 /*     |  <expr> <= <expr>                                     */
 /*     |  <expr> >= <expr>                                     */
 /*     |  <expr> <> <expr>                                     */
 /*     |  <expr> + <expr>                                      */
 /*     |  <expr> - <expr>                                      */
 /*     |  <expr> * <expr>                                      */
 /*     |  <expr> div <expr>                                    */
 /*     |  <expr> mod <expr>                                    */
 /*     |  - <expr>   	                                        */
 /*     |  <expr> < <expr>                                      */
 /*     |  <expr> == <expr>                                     */
 /*     |  <expr> > <expr>                                      */
 /*     |  <expr> <= <expr>                                     */
 /*     |  <expr> >= <expr>                                     */
 /*     |  <expr> <> <expr>                                     */
 /*     |  <expr> + <expr>                                      */
 /*     |  <expr> - <expr>                                      */
 /*     |  <expr> * <expr>                                      */
 /*     |  <expr> div <expr>                                    */
 /*     |  <expr> mod <expr>                                    */
 /*                                                             */
 /*  <expr0> ::= true                                           */
 /*     |  false                                                */
 /*     |  <num\_const>                                         */
 /*     |  <identifier>                                         */
 /*     |  (<applist>)                                          */
 /*     |  \ <pattern> . <expr>                                 */
 /*     |  let <identifier> = <expr> in  <expr>                 */
 /*     |  letrec <identifier> = <expr>                         */
 /*     |  if <expr> then  <expr> else  <expr>                  */
 /*     |  <expr> and  <expr>                                   */
 /*     |  <expr> or  <expr>                                    */
 /*     |  not <expr>                                           */
 /*     |  <list>                                               */
 /*     |  cons (<expr>,<expr>)                                 */ 
 /*     |  head (<expr>)                                        */
 /*     |  tail (<expr>)                                        */
 /*     |  isnil (<expr>)                                       */
 /*  <list> ::= nil                                             */
 /*     | [<exprlist>]                                          */
 /*  <exprlist> ::=        (* empty *)                          */
 /*     | <expr>                                                */
 /*     | <expr>,<exprlist>                                     */
 /*     | <expr>|<expr>                                         */
 /*  <applist> ::= <expr>                                       */
 /*     |  <applist> <expr0>                                    */
 /*     |  <expr>,<comlist>                                     */
 /*  <comlist> ::= <expr>                                       */
 /*     |  <expr>,<comlist>                                     */
 /*  <pattern> ::= <identifier>                                 */
 /*     |  cons(<pattern>,<pattern>)                            */
 /*     |  (<comlistpat>)                                       */
 /*  <comlistpat> ::= <pattern>                                 */
 /*     |  <pattern>,<comlistpat>                               */
 /*                                                             */
 /* The <expr0> nonterminal represents an expression which      */
 /* cannot start with a minus sign.                             */
 /* (comlist) is represents a tuple; tuples are                 */
 /* currently implemented as non-nil-terminated lists.          */
 /*                                                             */
 /* Each directive must be preceded by the symbol "#".          */
 /* There are seven directives:                                 */
 /*  - inspect  to enter inspection mode (the name of a         */
 /*             globally defined term to inspect can be passed  */
 /*             as a parameter; otherwise, inspection of the    */
 /*             last compiled term is assumed).                 */
 /*  - save	to save the graph of a term in a file.		*/
 /*		The first identifier is the file name, the 	*/
 /*		second is the term (if the latter does not 	*/
 /*             exist, the last term is taken).                 */
 /*  - quit     to exit from the compiler.                      */
 /*  - load     to load an external file; the file name must    */
 /*             be specified as a normal idenitifier            */
 /*  - garbage  to invoke gargabe collection                    */
 /*  - option   to choose a grabge collection strategy          */
 /*  - info     to get general informations on the computation  */
 /***************************************************************/

 /***************************************************************/
 /* 1. Inclusion of header files.				*/
 /***************************************************************/

%{
#include "bohm.h"

#include <stdio.h>
#include <stdlib.h>
%}


 /***************************************************************/
 /* 2. Inclusion of declarations that are being imported.	*/
 /***************************************************************/

%{
int yyerror(const char *msg);
%}

 /***************************************************************/
 /* 3. Definitions of variables to be exported.			*/
 /***************************************************************/

%{
bool			quit,
			       /* flag indicating quit request */
			loading_mode;
			       /* flag indicating if parsing is */
			       /* done after a load directive */
char                    *include_file;
FORM                    *lastinputterm;
			       /* pointer to the root of the */
			       /* term in input */
%}

 /***************************************************************/
 /* 4. Definitions strictly local to the module.                */
 /***************************************************************/

%{
#define UNBOUND_VARIABLE "scoping error: undefined variable"

int                    app_nesting_depth;
PATTERN                *pattmp;

static bool defined();
%}

 /***************************************************************/
 /* 5. Definition of grammar symbols attributes.		*/
 /***************************************************************/

%union	{
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
	}


 /***************************************************************/
 /* 6. Definitions of tokens.					*/
 /***************************************************************/

%token				EXPRDELIM      257
%token	<st_bucket>		ID	       258
%token	<num_const>		NUMCONST       259
%token				EQUAL          260
%token				LEQUAL         261
%token				MEQUAL         262
%token				NOTEQUAL       263
%token				LETKW	       400
%token				INKW           401
%token                          INSPECTKW      402
%token                          QUITKW         403
%token                          LOADKW         404
%token				LETRECKW       405
%token				TRUEKW         406
%token				FALSEKW        407
%token				IFKW           408
%token				THENKW         409
%token				ELSEKW         410
%token				ANDKW          411
%token				ORKW           412
%token				NOTKW          413
%token				DIVKW          414
%token				MODKW          415
%token				CONSKW         416
%token			        HEADKW         417
%token				TAILKW         418
%token				TESTNILKW      419
%token				DEFKW          420
%token				NILKW          422
%token				GARBAGEKW      423
%token				OPTIONKW       424
%token				INFOKW         425
%token				SAVEKW         426
%token <astring>                ASTRING        427



 /***************************************************************/
 /* 7. Association of attributes with nonterminals.		*/
 /***************************************************************/

%type	<root>		        input
%type	<root>		        directive
%type	<root>		        arg
%type	<root>		        term
%type	<root>		        global_decl
%type	<term>			expr
%type   <term>                  expr0
%type	<term>			applist
%type	<term>			comlist
%type	<term>			exprlist
%type	<term>			list
%type   <pattern>               pattern
%type   <pattern>               comlistpat


 /***************************************************************/
 /* 8. Precedence and associativity of operators.		*/
 /***************************************************************/

%nonassoc ELSEKW INKW '.' '='
%left ANDKW ORKW
%left NOTKW
%left '<' '>' EQUAL LEQUAL MEQUAL NOTEQUAL
%left '+' '-'
%left '*' DIVKW MODKW
%left NEG

 /***************************************************************/
 /* 9. Definition of the start symbol.				*/
 /***************************************************************/


%start			input


 /***************************************************************/
 /* 10. Grammar rules.						*/
 /***************************************************************/

%%

input           :      directive
		|               {
				   app_nesting_depth = 0;
				   destroy();
				   lastinputterm=NULL;
				}
		       term
				{
				   $$ = $2;
				}
		|        
				{
				   printf("no more input");
				   quit = true;
				   YYACCEPT;
				}
				; 

directive       :      '#' INSPECTKW arg EXPRDELIM
				{
				   $$ = $3;
				   inspect_driver($3);
				   YYACCEPT;
				}
		|      '#' QUITKW EXPRDELIM
				{
				   quit = true;
				   YYACCEPT;
				}
		|      '#' LOADKW ASTRING EXPRDELIM
				{
				  include_file = $3;
				  loading_mode = true;
				  printf("%s", include_file);
				  YYACCEPT;
				}
		|       '#' GARBAGEKW EXPRDELIM
				{
				   user();
				   YYACCEPT;
				}
		|       '#' OPTIONKW EXPRDELIM
				{
				   menu();
				   YYACCEPT;
				}
		|       '#' INFOKW EXPRDELIM
				{
				   info();
				   YYACCEPT;
				}
		|       '#' SAVEKW ASTRING EXPRDELIM
				{
				   save($3,lastinputterm,NULL);
                                   free($3);
				   YYACCEPT;
				}
		|       '#' SAVEKW ASTRING ID EXPRDELIM
				{
				   if (defined($4))
				      save($3,$4->curr_binding->root,$4->id);
				   else
				      {
					 signal_error(UNBOUND_VARIABLE);
					 YYACCEPT;
				      }
                                   free($3);
				   YYACCEPT;
				}
		;

arg             :
				{
				   $$ = lastinputterm;
				}
		|       ID
				{
				   if (defined($1))
				      $$ = $1->curr_binding->root;
				   else
				      {
					 signal_error(UNBOUND_VARIABLE);
					 YYACCEPT;
				      }
				 }
		;

term            :       expr EXPRDELIM
				{
				  lastinputterm = closeterm(0,$1);
				  $$ = lastinputterm;
				  reduce_term($$);
				  YYACCEPT;
				}
		|       global_decl EXPRDELIM
				{
				  no_destroy();
				  YYACCEPT;
				}
		;



global_decl	:    DEFKW ID '='
				{
				  app_nesting_depth++;
				}
		     expr
				{
				  app_nesting_depth--;
				  lastinputterm = closeterm(1,$5);
				  $$ = lastinputterm;
				  create_variable_binding($2,$$);
				}
		;

expr            :       expr0
                                {
                                  $$ = $1;
                                }
		|	'-' expr %prec NEG
				{
		 		  $$ = buildminusterm(app_nesting_depth, $2);
				}
		 |	expr ANDKW expr
				{
				  $$ = buildandterm(app_nesting_depth,
						       $1,$3);
				}
		 |	expr ORKW expr
				{
				  $$ = buildorterm(app_nesting_depth,
						       $1,$3);
				}
		 |	expr '<' expr
		 		{
		 		  $$ = buildrelopterm(app_nesting_depth,
		 		  		       $1,$3,LESS);
		 		}
		 |	expr EQUAL expr
		 		{
		 		  $$ = buildrelopterm(app_nesting_depth,
		 		  		       $1,$3,EQ);
		 		}
		 |	expr NOTEQUAL expr
		 		{
				  $$ = buildrelopterm(app_nesting_depth,
		 		  		       $1,$3,NOTEQ);
		 		}
		 |	expr '>' expr
		 		{
		 		  $$ = buildrelopterm(app_nesting_depth,
		 		  		       $1,$3,MORE);
				}
		 |	expr LEQUAL expr
		 		{
		 		  $$ = buildrelopterm(app_nesting_depth,
		 		  		       $1,$3,LEQ);
		 		}
		 |	expr MEQUAL expr
		 		{
		 		  $$ = buildrelopterm(app_nesting_depth,
		 		  		       $1,$3,MEQ);
		 		}
		 |	expr '+' expr
				{
				  $$ = buildmatterm(app_nesting_depth,
		 		  		       $1,$3,ADD);
				}
		 |	expr '-' expr
				{
		 		  $$ = buildmatterm(app_nesting_depth,
		 		  		       $1,$3,SUB);
				}
		 |	expr '*' expr
				{
		 		  $$ = buildmatterm(app_nesting_depth,
		 		  		       $1,$3,PROD);
				}
		 |	expr DIVKW expr
				{
		 		  $$ = buildmatterm(app_nesting_depth,
		 		  		       $1,$3,DIV);
				}
		 |	expr MODKW expr
				{
				  $$ = buildmatterm(app_nesting_depth,
		 		  		       $1,$3,MOD);
		 		}
                ;

expr0           : 	TRUEKW
				{
				  $$ = buildtrueterm(app_nesting_depth);
				}
		| 	FALSEKW
				{
				  $$ = buildfalseterm(app_nesting_depth);
				}
		| 	NUMCONST
				{
				  $$ = buildintterm(app_nesting_depth,$1);
				}
		|       ID
				{
				  if (defined($1))
				     $$ = buildvarterm(app_nesting_depth,$1);
				  else
				     {
					signal_error(UNBOUND_VARIABLE);
					YYERROR;
				     }
				}
		|       '(' applist ')'
				{
				  $$ = $2;
				}
		|       '\\' 
				{
				  push_local_env();
                                  app_nesting_depth++;
				}
			pattern 
                                {
                                  app_nesting_depth--;
                                }
                        '.' expr
				{
                                  pattmp=$3;
                                  $$ = 
                                    buildplambdaterm(app_nesting_depth,$3,$6);
                                  free_pattern(pattmp);
				  pop_local_env();
				}
		|       LETKW ID '='
				{
				  app_nesting_depth++;
				}
			expr INKW
				{
				  app_nesting_depth--;
				  push_local_env();
				  create_variable_binding($2, NULL);
				}
			expr
				{
				  $$ = buildletinterm(app_nesting_depth,
						      $2,$5,$8);
				  pop_local_env();
				}
		 |	LETRECKW ID '='
				{
				  push_local_env();
				  create_variable_binding($2, NULL);
				  app_nesting_depth++;
				 }
			expr
				{
				  $$ = build_mu_term(--app_nesting_depth,
						     $2,$5);
				  pop_local_env();
				 }
		 |	IFKW expr THENKW expr ELSEKW expr
				{
				  $$ = buildifelseterm(app_nesting_depth,
						       $2,$4,$6);
				}
		 |	list
				{
				  $$ = $1;
				}

		 |	NOTKW expr
		 		{
				  $$ = buildnotterm(app_nesting_depth,
		 		  		       $2);
				}
		 |	CONSKW '(' expr ',' expr ')'
				{
		 		  $$ = buildlist(app_nesting_depth,
		 		  		       $3,$5);
		 		}	
		 |	HEADKW '(' expr ')'
				{
		 		  $$ = buildcarterm(app_nesting_depth,
		 		  		       $3);
		 		}
		 |	TAILKW '(' expr ')'
				{
				  $$ = buildcdrterm(app_nesting_depth,
		 		  		       $3);
		 		}
		 |	TESTNILKW '(' expr ')'
				{
		 		  $$ = buildtestnil(app_nesting_depth,
		 		  		       $3);
				}
                 ;

list		 :	NILKW
				{
				  $$ = buildnillist(app_nesting_depth);
				}
		 |      '[' ']'
                                {
                                  $$ = buildnillist(app_nesting_depth);
				}
		 |	'[' exprlist
				{
				  $$ = $2;
				}
		 ;
exprlist	:	expr ']'
				{
				  $$ = buildlist(app_nesting_depth,
						$1,NULL);
				}
		|	expr ',' exprlist
				{
				  $$ = buildlist(app_nesting_depth,
						$1,$3);
				}
		|       expr '|' expr ']'
				{
				  $$ = buildlist(app_nesting_depth,
						 $1,$3);
				}
		;

applist         :       expr
                |       expr ',' comlist
                                {
		 		  $$ = buildlist(app_nesting_depth,
		 		  		       $1,$3);
                                }
		|       applist
				{
				  app_nesting_depth++;
				}
			expr0
				{ app_nesting_depth--;
				  $$ = buildappterm(app_nesting_depth,$1,$3);
				}
		;


comlist         :       expr
                                {
                                  $$=$1;
                                }
                |       expr ',' comlist
                                {
		 		  $$ = buildlist(app_nesting_depth,
		 		  		       $1,$3);
                                }


comlistpat      :       pattern
                                {
                                  $$=$1;
                                }
                |       pattern ',' comlistpat
                                {
                                  pattmp=(PATTERN *)malloc(sizeof(PATTERN));
                                  pattmp->term=
                                    buildlist1(app_nesting_depth,
                                              $1->term,$3->term);
                                  pattmp->var_list=
                                    mergevarlist($1->var_list,$3->var_list);
                                  free($1);
                                  free($3);
                                  $$=pattmp;
                                }

pattern         :       CONSKW '(' pattern ',' pattern ')'
                                {
                                  pattmp=(PATTERN *)malloc(sizeof(PATTERN));
                                  pattmp->term=
                                    buildlist1(app_nesting_depth,
                                              $3->term,$5->term);
                                  pattmp->var_list=
                                    mergevarlist($3->var_list,$5->var_list);
                                  free($3);
                                  free($5);
                                  $$=pattmp;
                                }
                |       NILKW
                                {
                                  pattmp=(PATTERN *)malloc(sizeof(PATTERN));
                                  pattmp->term=buildnillist(app_nesting_depth);
                                  pattmp->var_list=NULL;
                                  $$=pattmp;
                                }
                |       '(' comlistpat ')'
                                {
                                  $$=$2;
                                }
                |       ID
                                {
                                  pattmp=(PATTERN *)malloc(sizeof(PATTERN));
                                  pattmp->term=
                                    buildvoidterm(app_nesting_depth);
                                  create_variable_binding($1, NULL);
                                  pattmp->var_list=
                                    makevarlist($1,pattmp->term);
                                  $$=pattmp;
                                }

term    	:	error  EXPRDELIM
                                {
                                  error_detected = true;
                                  yyerrok;
                                  YYACCEPT;
				}
		;

%%

/* The following function checks if an identifier has been */
/* previously declared */
static bool defined(st)
	STBUCKET	*st;
			      /* pointer to the bucket for the */
			      /* identifier */
{
        return((st->curr_binding) != NULL);
}
