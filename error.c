#include "bohm.h"

#include <stdio.h>

bool error_detected;

void signal_error(const char *msg)
{
	error_detected = true;
	fprintf(stderr, "line %-5d\t--->\t%s\n", lines, msg);
}
