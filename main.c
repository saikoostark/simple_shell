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
 * @filrdr: function arg
 * @isfilrdr: function arg
 * @status: function arg
 * @atty: function arg
 */
void _readingInput(int argc, char const *argv[], char **str, size_t *size,
				   FILE **filrdr, int *isfilrdr,
				   int atty, int *status)
{
	ssize_t reads;

	if (argc == 1)
	{
		if (atty)
			printf("$ ");
		reads = getline(str, size, stdin);
		if (reads == -1)
		{
			freearg(str);
		}
	}
	else if (argc == 2)
	{
		if (*isfilrdr == 0)
		{
			*filrdr = fopen(argv[1], "r");
			if (filrdr == NULL)
				exit(1);
			*isfilrdr = 1;
		}
		reads = getline(str, size, *filrdr);
	}
	if (reads == -1)
	{
		if (*filrdr != NULL)
			fclose(*filrdr);
		exit(*status);
	}
	if ((*str)[strlen(*str) - 1] == '\n')
		(*str)[strlen(*str) - 1] = '\0';
	checkfreespaces(str);
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
	FILE *filrdr = NULL;
	int isfilrdr = 0, pid = 0, atty = 0, status = 0;
	void (*builtin)(char **);

	environ = envp;
	signal(SIGINT, _handleCtrlC);
	atty = isatty(STDIN_FILENO);
	while (1)
	{
		_readingInput(argc, argv, &str, &size, &filrdr, &isfilrdr, atty, &status);
		if (str == NULL || strlen(str) == 0)
			continue;
		args = _argsHandler(&str, &size);
		freearg(&str);
		builtin = checkbuild(args);
		if (builtin == NULL)
		{
			path = _isExist(args[0], &status);
			if (path)
			{
				pid = fork();
				errorfork(pid);
				if (pid == 0)
				{
					execve(path, args, environ);
					printf("%s: No such file or directory\n", args[0]);
					return (2);
				}
				else
					waitpid(pid, &status, 0);
			}
		}
		else if (builtin != NULL)
			builtin(args);
		freearg(&path);
		freeargs(&args);
	}
	return (WEXITSTATUS(status));
}
