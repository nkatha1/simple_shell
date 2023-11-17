#include "shell.h"

/**
 * history_dis - The description of the history
 * @c: The character
 *
 * Return : An integer
 */
int history_dis(__attribute__((unused))char**c,__attribute__((unused))int s)
{
	char *filename = ".shell_history";
	FILE *ff;
	char *line = NULL;
	size_t len = 0;
	int n = o;
	char *ch;

	ff = fopen(filename, "r");
	if (ff == NULL)
	{
		return (-1);
	}
	while ((getline(&line, &len, ff)) != -1)
	{
		n++;
		ch = _itoa(n);
		PRINTER(ch);
		free(ch);
		PRINTER(line);
		PRINTER(" ");
	}
	if (line)
		free (line);
	fclose(ff);
	return (0);
}

/**
 * print_echo _ It executes noraml echo
 * @input: The command that is parsed
 * Return: An integer
 */
int print_echo(char **input)
{
	int status;
	pid_t mypid;

	mypid = fork();
	if (mypid == 0)
	{
		if (execve("/bin/echo", input, environ) == -1)
		{
			return (-1);
		}
		exit(EXIT_FAILURE);
	}
	else if (mypid <0)
	{
		retutn (-1);
	}
	else
	{
		do {
			waitpid(mypid, &status, WUNTRACED);
		}while (!WIFEEXITED(status) && !WIFSIGNALED(status));
	}
	return (1);
}
