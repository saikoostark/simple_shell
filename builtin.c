#include "shell.h"

/**
 * env - prints the current envsment
 * @argv: array of arguments
 */
void _env(char **argv)
{
	int i;
	(void)argv;

	for (i = 0; envs[i]; i++)
	{
		printf("%s\n", envs[i]);
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

	for (i = 0; envs[i]; i++)
	{
		j = 0;
		if (argv[1][j] == envs[i][j])
		{
			while (argv[1][j])
			{
				if (argv[1][j] != envs[i][j])
					break;

				j++;
			}
			if (argv[1][j] == '\0')
			{
				k = 0;
				while (argv[2][k])
				{
					envs[i][j + 1 + k] = argv[2][k];
					k++;
				}
				envs[i][j + 1 + k] = '\0';
				return;
			}
		}
	}
	if (!envs[i])
	{

		envs[i] = _concat_all(argv[1], "=", argv[2]);
		envs[i + 1] = '\0';
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
	for (i = 0; envs[i]; i++)
	{
		j = 0;
		if (argv[1][j] == envs[i][j])
		{
			while (argv[1][j])
			{
				if (argv[1][j] != envs[i][j])
					break;

				j++;
			}
			if (argv[1][j] == '\0')
			{
				free(envs[i]);
				envs[i] = envs[i + 1];
				while (envs[i])
				{
					envs[i] = envs[i + 1];
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
		/* {"exit", exitt}, */
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
