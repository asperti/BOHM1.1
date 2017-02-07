/****************************************************************/
/* This modules carries out the storing of a graph on a textual */
/* file, to permit consultation.                                */
/* In particular, a list is stored of all the links existing    */
/* among the forms (specifying form types and ports), also      */
/* provided with an index of the forms and their associated     */
/* information. 					        */
/* The following function is external:                          */
/*  - save(): Saves a graph on a file.  			*/
/* The followinq functions are internal:                        */
/*  - present(): Checks whether a form has already been copied  */
/*               once.                                          */
/*  - stampa(): Saves on file a link				*/
/*  - save_aux(): Saves any graph part.				*/
/*  - put_form(): Prints form name.				*/
/*  - put_int(): Prints NIL, INT and BOOL forms names.		*/
/*  - num_port(): Returns a form's ports number.		*/
/*  - eindex(): Saves a file index row				*/
/****************************************************************/


/****************************************************************/
/* 1. Inclusion of header files.				*/
/****************************************************************/

#define	ENTRY		17
#define	NUM		13

#include "bohm.h"

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/****************************************************************/
/* 2. Inclusion of declarations that are being imported.        */
/****************************************************************/

/****************************************************************/
/* 3. Declaration of names strictly local to the module.	*/
/****************************************************************/

FILE	*save_file;
ELEM	*head,*tail;
int	max;
HIDDEN	int		present();
HIDDEN	void		save_aux();
HIDDEN	void		stampa();
HIDDEN	void		put_int();
HIDDEN	void		put_form();
HIDDEN	int		num_port();
HIDDEN	void		eindex();


/****************************************************************/
/* 4. Definitions of functions to be exported.			*/
/****************************************************************/

/* The following function saves a graph on a file.		*/
void save(name,root,id)
	char	*name;
	FORM	*root;
	char	*id;
{
  ELEM 	*p,*dep;

  if(root!=NULL){
    save_file=fopen(name,"w");
    if (save_file==NULL)
      exit(0);
    head=tail=NULL;
    max=1;
    stampa(root,0,present(root));
    if(root->nport[0]>=0)
      save_aux(root->nform[0],root->nport[0]);
    p=head;
    fprintf(save_file,"\n\n\nI N D E X :\n\n");
    while (p!=NULL) {
      eindex(p);
      dep=p;
      p=p->next;
      free(dep);
    }
    fclose(save_file);
    if (id==NULL)
      printf("\nSaved last input term in the file %s.\n",name);
    else
      printf("\nSaved %s term in the file %s.\n",id,name);
  }
  else {
    printf("******************************************\n");
    printf("* No terms inserted yet . . .            *\n");
    printf("******************************************\n");
  }
}

/****************************************************************/
/* 5. Definitions of functions strictly local to the module.	*/
/****************************************************************/

/* The following function checks whether a form has already 	*/
/* been copied once.						*/
HIDDEN int
present(form)
	FORM	*form;
{
  ELEM  *p;
  int risp=TRUE;

  p=head;
  while(p!=NULL && risp)
    if (p->node==form)
      risp=FALSE;
    else
      p=p->next;
  if (risp) {
    if (head==NULL) {
      head=tail=(ELEM *)malloc_da(sizeof(ELEM));
    }
    else {
      tail->next=(ELEM *)malloc_da(sizeof(ELEM));
      tail=tail->next;
    }
    tail->node=form;
    tail->next=NULL;
    tail->num=risp=max++;
  }
  return risp;
}

/* The following function saves on file a link			*/
HIDDEN void
stampa(form,p,card)
      FORM       *form;
      int        p;
      int	card;
{
  int 	p1;

  p1=form->nport[p];
  fprintf(save_file,"%4d ",card);
  put_form(form);
  if (p1<0) {
    fprintf(save_file,"%d -> 0 ",p);
    put_int(form->nform[p],p1);
  }
  else {
    fprintf(save_file,"%d -> %d ",p,p1);
    put_form(form->nform[p]);
  }
  fprintf(save_file,"\n");
}


/* The following function saves any graph part.			*/
HIDDEN void
save_aux(root,p)
      FORM       *root;
      int        p;
{
  int n,p1,card;

  card = present(root);
  if(card) {
    n=num_port(root->name);
    for (p1=0;p1<n;p1++)
	stampa(root,p1,card);
    for (p1=0;p1<n;p1++)
      if(root->nport[p1]>=0)
	save_aux(root->nform[p1],root->nport[p1]);
  }
}

/* The following function prints form name.			*/
HIDDEN void
put_form(f)
	FORM    *f;
{
  switch (f->name)
     {
	case FAN:
	   fprintf(save_file,"FAN       ");
	   break;
	case TRIANGLE:
	   fprintf(save_file,"TRIANGLE  ");
	   break;
	case ROOT:
	   fprintf(save_file,"ROOT      ");
	   break;
	case APP:
	   fprintf(save_file,"APP       ");
	   break;
	case LAMBDA:
	   fprintf(save_file,"LAMBDA    ");
	   break;
	case IFELSE:
	   fprintf(save_file,"IFELSE    ");
	   break;
	case AND:
	   fprintf(save_file,"AND       ");
	   break;
	case OR:
	   fprintf(save_file,"OR        ");
	   break;
	case NOT:
	   fprintf(save_file,"NOT       ");
	   break;
	case LESS:
	   fprintf(save_file,"LESS      ");
	   break;
	case LESS1:
	   fprintf(save_file,"LESS1     ");
	   break;
	case EQ:
	   fprintf(save_file,"EQ        ");
	   break;
	case EQ1:
	   fprintf(save_file,"EQ1       ");
	   break;
	case NOTEQ:
	   fprintf(save_file,"NOTEQ     ");
	   break;
	case NOTEQ1:
	   fprintf(save_file,"NOTEQ1    ");
	   break;
	case MORE:
	   fprintf(save_file,"MORE      ");
	   break;
	case MORE1:
	   fprintf(save_file,"MORE1     ");
	   break;
	case LEQ:
	   fprintf(save_file,"LEQ       ");
	   break;
	case LEQ1:
	   fprintf(save_file,"LEQ1      ");
	   break;
	case MEQ:
	   fprintf(save_file,"MEQ       ");
	   break;
	case MEQ1:
	   fprintf(save_file,"MEQ1      ");
	   break;
	case ADD:
	   fprintf(save_file,"ADD       ");
	   break;
	case ADD1:
	   fprintf(save_file,"ADD1      ");
	   break;
	case SUB:
	   fprintf(save_file,"SUB       ");
	   break;
	case SUB1:
	   fprintf(save_file,"SUB1      ");
	   break;
	case PROD:
	   fprintf(save_file,"PROD      ");
	   break;
	case PROD1:
	   fprintf(save_file,"PROD1     ");
	   break;
	case DIV:
	   fprintf(save_file,"DIV       ");
	   break;
	case DIV1:
	   fprintf(save_file,"DIV1      ");
	   break;
	case MOD:
	   fprintf(save_file,"MOD       ");
	   break;
	case MOD1:
	   fprintf(save_file,"MOD1      ");
	   break;
	case CONS:
	   fprintf(save_file,"CONS      ");
	   break;
	case CAR:
	   fprintf(save_file,"CAR       ");
	   break;
	case CDR:
	   fprintf(save_file,"CDR       ");
	   break;
	case TESTNIL:
	   fprintf(save_file,"TESTNIL   ");
	   break;
	case LAMBDAUNB:
	   fprintf(save_file,"LAMBDAUNB ");
	   break;
	case UNS_FAN1:
	   fprintf(save_file,"UNS_FAN1  ");
	   break;
	case UNS_FAN2:
	   fprintf(save_file,"UNS_FAN2  ");
	   break;
	case CAR1:
	   fprintf(save_file,"CAR1      ");
	   break;
	case CDR1:
	   fprintf(save_file,"CDR1      ");
	   break;
	case TESTNIL1:
	   fprintf(save_file,"TESTNIL1  ");
	   break;
	case CONS1:
	   fprintf(save_file,"CONS1     ");
	   break;
     }
}


/* The following function prints NIL, INT and BOOL forms names.	*/
HIDDEN void
put_int(f,p)
	FORM    *f;
	int	p;
{
  switch(p) {
	case T:
	   fprintf(save_file,"True          ");
	   break;
	case F:
	   fprintf(save_file,"False         ");
	   break;
	case INT:
	   fprintf(save_file,"Int: %" PRIdPTR " ", (intptr_t)f);
	   break;
	case NIL:
	   fprintf(save_file,"Nil          ");
	   break;
  }
}


/* The following function returns a form's ports number.	*/
HIDDEN 	int
num_port(name)
	int	name;
{
  int	risp;
  switch (name)
     {
	case ROOT:
		risp=1;
		break;
	case TRIANGLE:
	case NOT:
	case LESS1:
	case EQ1:
	case NOTEQ1:
	case MORE1:
	case LEQ1:
	case MEQ1:
	case ADD1:
	case SUB1:
	case PROD1:
	case DIV1:
	case MOD1:
	case CAR:
	case CDR:
	case TESTNIL:
	case LAMBDAUNB:
	case UNS_FAN1:
	case UNS_FAN2:
		risp=2;
		break;
	case FAN:
	case APP:
	case LAMBDA:
	case IFELSE:
	case AND:
	case OR:
	case LESS:
	case EQ:
	case NOTEQ:
	case MORE:
	case ADD:
	case LEQ:
	case MEQ:
	case SUB:
	case PROD:
	case DIV:
	case MOD:
	case CONS:
	case CAR1:
	case CDR1:
	case TESTNIL1:
	case CONS1:
		risp=3;
		break;
     }
  return risp;
}

/* The following function saves a file index row		*/
HIDDEN void
eindex(elem)
	ELEM    *elem;
{
  fprintf(save_file,"%3d ",elem->num);
  put_form(elem->node);
  fprintf(save_file,"index: %2d",elem->node->index);
  switch (elem->node->name)
     {
	case FAN:
	case CAR1:
	case CDR1:
	case TESTNIL1:
	   fprintf(save_file," nlevel[1]: %2d",elem->node->nlevel[1]);
	   fprintf(save_file," nlevel[2]: %2d",elem->node->nlevel[2]);
	   break;

	case TRIANGLE:
	case UNS_FAN1:
	case UNS_FAN2:
	   fprintf(save_file," nlevel[1]: %2d",elem->node->nlevel[1]);
	   break;

	case LESS1:
	case EQ1:
	case NOTEQ1:
	case MORE1:
	case LEQ1:
	case MEQ1:
	case ADD1:
	case SUB1:
	case PROD1:
	case DIV1:
	case MOD1:
	   fprintf(save_file," value %-d",elem->node->num_safe);
	   break;
     }
  fprintf(save_file,"\n");
}


