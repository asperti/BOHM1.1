/****************************************************************/
/*	                     STHANDLER.E			*/
/****************************************************************/


/****************************************************************/
/* 1. Declarations of variables.				*/
/****************************************************************/

extern	STBUCKET		*dictionary[];

extern	LOCALENVENTRY		*curr_local_env;


/****************************************************************/
/* 2. Declarations of functions.				*/
/****************************************************************/

extern	void		init_symbol_table(),
			search_bucket(),
			push_local_env(),
			pop_local_env(),
			pop_all_local_env(),
			create_variable_binding(),
                        create_local_variable_binding(),
			create_binding_for_undef_id();
