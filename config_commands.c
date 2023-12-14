#include "shell.h"
/**
 * getCommand - get the command to execute.
 * @s: pointer string.
 * @args: arguments.
 * @file: file
 * @env: environment variables.
 * @num: execution num.
 * @out: out
 * Return: out
 */
int getCommand(char *s, char **args, char *file, char **env, int num, int out)
{
	int (*validate)(char *, char **, char *, char **, int, int);

	validate = built_in_command(args[0]);
	if (validate)
		out = validate(s, args, file, env, num, out);
	else
		out = exe_command(args, file, env, num);
	return (out);
}
/**
 * arguments - separate the user's string into arguments.
 * @s: pointer string.
 * @environ: environment variables.
 * @count: execution counter.
 * @file: file
 * @out: out
 * Return: out
 */
int arguments(char *s, char *file, char **environ, int count, int out)
{
	char **arg = NULL, *token = NULL;
	int index = 0;

	arg = malloc(64 * sizeof(char *));
	if (!arg)

	{
		perror(ERROR_ALLOCATION);
		exit(0);
	}
	token = custom_strtok(s, SEP_ESPAC);
	while (token)
	{
		arg[index] = token;
		index++;
		token = custom_strtok(NULL, SEP_ESPAC);
	}
	arg[index] = NULL;
	out = getCommand(s, arg, file, environ, count, out);
	free(arg);
	return (out);
}
