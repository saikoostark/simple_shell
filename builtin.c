#include "shell.h"

/**
 * __exit - function
 * @argv: function arg
 * @status: function arg
 * @name: function arg
 */
void __exit(char **argv, int *status, char *name)
{
	int i, n;

	if (argv[1])
	{
		n = atoi(argv[1]);
		if (n <= -1 || !isdigit(argv[1][0]))
		{
			fprintf(stderr, "%s: 1: exit: Illegal number: %s\n", name, argv[1]);
			n = 2;
		}
		for (i = 0; argv[i]; i++)
			free(argv[i]);
		free(argv);
		freeargs(&environ);
		exit(n);
	}
	for (i = 0; argv[i]; i++)
		free(argv[i]);
	free(argv);
	freeargs(&environ);
	exit(*status);
}

/**
 * _env - function
 * @argv: function arg
 * @status: function arg
 * @name: function arg
 */
void _env(char **argv, int *status, char *name)
{
	int i;
	(void)argv;
	(void)status;
	(void)name;

	for (i = 0; environ[i]; i++)
	{
		printf("%s\n", environ[i]);
	}
}

/**
 * _setenv - function
 * @argv: function arg
 * @status: function arg
 * @name: function arg
 */
void _setenv(char **argv, int *status, char *name)
{
	int i, j, k;
	(void)status;
	(void)name;

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
		environ = realloc(environ, (i + 2) * sizeof(char *));
		environ[i] = _concat_all(argv[1], "=", argv[2]);
		environ[i + 1] = '\0';
	}
}

/**
 * _unsetenv - function
 * @argv: function arg
 * @status: function arg
 * @name: function arg
 */
void _unsetenv(char **argv, int *status, char *name)
{
	int i, j;
	(void)status;
	(void)name;

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

/**
 * checkbuild - function
 * @arv: function arg
 * Return: Always 0 (Success)
 */
void (*checkbuild(char **arv))(char **arv, int *status, char *name)
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

		if (arv[0] != NULL && T[i].name[j] == arv[0][j])
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
