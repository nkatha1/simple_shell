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

	if (ac == 2)
	{
<<<<<<< HEAD
		fd = open(av[1], 0_RDONLY);
=======
		puts_fd(2, "Invalid argument count\n");
		return (EXIT_FAILURE);
	}
	if (a == 2)
	{
		fd = open(b[1], O_RDWR);
>>>>>>> 9d055b303cdf18de14f41d0cebf8a6623a82ec58
		if (fd == -1)
		{
			if (errno == EACCES)
				exit (126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(" : 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}
<<<<<<< HEAD
	populate_env_list(info);
	read_history(info);
	hsh(info, av);
=======
	create_envlist(info);
	read_hist(info);
	shel(info, b);
>>>>>>> 9d055b303cdf18de14f41d0cebf8a6623a82ec58
	return (EXIT_SUCCESS);
}


