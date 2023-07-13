#include "shell.h"

int main(int argc, char const *argv[], char *envp[])
{

	char *str = NULL;
	size_t size;
	int pid;

	while (1)
	{

		printf("$ ");
		getline(&str, &size, stdin);
		char **args = _split_string(str, " ", &size);
		pid = fork();

		if (pid == 0)
		{
			execve(args[0], args, envp);
		}
		else
		{
			wait(NULL);
		}
	}

	return (0);
}
