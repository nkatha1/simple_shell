char *_strcpy(char *dest, char *src)
{
	int n;

	n = 0;
	while (src[n])
	{
		dest [n] = src[n];
		n++;
	}
	dest[n] = '\0';
	return (dest);
}

/**
 *str_cat - It concentates the two strings
 * @dest: The first String 
 * @src: The second string
 * Return: First string + second string char *
 */
char *str_cat(char *dest, char *src)
{
	char *s = dest;

	while (*dest != '\0')
	{
		dest++;
	}

	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
		*dest = '\0';
		return (s);
}
/**
 * str_chr - Locate Charactere In String
 * @s: The String Search In
 * @c:Character To Search For
 * Return: Pointer To Char*
 */
char *_strchr(char *s, char c)
{

	do	{

			if (*s == c)
			{
				break;
																		}
		}	while (*s++);

		return (s);
}
/**
 * strn_cmp - Compare Amount (n) Of Characters Of Two Strings.
 * @str1: first String.
 * @str2: second String.
 * @n: Amount Of Characters To Compare.
 *   
 * Return: 1 If The Strings Don't Match Otherwise 0
 */
int strn_cmp(const char *str1, const char *str2, size_t n)
{
	size_t t;

	if (str1 == NULL)
	return (-1);
	for (t = 0; t < n && str2[t]; t++)
	{
	if (str1[t] != str2[t])
		{
																return (1);
																		}
	}
			return (0);
}
/**
 * str_dup - Duplicate A String
 * @str:String
 * Return: Duplicate String Failed Null
 */
char *str_dup(char *str)
{
	size_t len, i;
	char *str2;

		len = _strlen(str);
		str2 = malloc(sizeof(char) * (len + 1));
		if (!str2)
		{
		return (NULL);
		}

		for (i = 0; i <= len; i++)
		{
		str2[i] = str[i];
		}

		return (str2);
}

