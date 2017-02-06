/****************************************************************/
/*	                GRAPHGENERATOR.E 			*/
/****************************************************************/


/****************************************************************/
/* 1. Declarations of variables.				*/
/****************************************************************/
extern unsigned		max_nodes,num_nodes;
extern BOOLEAN		is_global_var;
extern int		rec_er;

/****************************************************************/
/* 2. Declarations of functions.				*/
/****************************************************************/

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
