#include "shell.h"
/**
 * putc_fd - writes character to file descriptor
 * @fd: file descriptor
 * @c: character to print
 *
 * Return: int
 */
int putc_fd(int fd, char c)
{
	static char buffer[WRITE_BUF_SIZE];
	static int n = 0;

	 if (n >= WRITE_BUF_SIZE || c == BUF_FLUSH)
	 {
		 if (n > 0)
		 {
			 write(fd, buffer, n);
			 n = 0;
		 }
		 if (c == BUF_FLUSH)
			 write(fd, &c, 1);
	 }
	 if (c != BUF_FLUSH)
	 {
		 buffer[n++] = c;
	 }
	 return (1);
}
/**
 * puts_fd - prints input string
 * @fd: file descriptor to be writtrn to
 * @str: string to print
 *
 * Return: int
 */
int puts_fd(int fd, char *string)
{
	int n;

	if (string == NULL)
		return (0);

	n = 0;
	while (*string != NULL)
	{
		n += putc_fd(fd, *string++);
	}
	return (n);
}
/**
 * e_putc - writes character to stderr
 * @c: character to be written
 *
 * Return: int
 */
int e_putc(char c)
{
	static char buffer[WRITE_BUF_SIZE];
	static int n;

	if (c == BUF_FLUSH || n >= WRITE_BUF_SIZE)
	{
		if (n > 0)
		{
			write(2, buffer, n);
			n = 0;
		}
		if (c == BUF_FLUSH)
			write(2, &c, 1);
	}
	if (c != BUF_FLUSH)
		buffer[n++] = c;
	return (1);
}
/**
 * e_puts - prints input string
 * @string: string to be printed
 */
void e_puts(char *string)
{
	int n;

	n = 0;
	while (string[n] != '\0')
	{
		e_putc(string[n]);
		n++;
	}
}
