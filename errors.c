#include "shell.h"
/**
 * print_integer - prints integers
 * @fd: file descriptor
 * @n: input
 *
 * Return: int
 */
int print_integer(int fd, int n)
{
	int (*__putchar)(char) = _putchar;
	int i = 0, j;
	unsigned int abs, current;

	if (fd == STDERR_FILENO)
		__putchar = e_putc;

	if (n < 0)
	{
		abs = -n;
		_putchar('-');
		i++;
	}
	else
		abs = n;
	current = abs;
	for (j = 1000000000; j > 1; j /= 10)
	{
		if (abs / j)
		{
			__putchar('0' + current / j);
			i++;
		}
		current %= j;
	}
	__putchar('0' + current);
	i++;

	return (i);
}
/**
 * print_error - prints error message
 * @info: pointer to struct
 * @str: pointer to string
 */
void print_error(info_t *info, char *str)
{
	e_puts(info->filename);
	e_puts(": ");
	print_integer(info->line_number, STDERR_FILENO);
	e_puts(": ");
	e_puts(info->argv[0]);
	e_puts(": ");
	e_puts(str);
}
/**
 * convert_num - converts number
 * @base: integer
 * @n: long int
 * @flags: flag used
 *
 * Return: char
 */
char *convert_num(long int n, int base, int flags)
{
	static char buffer[100];
	static char *str;
	char *ptr;
	char sign = 0;
	unsigned long int k = n;

	if (!(flags & CONVERT_UNSIGNED) && n < 0)
	{
		k = -n;
		sign = '-';
	}
	str = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[99];
	*ptr = '\0';

	do 	{
		*--ptr = str[k % base];
		k /= base;
	} while (k != 0);

	if (sign)
	{
		*--ptr = sign;
	}
	return (ptr);
}
/**
 * replace_comments - replaces # with '/0'
 * @c: pointer to string
 *
 * Return: int
 */
void replace_comments(char *c)
{
	int n;

	for (n = 0; c[n] != '\0'; n++)
		if (c[n] == '#' && (!n || c[n - 1] == ' '))
		{
			c[n] = '\0';
			break;
		}
}
/**
 * str_int - converts string to integer
 * @c: string to be converted
 *
 * Return: int
 */
int str_int(char *c)
{
	unsigned long int res = 0;
	int n = 0;

	if (*c == '+')
		c++;

	for (n = 0; c[n] != '\0'; n++)
	{
		if (c[n] >= '0' && c[n] <= '9')
		{
			res *= 10;
			res += (c[n] - '0');
			if (res > INT_MAX)
			{
				return (-1);
			}
		}
		else
			return (-1);
	}
	return (res);
}
