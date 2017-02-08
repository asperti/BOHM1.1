#ifndef _BOHM_H
#define _BOHM_H

#include "define.h"
#include "typedef.h"

#include <stdbool.h>

extern 		FORM	*copy();
FORM *headfree;

extern 	void destroy();
extern 	void init_destroy();
extern 	void no_destroy();

extern char *malloc_da();
extern char *strdup_da();

extern bool		error_detected;

extern void		signal_error();

extern long unsigned 	er_count;
extern long unsigned 	cl_count;
extern long 		garb_time;
extern FORM		*del_head;

extern 	void		clean();
extern 	void		user();
extern 	void		init_garbage();
extern 	void		ins_del();

extern unsigned		max_nodes;
extern unsigned		num_nodes;
extern bool		is_global_var;
extern int		rec_er;

extern 		FORM	*closeterm();

extern TERM *buildvarterm();
extern TERM *buildlambdaterm();
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
extern void             free_varlist();
extern void             free_pattern();

VARLIST *mergevarlist();
VARLIST *makevarlist();

TERM                    *maketerm();

extern void		inspect_driver();
extern FORM             *inspect();

extern int		lines;

extern bool quit;
extern bool loading_mode;

extern char             *include_file;
extern FORM 		*lastinputterm;

extern int lines;
extern int lexemes_in_curr_line;

extern bool		out_listing;

extern int open_listing();
extern int produce_listing();
extern int white_space_listing();
extern int tab_listing();
extern int newline_listing();
extern int last_newline_listing();
extern int print_error_listing();
extern int print_warning_listing();
extern int clear_listing();
extern int close_listing();

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

extern	STBUCKET		*dictionary[];

extern	LOCALENVENTRY		*curr_local_env;

extern void init_symbol_table();
extern void search_bucket();
extern void push_local_env();
extern void pop_local_env();
extern void pop_all_local_env();
extern void create_variable_binding();
extern void create_local_variable_binding();
extern void create_binding_for_undef_id();

#endif
