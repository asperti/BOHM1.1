/****************************************************************/
/* This module supplies routines for dynamic allocation.	*/
/* It exports the following functions:                          */
/* - malloc_da(): it allocates a given amount of bytes; if it	*/
/*		  is unable to allocate, it signals this fact;	*/
/* - strdup_da(): it allocates a given string; if it is unable	*/
/*		  to allocate, it signals this fact.		*/
/****************************************************************/


/****************************************************************/
/* 1. Inclusion of header files.				*/
/****************************************************************/

#include "bohm.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/****************************************************************/
/* 2. Inclusion of declarations that are being imported.        */
/****************************************************************/


/****************************************************************/
/* 3. Definitions of variables to be exported.			*/
/****************************************************************/


/****************************************************************/
/* 4. Definitions strictly local to the module.                 */
/****************************************************************/

/* The following function signals errors causing abort. */
static void signal_crash(crash_type)
	int crash_type; /* crash type */
{
	/* crash messages */
	static STRING crash_msgs[] = {
		"not enough memory",
		"unable to open this file"
	};

	fprintf(stderr, "%s\n", crash_msgs[crash_type]);
	exit(COMPILERCRASH);
}

/****************************************************************/
/* 5. Definitions of functions to be exported.			*/
/****************************************************************/

 /* The following function implements a control interface for the */
 /* library function malloc(). */
STRING
malloc_da(size)
	unsigned	size;
					/* size of the object to be */
					/* allocated */
{
	STRING		p;

	p = (STRING)malloc(size);
	if (!p)
		signal_crash(NOTENOUGHMEMORY);

	return p;
}

 /* The following function implements a control interface for the */
 /* library function strdup(). */
STRING
strdup_da(s)
	STRING		s;
					/* string to be allocated */
{
	STRING		p;

	p = strdup(s);
	if (!p)
		signal_crash(NOTENOUGHMEMORY);

	return p;
}
