#include "shell.h"

/**
 * _split_string - function
 * @str: function arg
 * @delimiter: function arg
 * @count: function arg
 * Return: Always 0 (Success)
 */
char **_split_string(char *str, char *delimiter, size_t *count)
{
	/* int strLen = strlen(str); */
	int delimiterCount = 0;
	int delimiterLen = strlen(delimiter);
	char **splitArray;
	char *token;
	int i;
	const char *pos = str;

	str = strdup(str);
	while ((pos = strstr(pos, delimiter)) != NULL)
	{
		delimiterCount++;
		pos += delimiterLen;
	}

	splitArray = (char **)malloc((delimiterCount + 2) * sizeof(char *));
	if (splitArray == NULL)
	{
		printf("Memory allocation failed.\n");
		return (NULL);
	}

	token = _strtok((char *)str, delimiter);
	i = 0;
	while (token != NULL)
	{
		splitArray[i] = strdup(token);
		token = _strtok(NULL, delimiter);
		i++;
	}
	free(str);
	*count = delimiterCount + 1;
	splitArray[*count] = NULL;
	return (splitArray);
}

/**
 * _concat_all - function
 * @name: function arg
 * @sep: function arg
 * @value: function arg
 * Return: Always 0 (Success)
 */
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

/**
 * _remove_comment - function
 * @strs: function arg
 */
void _remove_comment(char **strs)
{
	size_t i;
	int isComment = 0;

	for (i = 0; strs[i] != NULL; i++)
	{
		if (strs[i][0] == '#' && isComment == 0)
		{
			isComment = 1;
		}

		if (isComment)
		{
			free(strs[i]);
			strs[i] = NULL;
		}
	}
}

/**
 * _remove_whitespaces - function
 * @str: function arg
 */
void _remove_whitespaces(char **str)
{
	char *newstr = NULL;
	int oldsize = 0, spcs = 0, newsize = 0, start = 0, end = 0, i = 0, j = 0;

	if (str == NULL || *str == NULL)
		return;
	oldsize = strlen(*str), end = oldsize;
	for (i = 0; (*str)[i] != '\0'; i++)
	{
		if ((*str)[i] != ' ')
		{
			start = (int)i;
			break;
		}
		spcs++;
	}
	for (i = oldsize - 1; i >= 0; i--)
	{
		if ((*str)[i] != ' ')
		{
			end = (int)i;
			break;
		}
		spcs++;
	}
	end++;
	newsize = (int)oldsize - spcs;
	newstr = malloc(newsize + 1);
	for (i = start, j = 0; i < end; i++, j++)
	{
		newstr[j] = (*str)[i];
	}
	newstr[j] = '\0';
	free(*str);
	*str = newstr;
}

/**
 * _strtok - function
 *  @str: function arg
 *  @delimiters: function arg
 */
char *_strtok(char *str, const char *delimiters)
{
	static char *token_ptr;
	char *token_start = NULL;

	if (str != NULL)
	{
		token_ptr = str;
	}

	if (token_ptr == NULL || *token_ptr == '\0')
	{
		return (NULL);
	}

	while (*token_ptr != '\0' && strchr(delimiters, *token_ptr) != NULL)
	{
		token_ptr++;
	}

	if (*token_ptr == '\0')
	{
		return (NULL);
	}

	token_start = token_ptr;

	while (*token_ptr != '\0' && strchr(delimiters, *token_ptr) == NULL)
	{
		token_ptr++;
	}
	if (*token_ptr != '\0')
	{
		*token_ptr = '\0';
		token_ptr++;
	}
	return (token_start);
}
