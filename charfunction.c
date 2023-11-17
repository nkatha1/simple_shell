#include "shell.h"
/**
 * strn_cpy - Copies a string.
 * @dest: The character
 * @src: The character
 * @n: The integer
 * Return: The character
 */

char *strn_cpy(char *dest, char *src, int n)
{
	int i;

	i = 0;
	while (i < n && *(src + 1))
	{
		*(dest + i) = *(src + i);
		i++;
	}
	while (i < n)
	{
		*(dest + i) = '\0';
		i++;
	}
	return (dest);	
}

/**
 * str_len - The strings length
 * @s: Character
 * Return: The integer
 */
int str_len(char *s)
{
	int i;

	for (i = 0; s[i] != '\0'; i++)
	{
		continue;
	}
	return (i);
}

/**
 * _atoi - Does the integer conversion
 * @s: The string
 * Return: An integer
 */
int _atoi(char *s)
{
	int i, n, j, x;

	i = n = 0;
	x = 1;
	while ((s[i] < '0' || s[i] > '9') && (s[i] != '\0'))
	{
		if (s[i] == '-')
		x *= -1;
		i++;
	}
	j = i;
	while ((s[j] >= '0') && (s[j] <= '9'))
	{
		n = (n * 10) + x * ((s[j]) - '0');
		j++;
	}
	return (n);
}

/**
 * _puts - Prints a string
 * @str: Character pointer
 * return: Void
 */
void _puts(char *str)
{
	int i;

	for (i = 0; str[i] != '\0'; i++)
	{
		_putchar(str[i]);
	}
	_putchar('n');
}
