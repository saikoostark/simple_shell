#include "shell.h"

void freearg(char *arg)
{

	if (arg != NULL)
	{
		free(arg);
		arg = NULL;
	}
}

void freeargs(char **args)
{
	size_t i;

	if (args != NULL)
	{

		for (i = 0; args[i]; i++)
		{
			free(args[i]);
			args[i] = NULL;
		}
		free(args);
		args = NULL;
	}
}
