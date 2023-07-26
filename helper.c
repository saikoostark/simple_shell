#include "shell.h"

/**
 * errorfork - function
 * @pid: function arg
 */
void errorfork(int pid)
{
	if (pid == -1)
		exit(EXIT_FAILURE);
}
