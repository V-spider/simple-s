#include "shell.h"


/**
* handle_segfault - handle segmentation fault
* @signo: signal number
*/
void handle_segfault(int signo __attribute__((unused)))
{
	/* Save the program's state and exit gracefully.*/
	exit(1);
}
