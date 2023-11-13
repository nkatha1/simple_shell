#include "shell.h"

/**
 * find_command - find command in path
 * @info: Pointer to struct
 */
void find_command(info_t *info)
{
	int n;
	int j;
	char *path = NULL;

	info->path = info->argv[0];

	if (info->linecount_flag == 1)
	{
		info->line_number++;
		info->linecount_flag = 0;
	}
	for (n = 0, j = 0, info->arg[n]; n++)
		if (!_isdelim(info->arg[n], " \t\n"))
			j++;
	if (j == NULL)
		return;

	path = path_finder(info, get_env(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_command(info);
	}
	else
	{
		if ((interact(info) || get_env(info, "PATH=") || info->argv[0][0] == '/'))
			if (_cmd(info, info->argv[0]))
				fork_command(info);
			else if (*(info->arg) != '\n')
			{
				info->status = 127;
				print_error(info, "command not found\n");
			}
	}

}

/**
 * shel - The shell loop
 * @info: Pointer to struct
 * @am: Agument main() vector.
 *
 * Return: int
 */
int shel(info_t *info, char **am)
{
	int bltin_ret = 0;
	ssize_t n = 0;

	while (bltin_ret != -2 && n != -1)
	{
		if (interact(info))
		{
			_puts("$ ");
			e_putc(BUF_FLUSH);
		}
		n = get_form(info);
		if (n != -1)
		{
			create_info(info, am);
			bltin_ret = check_builtin(info);
			if (bltin_ret == -1)
				find_command(info);
		}
		else if (interact(info))
			_putchar('\n');

		free_struct(info, 0);
	}
	w_history(info);
	free_struct(info, 1);

	if (!interact(info) && info->status)
		exit(info->status);
	if (bltin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (bltin_ret);
}

/**
 * fork_command - creates a child process
 * @info: Pointer to struct
 */
void fork_command(info_t *info)
{
	pid_t my_pid;

	my_pid = fork();
	if (my_pid == -1)
	{
		perror("Fork failed");
		return;
	}
	if (my_pid == 0)
	{
		if (execve(info->path, info->argv, _getenviron(info)) == -1)
		{
			free_struct(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission not granted\n");
		}
	}
}

/**
 * check_builtin - find builtin command
 * @info: Pointer to structt
 * 
 * Return: int
 */
int check_builtin(info_t *info)
{
	int i;
	int ret = -1;
	builtin_table bltintabl[] = 
	{
		{"exit", my_exit},
		{"env", my_env},
		{"setenv", my_setenv},
		{"unsetenv", my_unsetenv},
		{"cd", my_cd},
		{"alias", my_alias},
		{NULL, NULL}
	};

	for (i = 0, bltintabl[i].type; i++)
	{
		if (str_cmp(info->argv[0], bltintabl[i].type) == 0)
		{
			info->line_number++;
			ret = bltintabl[i].func(info);
			break;
		}
	}
	return (ret);
}
