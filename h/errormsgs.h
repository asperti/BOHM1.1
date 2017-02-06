/****************************************************************/
/*		          ERRORMSGS.H			        */
/****************************************************************/

 /* compile time error messages */
HIDDEN STRING		error_msgs[] = {
  "lexical error: illegal character",
  "lexical error: numerical constant overflow",
  "syntax error: identifier expected after let",
  "syntax error: bad expression in declaration",
  "syntax error: = expected after identifier in declaration",
  "syntax error",
  "syntax error: missing closed bracket",
  "syntax error: identifier expected after lambda",
  "syntax error: identifier expected after let in expression",
  "syntax error: bad expression in assignement of let_in expression",
  "syntax error: bad expression in body of let_in expression",
  "syntax error: bad expression",
  "syntax error: = expected after identifier in let_in expression",
  "syntax error: bad application",
  "scoping error: undefined variable"
};

 /* warning messages */
HIDDEN STRING		warning_msgs[] = {
  "warning: variable already declared"
};
