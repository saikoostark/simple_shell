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

/**
 * checkfreespaces - function
 * @str: function arg
 */
void checkfreespaces(char **str)
{
	size_t i = 0;

	for (i = 0; (*str)[i] != '\0'; i++)
	{
		if ((*str)[i] != ' ')
		{
			return;
		}
	}

	freearg(str);
}
