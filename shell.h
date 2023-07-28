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
#include <ctype.h>

extern char **environ;
typedef struct builtin
{
	char *name;
	void (*func)(char **);
} builtin;

/* string_functions.c */
char **_split_string(char *str, char *delim, size_t *count);
void _remove_comment(char **strs);
char *_concat_all(char *name, char *sep, char *value);
void _remove_whitespaces(char **str);
char *_strtok(char *str, const char *delimiters);

/* path_linker.c */
char *_getenv(const char *name);
char *_isExist(char *command, int *status);
void _replace_cmd(char **argv);

/* builtin.c */
void __exit(char **argv);
void _env(char **argv);
void _setenv(char **argv);
void _unsetenv(char **argv);
void (*checkbuild(char **arv))(char **arv);

/* main.c */
void _handleCtrlC(int sig_num);
void _readingInput(int argc, char const *argv[], char **str, size_t *size,
				   FILE **filereader, int *isFileReader, int atty, int *status);
char **_argsHandler(char **str, size_t *size);

/* memory.c */
void freearg(char **arg);
void freeargs(char ***argv);

/* helper.c */
void errorfork(int pid);
void checkfreespaces(char **str);
size_t strlendel(const char *str, char del);
int strnncmp(const char *str1, const char *str2, char del1, char del2);
#endif
