#include "shell.h"
/**
 * EXIT - close the shell process.
 * @s: string.
 * @arg: user-given arguments.
 * @environ: environment variables.
 * @count: execution counter.
 * @file: file
 * @out: out
 * Return: out
 */
int EXIT(char *s, char **arg, char *file, char **environ, int count, int out)
{
	(void)environ;

	if (arg[1])
	{
		print_errex(file, arg, count, ERROR_EXIT);
		return (127);
	}
	free(arg);
	free(s);
	exit(out);
}
/**
 *ENV - print environment variables.
 * @s: string.
 * @arg: user-given arguments.
 * @environ: environment variables.
 * @count: execution counter.
 * @file: file
 * @out: out
 * Return: 0
 */
int ENV(char *s, char **arg, char *file, char **environ, int count, int out)
{
	int i = 0;
	(void)s;

	if (arg[1] != NULL)
	{
		print_err(file, arg[0], count, ERROR_NOT_FILE_DIR);
		return (127);
	}
	while (environ[i])
	{
		_putchar(environ[i]);
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
	return (out);
}
/**
 * CD - change the current directory.
 * @s: string.
 * @arg: user-given arguments.
 * @environ: environment variables.
 * @count: execution counter.
 * @file: file
 * @out: out
 * Return: out
 */
int CD(char *s, char **arg, char *file, char **environ, int count, int out)
{
	char *pwd = NULL;
	(void)s;
	(void)environ;

	if (arg[1] == NULL)
	{
		out = change_to_home(arg, file, environ, count);
	}
	else if (_strcmp(arg[1], "-") == 0)
	{
		out = change_to_oldpwd(arg, file, environ, count);
	}
	else
	{
		out = change_to_directory(arg, file, count);
	}

	if (out != 127)
	{
		pwd = getcwd(NULL, 0);
		if (!pwd)
		{
			print_err(file, arg[0], count, ERROR_PWD);
			return (127);
		}
		setenv("OLDPWD", pwd, 1);
		free(pwd);
	}

	return (out);
}
