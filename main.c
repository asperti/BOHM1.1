#include "bohm.h"
#include "y.tab.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern FILE *yyin;

extern struct yy_buffer_state *yy_create_buffer(FILE *file, int size);
extern void yypush_buffer_state(struct yy_buffer_state *new_buffer);
extern void yypop_buffer_state(void);
extern int yyparse();

/* The following function changes the parser standard 	*/
/* input and call the parser function.			*/
static void compile(char *file)
{
     printf("\n******** loading file %s ********\n",file);
     yypush_buffer_state(yy_create_buffer( yyin, 16384));
     yyin = fopen(file,"r");
     if (yyin==NULL)
	   printf("Fatal Error: cannot open file %s.\n",file);
     else
	{
	   loading_mode = 1;
	   while ((quit == 0) && (error_detected == false))
	     {
		yyparse();
	     }
	   if (error_detected == false)
	      printf("\n******** %s loaded ********\n",file);
	   else
	      {
		 printf("\n***** loading file %s aborted *****\n",file);
		 error_detected = false;
	      }
	   quit = 0;
	   loading_mode = 0;
	 }
     yypop_buffer_state();
}

int main(argc,argv)
int argc;
char *argv[];
{
  option=1;
  seetime=0;
  seenode=0;
  seegarb=0;
  if(argc>1) {
      if(argc==2)
	    if (strcmp(argv[1],"-s")==0)
		menu();
	    else if (strcmp(argv[1],"-i")==0)
			info();
		 else{
			printf("Execution failed:Illegal option . . .\n");
			exit(1);
		}
      else if(argc==3)
		if(  ( (strcmp(argv[1],"-s")==0)&&
		       (strcmp(argv[2],"-i")==0) ) ||
		     ( (strcmp(argv[2],"-s")==0)&&
		       (strcmp(argv[1],"-i")==0) ) ){
			info();
			menu();
		}else{
			printf("Execution failed:Illegal option \n");
			printf("or duplicated option . . .\n");
			exit(1);
		}
	    else{
	       printf("Execution failed:Too many parameters . . .\n");
	       exit(1);
	       }
  }
  printf("\n");
  printf("***********************************************************\n");
  printf("***                  Welcome to the                     ***\n");
  printf("***        Bologna Optimal Higher-order Machine         ***\n");
  printf("***       Version 1.1 by A. Asperti, J. Chroboczek,     ***\n");
  printf("***               C. Giovannetti, C. Laneve,            ***\n");
  printf("***              P. Gruppioni and A. Naletto.           ***\n");
  printf("***          Dipartimento di Matematica, Bologna        ***\n");
  printf("***********************************************************\n\n");
  init_symbol_table();
  init_destroy();
  init_garbage();
  lines = 0;
  setbuf(stdout, NULL);
  lastinputterm = NULL;

  while (quit == 0)
     {
       printf("bohm>");
	yyparse();
	if (loading_mode==true)
	  {
	   printf("including %s",include_file);
	   compile(include_file);
	   loading_mode = false;
	  }
	error_detected = false;
	lines = 0;
     }
  printf("good bye\n");
  return 0;
}
