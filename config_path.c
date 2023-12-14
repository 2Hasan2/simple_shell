#include "shell.h"
/**
 * Get_Env - get env.
 * @environ: environment variables.
 * @variable: variable.
 * Return: result.
 */
char *Get_Env(char **environ, char *variable)
{
	int i = 0, j, length;
	char *path = NULL, *token = NULL, *result = NULL;

	length = _strlen(variable);
	while (environ[i])
	{
		j = 0;
		while (variable[j])
		{
			if (variable[j] != environ[i][j])
				break;
			j++;
		}
		if (j == length)
			break;
		i++;
	}
	if (!environ[i])
		return (NULL);
	path = malloc(sizeof(char) * (_strlen(environ[i]) + 1));
	if (!path)
		return (NULL);
	_strcpy(path, environ[i]);
	token = custom_strtok(path, "=");
	token = custom_strtok(NULL, "");
	if (!token)
	{
		free(path);
		return (NULL);
	}
	result = malloc(sizeof(char) * (_strlen(token) + 1));
	if (!result)
	{
		free(path);
		return (NULL);
	}
	_strcpy(result, token);
	free(path);
	return (result);
}
/**
 * check_exe - check exec.
 * @path: path.
 * @command: command.
 * Return: NULL.
 */
char *check_exe(char *path, char *command)
{
	char *dir = NULL, *dir_command = NULL;
	int length, entry;

	dir = custom_strtok(path, ":\n");
	while (dir)
	{
		length = _strlen(dir);
		length += _strlen(command);
		dir_command = malloc(sizeof(char) * (length + 2));
		if (!dir_command)
			return (NULL);
		dir_command[0] = '\0';
		_strcat(dir_command, dir);
		_strcat(dir_command, SEP_SLASH);
		_strcat(dir_command, command);
		entry = access(dir_command, F_OK | X_OK | R_OK);
		if (entry == 0)
			return (dir_command);
		free(dir_command);
		dir = custom_strtok(NULL, ":\n");
	}
	return (NULL);
}
/**
 * get_path - separate the string PATH into arguments.
 * @arg: pointer string.
 * @environ: environment variables.
 * @count: execution counter.
 * @file: file
 * Return: 0
 */
int get_path(char **arg, char *file, char **environ, int count)
{
	char *env = NULL, *copy = NULL;
	pid_t mypid;
	int state, out = 0;
	(void)file;
	(void)count;

	env = Get_Env(environ, "PATH");
	if (!env)
		return (-1);
	copy = arg[0];
	arg[0] = check_exe(env, arg[0]);
	if (arg[0] == NULL)
	{
		print_err(file, copy, count, "not found");
		if (env)
			free(env);
		return (127);
	}
	free(env);
	mypid = fork();
	if (mypid == 0)
		execve(arg[0], arg, environ);
	else
	{
		wait(&state);
		free(arg[0]);
		if (WIFEXITED(state))
			out = WEXITSTATUS(state);
	}
	return (out);
}
/**
 * exe_command - find and run a command.
 * @arg: user-given arguments.
 * @environ: environment variables.
 * @file: file
 * @count: count
 * Return: out
 */
int exe_command(char **arg, char *file, char **environ, int count)
{
	int entry, out = 0;
	pid_t mypid;
	int state;

	entry = access(arg[0], F_OK | X_OK | R_OK);
	if (entry == 0)
	{
		mypid = fork();
		if (mypid == 0)
		{
			execve(arg[0], arg, environ);
			exit(0);
		}
		else
		{
		wait(&state);
		if (WIFEXITED(state))
			out = WEXITSTATUS(state);
		}
	}
	else
	{
		out = get_path(arg, file, environ, count);
		if (out == -1)
		{
			print_err(file, arg[0], count, "not found");
			return (1);
		}
	}
	return (out);
}
