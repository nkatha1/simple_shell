#include "shell.h"
/**
 * interact - chacks if shell is in interactive mode
 * @info: pointer to struct
 *
 * Return: int
 */
int interact(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}
/**
 * _atoi - converts string to int
 * @c: string to be converted
 *
 * Return: int
 */
int _atoi(char *c)
{
	unsigned int i = 0;
	int n, res;
	int sign = 1, flag = 0;

	for (n = 0; c[n] != '\0' && flag != 2; n++)
	{
		if (c[n] == '-')
			sign *= -1;

		if (c[n] >= '0' && c[n] <= '9')
		{
			flag = 1;
			i *= 10;
			i += (c[n] - '0');
		}
		else if (flag == -1)
			flag = 2;
	}
	if (sign == -1)
		res = -i;
	else
		res = i;

	return (res);
}
/**
 * _isalpha - checks if alphabetic character
 * @n: character being checked
 *
 * Return: int
 */
int _isalpha(int n)
{
	if ((n >= 'A' && n <= 'Z') || (n >= 'a' && n <= 'z'))
		return (1);

	return (0);
}
/**
 * _isdelim - checks if its a delimiter
 * @c: character to be checked
 * @delim: delimeter
 *
 * Return: int
 */
int _isdelim(char c, char *delim)
{
	while (*delim != '\0')
	{
		if (*delim == c)
		{
			return (1);
		}
		delim++;
	}
	return (0);
}

