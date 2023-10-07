#include "shell.h"

/**
 * interactive - If shell is interactive it returns true.
 * @info: The adress of the struct.
 *
 * Return: If in interactive mode it ret 1,o/w ret 0.
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - If char is a delimeter it checks it.
 * @char: The character to check.
 * @delim: String delimeter.
 * Return: If it is true it ret 1, if false it is 0.
 */
int is_delim(char char, char *d)
{
	while (*delim)
		if (*delim++ == char)
			return (1);
	return (0);
}

/**
 * _isalpha - The alphabetic char it checks for it.
 * @char: The input character.
 * Return: If char is alphabetic it ret 1, if o/w 0.
*/

int _isalpha(int char)
{
	if ((char > = 'a' && char <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - A string to an integer it does the conversion.
 * @str: Converted string to be.
 * Return: If n o numbers in str 0,o/w converted number.
 */

int _atoi(char *str)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i=0; str[i] != '\0' && flag != 2; i++)
	{
		if (str[i] == '-')
			sign *= -1;

		if (str[i] >= '0' && str[i] <= '9')
		{
			flag = 1;
			result *=10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else 
		output = result;

	return (output);

}
