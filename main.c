#include "shell.h"

/**
 * _handleCtrlC - function
 * @sig_num: function arg
 */
void _handleCtrlC(int sig_num)
{
	(void)sig_num;
	_exit(EXIT_SUCCESS);
}

/**
 * _readingInput - function
 * @argc: function arg
 * @argv: function arg
 * @str: function arg
 * @size: function arg
 * @filereader: function arg
 * @isFileReader: function arg
 * @atty: function arg
 */
void _readingInput(int argc, char const *argv[], char **str, size_t *size,
				   FILE **filereader, int *isFileReader, int atty)
{
	ssize_t reads;

	if (argc == 1)
	{
		if (atty)
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
			printf("in file reader mode \n");
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

/**
 * _argsHandler - function
 * @str: function arg
 * @size: function arg
 * Return: Always 0 (Success)
 */
char **_argsHandler(char **str, size_t *size)
{
	char **args = NULL;

	_remove_whitespaces(str);
	args = _split_string(*str, " ", size);
	_remove_comment(args);
	_replace_cmd(args);
	return (args);
}

/**
 * main - function
 * @argc: function arg
 * @argv: function arg
 * @envp: function arg
 * Return: Always 0 (Success)
 */
int main(int argc, char const *argv[], char **envp)
{
	char *str = NULL, *path = NULL, **args = NULL;
	size_t size = 0;
	FILE *filereader = NULL;
	int isFileReader = 0, pid = 0, atty = 0;
	void (*builtin)(char **);

	environ = envp;
	signal(SIGINT, _handleCtrlC);
	atty = isatty(STDIN_FILENO);
	do
	{
		_readingInput(argc, argv, &str, &size, &filereader, &isFileReader, atty);
		if (strlen(str) == 0)
			continue;
		args = _argsHandler(&str, &size);
		freearg(&str);
		/* str = NULL; */
		builtin = checkbuild(args);
		if (builtin == NULL)
		{
			path = _isExist(args[0]);
			if (path)
			{
				pid = fork();
				errorfork(pid);
				if (pid == 0)
				{
					execve(path, args, environ);
					printf("%s: No such file or directory\n", args[0]);
					return (1);
				}
			}
		}
		else
			builtin(args);
		wait(NULL);
		freearg(&path);
		freeargs(&args);
	} while (atty);
	return (0);
}
