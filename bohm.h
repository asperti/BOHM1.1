#ifndef _BOHM_H
#define _BOHM_H

#include <stdio.h>

/* utility types */
typedef int		BOOLEAN;
typedef char		*STRING;

/* utility constants */
#define         ENTER                           10
#define		FALSE				0
#define		TRUE				1
#define		EOS				'\0'

/* constants concerning files */
#define		SUFFIXLENGTH			4
#define		NOMOREINPUT			1
#define		FROMCURRPOS			1

/* constants concerning numbers */
#define		MAXINT				2147483647
#define		NUMBASE				10
#define		NUMOUTOFRANGE			-1
#define		DUMMYINTCONSTVALUE		1

/* constants concerning keywords */
#define		KEYWORDNUM			27
#define		FIRSTKEYWORD			400
#define		LASTKEYWORD			426
#define		DEF				1
#define		SHARE				2
#define 	LOCAL				0

/* constants concerning P I/O library procedures */
#define		LIBRARYPROCNUM			0
#define		NOPAR				0
#define		NOPASSING			0

/* constants concerning the symbol table */
#define		DICTSIZE			211
#define		HASH1				4
#define		HASH2				0xf0000000
#define		HASH3				24

/* constants concerning the machine stack */
#ifndef         STACK_SIZE
#define		STACK_SIZE			(unsigned int)10000000
#endif

/* constants concerning scope analysis */
#define		NONESTING			-2
#define		EXTERNALENVNESTINGDEPTH		-1
#define		GLOBALENVNESTINGDEPTH		0

/* constants concerning compile time error messages */
#define		ILLEGALCHAR			0
#define		NUMOVERFLOW			1
#define		EXP_ID_AFTER_LET		2
#define         BAD_EXPR_IN_DECL                3
#define         EQUAL_EXPECTED_IN_DECL          4
#define         SINTAXERROR                     5
#define         CLOSE_BRACKET_EXPECTED          6
#define		EXP_ID_AFTER_LAMBDA		7
#define		EXP_ID_AFTER_LET_IN		8
#define		BAD_EXPR_IN_LET			9
#define		BAD_EXPR_IN_IN    		10
#define		BAD_EXPRESSION   		11
#define		EQUAL_EXPECTED_IN_LET_IN	12
#define		BAD_APPLICATION         	13
#define		UNBOUND_VARIABLE         	14

/* constants concerning warning messages */
#define		VAR_ALREADY_DECLARED		0

/* constants concerning garbage */
#define		OUT_OF_STACK		0
#define		IN_STACK		1
#define		DELETED			2
#define		EXISTENT		3
#define		NOTEXISTENT		4
#define		NOTINLIST		5


/* constant concerning form names */
#define         ROOT                            0
#define		T				-1
#define		F				-2
#define		NIL			        -3
#define		INT			        -4
#define		ERASE		       	        5

#define		NOT			        6
#define         TRIANGLE                        9
#define		NOTEQ			       10
#define		NOTEQ1			       11
#define		ADD1			       12
#define		SUB1			       13
#define		PROD1			       14
#define		DIV1			       15
#define		MOD1			       16
#define		LESS1			       17
#define		EQ1			       18
#define		MORE1			       19
#define		LEQ1			       20
#define		MEQ1			       21
#define		CAR			       22
#define		CDR			       23
#define		TESTNIL			       24
#define		LAMBDAUNB		       25
#define		UNS_FAN1		       27
#define		UNS_FAN2		       28

#define         APP                            29
#define         LAMBDA                         30
#define         FAN                            32
#define		AND			       33
#define		OR			       34
#define		ADD			       35
#define		SUB			       36
#define		PROD			       37
#define		DIV			       38
#define		MOD			       39
#define		LESS			       40
#define		EQ			       41
#define		MORE			       42
#define		LEQ			       43
#define		MEQ			       44
#define		CONS			       45

#define		IFELSE			       46
#define 	TESTNIL1		       47
#define 	CDR1			       48
#define 	CAR1			       49
#define 	CONS1			       50

/* constants concerning run time errors */
#define		RUNTIMEERROR			2

/* constants concerning crash handling */
#define		COMPILERCRASH			2
#define		NOTENOUGHMEMORY			0
#define		UNABLETOOPENFILE		1


#define		STAR          			1
#define		CIRCLE             		2

/* constants concerning readback */
#define	PRINT_MAX	100

/* constants concerning allocate form */
#define	FORM_NUM	1000

/* constants concerning copy */
#define	DIM_REL		256

#define NONAME 0

/* symbol table bucket type */
typedef	struct st_bucket
	{
		STRING			id;
						/* identifier */
		int			token;
						/* token associated with */
						/* the identifier (it can */
						/* be either ID or a keyword */
						/* token) */
		struct binding_entry	*curr_binding;
						/* pointer to the current */
						/* binding entry for the */
						/* identifier */
		struct st_bucket	*next_st_bucket;
						/* pointer to the bucket */
						/* for the next identifier */
						/* hashing in the same */
						/* linked list of buckets */
	}		STBUCKET;


/* local environment entry descriptor type */
typedef struct local_env_entry
	{
	  int			   nesting_depth;
					/* nesting depth associated */
					/* with the local environment */
	  struct binding_entry	   *last_local_binding;
					/* pointer to the entry for */
					/* the last binding enforced in */
					/* this environment */
	  struct local_env_entry   *prev_local_env;
					/* pointer to the entry for the */
					/* previous local environment */
	}		LOCALENVENTRY;


/* binding entry descriptor type */
typedef struct binding_entry
	{
	  struct st_bucket	*st_bucket;
					/* pointer to the bucket */
					/* for the identifier */
					/* involved in the binding */
	  struct form           *root;
                                        /* pointer to the root form */
                                        /* (for global identifiers) */
	  struct binding_entry	*prev_id_binding,
					/* pointer to the entry for */
					/* the binding previously */
					/* enforced for the same */
					/* identifier */
				*prev_local_binding;
					/* pointer to the entry for the */
					/* binding previously enforced */
					/* in the same local environment */
	  int			entry_type;
					/* indicates DEF, SHARE or LOCAL */
					/* type entry */
	}		BINDINGENTRY;

/* graphical form descriptor type */
typedef struct form
	{
	  char                   name;
					/* name of the form */
					/* (FAN, ROOT, CROISSANT */
					/* BRACKET)  */
	  int		        num_safe;
					/* Integer value for numeric */
					/* forms or indicator of safeness */
					/* for other forms  */
	  short int             index;
					/* index of the form */
	  char                  nport[3];
					/* numbers of the ports */
					/* where the three ports */
					/* of the form are connected to */
					/* (for CROISSANT and */
					/* BRACKET only the first two */
					/* fields are meaningful; for */
					/* ROOT only the first one is) */
	  struct form    *nform[3];
					/* pointer to the forms */
					/* where the three ports */
					/* of the form are connected to */
					/* (for CROISSANT and */
					/* BRACKET only the first two */
					/* fields are meaningful; for */
		                        /* ROOT only the first one is) */
	  short int             nlevel[3];

	  struct form           *next;
	  struct form           *prev;

	}		FORM;



/* free variable descriptor type */
typedef struct varentry
	{
	  struct st_bucket	*name;
					/* pointer to the st_bucket */
					/* for the variable */
	  struct form           *var;
					/* pointer to the form */
					/* for the variable */
	  struct varentry       *next;
					/* pointer to the next free */
					/* variable in a term */
	}               VARENTRY;

/* term descriptor type */
typedef struct term
	{
	  struct form           *rootf;
					/* pointer to the root form */
					/* of the term */
	  char                  rootp;
					/* number of the root port */
					/* of the term (0 for variables */
					/* and abstractions, 1 for */
					/* applications) */
	  struct varentry       *vars;
					/* pointer to the list of free */
					/* variables in the term */
	}               TERM;

typedef struct binding_id {
  struct st_bucket *id;
  struct form *form;
} BINDINGID;

typedef struct var_list {
  struct binding_id *id;
  struct var_list *next;
} VARLIST;

typedef struct pattern{
  struct var_list *var_list;
  struct term *term;
} PATTERN;

typedef struct new{
		struct form *node;
		struct new *prox;
}NEW;
typedef struct new1{
		struct form *rt;
		struct new1 *px;
}NEW1;

/* top level * o branching commands type */
typedef struct top_level_branching_info
	{
	  int top;             /* it can be STAR or CIRCLE */
	  struct top_level_branching_info *next ;
	}               TOPLEVEL_BRANCHING_INFO;

/* context type */
/* every context c has a shape of the kind  *o*oo..*o<c1,c2> */
/* where the initial sequence may be empty and the pair <c1,c2> */
/* may be absent */

typedef struct context
	{
	  TOPLEVEL_BRANCHING_INFO   *branching_info;
	  struct context            *fst;
	  struct context            *snd;
	}               CONTEXT;

/* stack of contexts entry type */
typedef struct context_stack
	{
	  FORM                 *argform;
				/* first form of the argument */
				/* of an application  */
	  int                  dbnm,
				/* de brujin number */
			       accessport;
				/* port of the first form of the */
				/* argument connected to the */
				/* application */
	  CONTEXT              *backup;
				/* application context. Used to resume */
				/* readback for the argument */
	  struct context_stack *tail;
				/* previous element in the stack */
	}              CONTEXT_STACK;

typedef	struct 	copy_form	{
	FORM			*src;
	FORM			*dest;
	struct copy_form	*next;
	}	COPY_FORM;

typedef	struct	elem {
		FORM		*node;
		int		num;
		struct elem	*next;
	} ELEM;

extern 		FORM	*copy();
extern void			signal_crash();
FORM *headfree;

extern 	void destroy();
extern 	void init_destroy();
extern 	void no_destroy();

extern STRING		malloc_da(),
			strdup_da();

extern BOOLEAN		error_detected;

extern void		signal_error(),
			signal_warning();

extern FILE		*fopen_f();

extern long unsigned 	er_count;
extern long unsigned 	cl_count;
extern long 		garb_time;
extern FORM		*del_head;

extern 	void		clean();
extern 	void		user();
extern 	void		init_garbage();
extern 	void		ins_del();

extern unsigned		max_nodes,num_nodes;
extern BOOLEAN		is_global_var;
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

extern FILE		*yyin;

extern int		yyleng,
			lines;

extern int		yylex();

typedef struct yy_buffer_state *YY_BUFFER_STATE;
extern YY_BUFFER_STATE yy_create_buffer (FILE *file,int size);
extern void yypush_buffer_state (YY_BUFFER_STATE new_buffer);
extern void yypop_buffer_state (void);

extern BOOLEAN          quit,
                        error_detected,
                        loading_mode;
extern char             *include_file;
extern FORM 		*lastinputterm;
extern FILE             *yyin;

extern int		lines,
			lexemes_in_curr_line;

extern BOOLEAN		out_listing;

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

extern void			compile();

extern 	int 		option;
extern 	unsigned 	limit;
extern 	BOOLEAN  	seetime;
extern 	BOOLEAN  	seenode;
extern 	BOOLEAN  	seegarb;

extern 	void	menu();
extern 	void	info();

extern 		FORM	*pop();
extern          void    push();
extern          void    init_stack();
extern          void    print_stack();
extern          int     get_next(),
                        get_max_ptr();

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

extern void		to_lower_s();
extern int 		to_nat_s(),
			length_s();
extern 	BOOLEAN		equal_s();

#endif
