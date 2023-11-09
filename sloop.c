#include "shell.h"

/**
 * find_cmd - A command in path, it finds it.
 * @info: Parameter struct and return info.
 *
 * Return: Void
 */
void find_cmd(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0, info->arg[i]; i++)
		if (!is_delim(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive (info) || _getenv(info, "PATH=")
			||info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}

}

/**
 * hsh - The shell loop that is main.
 * @info: Parameter and the return info struct.
 * @am: Agument main() vector.
 *
 * Return: Success 0, error 1, or on error code
 */
int hsh(info_t *info, char **am)
{
	ssize_t r = 0;
	int builtin_ret = 0;
	while (r != -1 && builtin_ret != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		r = get_input(info);
		if (r != -1)
		{
			set_info(info, am);
			builtin_ret = find_builtin(info);
			if (builtin_ret == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
write_history(info);
free_info(info, 1);
if (!interactive(info) && info->status)
	exit(info->status);
if (builtin_ret == -2)
{
	if (info->err_num == -1)
		exit(info->status);
	exit(info->err_num);
}
return (builtin_ret);
}

/**
 * fork_cmd - An exec thread, it forks it to do the cmd run.
 * @info: Parameter struct and return info.
 *
 * Return: It returns void.
 */
void fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT AN ERR FN */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT AN ERR FN */
	}
	else
	{
		wait(&(info->status));
		if (WIFEEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}


/**
 * find_builtin - A builtin command, it finds it.
 * @info: Parameter struct and return info.
 *
 * Return: unsuccesful builtin 1, builtin is successful 0, if builtin 
 *         signals exit -2, if builtin is not found -1.
 */
int find_builtin(info_t *info)

	int i, built_in_rwt = -1;
	builtin_table builtintbl[] = 
	{

		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysentenv},
		{"unsentenv", _myunsentenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	},

for (i =0, builtintbl[i].type; i++)
	if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
	{
		info->linecount++;
		built_in_ret = builtintbl[i].func(info);
		break;
	}
return (built_in_ret);
}
