#include "shell.h"

/**
 * main - The point of entry.
 * @a: The argument count.
 * @b: The argument vector.
 *
 * Return: On success 0, on err 1.
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
		fd = open(b[1], 0_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(b[0]);
				_eputs(": 0: Can't open ");
				_eputs(b[1]);
				_eputchar('\n');
				_eputhar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}
	populate_env_list(info);
	read_history(info);
	hsh(info, av);
	return (EXIT_SUCCESS);
}


