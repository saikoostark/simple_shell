#include "shell.h"

char **_split_string(char *str, char *delimiter, size_t *count)
{
	/* int strLen = strlen(str); */
	int delimiterCount = 0;
	int delimiterLen = strlen(delimiter);
	char **splitArray;
	char *token;
	int i;

	const char *pos = str;
	while ((pos = strstr(pos, delimiter)) != NULL)
	{
		delimiterCount++;
		pos += delimiterLen;
	}

	splitArray = (char **)malloc((delimiterCount + 1) * sizeof(char *));
	if (splitArray == NULL)
	{
		printf("Memory allocation failed.\n");
		return NULL;
	}

	token = strtok((char *)str, delimiter);
	i = 0;
	while (token != NULL)
	{
		splitArray[i] = strdup(token);
		token = strtok(NULL, delimiter);
		i++;
	}

	*count = delimiterCount + 1;
	splitArray[*count] = NULL;
	return splitArray;
}

void _remove_comment(char **strs)
{
	size_t i;

	for (i = 0; strs[i] != NULL; i++)
	{
		/* printf("%s\n", strs[i]); */
		if (strs[i][0] == '#')
		{
			strs[i] = NULL;
			break;
		}
		/* printf("%lu\n", i); */
	}
	/* printf("done removing\n"); */
}
