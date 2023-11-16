#include "shell.h"
/**
 * null_info - initializes struct
 * @info: pointer to struct
 */
void null_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}
/**
 * create_info - initializes struct
 * @info: pointer to struct
 * @ar: pointer to pointer to string
 */
void create_info(info_t *info, char **ar)
{
	int n = 0;

	info->filename = ar[0];
	if (info->arg)
	{
		info->argv = str_tow(info->arg, "\t");
		if (!info->argv)
		{
			info->argv = (char **)malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = str_dup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (n = 0; info->argv && info->argv[n]; n++)
			;
		info->argc = n;

		rep_alias(info);
		rep_variables(info);
	}
}
/**
 * free_struct - frees structures
 * @info: pointer to struct
 * @n: int
 */
void free_struct(info_t *info, int n)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;

	if (n)
	{
		if (info->env)
			free_l(&(info->env));

		if (info->alias)
			free_l(&(info->alias));

		if (!info->cmd_buf)
			free(info->arg);

		if (info->hist)
			free_l(&(info->hist));

		ffree(info->environ);
			info->environ = NULL;

		freemem((void **)info->cmd_buf);

		if (info->readfd > 2)
			close(info->readfd);

		_putchar(BUF_FLUSH);
	}
}
