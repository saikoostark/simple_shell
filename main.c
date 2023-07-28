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
	}
	else if (argc == 2)
	{
		if (*isfilrdr == 0)
		{
			*filrdr = fopen(argv[1], "r");
			if (*filrdr == NULL)
			{
				fprintf(stderr, "%s: 0: cannot open %s: No such file\n", argv[0], argv[1]);
				freearg(str);
				freeargs(&environ);
				exit(2);
			}
			*isfilrdr = 1;
		}

		reads = getline(str, size, *filrdr);
	}
	if (reads == -1)
	{
		if (*filrdr != NULL)
			fclose(*filrdr);
		freearg(str);
		freeargs(&environ);
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
	_remove_comment(&args);

	if (args)
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
	int isfilrdr = 0, pid = 0, atty = isatty(STDIN_FILENO), status = 0;
	void (*builtin)(char **, int *, char *);

	environ = envloader(envp);
	while (1)
	{
		_readingInput(argc, argv, &str, &size, &filrdr, &isfilrdr, atty, &status);
		if (str == NULL || strlen(str) == 0)
			continue;
		args = _argsHandler(&str, &size);
		freearg(&str);
		if (args == NULL)
			continue;
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
					return (2);
				}
				waitpid(pid, &status, 0);
				status = WEXITSTATUS(status);
			}
		}
		else if (builtin != NULL)
			builtin(args, &status, (char *)argv[0]);
		freearg(&path);
		freeargs(&args);
	}
	freeargs(&environ);
	return (WEXITSTATUS(status));
}
