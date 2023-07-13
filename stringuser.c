#include "shell.h"

char *_strtok(char *str, const char *delim)
{
	static char *next_token = NULL;
	if (str != NULL)
	{
		next_token = str;
	}
	if (next_token == NULL)
	{
		return NULL;
	}
	char *token_start = next_token;
	next_token += strspn(next_token, delim);
	if (*next_token == '\0')
	{
		next_token = NULL;
		return NULL;
	}
	char *token_end = next_token + strcspn(next_token, delim);
	if (*token_end != '\0')
	{
		*token_end = '\0';
		next_token = token_end + 1;
	}
	else
	{
		next_token = NULL;
	}
	return token_start;
}

char **_split_string(char *str, const char *delim, int *num_tokens)
{
	// Allocate an array of pointers to char
	char **tokens = NULL;
	int tokens_size = 0;

	// Split the string by the delimiter
	char *token = _strtok(str, delim);
	while (token != NULL)
	{
		// Add the token to the array
		if (tokens_size == 0)
		{
			tokens = (char **)malloc(sizeof(char *));
		}
		else
		{
			tokens = (char **)realloc(tokens, (tokens_size + 1) * sizeof(char *));
		}

		if (tokens == NULL)
		{
			printf("Error: Memory allocation failed\n");
			exit(1);
		}

		tokens[tokens_size] = token;
		tokens_size++;

		// Get the next token
		token = strtok(NULL, delim);
	}

	// Set the number of tokens
	*num_tokens = tokens_size;

	return tokens;
}
