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

	while (node != NULL)
	{
		c = start_with(node->str, form);
		if (c != NULL && *c != NULL)
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
	print_liststr(info->env);
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
		perror("wrong argument count\n");
		return (1);
	}

	name = info->argv[1];
	value = info->argv[2];
	if (_setenv(info, name, value))
		return (0);
	else
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
		perror("Error: Not enough arguments\n");
		return (1);
	}
	for (n = 1; n <= info->argc; n++)
	{
		if (_unsetenv(info, info->argv[n]) != 0)
		{
			printf("Failed to unset env variable '%s'\n", info->argv[n]);
			return (1);
		}
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
	ssize_t n;
	list_t *node = NULL;

	for (n = 0; environ[n]; n++)
	{
		add_end_node(&node, environ[n]);
	}
	info->env = node;
	return (0);
}
