#include "shell.h"
/**
 * *strn_cat - concatenates two strings
 * @dest: destination string
 * @src: source string
 * @n: number of bytes to be used
 *
 * Return: char
 */
char *strn_cat(char *dest, char *src, size_t n)
{
	char *c = dest;
	size_t i = 0, j = 0;

	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';

	return (c);
}
/**
 * *strn_cpy - copies string
 * @n: number of bytes to be copied
 * @dest: destination string
 * @src: source string
 *
 * Return: char
 */
char *strn_cpy(char *dest, char *src, size_t n)
{
	char *c = dest;
	size_t i = 0;

	while (i < n - 1 && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';

	return (c);
}
/**
 * *str_chr - locates character
 * @c: string to be checked
 * @s: character to look for
 *
 * Return: char
 */
char *str_chr(char *c, char s)
{
	while (*c != '\0')
	{
		if (*c == s)
			return (c);
		c++;
	}
	return (NULL);
}
