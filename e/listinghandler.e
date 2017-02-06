/****************************************************************/
/*	                  LISTINGHANDLER.E			*/
/****************************************************************/


/****************************************************************/
/* 1. Declarations of variables.				*/
/****************************************************************/

extern int		lines,
			lexemes_in_curr_line;

extern BOOLEAN		out_listing;


/****************************************************************/
/* 2. Declarations of functions.				*/
/****************************************************************/

extern			open_listing(),
			produce_listing(),
			white_space_listing(),
			tab_listing(),
			newline_listing(),
			last_newline_listing(),
			print_error_listing(),
			print_warning_listing(),
			clear_listing(),
			close_listing();
