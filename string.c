/****************************************************************/
/* This module supplies routines for string handling.		*/
/* It consists of the following functions:			*/
/* - to_lower_s(): it turns a given string into a lower case	*/
/*		   one;						*/
/* - to_nat_s(): it turns a given string of digits into a	*/
/*		 natural and checks for presence of overflow.	*/
/****************************************************************/


/****************************************************************/
/* 1. Inclusion of header files.				*/
/****************************************************************/

#include "bohm.h"

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

 /* The following function turns a given string into a lower case one. */
void to_lower_s(s)
	STRING		s;
					/* string to be turned */
{
	static int	diff = 'a' - 'A';

	for (; *s != EOS; s++)
		if (('A' <= *s) && (*s <= 'Z'))
			*s +=  diff;
}

 /* The following function turns a given string of digits into a natural */
 /* and checks for presence of overflow. */
int to_nat_s(s)
	STRING		s;
					/* string to be turned */
{
	long		n;

	for (n = 0; (n <= MAXINT) && (*s != EOS); s++)
		n = n * NUMBASE + (*s - '0');
	if (n > MAXINT)
		return(NUMOUTOFRANGE);
	else
		return((int)n);
}
