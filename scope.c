#include "bohm.h"

#include <stdio.h>

/* The following function checks if an identifier has been */
/* previously declared */

BOOLEAN defined(st)
	STBUCKET	*st;
			      /* pointer to the bucket for the */
			      /* identifier */
{
        return((st->curr_binding) != NULL);
}


