/****************************************************************/
/* This module implements the auxiliary stack used during       */
/* the reduction of a term.                                     */
/****************************************************************/

/****************************************************************/
/* 1. Inclusion of header files.				*/
/****************************************************************/

#include "bohm.h"

#include <stdio.h>
#include <assert.h>

/****************************************************************/
/* 2. Definitions of local variables     			*/
/****************************************************************/
static
int                      max_ptr,
                         next;
static
FORM       *stack[STACK_SIZE];

/****************************************************************/
/* 3. Definitions of variables to be exported.			*/
/****************************************************************/


BOOLEAN not_in_stack(f)
     FORM *f;
{
   BOOLEAN res;
   int     i;

   res = TRUE;
   for (i=0; i < next; i++)
     res = (res && !(stack[i]==f));
   return res;
}

FORM *pop()
{
   FORM *res;
   assert(next > 0);
   res = stack[--next];
   stack[next] = NULL;
   return res;
}

void push(f)
     FORM    *f;
{
     stack[next++] = f;
     if(next>=STACK_SIZE){
	printf("Stack Overflow . . .\n");
	getchar();getchar();
     }
}

void init_stack()
{
     next = 0;
     max_ptr = 0;
}

int get_max_ptr()
{
  return max_ptr;
}

int get_next()
{
  return next;
}

void print_stack()
{
  int i;
  FORM *nf;

  printf("******* Inizio stack\n");
  for (i=0; i < next; i++)
    {
      nf = inspect(0,stack[i]);
      if (i < next-1) assert(nf == stack[i+1]);
    }

}
