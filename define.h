#ifndef _DEFINE_H
#define _DEFINE_H

/* constants concerning keywords */
#define KEYWORDNUM			27
#define FIRSTKEYWORD			400

/* constants concerning the symbol table */
#define DICTSIZE			211
#define HASH1				4
#define HASH2				0xf0000000
#define HASH3				24

/* constants concerning the machine stack */
#ifndef         STACK_SIZE
#define STACK_SIZE			(unsigned int)10000000
#endif

/* constants concerning scope analysis */
#define NONESTING			-2

/* constants concerning compile time error messages */
#define ILLEGALCHAR			0
#define NUMOVERFLOW			1
#define UNBOUND_VARIABLE         	14

/* constants concerning garbage */
#define EXISTENT		3
#define NOTEXISTENT		4

/* constant concerning form names */
#define ROOT                            0
#define T				-1
#define F				-2
#define NIL			        -3
#define INT			        -4
#define ERASE		       	        5
#define NOT			        6
#define TRIANGLE                        9
#define NOTEQ			       10
#define NOTEQ1			       11
#define ADD1			       12
#define SUB1			       13
#define PROD1			       14
#define DIV1			       15
#define MOD1			       16
#define LESS1			       17
#define EQ1			       18
#define MORE1			       19
#define LEQ1			       20
#define MEQ1			       21
#define CAR			       22
#define CDR			       23
#define TESTNIL			       24
#define LAMBDAUNB		       25
#define UNS_FAN1		       27
#define UNS_FAN2		       28
#define APP                            29
#define LAMBDA                         30
#define FAN                            32
#define AND			       33
#define OR			       34
#define ADD			       35
#define SUB			       36
#define PROD			       37
#define DIV			       38
#define MOD			       39
#define LESS			       40
#define EQ			       41
#define MORE			       42
#define LEQ			       43
#define MEQ			       44
#define CONS			       45
#define IFELSE			       46
#define TESTNIL1		       47
#define CDR1			       48
#define CAR1			       49
#define CONS1			       50

/* constants concerning crash handling */
#define COMPILERCRASH			2
#define NOTENOUGHMEMORY			0

/* constants concerning readback */
#define PRINT_MAX	100

/* constants concerning allocate form */
#define FORM_NUM	1000

/* constants concerning copy */
#define DIM_REL		256

#endif
