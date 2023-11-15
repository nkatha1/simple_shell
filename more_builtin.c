#include "shell.h"
/**
 * my_alias - manage alias
 * @info: pointer to struct
 *
 * Return: int
 */
int my_alias(info_t *info)
{
	int n;
	list_t *node, *match;
	char *s = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node != NULL)
		{
			print_alias(node);
			node = node->next;
		}
	}
	for (n = 1; info->argv[n]; n++)
	{
		s = strchr(info->argv[n], '=');
		if (s)
		{
			if (info->argv[n] != NULL)
			{
				if (alias_set(info, info->argv[n]) != 0)
					return (1);
			}
		}
		else
		{
			match = node_start(info->alias, info->argv[n], '=');
			while (match != NULL)
			{
				print_alias(match);
				match = match->next;
			}
		}
	}
	return (0);
}

/**
 * alias_set - sets string alias
 * @info: pointer to struct
 * @str: string ehose alias is to be set
 *
 * Return: int
 */
int alias_set(info_t *info, char *str)
{
	char *c;

	c = strchr(str, '=');
	if (c == NULL)
		return (1);
	else
		return (alias_unset(info, str));

	return (add_endnode(&(info->alias), str, 0) == NULL);
}
/**
 * alias_unset - unsets string alias
 * @info: pointer to struct
 * @str: the alias string
 *
 * Return: int
 */
int alias_unset(info_t *info, char *str)
{
	int res, index;
	char *c, s;

	c = strchr(str, '=');
	if (c == NULL)
		return (1);

	s = *c;
	*c = '\0';

	index = get_node(info->alias, node_start(info->alias, str, -1));
	*c = s;

	if (index < 0)
		return (1);

	res = delete_node(info->alias, index);

	return (res);
}
/**
 * print_alias - prints alias
 * @node: pointer to struct
 * Return: int
 */
int print_alias(list_t *node)
{
	char *c, *s;

	if (node == NULL)
		return (1);

	c = strchr(node->str, '=');
	if (c == NULL)
		return (1);

	for (s = node->str; s <= c; s++)
		_putchar(*s);

	_puts(c + 1);
	return (0);
}
