/****************************************************************/
/*		          LOADER.C          			*/
/****************************************************************/
/* This module implements the "load" directive, that is used 	*/
/* to load a source file.		                        */
/* There is only one external function:                         */
/*  - compile(): it changes the parser standard input and call  */
/* 		 the parser function.				*/
/****************************************************************/

/****************************************************************/
/* Inclusion of header files.       				*/
/****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "h/const.h"
#include "h/types.h"
#include "h/y.tab.h"
#include "e/lambda_lexan.e"
#include "e/lambda_parser.e"


/****************************************************************/
/* Definitions of functions to be exported.			*/
/****************************************************************/

  
/* The following function changes the parser standard 	*/
/* input and call the parser function.			*/
void compile(file)
     STRING  file;
{
     printf("\n******** loading file %s ********\n",file);
     yypush_buffer_state(yy_create_buffer( yyin, 16384));
     yyin = fopen(file,"r");
     if (yyin==NULL)
	   printf("Fatal Error: cannot open file %s.\n",file);
     else
	{
	   loading_mode = 1;
	   while ((quit == 0) && (error_detected == FALSE))
	     {
		yyparse();
	     }
	   if (error_detected == FALSE)
	      printf("\n******** %s loaded ********\n",file);
	   else
	      {
		 printf("\n***** loading file %s aborted *****\n",file);
		 error_detected = FALSE;
	      }
	   quit = 0;
	   loading_mode = 0;
	 }
     yypop_buffer_state();
}





