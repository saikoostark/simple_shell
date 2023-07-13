#ifndef SHELL_H
#define SHELL_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/* stringuser */
char **_split_string(char *str, const char *delim, size_t *num_tokens);
char *_strtok(char *str, const char *delim);
#endif
