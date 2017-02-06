/****************************************************************/
/*		          CRASHHANDLER.C			*/
/****************************************************************/
/* This module supplies routines for unrecoverable error	*/
/* handling.							*/
/* It consists of the following function:			*/
/* signal_crash(): it prints on the screen the message		*/
/*		   corresponding to the unrecoverable error	*/
/*		   that occurred, then exits.			*/
/****************************************************************/


/****************************************************************/
/* 1. Inclusion of header files.				*/
/****************************************************************/

#include		"../h/const.h"
#include		"../h/types.h"
#include		<stdio.h>


/****************************************************************/
/* 2. Inclusion of declarations that are being imported.        */
/****************************************************************/


/****************************************************************/
/* 3. Definitions of variables to be exported.			*/
/****************************************************************/


/****************************************************************/
/* 4. Definitions of variables strictly local to the module.	*/
/****************************************************************/

#include		"../h/crashmsgs.h"


/****************************************************************/
/* 5. Definitions of functions to be exported.			*/
/****************************************************************/

 /* The following function signals errors causing abort. */
signal_crash(crash_type)
	int		crash_type;
					/* crash type */
{
	fprintf(stderr,
		"%s\n",
		crash_msgs[crash_type]);
	exit(COMPILERCRASH);
}

	
/****************************************************************/
/* 6. Definitions of functions strictly local to the module.	*/
/****************************************************************/






