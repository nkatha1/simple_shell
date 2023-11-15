#include "shell.h"

/**
 * main - The point of entry.
 * @ac: The argument count.
 * @av: The argument vector.
 *
 * Return: On success 0, on error 1.
 */
int main(int a, char **b)
{
	info_t info[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (a == 2)
	{
		puts_fd(2, "Invalid argument count\n");
		return (EXIT_FAILURE);
	}
	fd = open(b[1], O_RDWR);

	if (fd == -1)
	{
		if (errno == EACCES)
			exit (126);
		if (errno == ENOENT)
		{
			e_puts(b[0]);
			e_puts(" : 0: Can't open ");
			e_puts(b[1]);
			e_putc('\n');
			e_putc(BUF_FLUSH);
			exit(127);
		}
		return (EXIT_FAILURE);
	}
	info->readfd = fd;

	create_envlist(info);
	read_hist(info);
	shel(info, b);

	return (EXIT_SUCCESS);
}


