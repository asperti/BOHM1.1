/****************************************************************/
/*		         DYNALLHANDLER.C			*/
/****************************************************************/
/* This module supplies routines for dynamic allocation.	*/
/* It consists of the following functions:			*/
/* - malloc_da(): it allocates a given amount of bytes; if it	*/
/*		  is unable to allocate, it signals this fact;	*/
/* - strdup_da(): it allocates a given string; if it is unable	*/
/*		  to allocate, it signals this fact.		*/
/****************************************************************/


/****************************************************************/
/* 1. Inclusion of header files.				*/
/****************************************************************/

#include		"../h/const.h"
#include		"../h/types.h"
#include		<stdio.h>
#include		<string.h>
#include		<malloc.h>


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
 /* library function malloc(). */
STRING
malloc_da(size)
	unsigned	size;
					/* size of the object to be */
					/* allocated */
{
	STRING		p;

	p = (STRING)malloc(size);
	if (p != NULL)
		return(p);
	else
		signal_crash(NOTENOUGHMEMORY);
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
	if (p != NULL)
		return(p);
	else
		signal_crash(NOTENOUGHMEMORY);
}

/****************************************************************/
/* 6. Definitions of functions strictly local to the module.	*/
/****************************************************************/
