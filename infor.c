#include "shell.h"
/**
 * create_info - initializes struct
 * @info: pointer to struct
 * @ar: pointer to pointer to string
 */
void create_info(info_t *info, char **ar)
{
	info->filename = ar[0];
	if (info->arg != NULL)
	{
		info->argv = str_tow(info->arg, "\t");
		if (info->argv == NULL)
		{
			info->argv = (char **)malloc(sizeof(char *) * 2);
			if (info->argv != NULL)
			{
				info->argv[0] = str_dup(info->arg);
				info->argv[1] = NULL;
				info->argc = 1;
			}
		}
		else
		{
			info->argc = 0;
			while (info->argv[info->argc] != NULL)
				info->argc++;
		}
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
	free(info->argv);
	info->argv = NULL;
	free(info->path);
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

		free(info->environ);
		info->environ = NULL;

		info->cmd_buf = NULL;

		if (info->readfd > 2)
			close(info->readfd);

		_putchar(BUF_FLUSH);
	}
}
