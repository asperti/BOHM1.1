/***************************************************************************/
/*                             MENU.C                                      */
/***************************************************************************/
/* This module implements the menus to select the desired garbage strategy.*/
/* It may be:                                                              */
/* - garbage collection performed whenever possible.                       */
/* - garbage collection attempted only if the number of operators in the   */
/*   graph reaches a certain limit. In this case the user is asked to      */
/*   choose such limit.                                                    */
/* The only external functions are:                                        */
/* - menu(): It activates the different menus depending on user's choice.  */
/* - info(): It allows the user to get informations about the computation. */
/* The external functions are:                                             */
/* - do_menu1(): It prints the first menu, asking the user which strategy  */
/*               he wants to use.                                          */
/* - do_menu2(): If the second strategie has been chosen, this function    */
/*               shows some possible limits for memory occupation and asks */
/*               the user to select one of them.                           */
/* - do_menu3(): It is used to insert a limit different from the ones      */
/*               listed by the previous function.                          */
/*                                                                         */
/***************************************************************************/

/***************************************************************************/
/* 1. Inclusion of header files.                                           */
/***************************************************************************/

#include "bohm.h"

#include <stdio.h>
#include <stdlib.h>

HIDDEN BOOLEAN do_menu1();
HIDDEN BOOLEAN do_menu2();
HIDDEN void    do_menu3();
HIDDEN int     take_char();
  
/***************************************************************************/
/* 2. Definitions of variables to be exported.                             */
/***************************************************************************/

int	 option;  /* Initial option selected */
unsigned limit;   /* Limit for allocable operators (only for option 2) */
BOOLEAN  seetime;
BOOLEAN  seenode;
BOOLEAN  seegarb;



/****************************************************************************/
/* 3. Definitions of functions to be exported.                              */
/****************************************************************************/

void menu()
{
    if(do_menu1())
	if(do_menu2())
	    do_menu3();

    printf("***********************************************************\n");
    printf("* O.K. Your choice has been recorded . . .                *\n");
    printf("***********************************************************\n\n");
}


void info()
{
    int select='x';
    while((select!='y')&&(select!='n')){
	printf("Display time and number of interactions?\n");
	printf("Please answer 'y' or 'n' (type 'h' for help).\n\n>");
	select = take_char();
	printf("\n");
	switch(select){
	    case 'y':
		seetime=TRUE;
		break;
	    case 'n':
		seetime=FALSE;
		break;
	    case 'h':
		printf("HELP . . .\n\n");
		printf("Answering 'y', the interpreter will display,\n");
		printf("after each reduction, the following informations:\n");
		printf("- Time taken by reduction, divided into:\n");
		printf("-     User   time (given in seconds).\n");
		printf("-     System time (given in seconds).\n");
		printf("- Total number of interactions.\n");
		printf("  (but the garbage ones)\n");
		printf("- Total number of family redex reductions.\n");
		printf("- Total number of proper interactions.\n");
		printf("  (those involving not-structural nodes\n");
		break;
	    default:
		printf("Illegal answer (type 'h' for help) . . .\n");
		break;
	}
    printf("\n");
    }
    select = 'x';
    while((select!='y')&&(select!='n')){
	printf("Display memory occupation informations ?\n");
	printf("Please answer 'y' or 'n' (type 'h' for help).\n\n>");
	select = take_char();
	printf("\n");
	switch(select){
	    case 'y':
		seenode=TRUE;
		break;
	    case 'n':
		seenode=FALSE;
		break;
	    case 'h':
		printf("HELP . . .\n\n");
		printf("Answering 'y', the program will display\n");
		printf("the following informations:\n");
		printf("- Initial number of nodes\n");
		printf("  (at the beginning of every reduction).\n");
		printf("- Maximum number of nodes\n");
		printf("  (existing at the same time during the\n");
		printf("  whole program execution).\n");
		printf("- Final number of nodes\n");
		printf("  (at the end of every reduction).\n");
		break;
	    default:
		printf("Illegal answer (type 'h' for help) . . .\n");
	}
    printf("\n");
    }
    select = 'x';
    while((select!='y')&&(select!='n')){
	printf("Display garbage collection informations ?\n");
	printf("Please answer 'y' or 'n' (type 'h' for help).\n\n>");
	select = take_char();
	printf("\n");
	switch(select){
	    case 'y':
		seegarb=TRUE;
		break;
	    case 'n':
		seegarb=FALSE;
		break;
	    case 'h':
		printf("HELP . . .\n\n");
		printf("Answering 'y' the program will display\n");
		printf("the following informations:\n");
		printf("- Number of erasing operations required\n");
		printf("  for eliminating the previous term and\n");
		printf("  the corresponding time.\n");
		printf("- Number of erasing operations performed\n");
		printf("  during the actual reduction, the\n");
		printf("  corresponding time, and the number\n");
		printf("  of garbage collection activations\n");
		printf("- Number of erasing operations done\n");
		printf("  in collecting disconnected parts of the\n");
		printf("  term.\n");
		break;
	    default:
		printf("Illegal answer (type 'h' for help) . . .\n");
	}
    printf("\n");
    }
    system("clear");
    printf("***********************************************************\n");
    printf("* O.K. Your choice has been recorded . . .                *\n");
    printf("***********************************************************\n\n");

}


/****************************************************************************/
/* 4. Definitions of functions strictly local to the module.                */
/****************************************************************************/

HIDDEN
int take_char()
{
    int taken;
    BOOLEAN warning;
    do{
	warning=FALSE;
	do
	    taken = getchar();
	while (taken == ENTER);
	while(getchar()!=ENTER)
	    warning=TRUE;
	if(warning){
	    printf("\nOne-character answer is required.\n");
	    printf("Answer again please . . .\n\n>");
	}
    }while(warning);
    return(taken);
}

HIDDEN
BOOLEAN do_menu1()
{
    BOOLEAN cont = FALSE;
    option=0;
    while((option!=1)&&(option!=2)&&(option!=3)){
	printf("Please choose one of the following strategies:\n");
	printf("1. Garbage collection performed whenever possible.\n");
	printf("2. Garbage collection depending on memory occupation.\n");
	printf("3. No garbage collection.\n");
	printf("4. Help . . .\n\n>");
	scanf("%d",&option);
	while(getchar()!=ENTER);
	system("clear");
	if(option==4){
	    printf("HELP . . .\n\n");
	    printf("Choosing  option  1.  garbage  collection will be\n");
	    printf("invoked whenever possible.                       \n");
	    printf("With  option  2.  g.c. will be attempted whenever\n");
	    printf("the  number  of allocated nodes reaches a certain\n");
	    printf("limit that you may specify using a menu.         \n");
	    printf("Both options  support the possibility  of erasing\n");
	    printf("the previous term when a new reduction is started\n");
	    printf("(obviously,  this  is  done  only if the previous\n");
	    printf("term wasn't a global declaration. \n");
	    printf("Option 3. prevents  g.c. if not explicitly called\n");
	    printf("by the user via the '#garbage' directive.\n\n");
	}else if((option!=1)&&(option!=2)&&(option!=3))
		printf("Illegal option . . .\n\n");
    }
    if(option==2)
	cont=TRUE;
    return(cont);
}

HIDDEN
BOOLEAN do_menu2()
{
    BOOLEAN cont=FALSE;
    int select=0;
    while((select!=1)&&(select!=2)&&(select!=3)&&(select!=4)){
	printf("Please choose a limit for memory occupation:\n");
	printf("1. 5000 operators.\n");
	printf("2. 10000 operators.\n");
	printf("3. 20000 operators.\n");
	printf("4. others.\n");
	printf("5. Help . . .\n\n>");
	scanf("%d",&select);
	while(getchar()!=ENTER);
	system("clear");
	if(select==5){
	    printf("HELP . . .\n\n");
	    printf("Options  1.  2.  3.  fix the upper bound to the\n");
	    printf("specified value.\n");
	    printf("Option 4. allows you to input a different value.\n");
	}else if((select!=1)&&(select!=2)&&(select!=3)&&(select!=4))
		printf("Illegal option . . .\n\n");
    }
    switch(select){
	case 1:
	    limit=5000;
	    break;
	case 2:
	    limit=10000;
	    break;
	case 3:
	    limit=20000;
	    break;
	case 4:
	    cont=TRUE;
	    break;
    }
    return(cont);
}

HIDDEN void
do_menu3()
{
    while((limit<1000)||(limit>50000)){
	printf("Please insert an upper bound for memory utililization:\n>");
	scanf("%u",&limit);
	while(getchar()!=ENTER);
	system("clear");
	if((limit<1000)||(limit>50000)){
	    limit = 0;
	    printf("You have to fix an upper bound for the number of\n");
	    printf("nodes, before garbage collection is attempted.\n");
	    printf("The possible range is from 1000 to 50000.\n\n");
	}
    }
}

