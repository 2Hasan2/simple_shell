#include "shell.h"

/**
 * built_in_command - Searches for a built-in command
 * and returns its corresponding function.
 * @str: The command to search for.
 * Return: A pointer to the function corresponding
 * to the built-in command, or NULL if not found.
 */
int (*built_in_command(char *str))(char *, char **, char *, char **, int, int)
{
	built commands[] = {
		{"env", ENV},
		{"exit", EXIT},
		{"cd", CD},
		{NULL, NULL}
	};
	int i = 0;

	while (commands[i].command)
	{
		if (_strcmp(commands[i].command, str) == 0)
			return (commands[i].fun);
		i++;
	}
	return (NULL);
}
