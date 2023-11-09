#include "shell.h"

/**
 * _puts - An input string, it prints it.
 * @rin: String to be printed.
 *
 * Return: It returns nothing.
 */
void _puts(char *rin)
{
	int i = 0;

	if (!rin)
		return;
	while (rin[i] != '\0')
	{
		_putchar(rin[i]);
		i++;
	}
}

/**
 * _scp -It copies a string.
 * @st: Destination.
 * @rc: Source.
 *
 * Return: Destination pointer.
 */
char *_scp(char *st, char *rc)
{
	int i = 0;

	if (st == rc || rc == 0)
		return (st);
	while (rc[i])
	{
		st[i] = rc[i];
		i++;
	}
	st[i] = 0;
	return (st);
}

/**
 * _putchar - The char c to stdout, it writes it.
 * @pc: Char to print.
 *
 * Return: 1 on success, -1 on error, errno set appropiately.
 */
int _putchar(char pc)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (pc == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (pc !=BUF_FLUSH)
		buf[i++] = pc;
	return (1);
}

/**
 * _dp - The string, it duplicates it.
 * @tr: String to duplicate.
 *
 * Return: Duplicated string pointer.
 */
char *_dp(const char *tr)
{
	int length = 0;
	char *ret;

	if (tr == NULL)
		return (NULL);
	while (*tr++)
		lenth++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--tr;
	return (ret);
}

