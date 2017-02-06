/****************************************************************/
/*		         NUMBERHANDLER.C			*/
/****************************************************************/
/* This module supplies routines for number handling.		*/
/* It consists of the following function:			*/
/* - digits_n(): it computes the number of digits of a given	*/
/*		 integer.					*/
/****************************************************************/


/****************************************************************/
/* 1. Inclusion of header files.				*/
/****************************************************************/

#include		"../h/const.h"


/****************************************************************/
/* 2. Inclusion of declarations that are being imported.        */
/****************************************************************/


/****************************************************************/
/* 3. Definitions of variables to be exported.			*/
/****************************************************************/


/****************************************************************/
/* 4. Definitions of variables strictly local to the module.	*/
/****************************************************************/


/****************************************************************/
/* 5. Definitions of functions to be exported.			*/
/****************************************************************/

 /* The following function computes the number of digits of a given */
 /* integer. */
digits_n(n)
	int		n;
					/* integer whose number of */
					/* digits is to be computed */
{
	int		digits;

	for (digits = 1; (n = n / NUMBASE) != 0; digits++);
	return(digits);
}


/****************************************************************/
/* 6. Definitions of functions strictly local to the module.	*/
/****************************************************************/
