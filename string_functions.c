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

char *_concat_all(char *name, char *sep, char *value)
{
	char *result;
	int l1, l2, l3, i, k;

	l1 = strlen(name);
	l2 = strlen(sep);
	l3 = strlen(value);

	result = malloc(l1 + l2 + l3 + 1);
	if (!result)
		return (NULL);

	for (i = 0; name[i]; i++)
		result[i] = name[i];
	k = i;

	for (i = 0; sep[i]; i++)
		result[k + i] = sep[i];
	k = k + i;

	for (i = 0; value[i]; i++)
		result[k + i] = value[i];
	k = k + i;

	result[k] = '\0';

	return (result);
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
