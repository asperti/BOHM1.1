/****************************************************************/
/*	       	     	    LAMBDA_LEXAN.E 			*/
/****************************************************************/


/****************************************************************/
/* 1. Declarations of variables.				*/
/****************************************************************/

extern FILE		*yyin;

extern int		yyleng,
			lines;

/****************************************************************/
/* 2. Declarations of functions.				*/
/****************************************************************/

extern int		yylex();

typedef struct yy_buffer_state *YY_BUFFER_STATE;
extern YY_BUFFER_STATE yy_create_buffer (FILE *file,int size);
extern void yypush_buffer_state (YY_BUFFER_STATE new_buffer);
extern void yypop_buffer_state (void);