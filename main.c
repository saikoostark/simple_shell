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
	int pid;
	/* size_t i; */

	envs = envp;

	signal(SIGINT, handleCtrlC);
	if (argc == 2)
		printf("%s\n", argv[1]);

	while (1)
	{

		/* if (args)
		{
			for (i = 0; args[i]; i++)
			{
				printf("try to free %s\n", args[i]);
				free(args[i]);
			}

			printf("try to free the whole args\n");
			free(args);
		} */

		printf("$ ");
		reads = getline(&str, &size, stdin);

		if (reads == -1)
			exit(0);

		if (str[strlen(str) - 1] == '\n')
			str[strlen(str) - 1] = '\0';

		if (strlen(str) == 0)
			continue;

		args = _split_string(str, " ", &size);
		_remove_comment(args);
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
