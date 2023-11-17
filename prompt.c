#include "shell.h"
/**
 * print_error - prints errors
 * @in: input string
 * @c: integer
 * @argv: pointer to pointer to string
 */
void print_error(char *in, int c, char **argv)
{
	char *s;

	PRINTER(argv[0]);
	PRINTER(": ");
	s = _itoa(c);
	PRINTER(s);
	free(s);
	PRINTER(": ");
	PRINTER(in);
	PRINTER(": could not find input\n");
}
/**
 * prompt - displays prompt
 */
void prompt(void)
{
	PRINTER("$ ");
}
