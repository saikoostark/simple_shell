#include "shell.h"

int main(int argc, char const *argv[])
{

	char *str = NULL;
	size_t size;
	int pid;
	char **args;

	if (argc == 2)
		printf("%s\n", argv[1]);

	while (1)
	{

		printf("$ ");
		getline(&str, &size, stdin);
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
			printf("%s: No such file or directory\n", argv[0]);
			return (1);
		}
		else
		{
			wait(NULL);
		}
	}

	return (0);
}
