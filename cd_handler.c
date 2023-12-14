#include "shell.h"

/**
 * change_to_home - Change to the home directory.
 * @arg: User-given arguments.
 * @file: File.
 * @environ: Environment variables.
 * @count: Execution counter.
 *
 * Return: 0 on success, 127 on failure.
 */
int change_to_home(char **arg, char *file, char **environ, int count)
{
	char *home = Get_Env(environ, "HOME");

	if (!home)
	{
		print_err(file, arg[0], count, ERROR_HOME);
		return (127);
	}

	if (chdir(home) == -1)
	{
		print_err(file, arg[0], count, ERROR_HOME);
		free(home);
		return (127);
	}

	free(home);
	return (0);
}

/**
 * change_to_oldpwd - Change to the oldpwd directory.
 * @arg: User-given arguments.
 * @file: File.
 * @environ: Environment variables.
 * @count: Execution counter.
 *
 * Return: 0 on success, 127 on failure.
 */
int change_to_oldpwd(char **arg, char *file, char **environ, int count)
{
	char *oldpwd = Get_Env(environ, "OLDPWD");

	if (!oldpwd)
	{
		print_err(file, arg[0], count, ERROR_OLDPWD);
		return (127);
	}

	if (chdir(oldpwd) == -1)
	{
		print_err(file, arg[0], count, ERROR_OLDPWD);
		free(oldpwd);
		return (127);
	}

	free(oldpwd);
	return (0);
}

/**
 * change_to_directory - Change to the specified directory.
 * @arg: User-given arguments.
 * @file: File.
 * @count: Execution counter.
 *
 * Return: 0 on success, 127 on failure.
 */
int change_to_directory(char **arg, char *file, int count)
{
	if (chdir(arg[1]) == -1)
	{
		print_err(file, arg[0], count, ERROR_NOT_FILE_DIR);
		return (127);
	}

	return (0);
}
