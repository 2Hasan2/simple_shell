#include "shell.h"
/**
 * args_non_interactive - separate the user's string into arguments.
 * @file: file
 * @environ: environment variables.
 * @s: pointer string.
 * @out: exit status.
 * Return: out
 */
int args_non_interactive(char *file, char **environ, char *s, int out)
{
	char **arg = NULL, *token = NULL;
	int index = 0, count = 1;

	arg = malloc(64 * sizeof(char *));
	if (!arg)
		exit(0);
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
/**
 * check_input_non_interactive - check the string
 * @str: string
 * @length: size string
 * Return: 0 or 1;
 */
int check_input_non_interactive(char *str, ssize_t length)
{
	ssize_t i = 0;

	while (i < length)
	{
		if (str[i] != '\t' && str[i] != ' ' && str[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}
/**
 * non_interactive - environment in no-interactive mode.
 * @environ: environment variables.
 * @file: file
 */
void non_interactive(char **environ, char *file)
{
	char *str = NULL, buf = '\0';
	int out = 0;
	size_t size = 64, multi = 1, index = 0;

	str = malloc(sizeof(char) * size);
	if (!str)
		exit(0);
	while (read(STDIN_FILENO, &buf, 1) > 0)
	{
		str[index] = buf;
		if (buf == '\0' || buf == '\n')
		{
			str[index + 1] = '\0';
			if (check_input_non_interactive(str, _strlen(str)) == 0)
				out = args_non_interactive(file, environ, str, out);
			index = -1;
			free(str);
			str = malloc(sizeof(char) * size);
			if (!str)
				exit(0);
		}
		if (index == (size * multi) - 2)
		{
			str[index + 1] = '\0';
			str = reallocate_mem(str, size * multi, size * (multi + 1));
			multi++;
		}
		index++;
	}
	free(str);
	exit(out);
}
