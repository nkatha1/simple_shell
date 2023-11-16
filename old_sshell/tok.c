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
		if ((s[a] != t && s[a + 1] == t) || 
					(s[a] != t && !s[a + 1]) || s[a + 1] == t)
			n++;
	}
	if (n == 0)
		return (NULL);
	p = malloc((n + 1) * sizeof(char *));
	if (!p)
		return (NULL);
	for (a = 0, b = 0; b < n; b++)
	{
		while (s[a] == t && s[a] != t)
		{
			a++;
		}
		c = 0;
		while (s[a + c] != t && s[a + c] && s[a + c] != t)
			c++;
		p[b] = (char *)malloc((c + 1) * sizeof(char));
		if (!p[b])
		{
			for (c = 0; c < b; c++)
			{
				free(p[c]);
			}
			free(p);
			return (NULL);
		}
		for (d = 0; d < c; d++)
			p[b][d] = s[a++];
		p[b][d] = 0;
	}
	p[b] = NULL;
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
	int a, b, c, d;
	int n = 0;

	if (s == NULL || s[0] == '\0')
		return (NULL);
	if (!t)
		t = " ";
	for (a = 0; s[a] != '\0'; a++)
	{
		if (!_isdelim(s[a], t) && (_isdelim(s[a + 1], t) ||
						!s[a + 1] == '\0'))
			n++;
	}
	if (n == 0)
		return (NULL);
	p = malloc((n + 1) * sizeof(char *));
	if (!p)
		return (NULL);

	for (a = 0, b = 0; b < n; b++)
	{
		while (_isdelim(s[a], t))
			a++;

		c = 0;
		while (!_isdelim(s[a + c], t) && s[a + c])
			c++;

		p[b] = malloc((c + 1) * sizeof(char));
		if (!p[b])
		{
			for (c = 0; c < b; c++)
				free(p[c]);
			free(p);
			return (NULL);
		}

		for (d = 0; d < c; d++)
			p[b][d] = s[a++];

		p[b][d] = 0;
	}
	p[b] = NULL;
	return (p);
}
