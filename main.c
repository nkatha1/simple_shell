#include "shell.h"
/**
 * main - entry point.
 * Return: 0.
 */

int main(void)
{
	char command[MAX_COMMAND_LENGTH];

	while (1)
	{
		printf("PnJShell> ");

		if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL)
		{
			printf("\n");
			break;
		}
		command[strcspn(command, "\n")] = '\0';

		execute_command(command);
	}

	return (0);
}
