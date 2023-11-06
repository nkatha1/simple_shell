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
	int i = 0, j;
	int c[12];
	
	if (fd != 1)
		fd = 2;

	j = 0;
	if (n < 0)
	{
		_putchar('-');
		j++;
		n = -n;
	}
	if (n == 0)
		c[i++] = 0;
	else
	{
		while (n > 0)
		{
			c[i] = n % 10;
			n /= 10;
			i++;
		}
	}
	for (i--; i >= 0; i--)
	{
		_putchar('0' + c[i]);
		j++;
	}
	return(j);
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
	static char str[] = "0123456789ABCDEF";
	char *ptr;
	unsigned long int k = (n < 0 && !(flags & CONVERT_UNSIGNED)) ? -n : n;

	ptr = &buffer[99];
	*ptr = '\0';
	do {
		*--ptr = str[k % base];
		k /= base;
	} while (k != 0);

	if (n < 0 && !(flags & CONVERT_UNSIGNED))
	{
		*--ptr = '-';
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
	int i;

	i = 0;
	n = 0;
	while (c[n] != '\0')
	{
		if (c[n] == '#' && (n == 0 || c[n - 1] == ' '))
		{
			i = 1;
		}
		if (i)
		{
			if (c[n] != '\n')
				c[n] = ' ';
			else
				i = 0;
		}
		n++;
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
	int sign = 1;
	int res = 0;
	int n = 0;

	if (*c == '-')
	{
		sign = -1;
		c++;
	}
	else if (*c == '+')
		c++;

	while (c[n] != '\0')
	{
		if (c[n] >= '0' && c[n] <= '9')
		{
			if (res > (INT_MAX - (c[n] - '0')) / 10)
				return (-1);
		}
		res = res * 10 + (c[n] - '0');
		else
			return (-1);
		n++;
	}
	return (res * sign);
}
