#ifndef SHELL_H
#define SHELL_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


/* stringuser */
char **split_string(char *str, const char *delim, int *num_tokens);
char *my_strtok(char *str, const char *delim);
#endif
