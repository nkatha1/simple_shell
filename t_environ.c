#include "shell.h"

/**
 * _myenv - The current environment it prints it.
 * @info: Potential arguments structure used to mantain
 *         function prototype that is constant.
 * Return: Returns 0 always.
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - Value of the environment variable it gets it.
 * @info: Potential arguments structure used to mantain
 *        function prototype that is constant.
 * @name: The environment variable name.
 * Return: It retuns the value.
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
 * @info: Potential arguments structutre used to mantain 
 *        function prototype that is constant.
 * Return: Returns 0 always.
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
 * _myunsetenv - An environ variable, it removes it.
 * @info: Potential arguments structure used to mantain 
 *        function prototype that is constant.
 * Return: Returns 0 always.
 */
int _myunsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->[i]);

	return (0);
}

/**
 * populate_env_list - An eni list that is linked its populates it.
 * @info: Potential arguments structure used to mantain
 *        function prototype that is constant.
 * Return: Returns 0 always.
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
