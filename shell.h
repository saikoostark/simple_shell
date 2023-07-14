#ifndef SHELL_H
#define SHELL_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

/* stringuser */
char **_split_string(char *str, char *delim, size_t *count);
void _remove_comment(char **strs);
#endif
