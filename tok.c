#include "shell.h"

/**

* **troh1 - It does the splitting of the string into words.
* @is: String input.
* @t: Delimeter.
* Return: It returns a ptr to the string array, failure returns NULL.
*/
char **troh1(char *is, char *t)
{
	int i, j, k, numWords = 0;
	char **is;

	if (is == NULL || is[0] == 0)
		return (NULL);
	for (i = 0; is[i] != '\0'; i++)
		if ((is[i] != t && is[i + 1] == t) ||
			(is[i] !=t && !is[i + 1]) || is[i + 1] == t)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if ( !s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j ++)
	{
		while (is[i] == t && is [ i + k] && is[ i + k] != t)
		       k++;
	s[j] = malloc(( k + 1) * sizeof(char));
	if (!s[j])
	{
		for (k = 0; k < j; k++)
			free(s[k]);
	free(s);
	return (NULL);
	}
for (m = 0; m < k; m++)
	s[j][m] = is[i++];
	s[k][m] = 0;
}
s[j] = NULL;
return (s);
}

/**
 *  **troh2 - Delimeters that are repeated are ignored,and it does the 
 *            splitting of string into words.
 * @is: String input.
 * @t: Delimeter.
 * Return: The array strings pointer, failure returns NULL.
 */
char **troh2(char *is, char *t)
{
	int i, j, k, m, numwords = 0;
	char **is;
	
	if (str == NULL || is[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; is[i] != '\0'; i++)
		if (!is_delim(is[i], t) && (is_delim(is[i + 1], t)
			numwords++;


	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (is_delim(is[i], t))
			i++;
		k = 0;
		while (!is_delim(t[ i + k], t) && is[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
		for (k = 0; k <j; k++)
			free(s[k]);
		free(s);
		return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = is[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
