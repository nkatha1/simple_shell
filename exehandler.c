#include "shell.h"
/**
 * handle_builtin - It handles the builtin 
 * @cmd: The cmd
 * 
 * Return: integer
 */
int handle_builtin(char **cmd, int er)
{
	bul_t bil[] = {

		{"history", history_dis},
		{"help", display_help},
		{"cd", change_dir},
		{"echo", echo_bul},
		{"env", dis_env},
		{NULL, NULL}
	}
	int i = 0;

	while ((bil + i)->command)
	{
		if(str_cmp(cmd[0], (bil + 1)->command) == 0)
		{
			return ((bil + i)->fun (cmd, er));
		}
		i++;
	}
	return (-1);
}

/**
 * check_cmd - The simple shell command it executes it
 *
 * @cmd: The command that is parsed
 * @input: The user input
 * @c:  The Shell Excution Time Case of command that is not found
 * @argv: The name of the program
 * Return: Case cmmand 1, Null -1, wrong command 0 command executed
 */
int check_cmd(char **cmd, char *input, int c, char **argv)
{
	pid_t pid;
	int status;

	if (*cmd == NULL)
	{
		return (-1);
	}

	pid = fork ();
	if (pid == -1)
	{
	perror("Error");
	return (-1);
	}

	if (pid == 0)
	{
	if(strn_cmp(*cmd, "./", 2)!=0 && strn_cmp(*cmd, "/", 1) != 0)
	{
	path_cmd(cmd);
	}

	if (execve(*cmd, cmd, environ) == -1)
	{
	print_error(cmd[0], c, argv);
	free(input);
	free(cmd);
	exit(EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
	}
	wait(&status);
	return (0);
}

/**
 * signal_to_handler - The ^C handle
 * @sig: The captured signal
 * Return: Void
 */
void signal_to_handle(int sig)
{
	if(sig == SIGINT)
	{
	PRINTER("\n$");
	}
}

