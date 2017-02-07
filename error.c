/****************************************************************/
/* This module supplies routines for error handling.		*/
/* Upon error detection, the corresponding error message is	*/
/* printed on the screen.                                	*/
/* - signal_error(): it signals lexical, syntax and semantic	*/
/*		     errors;					*/
/* - signal_warning(): it signals warnings.			*/
/****************************************************************/


/****************************************************************/
/* 1. Inclusion of header files.				*/
/****************************************************************/

#include "bohm.h"

#include <stdio.h>

/****************************************************************/
/* 2. Inclusion of declarations that are being imported.        */
/****************************************************************/


/****************************************************************/
/* 3. Definitions of variables to be exported.			*/
/****************************************************************/

BOOLEAN			error_detected;
			      /* flag indicating whether an */
			      /* error has been detected */

/****************************************************************/
/* 4. Definitions of variables strictly local to the module.	*/
/****************************************************************/

/* compile time error messages */
HIDDEN STRING		error_msgs[] = {
  "lexical error: illegal character",
  "lexical error: numerical constant overflow",
  "syntax error: identifier expected after let",
  "syntax error: bad expression in declaration",
  "syntax error: = expected after identifier in declaration",
  "syntax error",
  "syntax error: missing closed bracket",
  "syntax error: identifier expected after lambda",
  "syntax error: identifier expected after let in expression",
  "syntax error: bad expression in assignement of let_in expression",
  "syntax error: bad expression in body of let_in expression",
  "syntax error: bad expression",
  "syntax error: = expected after identifier in let_in expression",
  "syntax error: bad application",
  "scoping error: undefined variable"
};

/* warning messages */
HIDDEN STRING		warning_msgs[] = {
  "warning: variable already declared"
};

/****************************************************************/
/* 5. Definitions of functions to be exported.			*/
/****************************************************************/

 /* The following function signals lexical, syntax and semantic */
 /* errors. */
void signal_error(error_msg_num)
	int		error_msg_num;
					/* error message number */
{
	error_detected = TRUE;
	fprintf(stderr,
		"line %-5d\t--->\t%s\n",
		lines,
		error_msgs[error_msg_num]);
}

 /* The following function signals warnings. */
void signal_warning(warning_msg_num)
	int		warning_msg_num;
					/* warning message number */
{
	fprintf(stderr,
		"line %-5d\t--->\t%s\n",
		lines,
		warning_msgs[warning_msg_num]);
}


/****************************************************************/
/* 6. Definitions of functions strictly local to the module.	*/
/****************************************************************/


