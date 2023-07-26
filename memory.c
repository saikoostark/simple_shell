#include "shell.h"
/**
 * freearg - function
 * @arg: function arg
 */
void freearg(char **arg)
{

	if (*arg != NULL)
	{
		free(*arg);
		*arg = NULL;
	}
}

/**
 * freeargs - function
 * @args: function arg
 */
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
