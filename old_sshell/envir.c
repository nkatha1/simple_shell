#include "shell.h"

/**
 * get_env - The value of an environment variable, it gets it.
 * @info: pointer to struct
 * @form: pointer to string
 *
 * Return: char
 */
char *get_env(info_t *info, const char *form)
{
	char *c;
	list_t *node = info->env;

	while (node)
	{
		c = start_with(node->str, form);
		if (c && *c)
			return (c);
		node = node->next;
	}
	return (NULL);
}
/**
 * my_env - prints current environment
 * @info: pointer to struct
 *
 * Return: int
 */
int my_env(info_t *info)
{
	print_str_list(info->env);
	return (0);
}
/**
 *my_setenv - sets environment variable
* @info: pointer to struct
*
* Return: int
*/
int my_setenv(info_t *info)
{
	char *name;
	char *value;

	if (info->argc != 3)
	{
		e_puts("wrong argument count\n");
		return (1);
	}

	name = info->argv[1];
	value = info->argv[2];
	if (set_env(info, name, value))
		return (0);

	return (1);
}

/**
 * my_unsetenv - unsets an environment variable
 * @info: Pointer to struct
 *
 * Return: int
 */
int my_unsetenv(info_t *info)
{
	int n;

	if (info->argc == 1)
	{
		e_puts("Error: Not enough arguments\n");
		return (1);
	}
	for (n = 1; n <= info->argc; n++)
	{
		un_setenv(info, info->argv[n]);
	}
	return (0);
}

/**
 * create_envlist - populates a linked list on env
 * @info : Pointer to struct
 * .
 * Return: int
 */
int create_envlist(info_t *info)
{
	size_t n;
	list_t *node = NULL;

	for (n = 0; environ[n]; n++)
	{
		add_endnode(&node, environ[n], 0);
	}
	info->env = node;
	return (0);
}
