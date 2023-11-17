#include "shell.h"
/**
 * parsecmd - parse commands
 * @in: pointer to string
 *
 * Return: pointer to pointer to string
 */
char **parsecmd(char *in)
{
	char *c;
	char **token;
	int n;
	int bufsize = BUFSIZE;

	if (in == NULL)
		return (NULL);

	token = malloc(sizeof(char *) * bufsize);
	if (!token)
	{
		perror("Error");
		return (NULL);
	}
	c = str_tok(in, "\n");
	for (n = 0; c; n++)
	{
		token[n] = c;
		c = str_tok(NULL, "\n");
	}
	token[n] = NULL;

	return (token);
}
