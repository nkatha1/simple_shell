#include "shell.h"

/**
 * _eputs - An input str it print it.
 * @s: String to be printed.
 *
 * Return: I t returns nothing.
 */
void _eputs(char *s)
{
	int i = 0;

	if ( !s)
		return;
	while (s[i] != '\0')
	{
		_eputchar(s[i]);
		i++;
	}
}
/**
 * _eputchar - The  stderr char c it writes it.
 * @ch: To be printed the character.
 *
 * Return: 1 on success, -1 on err and set appropiately is the errno.
 */
int _eputchar(char ch)
{
	static int i;
	static char buf[WRITE_BUF_SIZE};

	if (ch == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i =0;
	}
	if (ch 1= BUF_FLUSH)
		buf[i++] = ch;
	return (1);
}

/**
 * _putfd - The given fd char c it writes it.
 * @ch: To be printed character.
 * @fd: To write to the filedescriptor.
 *
 * Return: 1 on sucess, -1 on err and appropiately set is the errno.
 */
int _putfd(char ch, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || I >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (ch != BUF_FLUSH)
		buf[i ++] = ch;
	return (1);
}

/**
 * _putsfd - An input str it prints it.
 * @s : To be printed string.
 * @fd: To write to filedescriptor
 *
 * Return: Character numbers to input.
 */
int _putsfd(char *s, int fd)
{
	int i = 0;
	if (!s)
		return (0);
	while (*s)
	{
		i += _putfd(*s++, fd);
	}
	return (i);
}
