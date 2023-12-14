#include "shell.h"

/**
 * custom_getline - Read a line from the given stream
 * @lineptr: Pointer to the buffer where the line is stored
 * @n: Pointer to the size of the buffer
 * @stream: File stream to read from
 *
 * Return: Number of characters read (including newline), or -1 on failure
 */
ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream)
{
	int c;
	size_t i = 0;
	char *temp;

	if (lineptr == NULL || n == NULL)
	{
		errno = EINVAL;
		return (-1);
	}
	if (*lineptr == NULL || *n == 0)
	{
		*n = 128;
		*lineptr = malloc(*n);
		if (*lineptr == NULL)
			return (-1);
	}
	while ((c = fgetc(stream)) != EOF)
	{
		if (i >= *n - 1)
		{
			/* Resize the buffer if needed */
			*n *= 2;
			temp = realloc(*lineptr, *n);
			if (temp == NULL)
				return (-1); /* Allocation error */
			*lineptr = temp;
		}
		(*lineptr)[i++] = c;
		if (c == '\n')
			break; /* Stop reading at newline */
	}
	if (i == 0)
		return (-1); /* No characters read */
	(*lineptr)[i] = '\0'; /* Null-terminate the string */
	return (i); /* Number of characters read (including newline) */
}


/**
 * custom_strtok - custom custom_strtok function.
 * @str: string to tokenize.
 * @delim: delimiter.
 * Return: pointer to the next token.
 */

char *custom_strtok(char *str, const char *delim)
{
	static char *next_token;
	char *token;

	/* If str is NULL, continue from where we left off */
	if (str == NULL)
	{
		str = next_token;
	}

	/* Find the start of the next token */
	str += strspn(str, delim);
	if (*str == '\0')
	{
		next_token = NULL;
		return (NULL);
	}

	/* Find the end of the token */
	token = str;
	str = strpbrk(token, delim);
	if (str == NULL)
	{
		/* This token finishes the string */
		next_token = NULL;
	}
	else
	{
		/* Terminate the token and make next_token point past it */
		*str = '\0';
		next_token = str + 1;
	}

	return (token);
}
