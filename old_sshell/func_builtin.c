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
	if (!c)
		_puts("getcwd failure\n");
	if (!info->argv[1])
	{
		s = get_env(info, "HOME=");
		if (!s)
		{
			res = chdir((s = get_env(info, "PWD=")) ? s : "/");
		}
		else
			res = chdir(s);
	}
	else if (str_cmp(info->argv[1], "-") == 0)
	{
		if (!get_env(info, "OLDPWD="))
		{
			_puts(c);
			_putchar('\n');
			return (1);
		}
		_puts(get_env(info, "OLDPWD=")), _putchar('\n');
		res = chdir((s = get_env(info, "OLDPWD=")) ? s : "/");
	}
	else
		res = chdir(info->argv[1]);

	if (res == -1)
	{
		print_error(info, "can't change directory");
		e_puts(info->argv[1]), e_putc('\n');
	}
	else
	{
		set_env(info, "OLDPWD", get_env(info, "PWD="));
		set_env(info, "PWD", getcwd(buf, 1024));
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
		res = str_int(info->argv[1]);
		if (res == -1)
		{
			info->status = 2;
			print_error(info, "invalid number: ");
			e_puts(info->argv[1]);
			e_putc('\n');
			return (1);
		}
		info->err_num = str_int(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}
