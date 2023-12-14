#include "shell.h"
/**
 * _strcat - concatenate two strings.
 * @old: First string to append.
 * @new: Second string to append.
 * Return: Pointer to the resulting string.
 **/
void _strcat(char *new, char *old)
{
	int i = 0, j;

	while (new[i])
		i++;
	for (j = 0; old[j]; j++, i++)
		new[i] = old[j];
	new[i] = '\0';
}
/**
 * _strlen - length of a string.
 * @string: pointer.
 * Return: result.
 */
int _strlen(char *string)
{
	int cifras = 0;

	while (*(string + cifras) != '\0')
		cifras++;
	return (cifras);
}
/**
 * _strcpy - copies the string pointed to by old.
 *
 * @new: pointer.
 * @old: pointer.
 *
 * Return: void.
 */
char *_strcpy(char *new, char *old)
{
	int i;

	for (i = 0; old[i] != '\0'; i++)
		new[i] = old[i];
	new[i] = '\0';
	return (new);
}
/**
 * _strcmp - compare two strings.
 * @str1: string #1.
 * @str2: string #2.
 * Return: 0 if s1 and s2 are equal.
 **/
int _strcmp(char *str1, char *str2)
{
	int i = 0;

	while (str1[i] != '\0' && str2[i] != '\0')
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}
