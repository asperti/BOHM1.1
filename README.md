# BOHM1.1
Bologna Optimal Higher-Order Machine, Version 1.1

This is a "porting" of BOHM1.1 to C99. No major modifications have been apported to the original source code, 
but for minor bug fixes. Please, be aware that this is an old code, essentially belonging to a pre-XML era. 
Anybody interested to contribute is welcome. Many improvements can be done starting from

    1. a new syntax (possibly coq inspired)
    2. a new (reentrant) parser
    3. a more modular (possibly automatically generated) code
    4. a type checker

About the current syntax, please be aware that applications ALWAYS require parenthesis around them (left associative, 
of course), the rest is more or less as expected. Consult the README_more (old, original README) file or the examples 
for more information.

To cite this software, please use the following references:

    1. Andrea Asperti, Cecilia Giovanetti, Andrea Naletto. The Bologna Optimal Higher-Order Machine, 
    J. Funct. Program. v.6, n.6. pp 763--810, 1996, doi = 10.1017/S0956796800001994

    2. Andrea Asperti, Stefano Guerrini. The Optimal Implementation of Functional Programming Languages. 
    Cambridge Tracts in Theoretical Computer Science, v.45, Cambridge University Press, 1998, isbn = 9780521621120
