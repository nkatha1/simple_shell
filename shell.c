#include "shell.h"
/**
 * main - programs entry point
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: int
 */
int main(__attribute__((unused)) int argc, char **argv)
{
	char *in, **cm;
	int c = 0, res;
	int s = 1, st = 0;

	if (argv[1] != NULL)
		read_file(argv[1], argv);
	signal(SIGINT, signal_to_handle);

	while (s)
	{
		c++;
		if (isatty(STDIN_FILENO))
			prompt();
		in = get_line();
		if (in[0] == '\0')
			continue;

		history(in);
		cm = parse_cmd(in);
		if (str_cmp(cm[0], "exit") == 0)
		{
			exit_bul(cm, in, argv, c);
		}
		else if (str_cmp(cm[0], "setenv") == 0)
		{
			if (cm[1] != NULL && cmd[2] != NULL)
			{
				res = set_env(cm[1], cm[2]);
				if (res != 0)
					fprintf(stderr, "set_env failed\n");
				else
					fprintf(stderr, "invalid usage of set_env\n");
			}
		}
		else if (str_cmp(cm[0], "unsetenv") == 0)
		{
			if (cm[1] != NULL)
			{
			res = un_setenv(cm[1]);
			if (res != 0)
				fprintf(stderr, "unsetenv failure\n");
			else
				fprintf(stderr, "Invalid usage of unsetenv\n");
			}
		}
		else if (check_builtin(cm) == 0)
		{
			st = handle_builtin(cm, st);
			free_all(cm, in);
			continue;
		}
		else
		{
			st = check_cmd(cm, in, c, argv);
		}
		free_all(cm, in);
	}
	return (s);
}
/**
 * create_env - create environment variables
 * @env: environment variables array
 */
void create_env(char **env)
{
	int n;

	for (n = 0; environ[n]; n++)
		env[n] = str_dup(environ[n]);
	env[n] = NULL;
}
/**
 * check_builtin - checks builtin functions
 * @cm: command to check
 *
 * Return: int
 */
int check_builtin(char **cm)
{
	bul_t fun[] = {
		{"history", NULL},
		{"echo", NULL},
		{"help", NULL},
		{"cd", NULL},
		{NULL, NULL}
	};

	int n = 0;

	if (*cm == NULL)
		return (-1);

	while ((fun + n)->command)
	{
		if (str_cmp(cmd[0], (fun + n)->command) == 0)
			return (0);
		n++;
	}
	return (-1);
}
