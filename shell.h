#ifndef SHELL_H
#define SHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <stddef.h>
#include <sys/stat.h>
#include <signal.h>

extern char **envs;

typedef struct builtin
{
	char *name;
	void (*func)(char **);
} builtin;

/* string_functions.c */
char **_split_string(char *str, char *delim, size_t *count);
void _remove_comment(char **strs);
char *_concat_all(char *name, char *sep, char *value);

/* path_linker.c */
char *_getenv(const char *name);
char *_isExist(char *command);
void _replace_cmd(char **argv);

/* builtin.c */
void _env(char **argv);
void _setenv(char **argv);
void _unsetenv(char **argv);
void (*checkbuild(char **arv))(char **arv);

#endif
