#include "shell.h"

void __exit(char **argv)
{
	int i, n;

	if (argv[1])
	{
		n = atoi(argv[1]);
		if (n <= -1)
			n = 2;
		for (i = 0; argv[i]; i++)
			free(argv[i]);
		free(argv);
		exit(n);
	}
	for (i = 0; argv[i]; i++)
		free(argv[i]);
	free(argv);
	exit(0);
}

/**
 * env - prints the current environment
 * @argv: array of arguments
 */
void _env(char **argv)
{
	int i;
	(void)argv;

	for (i = 0; environ[i]; i++)
	{
		printf("%s\n", environ[i]);
	}
}

void _setenv(char **argv)
{
	int i, j, k;

	if (!argv[1] || !argv[2])
	{
		perror(_getenv("_"));
		return;
	}

	for (i = 0; environ[i]; i++)
	{
		j = 0;
		if (argv[1][j] == environ[i][j])
		{
			while (argv[1][j])
			{
				if (argv[1][j] != environ[i][j])
					break;

				j++;
			}
			if (argv[1][j] == '\0')
			{
				k = 0;
				while (argv[2][k])
				{
					environ[i][j + 1 + k] = argv[2][k];
					k++;
				}
				environ[i][j + 1 + k] = '\0';
				return;
			}
		}
	}
	if (!environ[i])
	{

		environ[i] = _concat_all(argv[1], "=", argv[2]);
		environ[i + 1] = '\0';
	}
}

void _unsetenv(char **argv)
{
	int i, j;

	if (!argv[1])
	{
		perror(_getenv("_"));
		return;
	}
	for (i = 0; environ[i]; i++)
	{
		j = 0;
		if (argv[1][j] == environ[i][j])
		{
			while (argv[1][j])
			{
				if (argv[1][j] != environ[i][j])
					break;

				j++;
			}
			if (argv[1][j] == '\0')
			{
				free(environ[i]);
				environ[i] = environ[i + 1];
				while (environ[i])
				{
					environ[i] = environ[i + 1];
					i++;
				}
				return;
			}
		}
	}
}

void (*checkbuild(char **arv))(char **arv)
{
	int i, j;
	builtin T[] = {
		{"exit", __exit},
		{"env", _env},
		{"setenv", _setenv},
		{"unsetenv", _unsetenv},
		{NULL, NULL}};

	for (i = 0; T[i].name; i++)
	{
		j = 0;
		if (T[i].name[j] == arv[0][j])
		{
			for (j = 0; arv[0][j]; j++)
			{
				if (T[i].name[j] != arv[0][j])
					break;
			}
			if (!arv[0][j])
				return (T[i].func);
		}
	}
	return (NULL);
}
