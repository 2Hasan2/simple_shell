#include "shell.h"
/**
 * check_input - validate the input string.
 * @str: is the string.
 * @length: string size.
 * Return: 1 if the string is valid, else 0.
 **/
int check_input(char *str, ssize_t length)
{
	ssize_t i = 0, count = 1;

	while (i < length)
	{
		if (str[i] == '\t' || (str[i] == ' '
		&& (str[i + 1] == ' ' || str[i + 1] == '\n')))
		{
			if (str[i] == '\t')
				str[i] = ' ';
			count++;
		}
		i++;
	}
	return (count != i);
}
/**
 * LOOP - interactive mode.
 * @environ: environment variables.
 * @file: file
 */
void LOOP(char **environ, char *file)
{
	char *str = NULL;
	int count = 1, out = 0;
	size_t size = 64;
	ssize_t len_line;

	signal(SIGINT, tap);
	while (1)
	{
		write(STDOUT_FILENO, PROMPT, 2);
		str = malloc(sizeof(char) * size);
		if (!str)
		{
			perror(ERROR_ALLOCATION);
			exit(0);
		}
		len_line = custom_getline(&str, &size, stdin);
		if (len_line == EOF)
		{
			write(STDOUT_FILENO, "\n", 1);
			free(str);
			exit(out);
		}
		if (len_line > 1 && str[0] != '\n')
		{
			if (check_input(str, len_line) > 0)
				out = arguments(str, file, environ, count, out);
		}
		count++;
		free(str);
	}
}
