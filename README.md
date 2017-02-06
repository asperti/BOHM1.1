# BOHM1.1
Bologna Optimal Higher-Order Machine, Version 1.1

This is a "porting" of BOHM1.1 to C99.  No major modifications
have been apported to the original source code, but for minor bug
fixes.  Please, be aware that this is an old code, essentially
belonging to a pre-XML era.  Anybody interested to contribute is
welcome.  Many improvements can be done starting from

* a new syntax (possibly coq inspired);
* a new (reentrant) parser;
* a more modular (possibly automatically generated) code;
* a type checker.

To cite this software, please use the following references:

1. Andrea Asperti, Cecilia Giovanetti, Andrea Naletto.
The Bologna Optimal Higher-Order Machine,
J. Funct. Program. v.6, n.6. pp 763--810, 1996,
doi = 10.1017/S0956796800001994

2. Andrea Asperti, Stefano Guerrini.
The Optimal Implementation of Functional Programming Languages.
Cambridge Tracts in Theoretical Computer Science, v.45,
Cambridge University Press, 1998, isbn = 9780521621120

About the current syntax, please be aware that applications
_always_ require parenthesis around them (left associative,
of course), the rest is more or less as expected.  Please consult
the full README below or the examples for more information.

```
/***************************************************************/
/*		             README 			       */
/***************************************************************/

The Bologna Optimal Higher-order Machine (BOHM) is a prototype
implementation of a variant of Lamping-Gonthier's optimal graph
reduction technique relative to a lambda-calculus enriched with
primitive data types (boolean, integers, and lists).

BOHM has been developed by A.Asperti, J.Chroboczek, C.Giovannetti,
C.Laneve, P.Gruppioni and A. Naletto at the Department of
Mathematics of the University of Bologna, Italy.  The main authors can
be reached by e-mail as <asperti@cs.unibo.it>.

The machine reduces terms to their weak head normal forms,
according to a lazy-family strategy (i.e. it always reduces the
whole redex-family of the leftmost outermost one, until a weak
head normal form is reached).

This work has been partially supported by

	   ESPRIT Basic Research Project 6454 - CONFER.



INSTALLATION

In order to compile BOHM, simply cd to the directory where you
untarred the distribution and type:

  make

or

  make CC=gcc CFLAGS=-O2

if you want to use the GNU C compiler.  This step will create an
executable called `opt'.  You may always return to the original state
of the distribution by typing

  make clean

USAGE

Calling opt will open an interactive environment. You may now
introduce a term ended by a double semicolon, that will be immediately
reduced by the interpreter.

The source language is a sugared lambda-calculus enriched by primitive
data types and basic operations over them:

- Integers and mathematical operations.
- Booleans and relational operations.
- Lists and related operators.
- Fixed point operator for recursive definitions.

More precisely, the syntax of expressions is given by the following
grammar: (out of date -- no patterns, no tuples)

     <expr> ::= <expr0>
        |  <expr> < <expr>
        |  <expr> == <expr>
        |  <expr> > <expr>
        |  <expr> <= <expr>
        |  <expr> >= <expr>
        |  <expr> <> <expr>
        |  <expr> + <expr>
        |  <expr> - <expr>
        |  <expr> * <expr>
        |  <expr> div <expr>
        |  <expr> mod <expr>
        |  - <expr>   	

     <expr0> ::= true
        |  false
        |  <num\_const>
        |  <identifier>
        |  (<applist>)
        |  \ <identifier> . <expr>
        |  let <identifier> = <expr> in  <expr>
        |  rec <identifier> = <expr>
        |  if <expr> then  <expr> else  <expr>
        |  <expr> and  <expr>
        |  <expr> or  <expr>
        |  not <expr>
        |  <list>
        |  cons (<expr>,<expr>)
        |  head (<expr>)
        |  tail (<expr>)
        |  isnil (<expr>)

    <list> ::= nil
	| [<exprlist>]

    <exprlist> ::=                  (* empty *)
        | <expr>
	| <expr>,<exprlist>
        | <expr>|<expr>

    <applist> ::= <expr>
       |  <applist> <expr0>

The <expr0> nonterminal represents an expression that cannot begin
with a unary minus sign; it serves to avoid conflicts between f(-g)
and (f-g).  Remember to paranthesize arithmetic and boolean
expressions when passing them as an argument to a function.

Furthermore, any string between `(*' and `*)' is treated as whitespace.

See the subdirectory "examples" for some examples of programs.

There is also a global let instuction, to build up a global
environment. The syntax for such a global declaration is:

	def x = e ;;

The exact semantics of the def declaration is subject to change;
beware of name collisions!

The directive

	#quit;;

terminates the session (you may also quit by typing ^D).

After compiling a term, you may visit its graph representation by
typing the directive

	#inspect;;

This enters in "inspection mode". You are at the root form of the
term. To move along the graph, type the number of the port you wish to
exit through: you will move to the next form connected with the
previous one at the specified port. You may also inspect a previously
defined term, by typing

	#inspect term_name;;

You may also save it typing the directive

	#save file_name;;

for the last term; otherwise for a generic term

	#save "file_name" term_name;;

The directive

	#load "file_name";;

allows the user to compile an external file file_name.

The directive

	#option;;

allows you to choose a garbage strategie during execution, by
presenting a series of menus containing the possible modalities.  Such
menus can also be obtained at the beginning of execution by calling
opt with option "-s".

Garbage collection can also be explicitly invoked by the user by
calling the directive

	#garbage;;

The interpreter also displays some data about the computation, such as
the dimension of the graph or the time required for reduction.  These
informations can be viewed by typing the directive

	#info;;

and selecting the parameter of interest from the displayed menus.
These menus are also presented if the program is called with option
"-i".



CONTENTS

The main directory contains the following files

- README.md
- Makefile
- copy.c
- destroyer.c
- garbage.c
- graphgenerator.c
- inspect.c
- lambda_lexan.l
- lambda_parser.y
- loader.c
- m_stack.c
- main.c
- menu.c
- readback.c
- reducer.c
- save.c
- scope_analysis.c
- sthandler.c

Moreover, there are two directories: "e" and "h".

The directory "e" contains the following export files:
- copy.e
- crashhandler.e
- destroyer.e
- dynallhandler.e
- filehandler.e
- errorhandler.e
- garbage.e
- graphgenerator.e
- inspect.e
- lambda_lexan.e
- lambda_parser.e
- listinghandler.e
- loader.e
- m_stack.e
- menu.e
- numberhandler.e
- readback.e
- reducer.e
- save.e
- scope_analysis.e
- sthandler.e
- stringhandler.e
- crashhandler.c
- errorhandler.c
- stringhandler.c
- dynallhandler.c
- filehandler.c
- numberhandler.c

The directory "h" contains the following header files:
- const.h
- crashmsgs.h
- errormsgs.h
- iolibrary.h
- keywords.h
- types.h
```
