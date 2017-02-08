/****************************************************************/
/* This module implements the auxiliary stack used during       */
/* the reduction of a term.                                     */
/****************************************************************/

#include "bohm.h"

#include <stdio.h>
#include <assert.h>

static int auxnext;
static FORM *auxstack[STACK_SIZE];

FORM *pop()
{
	FORM *res;

	assert(auxnext > 0);
	--auxnext;
	res = auxstack[auxnext];
	auxstack[auxnext] = NULL;
	return res;
}

void push(FORM *f)
{
	auxstack[auxnext] = f;

	++auxnext;
	if(auxnext >= STACK_SIZE) {
		printf("Stack Overflow . . .\n");
		getchar();
		getchar();
	}
}

void init_stack()
{
	auxnext = 0;
}
