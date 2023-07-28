#include "shell.h"

/**
 * _cd - function
 * @argv: function arg
 * @status: function arg
 * @name: function arg
 */
void _cd(char **argv, int *status, char *name)
{
	char *oldpath = NULL, *newpath = NULL, **oldargs = NULL,
		 **newargs = NULL, *tmp;
	size_t size = 1024;
	(void)oldpath, (void)newargs;

	if (!argv[1])
	{
		tmp = _getenv("HOME");
		if (tmp == NULL)
			return;
		newpath = strdup(_getenv("HOME"));
	}
	else
	{
		if (strcmp(argv[1], (char *)"-") == 0)
			tmp = _getenv("OLDPWD"), newpath = (tmp != NULL) ? strdup(tmp) : NULL;
		else
			newpath = strdup(argv[1]);
	}
	oldpath = strdup(_getenv("PWD"));
	if (newpath != NULL && chdir(newpath) == 0)
	{
		freearg(&newpath), newpath = malloc(1024), getcwd(newpath, size);
		if (argv[1] && strcmp(argv[1], (char *)"-") == 0)
			printf("%s\n", newpath);
		oldargs = malloc(4 * sizeof(char *)), newargs = malloc(4 * sizeof(char *));
		newargs[0] = strdup("setenv"), newargs[1] = strdup("PWD"),
		newargs[2] = strdup(newpath), newargs[3] = NULL;
		oldargs[0] = strdup("setenv"), oldargs[1] = strdup("OLDPWD"),
		oldargs[2] = strdup(oldpath), oldargs[3] = NULL;
		_setenv(oldargs, status, name), _setenv(newargs, status, name);
		freeargs(&newargs), freeargs(&oldargs), freearg(&oldpath), freearg(&newpath);
	}
	else if (newpath != NULL)
	{
		fprintf(stderr, "%s: 1: cd: can't cd to %s\n", name, newpath);
		freearg(&oldpath), freearg(&newpath);
	}
}
