/****************************************************************/
/*		          FILEHANDLER.C			        */
/****************************************************************/
/* This module supplies routines for file handling.		*/
/* It consists of the following function:			*/
/* - fopen_f(): it opens a given file; if it is unable to open	*/
/*		the file, it signals this fact.			*/
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

#include		"../e/crashhandler.e"


/****************************************************************/
/* 3. Definitions of variables to be exported.			*/
/****************************************************************/


/****************************************************************/
/* 4. Definitions of variables strictly local to the module.	*/
/****************************************************************/


/****************************************************************/
/* 5. Definitions of functions to be exported.			*/
/****************************************************************/

 /* The following function implements a control interface for the */
 /* library function fopen(). */
FILE *
fopen_f(file_name, access)
	STRING		file_name,
					/* name of the file to be opened */
			access;
					/* access kind */
{
	FILE		*f;

	f = fopen(file_name, access);
	if (f != NULL)
		return(f);
	else
	{
		fprintf(stderr,
			"%s: ",
			file_name);
		signal_crash(UNABLETOOPENFILE);
	}
}


/****************************************************************/
/* 6. Definitions of functions strictly local to the module.	*/
/****************************************************************/


