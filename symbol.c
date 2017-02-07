/****************************************************************/
/* This module supplies routines for symbol table handling.	*/
/* The symbol table consists of two parts: a dictionary and a	*/
/* scope stack.							*/
/* The dictionary is organized in the following way:		*/
/* - there is a bucket for each distinct identifier; the bucket */
/*   contains:							*/
/*   - a field containing a pointer to the sequence of		*/
/*     characters that spell out the identifier;		*/
/*   - a field indicating the token associated with the		*/
/*     identifier (remember that keywords are treated as	*/
/*     identifiers);						*/
/*   - a field containing a pointer to the entry for the	*/
/*     current binding in which the identifier is involved;	*/
/*   - a field containing a pointer to the next bucket;		*/
/* - buckets are collected into linked lists; each list is	*/
/*   self-organizing, i.e. the first bucket of the list is	*/
/*   associated with the last identifier inserted into or	*/
/*   looked for.                                            	*/
/* - the first bucket of each list is pointed to by a pointer   */
/*   stored in a hash table that contains 211 pointers; the	*/
/*   hash function that has been used was studied by P. J.	*/
/*   Weinberger (see A. V. Aho-R. Sethi-J. D. Ullman/		*/
/*   "Compilers"/pages 433-438).		                */
/* The scope stack has been meant to be easily extendible to    */
/*   the case of multibinding, and is organized in the          */
/*   following way:		                                */
/* - there is an entry for each distinct local environment; the	*/
/*   entry contains:						*/
/*   - a field containing the nesting depth associated with the	*/
/*     local environment of the function (not used);		*/
/*   - a field containing a pointer to the entry for the last	*/
/*     binding created in this local environment (in the case   */
/*     of pure lambda calculus this entry is unique);		*/
/*   - a field containing a pointer to the entry for the	*/
/*     previous local environment;				*/
/* - local environment entries are collected into a linked list */
/*   implementing a stack; the first two entries pushed onto	*/
/*   the scope stack concern the external environment (set of	*/
/*   bindings involving library procedures: it is empty,        */
/*   for the moment) and the global environment.                */
/* The two parts of the symbol table interact as follows:	*/
/* - there is an entry for each distinct binding; the entry	*/
/*   contains:							*/
/*   - a field containing a pointer to the bucket for the	*/
/*     identifier involved in the binding;			*/
/*   - a field containing a pointer to the previous binding	*/
/*     for the identifier involved in this binding;		*/
/*   - a field containing a pointer to the previous binding	*/
/*     created in the local environment containing this		*/
/*     binding;							*/
/* - binding entries are collected into linked lists; each	*/
/*   binding entry lies in:					*/
/*   - the binding entry list for the identifier involved in	*/
/*     the binding (this list is not doubly linked thanks to	*/
/*     the presence, in each binding entry, of the field	*/
/*     containing a pointer to the bucket for the identifier	*/
/*     involved in the binding);				*/
/*   - the binding entry list for the local environment in	*/
/*     which the binding has been created.			*/
/* - init_symbol_table(): it initializes the symbol table by	*/
/*			  inserting keywords into the		*/
/*			  dictionary and the external and	*/
/*			  global environments into the scope	*/
/*			  stack;				*/
/* - search_bucket(): it searches the symbol table for the	*/
/*		      bucket containing a given identifier, and	*/
/*		      inserts it if it is not present;		*/
/* - push_local_env(): it pushes a new local environment entry	*/
/*		       onto the scope stack;			*/
/* - pop_local_env(): it pops a local environment entry off the	*/
/*		      scope stack;				*/
/* - pop_all_local_env(): it pops all local environment entry 	*/
/*			  off the scope stack;			*/
/* - create_variable_binding(): it creates an entry for 	*/
/*				a variable declaration          */
/* - allocate_bucket(): it allocates a bucket for an		*/
/*			identifier;				*/
/* - move_bucket(): it moves a bucket to the head of the list	*/
/*		    in which it lies;				*/
/* - hash_pjw(): it computes the hash function;			*/
/* - push_external_env(): it pushes the entry for the external	*/
/*			  environment onto the scope stack;	*/
/* - push_global_env(): it pushes the entry for the global	*/
/*			environment onto the scope stack;	*/
/* - allocate_local_env_entry(): it allocates a local		*/
/*				 environment entry;		*/
/* - allocate_binding_entry(): it allocates a binding entry.	*/
/****************************************************************/


/****************************************************************/
/* 1. Inclusion of header files.				*/
/****************************************************************/

#include "bohm.h"
#include "y.tab.h"

#include <stdio.h>
#include <malloc.h>


/****************************************************************/
/* 2. Inclusion of declarations that are being imported.        */
/****************************************************************/


/****************************************************************/
/* 3. Definitions of variables to be exported.			*/
/****************************************************************/

STBUCKET		*dictionary[DICTSIZE];
			       /* pointers to bucket lists */

LOCALENVENTRY		*curr_local_env;
			       /* pointer to the entry for the */
			       /* current local environment */


/****************************************************************/
/* 4. Definitions of variables strictly local to the module.	*/
/****************************************************************/

HIDDEN LOCALENVENTRY	*external_env;
			       /* pointer to the entry for the */
			       /* external environment */

HIDDEN int		curr_nesting_depth;
		               /* current nesting depth */

HIDDEN void             push_external_env();
HIDDEN void             push_global_env();
HIDDEN int              hash_pjw();
HIDDEN void             allocate_local_env_entry();
HIDDEN void             allocate_binding_entry();
HIDDEN void             move_bucket();
HIDDEN void             allocate_bucket();

/* I/O library procedure names */
HIDDEN STRING		library_proc_names[] = {"empty"
					       };

/* keywords */
HIDDEN STRING		keywords[] =
				{
					"let",
					"in",
                                        "inspect",
                                        "quit",
					"load",
					"rec",
					"true",
					"false",
					"if",
					"then",
					"else",
					"and",
					"or",
					"not",
					"div",
					"mod",
					"cons",
					"head",
					"tail",
					"isnil",
					"def",
					"share",
					"nil",
					"garbage",
					"option",
					"info",
					"save",
				};

/****************************************************************/
/* 5. Definitions of functions to be exported.			*/
/****************************************************************/

 /* The following function initializes the symbol table by inserting */
 /* P keywords into the dictionary and the external and global */
 /* environments into the scope stack. */
void init_symbol_table()
{
	STBUCKET	*st;
	int		i;

	/* initialize the dictionary */
	for (i = 0; i < DICTSIZE; i++)
		dictionary[i] = NULL;

	/* insert P keywords into the appropriate bucket lists */

	for (i = 0; i < KEYWORDNUM; i++) 
	{
		search_bucket(&st,
			      keywords[i]);
		st->token = FIRSTKEYWORD + i;
	}

	/* initialize the scope stack */
	curr_local_env = NULL;
	curr_nesting_depth = NONESTING;

	push_external_env();
	push_global_env();
}

 /* The following function searches the symbol table for an identifier */
 /* and inserts it if it is not present; the function returns the */
 /* pointer to the bucket containing information associated with the */
 /* given identifier. The bucket associated with the given identifier */
 /* becomes the first one in its list. */

void search_bucket(st, id)
	STBUCKET	**st;
					/* pointer to the bucket containing */
					/* the identifier */
	STRING		id;
					/* identifier */
{
	int		dict_index;
					/* value returned by the */
					/* hash function */
	STBUCKET	*prev,
			*curr;

        /* turn the identifier into lower case */
        to_lower_s(id);
        
        /* apply the hash function */
        dict_index = hash_pjw(id);
        
        /* scan the bucket list indicated by the hash function */
        prev = curr = dictionary[dict_index];
        while ((curr != NULL) && (!equal_s(id, curr->id)))
          {
            prev = curr;
            curr = curr->next_st_bucket;
          }
	if (curr == NULL)
          /* the identifier is not in the list */
          {
            allocate_bucket(st,
                            id);
            move_bucket(*st,
                        dict_index);
          }
	else
          /* the identifier is already in the list */
          {
            *st = curr;
            if (prev != curr)
              /* the identifier is not in the first position */
              {
                prev->next_st_bucket = curr->next_st_bucket;
                move_bucket(curr,
                            dict_index);
              }
          }
}


 /* The following function pushes a new local environment entry onto */
 /* the scope stack. */
void push_local_env()
{
   curr_nesting_depth++;
   allocate_local_env_entry();
}

 /* The following function pops a local environment entry off */
 /* the scope stack. */
void pop_local_env()
{
	LOCALENVENTRY	*le;
	BINDINGENTRY	*b;

	le = curr_local_env;

	/* remove all the entries for bindings created in the */
	/* local environment */
	while (le->last_local_binding != NULL)
		{
			b = le->last_local_binding;
			b->st_bucket->curr_binding = b->prev_id_binding;
			le->last_local_binding = b->prev_local_binding;
			free(b);
		}

	 curr_local_env = le->prev_local_env;
	 free(le);
	 curr_nesting_depth--;
}

 /* The following function pops all local environment entry off */
 /* the scope stack. */
void pop_all_local_env()
{
  while (curr_nesting_depth>NONESTING)
    pop_local_env();
}


 /* The following function creates entries for a variable binding */
void create_variable_binding(st,rootform,type)
	STBUCKET	*st;
				/* pointer to the bucket for the */
				/* identifier which is to be bound */
				/* to a procedure */
	FORM            *rootform;
				/* pointer to the rootform of the */
				/* term associated with the identifier */
				/* (for global declarations only) */
	int		type;
				/* indicates DEF, SHARE or LOCAL */
				/* type entry */
{
	allocate_binding_entry(st,curr_local_env,rootform,type);
}
#if 0
void create_local_variable_binding(st,term)
	STBUCKET	*st;
				/* pointer to the bucket for the */
				/* identifier which is to be bound */
				/* to a procedure */
	TERM            *term;
				/* pointer to the rootform of the */
				/* term associated with the identifier */
				/* (for global declarations only) */
{
	allocate_local_binding_entry(st,curr_local_env,term->rootf,term->rootp);
}
#endif

 /* The following function creates an entry for a binding concerning */
 /* an identifier used but not defined. The entry for the binding is */
 /* inserted into the binding entry list for the external environment. */

void create_binding_for_undef_id(st,rootform)
	STBUCKET	*st;
				/* pointer to the bucket for the */
				/* identifier which is to be bound */
	FORM            *rootform;
				/* pointer to the rootform of the */
				/* term associated with the identifier */
				/* (for global declarations only) */
{
	allocate_binding_entry(st,external_env,rootform,LOCAL);
}



/****************************************************************/
/* 6. Definitions of functions strictly local to the module.	*/
/****************************************************************/

 /* The following function allocates a bucket for an identifier. */
HIDDEN
void allocate_bucket(st, id)
	STBUCKET	**st;
					/* pointer to the bucket to be */
					/* allocated */
	STRING		id;
					/* identifier */
{
	*st = (STBUCKET *)malloc_da(sizeof(STBUCKET));
	(*st)->id = strdup_da(id);
	(*st)->token = ID;
	(*st)->curr_binding = NULL;
	(*st)->next_st_bucket = NULL;
}

 /* The following function moves a bucket to the head of the */
 /* list in which it lies. */
HIDDEN
void move_bucket(st, dict_index)
	STBUCKET	*st;
					/* pointer to the bucket to */
					/* be moved */
	int		dict_index;
					/* index corresponding to */
					/* the list in which the */
					/* bucket lies */
{
	st->next_st_bucket = dictionary[dict_index];
	dictionary[dict_index] = st;
}

 /* The following function implements Weinberger's hash function. */
HIDDEN int
hash_pjw(id)
	STRING		id;
					/* identifier to be hashed */
{
	unsigned	h,
			g;

	for (h = 0; *id != EOS; id++)
	{
		h = (h << HASH1) + (*id);
		g = h & HASH2;
		if (g)
			h = h ^ (g >> HASH3) ^ g;
	}
	return(h % DICTSIZE);
}

 /* The following function pushes the entry for the external environment */
 /* onto the scope stack. */
HIDDEN
void push_external_env()
{
	STBUCKET	*st;
	int		i;

	push_local_env(NULL);
	external_env = curr_local_env;
	for (i = 0; i < LIBRARYPROCNUM; i++)
	{
		search_bucket(&st,
			      library_proc_names[i]);
		allocate_binding_entry(st,external_env,NULL,DEF);
	}
}

 /* The following function pushes the entry for the global environment */
 /* onto the scope stack. */
HIDDEN
void push_global_env()
{
	push_local_env();
}

 /* The following function allocates a local environment entry. */
HIDDEN 
void allocate_local_env_entry()
{
	LOCALENVENTRY	*le;
					/* pointer to the entry to */
					/* be allocated */
	le = (LOCALENVENTRY *)malloc_da(sizeof(LOCALENVENTRY));
	le->nesting_depth = curr_nesting_depth;
	le->last_local_binding = NULL;
	le->prev_local_env = curr_local_env;
	curr_local_env = le;
}

 /* The following function allocates a binding entry. */
HIDDEN 
void allocate_binding_entry(st,le,rootform,type)
	STBUCKET	*st;
				/* pointer to the bucket for the */
				/* identifier involved in the binding */
	LOCALENVENTRY	*le;
				/* pointer to the entry for the */
				/* environment in which the binding */
				/* is to be created */
	FORM            *rootform;
				/* pointer to the rootform of the */
				/* term associated with the identifier */
				/* (for global declarations only) */
	int		type;
				/* indicates DEF, SHARE or LOCAL */
				/* type entry */
{
	BINDINGENTRY	*b;

	b = (BINDINGENTRY *)malloc_da(sizeof(BINDINGENTRY));
	b->st_bucket = st;
	b->root = rootform;
	b->prev_id_binding = st->curr_binding;
	st->curr_binding = b;
	b->prev_local_binding = le->last_local_binding;
	le->last_local_binding = b;
	b->entry_type = type;
}

#if 0
HIDDEN
void allocate_local_binding_entry(st,le,rootform,port)
	STBUCKET	*st;
				/* pointer to the bucket for the */
				/* identifier involved in the binding */
	LOCALENVENTRY	*le;
				/* pointer to the entry for the */
				/* environment in which the binding */
				/* is to be created */
	FORM            *rootform;
				/* pointer to the rootform of the */
				/* term associated with the identifier */
				/* (for global declarations only) */
	int		port;
{
	BINDINGENTRY	*b;

	b = (BINDINGENTRY *)malloc_da(sizeof(BINDINGENTRY));
	b->st_bucket = st;
	b->root = rootform;
        b->port = port;
	b->prev_id_binding = st->curr_binding;
	st->curr_binding = b;
	b->prev_local_binding = le->last_local_binding;
	le->last_local_binding = b;
	b->entry_type = type;
}

#endif
