#ifndef _TYPEDEF_H
#define _TYPEDEF_H

/* symbol table bucket type */
typedef	struct st_bucket
	{
		char *			id;
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

#endif
