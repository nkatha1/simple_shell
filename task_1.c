#include "shell.h"
/**
 * execute_command - used to execute a command.
 * @command: command to be executed.
 * Return: 0.
 */

void execute_command(const char *command)
{
	pid_t pid = fork();

	if (pid < 0)
	{
		perror("Fork failed");
		_exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		char *args[2] = {NULL, NULL};

		args[0] = strdup(command);
		execve(command, args, NULL);
		perror("Execution failed");
		_exit(EXIT_FAILURE);
	}
	else
	{
		int status;

		waitpid(pid, &status, 0);
	}
}
