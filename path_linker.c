#include "shell.h"

/**
 * _getenv - function
 * @name: function arg
 * Return: Always 0 (Success)
 */
char *_getenv(const char *name)
{
	int i;
	char *value;
	/* printf("name is > %s\n", name); */
	if (!name)
		return (NULL);
	for (i = 0; environ[i]; i++)
	{

		if (strnncmp(name, environ[i], '\0', '='))
		{
			/* printf("%s <=> %s", name, environ[i]); */
			value = (environ[i] + strlen(name) + 1);
			return (value);
		}
	}
	return (NULL);
}

/**
 * _isExist - function
 * @command: function arg
 * @status: function arg
 * Return: Always 0 (Success)
 */
char *_isExist(char *command, int *status)
{

	char **paths;
	size_t lenpaths;
	char *fullpath, *pathenv;
	size_t i;

	if (access(command, F_OK) != -1)
	{
		return (strdup(command));
	}
	pathenv = _getenv("PATH");

	if (pathenv == NULL || strlen(pathenv) == 0)
	{
		fprintf(stderr, "%s: 1: %s: not found\n", _getenv("_"), command);
		*status = 127;
		return (NULL);
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
	fprintf(stderr, "%s: 1: %s: not found\n", _getenv("_"), command);
	*status = 127;
	return (NULL);
}

/**
 * _replace_cmd - function
 * @argv: function arg
 * @status: function arg
 */
void _replace_cmd(char **argv, int *status)
{
	int i;
	size_t strlength;
	char *pid_str, *temp, buffer[15];

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
					sprintf(buffer, "%d", *status);
					argv[i] = strdup(buffer);
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
