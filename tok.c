#include "shell.h"

/**
* **str_tow2 - splits string
* @s: String pointer
* @t: Delimeter.
*
* Return: char
*/
char **str_tow2(char *s, char t)
{
	char **p;
	int a, b, c, d;
	int n = 0;

	if (s == NULL || s[0] == '\0')
		return (NULL);
	for (a = 0; s[a] != '\0'; a++)
	{
		if (s[a] == t)
			n++;
	}
	if (n == 0)
		return (NULL);
	p = malloc((n + 1) * sizeof(char *));
	if (p == NULL)
		return (NULL);
	a = 0;
	b = 0;
	c = 0;
	while (b < n)
	{
		while (s[a] != t && s[a] != '\0')
		{
			c++;
			a++;
		}
		p[b] = (char *)malloc((c + 1) * sizeof(char));
		if (p[b] == NULL)
		{
			for (d = 0; d < b; d++)
			{
				free(p[d]);
			}
			free(p);
			return (NULL);
		}
		strn_cpy(p[b], s + a - c, c);
		p[b][c] = '\0';
		a++;
		b++;
	}
	p[n] = NULL;

	return (p);
}

/**
 * **str_tow - splits string
 * @s: pointer to string
 * @t: Delimeter.
 *
 * Return: char
 */
char **str_tow(char *s, char *t)
{
	char **p;
	int a, b, c, d, e;
	int n = 0;

	if (s == NULL || s[0] == '\0')
		return (NULL);
	if (t == NULL)
		t = " ";
	for (a = 0; s[a] != '\0'; a++)
	{
		if (!is_delim(s[a], t) && (is_delim(s[a + 1], t ||
						s[a + 1] == '\0')))
			n++;
	}
	if (n == 0)
		return (NULL);
	p = malloc((n + 1) * sizeof(char *));
	if (!p)
		return (NULL);

	a = 0;
	b = 0;
	while (b < n)
	{
		while (is_delim(s[a], t))
			a++;

		c = 0;
		while (!is_delim(s[a + c], t) && s[a + c])
			c++;

		p[b] = malloc((c + 1) * sizeof(char));
		if (!p[b])
		{
		for (e = 0; e < b; e++)
			free(p[e]);
		free(p);
		return (NULL);
		}

		for (d = 0; d < c; d++)
			p[b][d] = s[a++];

		p[b][d] = '\0';
		b++;
	}
	p[b] = NULL;
	return (p);
}
