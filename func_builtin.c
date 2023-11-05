#include "shell.h"
/**
 * chadir - changes current directory
 * @info: pointer to a structure
 *
 * Return: int
 */
int chadir(info_t *info)
{
	int res;
	char *c, *s;
	char buf[1024];

	c = getcwd(buf, 1024);
	if (c == NULL)
		perror("getcwd failure\n");
	if (info->argv[1] == NULL)
	{
		s = _getenv(info, "HOME=");
		if (s == NULL)
		{
			res = chdir((s = _getenv(info, "PWD=")) ? s : "/");
		}
		else
			res = chdir(s);
	}
	else if (strcmp(info->argv[1], "-") == 0)
	{
		if (_getenv(info, "OLDPWD=") == NULL)
		{
			printf("%s\n", c);
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		res = chdir((s = _getenv(info, "OLDPWD=")) ? s : "/");
	}
	else
		res = chdir(info->argv[1]);

	if (res == -1)
	{
		perror("can't change directory");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "PWD", getcwd(buf, 1024));
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
	}
	return (0);
}

/**
 * shell_exit - exits the shell
 * @info: pointer to struct
 *
 * Return: int
 */
int shell_exit(info_t *info)
{
	int res;

	if (info->argv[1])
	{
		res = _erratoi(info->argv[1]);
		if (res == -1)
		{
			info->status = 2;
			perror("exit failure");
			printf("%s\n", info->argv[1]);
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-1);
	}
	info->err_num = -1;
	return (-1);
}
