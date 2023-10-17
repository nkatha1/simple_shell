#include "shell.h"

/**
 * _myenv - prints the current environ
 * @info: structure used to maintain
 *	constant function prototypes
 * Return: always 0
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - gets value of environ variable
 * @info: structure that maintains
 *	constant function prototypes
 * @name: environment variable name
 * Return: returns the value
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - initializes a new environ variableor modify existing
 * @info: structure that maintains
 *	constant function prototypes
 * Return: always 0
 */
int _mysetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguments\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * _myunsetenv - removes an environ variable
 * @info: structure that maintains
 *	constant function prototypes
 * Return: always 0
 */
int _myunsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("too few arguments\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * populate_env_list - populates env linked list
 * @info: structure that maintains
 *	constant function prototypes
 * Return: always 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}