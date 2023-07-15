#include "shell.h"

/* char **environ = NULL; */

void _handleCtrlC(int sig_num)
{
	(void)sig_num;
	exit(0);
}

void _readingInput(int argc, char const *argv[], char **str, size_t *size,
				   FILE **filereader, int *isFileReader)
{
	ssize_t reads;

	if (argc == 1)
	{
		printf("$ ");
		reads = getline(str, size, stdin);
	}
	else if (argc == 2)
	{
		if (*isFileReader == 0)
		{
			*filereader = fopen(argv[1], "r");
			if (filereader == NULL)
				exit(1);
			*isFileReader = 1;
		}
		reads = getline(str, size, *filereader);
	}
	if (reads == -1)
	{
		if (*filereader != NULL)
			fclose(*filereader);
		exit(0);
	}
	if ((*str)[strlen(*str) - 1] == '\n')
		(*str)[strlen(*str) - 1] = '\0';
}

char **_argsHandler(char **str, size_t *size)
{
	char **args = NULL;

	args = _split_string(*str, " ", size);
	_remove_comment(args);
	_replace_cmd(args);
	return (args);
}

int main(int argc, char const *argv[], char **envp)
{
	char *str = NULL, *path = NULL, **args = NULL;
	size_t size = 0, i = 0;
	FILE *filereader = NULL;
	int isFileReader = 0, pid = 0;
	void (*builtin)(char **);

	environ = envp;
	signal(SIGINT, _handleCtrlC);
	while (1)
	{

		_readingInput(argc, argv, &str, &size, &filereader, &isFileReader);
		if (strlen(str) == 0)
			continue;
		args = _argsHandler(&str, &size);
		builtin = checkbuild(args);
		if (builtin != NULL)
		{
			builtin(args);
			continue;
		}
		path = args[0];
		path = _isExist(path);
		if (!path)
		{
			printf("%s: No such file or directory\n", args[0]);
			continue;
		}
		pid = fork();
		if (pid == 0)
		{
			execve(path, args, environ);
			printf("%s: No such file or directory\n", args[0]);
			return (1);
		}
		wait(NULL);
		if (path != NULL)
		{
			free(path);
			path = NULL;
		}

		if (str != NULL)
		{
			free(str);
			str = NULL;
		}

		if (args != NULL)
		{
			for (i = 0; args[i]; i++)
			{
				if (args[i] != NULL)
				{
					free(args[i]);
					args[i] = NULL;
				}
			}
			free(args);
			args = NULL;
		}
	}
	return (0);
}
