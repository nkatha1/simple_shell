#include "shell.h"

/**
 * start_with - checks beginning of string
 * @str1: string to be checked
 * @str2: substring to look for
 *
 * Return: char
 */
char *start_with(const char *str1, const char *str2)
{
	const char *str3 = str2;

	while (*str1 && *str2)
	{
		if (*str2 != *str1)
			return (NULL);
		str1++;
		str2++;
	}
	if (*str2 == '\0')
		return ((char *)str3);

	return (NULL);
}

/**
 * str_len - returns string length
 * @c: pointer to String.
 *
 * Return: int
 */
int str_len(char *c)
{
	int n;

	if (c == NULL)
		return (0);

	n = 0;
	while (*c != '\0')
	{
		n++;
		c++;
	}
	return (n);
}

/**
 * str_cat - concatenates two strings
 * @dest: Buffers destination.
 * @source: Buffers source.
 *
 * Return: char
 */
char *str_cat(char *dest, const char *source)
{
	char *res = dest;

	while (*dest)
		dest++;
	while (*source)
		*dest++ = *source++;
	*dest = '\0';
	return (res);
}

/**
 * str_cmp - compares strings
 * @str1: first string
 * @str2: second string
 *
 * Return: int
 */
int str_cmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else if (*str1 > *str2)
		return (1);
	else
		return (-1);
}
