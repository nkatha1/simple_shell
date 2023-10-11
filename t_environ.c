#include "shell.h"

/**
 * _myenv - prints the current environment.
 * @info: structure containing potential arguments used
 *		to maintain constant function prototypes.
 * Return: Always 0
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - gets the value of an environ variable
 * @info: structure containing potential arguments used
 *		to maintain constant function prototypes.
 * @name: environment variable name.
 * Return: Always 0
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - initialize a new environment variable,
 *		or modify an existing one.
 * @info: structure containing potential arguments used
 *		to maintain constant function prototypes.
 * Return: Always 0
 */
int _mysetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * populate_env_list - populate env linked list
 * @info: structure conataining potential arguments used
 *		to maintain constant function prototypes.
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node(&node, environ[i], 0);
	info->env = node;
	return (0);
}
