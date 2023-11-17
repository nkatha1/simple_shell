#include "shell.h"
/**
 * print_number_in - print number
 * @n: integer
 */
void print_number_in(int n)
{
	unsigned int i = n;

	if (n < 0)
	{
		_putchar('-');
		i = -i;
	}
	if ((i / 10) > 0)
		print_number(i / 10);

	_putchar(i % 10 + '0');
}
/**
 * print_number - prints numbers
 * @n: unsigned integer
 */
void print_number(unsigned int n)
{
	unsigned int i = n;

	if ((i / 10) > 0)
		print_number(i / 10);

	_putchar(i % 10 + '0');
}
