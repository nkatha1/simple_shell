#include "shell.h"
/**
 * check_delim - checks delimeter
 * @c: character
 * @str: string eing checked
 *
 * Return: unsigned int
 */
unsigned int check_delim(char c, const char *str)
{
	unsigned int n;

	for (n = 0; str[n] != '\0'; n++)
	{
		if (c == str[n])
			return (1);
	}
	return (0);
}
/**
 * str_tok - tokenize a string
 * @str: pointer to string
 * @d: delimeter
 *
 * Return: char
 */
char *str_tok(char *str, const char *d)
{
unsigned int i;
static char *n;
static char *t;

if (str != NULL)
n = str;
t = n;
if (t == NULL)
return (NULL);

for (i = 0; t[i] != '\0'; i++)
{
if (check_delim(t[i], d) == 0)
break;
}
if (n[i] == '\0' || n[i] == '#')
{
n = NULL;
return (NULL);
}
t = n + i;
n = t;
for (i = 0; n[i] != '\0'; i++)
{
if (check_delim(n[i], d) == 1)
break;
}
if (n[i] == '\0')
n = NULL;
else
{
n[i] = '\0';
n = n + i + 1;
if (*n == '\0')
n = NULL;
}
return (t);
}
