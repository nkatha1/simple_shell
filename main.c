#include "shell.h"

/**
 * main - The point of entry.
 * @a: The argument count.
 * @b: The argument vector.
 *
 * Return: int
 */
int main(int a, char **b)
{
	int fd = 2;
	info_t info[] = { INFO_INIT };

	if (a != 2 || b == NULL)
	{
		puts_fd(2, "Invalid argument count\n");
		return (EXIT_FAILURE);
	}
	if (a == 2)
	{
		fd = open(b[1], 0_RDWR);
		if (fd == -1)
		{
			perror("Failure opening file");

			if (errno == EACCES)
				puts_fd(2,"Permission denied\n");
			if (errno == ENOENT)
			{
				puts_fd(2, "File not found\n");
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}
	create_envlist(info);
	read_hist(info);
	hsh(info, b);
	return (EXIT_SUCCESS);
}
