/****************************************************************/
/* This module implements the readback procedure as defined     */
/* is Asperti Laneve: Interaction Systems II.                   */
/* The only external function is                                */
/* - rdbk():     it provides the readback in standard syntax    */
/*               of the graphical term whose root is passed     */
/*               as input parameter.                            */
/****************************************************************/


/****************************************************************/
/* Inclusion of header files.	  			        */
/****************************************************************/

#include "bohm.h"

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

/****************************************************************/
/* Declaration of variables strictly local to the module.	*/
/****************************************************************/
HIDDEN int left_to_print;
                  /* maximum number of characters yet to print */

/****************************************************************/
/* Declaration of functions strictly local to the module.	*/
/****************************************************************/
HIDDEN void rdbk_1(), rdbk_list();


/****************************************************************/
/* Definitions of functions to be exported.			*/
/****************************************************************/

 /* the following function prints on the standard output the */
 /* standard syntactical representation of the graphical term */
 /* whose root is passed in input */
void rdbk(form)
     FORM *form;
{
  left_to_print=PRINT_MAX;
  printf("  ");
  rdbk_1(form,0);
  printf("\n");
}

HIDDEN void rdbk_1(form,port)
     FORM *form;
     int port;
{
  if(left_to_print>0)
    if(form->nport[port]<0) {
      switch(form->nport[port]){
      case INT:
	left_to_print-=printf("%" PRIdPTR, (intptr_t)form->nform[0]);
	break;
      case T:
	left_to_print-=printf("TRUE");
	break;
      case F:
	left_to_print-=printf("FALSE");
	break;
      case NIL:
	left_to_print-=printf("[]");
	break;
      default:
      left_to_print-=printf("...");
      } 
    }
    else
      switch(form->nform[port]->name){
      case LAMBDA:
      case LAMBDAUNB:
	if(form->nport[port]==0)
          left_to_print-=printf("#<function>");
        else
          left_to_print-=printf("...");
        break;
      case CONS:
	if(form->nport[port]==0) {
          left_to_print-=printf("[");
          rdbk_1(form->nform[port],1);
          rdbk_list(form->nform[port],2);
        } else {
          left_to_print-=printf("...");
        }
	break;
      case FAN:
        if(form->nport[port]!=0)
          rdbk_1(form->nform[port],0);
        else {
	  left_to_print-=printf("...");
	}
        break;
      case TRIANGLE:
        rdbk_1(form->nform[port],!form->nport[port]);
        break;
      default:
        left_to_print-=printf("...");
      }
  else
    left_to_print-=printf("...");
}

HIDDEN void rdbk_list(form,port)
FORM *form;
int port;
{
  if((int)form->nport[port]==NIL)
    left_to_print-=printf("]");
  else if(left_to_print<=0)
    left_to_print-=printf("...]");
  else if(form->nport[port]<0) {
    left_to_print-=printf("|");
    rdbk_1(form,port);
    left_to_print-=printf("]");
  } else if(form->nform[port]->name==TRIANGLE ||
	    (form->nform[port]->name==FAN && form->nport[port]!=0))
    rdbk_list(form->nform[port],!form->nport[port]);
  else if(form->nform[port]->name!=CONS || form->nport[port]!=0) {
    left_to_print-=printf("|");
    rdbk_1(form,port);
    left_to_print-=printf("]");
  } else {
    left_to_print-=printf(",");
    rdbk_1(form->nform[port],1);
    rdbk_list(form->nform[port],2);
  }
}

