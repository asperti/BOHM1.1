#ifndef _BOHM_H
#define _BOHM_H

#include "define.h"
#include "struct.h"

#include <stdbool.h>

extern 		FORM	*copy();
extern FORM *headfree;

extern 	void destroy();
extern 	void init_destroy();
extern 	void no_destroy();

extern char *malloc_da();
extern char *strdup_da();

extern bool		error_detected;

extern void		signal_error();

extern long unsigned 	er_count;
extern long unsigned 	cl_count;
extern FORM		*del_head;

extern 	void		clean();
extern 	void		user();
extern 	void		init_garbage();
extern 	void		ins_del();

extern unsigned		max_nodes;
extern unsigned		num_nodes;

extern 		FORM	*closeterm();

extern TERM *buildvarterm();
extern TERM *buildplambdaterm();
extern TERM *buildappterm();
extern TERM *buildletinterm();
extern TERM *build_mu_term();
extern TERM *buildtrueterm();
extern TERM *buildfalseterm();
extern TERM *buildifelseterm();
extern TERM *buildandterm();
extern TERM *buildorterm();
extern TERM *buildnotterm();
extern TERM *buildrelopterm();
extern TERM *buildmatterm();
extern TERM *buildminusterm();
extern TERM *buildintterm();
extern TERM *buildlist();
extern TERM *buildlist1();
extern TERM *buildcarterm();
extern TERM *buildcdrterm();
extern TERM *buildtestnil();
extern TERM *buildnillist();
extern TERM *buildvoidterm();

extern void connect();
extern void int_connect();
extern void bool_connect();
extern void connect1();

extern void             allocate_form();
extern void             myfree();
extern void             free_pattern();

VARLIST *mergevarlist();
VARLIST *makevarlist();

extern void		inspect_driver();

extern bool quit;
extern bool loading_mode;

extern char             *include_file;
extern FORM 		*lastinputterm;

extern int lines;

extern 	int 		option;
extern 	unsigned 	limit;
extern 	bool  	seetime;
extern 	bool  	seenode;
extern 	bool  	seegarb;

extern 	void	menu();
extern 	void	info();

extern void  	                rdbk();

extern void		reduce_term();

extern	void		save();

extern void init_symbol_table();
extern void search_bucket();
extern void push_local_env();
extern void pop_local_env();
extern void create_variable_binding();

#endif
