#ifndef _BOHM_H
#define _BOHM_H

#include "define.h"
#include "struct.h"

#include <stdbool.h>
#include <time.h>

extern bool error_detected;
extern bool loading_mode;
extern bool quit;
extern bool seegarb;
extern bool seenode;
extern bool seetime;
extern char *include_file;
extern clock_t sys_garb_time;
extern clock_t usr_garb_time;
extern FORM *del_head;
extern FORM *headfree;
extern FORM *lastinputterm;
extern int lines;
extern int option;
extern long unsigned cl_count;
extern long unsigned er_count;
extern unsigned limit;
extern unsigned max_nodes;
extern unsigned num_nodes;

extern char *malloc_da();
extern char *strdup_da();
extern FORM *closeterm();
extern FORM *copy();
extern TERM *buildandterm();
extern TERM *buildappterm();
extern TERM *buildcarterm();
extern TERM *buildcdrterm();
extern TERM *buildfalseterm();
extern TERM *buildifelseterm();
extern TERM *buildintterm();
extern TERM *buildletinterm();
extern TERM *buildlist();
extern TERM *buildlist1();
extern TERM *buildmatterm();
extern TERM *buildminusterm();
extern TERM *build_mu_term();
extern TERM *buildnillist();
extern TERM *buildnotterm();
extern TERM *buildorterm();
extern TERM *buildplambdaterm();
extern TERM *buildrelopterm();
extern TERM *buildtestnil();
extern TERM *buildtrueterm();
extern TERM *buildvarterm();
extern TERM *buildvoidterm();
extern VARLIST *makevarlist();
extern VARLIST *mergevarlist();
extern void allocate_form();
extern void bool_connect();
extern void clean();
extern void connect();
extern void connect1();
extern void create_variable_binding();
extern void destroy();
extern void free_pattern();
extern void info();
extern void init_destroy();
extern void init_garbage();
extern void init_symbol_table();
extern void ins_del();
extern void inspect_driver();
extern void int_connect();
extern void menu();
extern void myfree();
extern void no_destroy();
extern void pop_local_env();
extern void push_local_env();
extern void rdbk();
extern void reduce_term();
extern void save();
extern void search_bucket();
extern void signal_error();
extern void user();

#endif
