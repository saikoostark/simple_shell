#include "shell.h"

char **envs = NULL;

void handleCtrlC(int sig_num)
{
	(void)sig_num;
	exit(0);
}

int main(int argc, char const *argv[], char **envp)
{

	char *str = NULL, *path;
	size_t size;
	char **args;
	ssize_t reads;
	FILE *filereader;
	int isFileReader = 0;
	int pid;
	void (*builtin)(char **);

	/* size_t i; */

	envs = envp;

	signal(SIGINT, handleCtrlC);

	while (1)
	{

		if (argc == 1)
		{
			printf("$ ");
			reads = getline(&str, &size, stdin);
		}
		else if (argc == 2)
		{
			if (isFileReader == 0)
			{
				filereader = fopen(argv[1], "r");
				if (filereader == NULL)
					exit(1);
				isFileReader = 1;
			}
			reads = getline(&str, &size, filereader);
		}
		if (reads == -1)
			exit(0);

		if (str[strlen(str) - 1] == '\n')
			str[strlen(str) - 1] = '\0';

		if (strlen(str) == 0)
			continue;

		args = _split_string(str, " ", &size);
		_remove_comment(args);
		_replace_cmd(args);

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
		else
		{
			wait(NULL);
		}
	}

	return (0);
}
