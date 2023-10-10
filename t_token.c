#include "shell.h"

/**
 * strtow - splits a string into words. Repeat delimiters are ignored.
 * @st: Strings input.
 * @d: Strings delimeter.
 * Return: Array of strings pointr, failure or NULL.
 */

char **strtow(char *st, char *d)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (st == NULL || st[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; st[i] != '\0'; i++)
		if (!is_delim(st[i], d) && (is_delim(st[i + 1], d) || !st[i + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (is_delim(st[i], d))
			i++;

		k = 0;
		while (!is_delim(st[i + k], d) && st[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = st[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * **strtow2 - Words in the string it does the splitting.
 * @st: Strings input.
 * @delim: Delimeter.
 * Return: Strings array pointer, failure or NULL.
 */
char **strtow2(char *st, char delim)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (st == NULL || st[0] == 0)
		return (NULL);
	for (i = 0; st[i] != '\0'; i++)
		if ((st[i] != delim && st[i + 1] == delim) ||
		(st[i] != delim && !st[i + 1]) || st[i + 1] == delim)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (st[i] == delim && st[i] != delim)
			i++;
		k = 0;
		while (st[i + k] != delim && st[i + k] && st[i + k] != delim)
			k++;
		s[j] = malloc((k + 1)  * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = st[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}


