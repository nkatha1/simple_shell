#include "shell.h"
/**
 * str_cmp - compares strings
 * @str1: pointer to string
 * @str2: pointer to string
 *
 * Return: int
 */
int str_cmp(char *str1, char *str2)
{
int n = 0, i, len, len1;
len = str_len(str1);
len1 = str_len(str2);

	if (str1 == NULL || str2 == NULL)
		return (1);
	if (len != len1)
		return (1);
	for (i = 0; str1[i]; i++)
	{
		if (str1[i] != str2[i])
		{
			n = str1[i] - str2[i];
			break;
		}
		else
			continue;
	}
	return (n);
}

/**
* is_alpha - Check if it is alphabetic
* @c: The character
* Return: If true 1, false 0.
*/
int is_alpha(int c)
{
if (((c >= 65) && (c <= 90)) || ((c >= 97) && (c <= 122)))
{
return (1);
}
else
{
return (0);
}
}

/**
* _itoa - Does the conversion of a string to a character
* @n: The integer to convert
* Return: The character pointer.
*/
char *_itoa(unsigned int n)
{
	int len = 0, i = 0;
	char *s;

	len = intlen(n);
	s = malloc(len + 1);
	if (!s)
		return (NULL);
	*s = '\0';
	while (n / 10)
	{
		s[i] = (n % 10) + '0';
		n /= 10;
		i++;
	}
	s[i] = (n % 10) + '0';
	array_rev(s, len);
	s[i + 1] = '\0';
	return (s);
}

/**
* array_rev - reverses the array
* @arr: The array to reverse
* @len: The length of the array
* Return: void(The array reverse)
*/
void array_rev(char *arr, int len)
{
	int i;
	char tmp;

	for (i = 0; i < (len / 2); i++)
	{
		tmp = arr[i];
		arr[i] = arr[(len - 1) - i];
		arr[(len - 1) - i] = tmp;
	}
}

/**
* intlen - it determines the length of integer
* @n: The given integer
* Return: The lenth of integer
*/
int intlen(int n)
{
	int len = 0;


	while (n != 0)
	{
		len++;
		n /= 10;
	}
return (len);
}
