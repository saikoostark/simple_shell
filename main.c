#include "shell.h"

int pid;
void handleCtrlC(int sig_num)
{
	(void)sig_num;
	exit(0);
}

int main(int argc, char const *argv[])
{

	char *str = NULL;
	size_t size;
	char **args;
	ssize_t reads;

	signal(SIGINT, handleCtrlC);
	if (argc == 2)
		printf("%s\n", argv[1]);

	while (1)
	{

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

		pid = fork();

		if (pid == 0)
		{
			execvp(args[0], args);
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
