#include "shell.h"

/**
 * errorfork - function
 * @pid: function arg
 */
void errorfork(int pid)
{
	if (pid == -1)
		exit(EXIT_FAILURE);
}

/**
 * checkfreespaces - function
 * @str: function arg
 * Return: Always 0 (Success)
 */
void checkfreespaces(char **str)
{
	size_t i = 0;

	for (i = 0; (*str)[i] != '\0'; i++)
	{
		if ((*str)[i] != ' ')
		{
			return;
		}
	}

	freearg(str);
}

/**
 * strlendel - function
 * @str: function arg
 * @del: function arg
 */
size_t strlendel(const char *str, char del)
{

	size_t size = 0;

	while (str[size] != '\0' && str[size] != del)
	{
		size++;
	}

	return (size);
}

/**
 * strnncmp - function
 * @str1: function arg
 * @str2: function arg
 * @del1: function arg
 * @del2: function arg
 * Return: Always 0 (Success)
 */
int strnncmp(const char *str1, const char *str2, char del1, char del2)
{
	size_t size1 = strlendel(str1, del1);
	size_t size2 = strlendel(str2, del2);
	size_t i = 0;

	if (size1 != size2)
		return (0);

	for (i = 0; i < size1; i++)
	{
		if (str1[i] != str2[i])
			return (0);
	}
	return (1);
}
