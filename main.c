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
		pid = fork();

		if (pid == 0)
		{
			execve(str, NULL, envp);
		}
		else
		{
			wait(NULL);
		}
	}

	return (0);
}
