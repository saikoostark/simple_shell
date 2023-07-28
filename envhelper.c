#include "shell.h"

/**
 * envloader - function
 * @envp: function arg
 * Return: Always 0 (Success)
 */
char **envloader(char **envp)
{
	size_t size = 0, i = 0;
	char **new_envp;

	while (envp[size++])
	{
	}
	new_envp = malloc(size * sizeof(char *));

	for (i = 0; envp[i]; i++)
	{
		new_envp[i] = strdup(envp[i]);
	}

	new_envp[i] = NULL;
	return (new_envp);
}
