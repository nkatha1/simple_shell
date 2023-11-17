#include "shell.h"

/**
 * history - presents history
 * @input: pointer to string
 *
 * Return: int
 */
int history(char *input)
{
	ssize_t ff, w;
	int len = 0;
	char *file = ".shell_history";

	if (!file)
		return (-1);

	ff = open(file, O_CREAT | O_RDWR | O_APPEND, 0600);
	if (ff < 0)
		return (-1);
	if (input)
	{
		while (input[len])
			len++;
		w = write(ff, input, len);
		if (w < 0)
			return (-1);
	}
	return (1);
}

/**
 * free_env - free env variable array
 * @env: environment variables
 */
void free_env(char **env)
{
	int i;

	for (i = 0; env[i]; i++)
	{
		free(env[i]);
	}
}
