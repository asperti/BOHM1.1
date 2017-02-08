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

extern STRING		malloc_da(),
			strdup_da();

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

extern unsigned		max_nodes,num_nodes;
extern bool		is_global_var;
extern int		rec_er;

extern 		FORM	*closeterm();
extern 		TERM    *buildvarterm(),
        		*buildlambdaterm(),
        		*buildplambdaterm(),
        		*buildappterm(),
        		*buildletinterm(),
                        *build_mu_term(),
                        *buildtrueterm(),
                        *buildfalseterm(),
                        *buildifelseterm(),
			*buildandterm(),
			*buildorterm(),
			*buildnotterm(),
			*buildrelopterm(),
			*buildmatterm(),
			*buildminusterm(),
			*buildintterm(),
			*buildlist(),
			*buildlist1(),
			*buildcarterm(),
			*buildcdrterm(),
			*buildtestnil(),
			*buildnillist(),
                        *buildvoidterm();
extern void             connect(),
			int_connect(),
			bool_connect(),
			connect1();
extern void             allocate_form();
extern void             myfree();
extern void             free_varlist();
extern void             free_pattern();

VARLIST                 *mergevarlist(),
                        *makevarlist();
TERM                    *maketerm();

extern void		inspect_driver();
extern FORM             *inspect();

extern int		lines;

extern bool          quit,
                        loading_mode;
extern char             *include_file;
extern FORM 		*lastinputterm;

extern int		lines,
			lexemes_in_curr_line;

extern bool		out_listing;

extern int		open_listing(),
			produce_listing(),
			white_space_listing(),
			tab_listing(),
			newline_listing(),
			last_newline_listing(),
			print_error_listing(),
			print_warning_listing(),
			clear_listing(),
			close_listing();

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

extern	void		init_symbol_table(),
			search_bucket(),
			push_local_env(),
			pop_local_env(),
			pop_all_local_env(),
			create_variable_binding(),
                        create_local_variable_binding(),
			create_binding_for_undef_id();

#endif
