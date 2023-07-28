#include "shell.h"

/**
 * envloader - function
 * @envp: function arg
 */
void envloader(char **envp)
{
	size_t size = 0, i = 0;
	char *tmp = NULL, **newargs = NULL;

	while (envp[size++])
	{
	}
	environ = malloc(size * sizeof(char *));

	for (i = 0; envp[i]; i++)
	{
		environ[i] = strdup(envp[i]);
	}

	environ[i] = NULL;

	tmp = _getenv("OLDPWD");
	if (tmp)
	{
		newargs = malloc(4 * sizeof(char *));
		newargs[0] = strdup("setenv"), newargs[1] = strdup("OOLDPWD"),
		newargs[2] = strdup(tmp), newargs[3] = NULL;
		_setenv(newargs, NULL, NULL);
		freeargs(&newargs);
	}
}
