#include "shell.h"
/**
 * exit_bul_file - exit shell case
 * @cm: command to ba parsed
 * @line: input line
 * @fd: file descriptor
 *
 * Return: int
 */
void exit_bul_file(char **cm, char *line, FILE *fd)
{
	int n, st;

	if (cm[1] == NULL)
	{
		free(line);
		free(cm);
		fclose(fd);
		exit(errno);
	}
	while (cm[1][n])
	{
		if (is_alpha(cm[1][n++]) < 0)
			perror("Invalid number");
	}
	st = _atoi(cm[1]);
	free(line);
	free(cm);
	fclose(fd);
	exit(st);
}
/**
 * treat_f - parse commands in a line of a file
 * @line: file line
 * @c: count
 * @fd: file descriptor
 * @argv: argument vector
 */
void treat_f(char *line, int c, FILE *fd, char **argv)
{
	int s = 0;
	char **cm;

	cm = parsecmd(line);

	if (strn_cmp(cm[0], "exit", 4) == 0)
		exit_bul_file(cm, line, fd);
	else if (check_builtin(cm) == 0)
	{
		s = handle_builtin(cm, s);
		free(cm);
	}
	else
	{
		s = check_cmd(cm, line, c, argv);
		free(cm);
	}
}
/**
 * read_file - reads file
 * @file: pointer to string
 * @argv: argument vector
 */
void read_file(char *file, char **argv)
{
	int c = 0;
	size_t length = 0;
	char *line = NULL;
	FILE *fd;

	fd = fopen(file, "r");
	if (fd == NULL)
		exit(EXIT_FAILURE);
	while ((getline(&line, &length, fd)) != -1)
	{
		c++;
		treat_f(line, c, fd, argv);
	}
	if (line)
		free(line);
	fclose(fd);
	exit(0);
}
