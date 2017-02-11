/*************************************************************************/
/* This module implements the garbage collector.                         */
/* It works by local interactions, propagating all the erase-operators   */
/* in the graph. Each erase-operator terminates its travelling either by */
/* annihilating against another one, or being "absorbed" by a different  */
/* operator, such as "lambdaunb", "uns_fan1", "uns_fan2".                */
/* When the garbage collector is activated, it finds all erase operators */
/* looking into a list in which they are inserted when created.          */
/* The following functions are external:                                 */
/* - init_garbage: it initializes the erase-list inserting the first     */
/*		   node. 						 */
/* - ins_del(): insert a new erase operator at the head of a list        */
/*              to be scanned when the G.C. is activated.                */
/* - clean(): it activates the G.C. by scanning the erase-list and by    */
/*            propagating them in the graph. It uses the local function  */
/*            "garbage()" which propagates a single node and             */
/*            inserts in the erases list new operators originated by     */
/*            duplication rules during travelling.                       */
/* - user():  it only calls the previous function and prints some data   */
/*            when the user digits the directive"#garbage".              */
/* The following functions are internal:                                 */
/* - garbage(): It performs the propagation of a single erase node by    */
/*              applicating garbage rules.                               */
/*************************************************************************/

/*************************************************************************/
/* 1. Inclusion of header files.                                         */
/*************************************************************************/

#include "bohm.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/times.h>

/*************************************************************************/
/* 2. Inclusion of declarations that are being imported.                 */
/*************************************************************************/

/*************************************************************************/
/* 3. Declaration of names strictly local to the module.                 */
/*************************************************************************/

/* constants concerning garbage */
#define EXISTENT		3
#define NOTEXISTENT		4

static long unsigned er_count; /* counter for erasing operations */
static long unsigned cl_count; /* counter for clean() calls */
static clock_t usr_garb_time;
static clock_t sys_garb_time;

static void     garbage();

/*************************************************************************/
/* 4. Definitions of variables to be exported.                           */
/*************************************************************************/

FORM *del_head=NULL;        	     /* head of erases list */
struct tms partial_time, final_time;

/*************************************************************************/
/* 5. Definitions of functions to be exported.                           */
/*************************************************************************/

 /* The following function initializes the erase-list inserting */
 /* the first node. */
void init_garbage()
{
	del_head=(FORM *)malloc_da(sizeof(FORM));
	del_head->nform[1]=NULL;
}

 /* The following function insert a new erase operator at the 	*/
 /* head of a list to be scanned when the G.C. is activated.  	*/
void ins_del(d)
FORM *d;
{
	d->index=EXISTENT;
	d->nform[1]=del_head->nform[1];
	del_head->nform[1]=d;
}

 /* The following function activates the G.C. by scanning the   */
 /* erase-list and by propagating them in the graph. It uses    */
 /* the local function "garbage()" which propagates a single    */
 /* node and inserts in the erases list new operators 		*/
 /* originated by duplication rules during travelling.          */
void clean()
{
	FORM *q;
	if (seegarb)
	  times(&partial_time);
	cl_count++;
	while((q=del_head->nform[1])!=NULL) {
	  del_head->nform[1]=q->nform[1];
	  if((q->index)==NOTEXISTENT)
	    myfree(q);
	  else
	    garbage(q);
	}
	if (seegarb) {
	  times(&final_time);
	  usr_garb_time+=final_time.tms_utime - partial_time.tms_utime;
	  usr_garb_time+=final_time.tms_stime - partial_time.tms_stime;
	}
}


 /* The following function it only calls the previous function  */
 /* and prints some data when the user digits the directive     */
 /* "#garbage".              					*/
void user()
{
	printf("*****************************************************\n");
	printf("Initial number of nodes %u\n",num_nodes);
	printf("Please wait . . .\n");
	clean();
	printf("Final number of nodes %u\n",num_nodes);
	printf("*****************************************************\n");
}

/************************************************ ************************/
/* 6. Definitions of functions strictly local to the module.             */
/*************************************************************************/


 /* The following function performs the propagation of a single	*/
 /* erase node by applicating garbage rules. 			*/
static void garbage(erase)
FORM *erase;
{
	bool end=false;
	FORM *form,*nextform,*newform;
	int port,nextport;
	int p1,p2;

	nextform=erase->nform[0];
	nextport=erase->nport[0];
	myfree(erase);
	while(!end) {
	  form=nextform;
	  port=nextport;
	  if(port<0) {
	    er_count++;
	    end=true;
	  }
	  else {
	    switch(form->name){

	      case TESTNIL1:
		if(port==0) {
		  er_count++;
		  form->name=ERASE;
		  nextform=form->nform[2];
		  nextport=form->nport[2];
		  connect1(form,0,form->nform[1],form->nport[1]);
		  ins_del(form);
		}
		else {
		  if(port==1) {
		    if (form->nlevel[2]==0) {
		      connect1(form->nform[2],
			       form->nport[2],
			       form->nform[0],
			       form->nport[0]);
		      myfree(form);
		    }
		    else {
		      form->name=TRIANGLE;
		      connect1(form,1,form->nform[2],form->nport[2]);
		      form->nlevel[1] = form->nlevel[2];
		      form->index-=1;
		    }
		  }
		  else {
		    if (form->nlevel[1]==0) {
		      form->name=TESTNIL;
		    }
		    else {
		      form->name=TRIANGLE;
		      allocate_form(&newform,TESTNIL,form->index);
		      connect1(newform,0,form->nform[0],form->nport[0]);
		      connect(newform,1,form,0);
		      form->index-=1;
		    }
		  }
		  end=true;
		}
		break;

	      case CAR1:
		if(port==0) {
		  er_count++;
		  form->name=ERASE;
		  nextform=form->nform[2];
		  nextport=form->nport[2];
		  connect1(form,0,form->nform[1],form->nport[1]);
		  ins_del(form);
		}
		else {
		  if(port==1) {
		    if (form->nlevel[2]==0) {
		      connect1(form->nform[2],
			       form->nport[2],
			       form->nform[0],
			       form->nport[0]);
		      myfree(form);
		    }
		    else {
		      form->name=TRIANGLE;
		      connect1(form,1,form->nform[2],form->nport[2]);
		      form->nlevel[1] = form->nlevel[2];
		      form->index-=1;
		    }
		  }
		  else {
		    if (form->nlevel[1]==0) {
		      form->name=CAR;
		    }
		    else {
		      form->name=TRIANGLE;
		      allocate_form(&newform,CAR,form->index);
		      connect1(newform,0,form->nform[0],form->nport[0]);
		      connect(newform,1,form,0);
		      form->index-=1;
		    }
		  }
		  end=true;
		}
		break;

	      case CDR1:
		if(port==0) {
		  er_count++;
		  form->name=ERASE;
		  nextform=form->nform[2];
		  nextport=form->nport[2];
		  connect1(form,0,form->nform[1],form->nport[1]);
		  ins_del(form);
		}
		else {
		  if(port==1) {
		    if (form->nlevel[2]==0) {
		      connect1(form->nform[2],
			       form->nport[2],
			       form->nform[0],
			       form->nport[0]);
		      myfree(form);
		    }
		    else {
		      form->name=TRIANGLE;
		      connect1(form,1,form->nform[2],form->nport[2]);
		      form->nlevel[1] = form->nlevel[2];
		      form->index-=1;
		    }
		  }
		  else {
		    if (form->nlevel[1]==0) {
		      form->name=CDR;
		    }
		    else {
		      form->name=TRIANGLE;
		      allocate_form(&newform,CDR,form->index);
		      connect1(newform,0,form->nform[0],form->nport[0]);
		      connect(newform,1,form,0);
		      form->index-=1;
		    }
		  }
		  end=true;
		}
		break;

	      case CONS1:
		if(port==0) {
		  er_count++;
		  nextform=form->nform[2];
		  nextport=form->nport[2];
		  form->name=ERASE;
		  connect1(form,0,form->nform[1],form->nport[1]);
		  ins_del(form);
		}
		else {
		  if(port==1) {
		    form->name=CDR;
		    connect1(form->nform[2],form->nport[2],form,1);
		  }
		  else
		    form->name=CAR;
		  end=true;
		}
		break;

	      case FAN:
		if(port==0) {
		  er_count++;
		  nextform=form->nform[2];
		  nextport=form->nport[2];
		  form->name=ERASE;
		  connect1(form,0,form->nform[1],form->nport[1]);
		  ins_del(form);
		}
		else {
		  if(form->num_safe)
		    if (port==1){
		      form->name=TRIANGLE;
		      connect1(form,1,form->nform[2],form->nport[2]);
		      form->nlevel[1] = form->nlevel[2];
		    }
		    else
		      form->name=TRIANGLE;
		  else
		    if(port==1){
		      form->name=UNS_FAN1;
		      connect1(form,1,form->nform[2],form->nport[2]);
		      form->nlevel[1] = form->nlevel[2];
		    }
		    else
		      form->name=UNS_FAN2;
		  end=true;
		}
		break;

	      case TRIANGLE:
	      case LAMBDAUNB:
	      case TESTNIL:
	      case CAR:
	      case CDR:
	      case NOT:
	      case EQ1:
	      case NOTEQ1:
	      case LEQ1:
	      case MEQ1:
	      case MORE1:
	      case LESS1:
	      case ADD1:
	      case SUB1:
	      case PROD1:
	      case DIV1:
	      case MOD1:
	      case UNS_FAN1:
	      case UNS_FAN2:
		er_count++;
		if (port==0) {
		  nextform=form->nform[1];
		  nextport=form->nport[1];
		}
		else {
		  nextform=form->nform[0];
		  nextport=form->nport[0];
		}
		myfree(form);
		break;

	      case APP:
	      case CONS:
	      case EQ:
	      case NOTEQ:
	      case LEQ:
	      case MEQ:
	      case MORE:
	      case LESS:
	      case ADD:
	      case SUB:
	      case PROD:
	      case DIV:
	      case MOD:
	      case AND:
	      case OR:
	      case IFELSE:
		er_count++;
		switch (port){
		  case 0:
		    p1=1;p2=2;
		    break;
		  case 1:
		    p1=0;p2=2;
		    break;
		  case 2:
		    p1=0;p2=1;
		    break;
		}
		nextform=form->nform[p2];
		nextport=form->nport[p2];
		form->name=ERASE;
		connect1(form,0,form->nform[p1],form->nport[p1]);
		ins_del(form);
		break;

	      case LAMBDA:
		if(port!=2){
		  er_count++;
		  nextform=form->nform[!port];
		  nextport=form->nport[!port];
		  form->name=ERASE;
		  connect1(form,0,form->nform[2],form->nport[2]);
		  ins_del(form);
		}
		else{
		  form->name=LAMBDAUNB;
		  end=true;
		}
		break;

	      case ERASE:
		er_count++;
		form->index=NOTEXISTENT;
		end=true;
		break;

	      default:
		printf("Error: form %d\n",(erase->nform[0])->name);
		exit(1);
		break;
	    }
	  }
	}
}

void reset_garbage()
{
	er_count = 0;
	cl_count = 0;
	usr_garb_time = 0;
	sys_garb_time = 0;
}

void show_garb_stat()
{
	printf("Total number of garbage calls      %lu\n", cl_count);
	printf("Total number of garbage operations %lu\n", er_count);
	printf("Garbage collection done in %.2f:usr %.2f:sys seconds\n",
		(double)usr_garb_time / 60, (double)sys_garb_time / 60);
	printf("*****************************************************\n");
}
