#include "shell.h"

char **envs = NULL;

void handleCtrlC(int sig_num)
{
	(void)sig_num;
	exit(0);
}

void readingInput(int argc, char const *argv[], char **str, size_t *size,
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
			printf("begin func\n");
			*filereader = fopen(argv[1], "r");
			if (filereader == NULL)
				exit(1);
			*isFileReader = 1;
			printf("end func\n");
		}
		reads = getline(str, size, *filereader);
	}
	if (reads == -1)
		exit(0);
	if ((*str)[strlen(*str) - 1] == '\n')
		(*str)[strlen(*str) - 1] = '\0';
	printf("end of function\n");
}

char **argsHandler(char **str, size_t *size)
{
	char **args = NULL;

	args = _split_string(*str, " ", size);
	_remove_comment(args);
	_replace_cmd(args);
	return (args);
}

int main(int argc, char const *argv[], char **envp)
{
	char *str = NULL, *path, **args;
	size_t size;
	FILE *filereader = NULL;
	int isFileReader = 0, pid = 0;
	void (*builtin)(char **);

	envs = envp;
	signal(SIGINT, handleCtrlC);
	while (1)
	{
		readingInput(argc, argv, &str, &size, &filereader, &isFileReader);
		printf("%s > %lu\n", str, size);
		if (strlen(str) == 0)
			continue;
		args = argsHandler(&str, &size);
		builtin = checkbuild(args);
		if (builtin != NULL)
		{
			builtin(args);
			continue;
		}
		path = strdup(args[0]);
		path = _isExist(path);
		if (!path)
		{
			printf("%s: No such file or directory\n", args[0]);
			continue;
		}
		pid = fork();
		if (pid == 0)
		{
			execve(path, args, envs);
			printf("%s: No such file or directory\n", args[0]);
			return (1);
		}
		wait(NULL);
	}
	return (0);
}
