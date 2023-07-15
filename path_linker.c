#include "shell.h"

/**
 * _getenv - gets the value of the global variable
 * @name: name of the global variable
 * Return: string of value
 */
char *_getenv(const char *name)
{
	int i, j;
	char *value;

	if (!name)
		return (NULL);
	for (i = 0; envs[i]; i++)
	{
		j = 0;
		if (name[j] == envs[i][j])
		{
			while (name[j])
			{
				if (name[j] != envs[i][j])
					break;

				j++;
			}
			if (name[j] == '\0')
			{
				value = (envs[i] + j + 1);
				return (value);
			}
		}
	}
	return (0);
}

char *_isExist(char *command)
{

	char **paths;
	size_t lenpaths;
	char *fullpath;
	size_t i;

	paths = _split_string(_getenv("PATH"), ":", &lenpaths);

	if (access(command, F_OK) != -1)
	{
		return (command);
	}

	for (i = 0; paths[i]; i++)
	{
		fullpath = _concat_all(strdup(paths[i]), "/", strdup(command));
		if (access(fullpath, F_OK) != -1)
		{
			return (fullpath);
		}
		free(fullpath);
	}
	return (NULL);
}

void _replace_cmd(char **argv)
{
	int i;
	size_t strlength;
	char *pid_str;

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
					argv[i] = pid_str;
				}
				else if (argv[i][1] == '?')
				{
				}
				else
				{
					argv[i] = _getenv(argv[i] + 1);
				}
			}
		}
	}
}
