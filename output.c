#include "shell.h"
/**
 * pre_error - prints output
 * @argv: pointer to pointer to string
 * @n: integer
 * @in: input
 */
void pre_error(char **argv, int n, char **in)
{
	char *c = _itoa(n);

	PRINTER(argv[0]);
	PRINTER(": ");
	PRINTER(c);
	PRINTER(": ");
	PRINTER(in[0]);
	PRINTER(": invalid entry: ");
	PRINTER(input[1]);
	PRINTER("\n");
	free(c);
}
