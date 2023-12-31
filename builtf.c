#include "shell.h"
/**
 * exit_bul - exit builtin
 * @cmd: pointer to pointer
 * @input: pointer to string
 * @argv: pointer to pointer
 * @c: integer
 */
void exit_bul(char **cmd, char *input, char **argv, int c)
{
	int statue, i = 0;

	if ((cmd[1]) == NULL)
	{
		free(cmd);
		free(input);
		exit(EXIT_SUCCESS);
	}
	while (cmd[1][i])
	{
		if (is_alpha(cmd[1][i++]) != 0)
		{
			pre_error(argv, c, cmd);
			break;
		}
		else
		{
			statue = _atoi(cmd[1]);
			free(cmd);
			free(input);
			exit(statue);
		}
	}
}

/**
 * ch_dir - The dir, it changes it
 * @cmd: Thecommand that is parsed.
 * @er: Last command executed statue
 * Return: Success 1, 0 failure( For old pwd 0 always case no old pwd)
 */
int ch_dir(char **cmd, __attribute__((unused))int er)
{
	int value = -1;
	char cwd[PATH_MAX];

	if ((cmd[1]) == NULL)
		value = chdir(getenv("HOME"));
	else if (str_cmp(cmd[1], "-") == 0)
	{
		value = chdir(getenv("OLDPWD"));
	}
	else
		value = chdir(cmd[1]);

	if (value == -1)
	{
		perror("hsh");
		return (-1);
	}
	else if (value != -1)
	{
		getcwd(cwd, sizeof(cwd));
		setenv("OLPWD", getenv("PWD"), 1);
		setenv("PWD", cwd, 1);
	}
	return (0);
}
/**
 * dis_env - Does the environment variable display
 * @cmd: The command that is parsed.
 * @er: Last executed command statue
 * Return: It is always 0.
 */
int dis_env(__attribute__((unused))char **cmd, __attribute__((unused)) int er)
{
	size_t i;
	int len;

	for (i = 0; environ[i] != NULL; i++)
	{
		len = str_len(environ[i]);
		write(1, environ[i], len);
		write(STDOUT_FILENO, "\n", 1);
	}
	return (0);
}

/**
 * dis_help - Does the display of the help builtin
 * @cmd: The command that is parsed
 * @er: Last executed command statue
 * Return: On success 0, failure -1.
 */
int dis_help(char **cmd, __attribute__((unused))int er)
{
char c;
int fd, fw, rd = 1;

fd = open(cmd[1], O_RDONLY);
if (fd < 0)
{
	perror("Error");
	return (0);
}
while (rd > 0)
{
	rd = read(fd, &c, 1);
	fw = write(STDOUT_FILENO, &c, rd);
	if (fw < 0)
	{
	return (-1);

	}
}
_putchar('\n');
return (0);
}

/**
 * echo_bul - The echo cases, it executes them
 * @st: Last executed command statue
 * @cmd: The command that's parsed
 * Return: Execute noraml echo or 0 always
 */
int echo_bul(char **cmd, int st)
{
	unsigned int pid = getppid();
	char *path;

	if (strn_cmp(cmd[1], "$?", 2) == 0)
	{
		print_number_in(st);
		PRINTER("\n");
	}
	else if (strn_cmp(cmd[1], "$$", 2) == 0)
	{
		print_number(pid);
		PRINTER("\n");
	}
	else if (strn_cmp(cmd[1], "$PATH", 5) == 0)
	{
		path = get_env("PATH");
		PRINTER(path);
		PRINTER("\n");
		free(path);
	}
	else
	{
		return (print_echo(cmd));
	}
	return (1);
}
