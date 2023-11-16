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
	list_t *node = NULL;
	char *s = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (n = 1; info->argv[n]; n++)
	{
		s = str_chr(info->argv[n], '=');
		if (s)
		{
			alias_set(info, info->argv[n]);
		}
		else
			print_alias(node_start(info->alias, info->argv[n], '='));
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

	c = str_chr(str, '=');
	if (!c)
		return (1);
	if (!*++c)
		return (alias_unset(info, str));

	alias_unset(info, str);
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
	if (!c)
		return (1);

	s = *c;
	*c = 0;

	index = get_node(info->alias, node_start(info->alias, str, -1));

	if (index < 0)
		return (1);

	res = delete_node(&(info->alias), index);
	*c = s;

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

	if (node)
	{
		c = str_chr(node->str, '=');
		for (s = node->str; s <= c; s++)
			_putchar(*s);
		_putchar('\'');
		_puts(c + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}
/**
 * my_hist - shows history
 * @info: poiter to struct
 *
 * Return: int
 */
int my_hist(info_t *info)
{
	print_list(info->hist);
	return (0);
}
