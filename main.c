#include "shell.h"

/**
 * main - The point of entry.
 * @ac: The argument count.
 * @av: The argument vector.
 *
 * Return: On success 0, on error 1.
 */
int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (ac < 2) {
		puts_fd(2, "Invalid argument count\n");
		return (EXIT_FAILURE);
				}

	if (ac >=3)
	{
		fd = open(av[1], O_RDWR);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit (126);
			if (errno == ENOENT)
			{
				puts_fd(2, "No entry\n");
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}
	create_envlist(info);
	read_hist(info);
	shel(info, av);

	return (EXIT_SUCCESS);
}


