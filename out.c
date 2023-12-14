#include "shell.h"
/**
 * tap - print a prompt.
 * @number: number to print.
 * Return: void.
 */
void tap(int number)
{
	(void)number;

	write(STDOUT_FILENO, "\nhsh$ ", 6);
}
/**
 * _putchar - print a string.
 * @c: string to print.
 * Return: void.
 */
void _putchar(char *c)
{
	int i = 0;

	while (c[i])
	{
		write(STDOUT_FILENO, &c[i], 1);
		i++;
	}
}
/**
 * print_num - print a number.
 * @number: number to print.
 * Return: void.
 */
void print_num(int number)
{
	int length = 0, aux = 1, i;
	char c;

	if (number < 0)
		write(STDOUT_FILENO, "-", 1);
	while (number / aux >= 10 || number / aux <= -10)
	{
		length++;
		aux = aux * 10;
	}
	for (i = 0; i <= length; i++)
	{
		if (number < 0)
		{
			c = -((number / aux) % 10) + '0';
			write(STDOUT_FILENO, &c, 1);
		}
		else
		{
			c = ((number / aux) % 10) + '0';
			write(STDOUT_FILENO, &c, 1);
		}
		number = number % aux;
		aux = aux / 10;
	}
}
/**
 * print_err - print a error format.
 * @file: execution file.
 * @arg: user-given arguments.
 * @count: execution counter.
 * @message: error message to print.
 * Return: void.
 */
void print_err(char *file, char *arg, int count, char *message)
{
	_putchar(file);
	write(STDOUT_FILENO, ": ", 2);
	print_num(count);
	write(STDOUT_FILENO, ": ", 2);
	_putchar(arg);
	write(STDOUT_FILENO, ": ", 2);
	_putchar(message);
	write(STDOUT_FILENO, "\n", 1);
}
/**
 * print_errex - print error format.
 * @file: execution file.
 * @arg: user-given arguments.
 * @count: execution counter.
 * @message: error message to print.
 */
void print_errex(char *file, char **arg, int count, char *message)
{
	_putchar(file);
	write(STDOUT_FILENO, ": ", 2);
	print_num(count);
	write(STDOUT_FILENO, ": ", 2);
	_putchar(arg[0]);
	write(STDOUT_FILENO, ": ", 2);
	_putchar(message);
	write(STDOUT_FILENO, ": ", 2);
	_putchar(arg[1]);
	write(STDOUT_FILENO, "\n", 1);
}
