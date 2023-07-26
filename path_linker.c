#include "shell.h"

/**
 * _getenv - function
 * @name: function arg
 * Return: Always 0 (Success)
 */
char *_getenv(const char *name)
{
	int i, j;
	char *value;

	if (!name)
		return (NULL);
	for (i = 0; environ[i]; i++)
	{
		j = 0;
		if (name[j] == environ[i][j])
		{
			while (name[j])
			{
				if (name[j] != environ[i][j])
					break;

				j++;
			}
			if (name[j] == '\0')
			{
				value = (environ[i] + j + 1);
				return (value);
			}
		}
	}
	return (NULL);
}

/**
 * _isExist - function
 * @command: function arg
 * Return: Always 0 (Success)
 */
char *_isExist(char *command)
{

	char **paths;
	size_t lenpaths;
	char *fullpath;
	size_t i;

	if (access(command, F_OK) != -1)
	{

		return (strdup(command));
	}

	paths = _split_string(_getenv("PATH"), ":", &lenpaths);

	for (i = 0; paths[i]; i++)
	{
		fullpath = _concat_all(paths[i], "/", command);
		if (access(fullpath, F_OK) != -1)
		{
			freeargs(&paths);
			return (fullpath);
		}
		free(fullpath);
	}

	freeargs(&paths);
	printf("%s: No such file or directory\n", command);
	return (NULL);
}

/**
 * _replace_cmd - function
 * @argv: function arg
 */
void _replace_cmd(char **argv)
{
	int i;
	size_t strlength;
	char *pid_str, *temp;

	for (i = 0; argv[i]; i++)
	{
		if (argv[i][0] == '$')
		{
			strlength = strlen(argv[i]);
			if (strlength > 1)
			{
				if (argv[i][1] == '$')
				{
					pid_str = malloc(16 * sizeof(char));
					snprintf(pid_str, 16, "%d", getpid());
					freearg(&argv[i]);
					argv[i] = pid_str;
				}
				else if (argv[i][1] == '?')
				{
					freearg(&argv[i]);
					argv[i] = strdup("0");
				}
				else
				{
					temp = _getenv(argv[i] + 1);
					freearg(&argv[i]);
					if (temp != NULL)
						argv[i] = strdup(temp);
					else
						argv[i] = strdup("");
				}
			}
		}
	}
}
