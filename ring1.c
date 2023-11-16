#include "shell.h"

/**
 * _puts - print string
 * @s: String to be printed.
 */
void _puts(char *s)
{
	int n;

	if (!s)
		return;

	for (n = 0; s[n] != '\0'; n++)
	{
		_putchar(s[n]);
	}
}

/**
 * str_cpy - copies string.
 * @dest: Destination string.
 * @source: Source string
 *
 * Return: char
 */
char *str_cpy(char *dest, char *source)
{
	int i;

	if (dest == source || source == 0)
		return (dest);
	i = 0;
	while (source[i])
	{
		dest[i] = source[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

/**
 * _putchar - writes to stdout
 * @c: character
 *
 * Return: int
 */
int _putchar(char c)
{
	static char buffer[WRITE_BUF_SIZE];
	static int i;

	if (i >= WRITE_BUF_SIZE || c == BUF_FLUSH)
	{
		write(1, buffer, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buffer[i++] = c;
	return (1);
}

/**
 * str_dup - duplicate string
 * @s: String to duplicate.
 *
 * Return: char
 */
char *str_dup(const char *s)
{
	char *res;
	int len;

	if (s == NULL)
		return (NULL);

	len = 0;
	while (*s++)
		len++;

	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);

	for (len++; len--;)
		res[len] = *--s;

	return (res);
}
