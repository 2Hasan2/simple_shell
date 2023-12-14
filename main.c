#include "shell.h"
/**
 * main - main function.
 * @argc: number of arguments.
 * @arg: user-given arguments.
 * @environ: environment variables.
 * Return: 0
 */
int main(int argc, char **arg, char **environ)
{
	(void)argc;
	if (isatty(STDIN_FILENO))
		LOOP(environ, arg[0]);
	else
		non_interactive(environ, arg[0]);
	return (0);
}
