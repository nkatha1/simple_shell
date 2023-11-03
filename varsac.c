#include "shell.h"

/**
 * is_chain -If the current character in the buffer is a chain delimeter
 * 		it tests that.
 * @info: Struct parameter.
 * @buf: Character's buffer.
 * @p: In buffer current position adress.
 *
 * Return: If it is a chain delimeter returns 1, o/w 0.
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf [j + 1]  == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';') /* E.O.C found */
	{
		buf[j] = 0; /* Semicolon replace with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}
/**
 * check_chain - Based on last status, it checks if we should continue chaining
 * @info: Struct parameter.
 * @buf: Buffers character.
 * @p: Current position adress in buffer.
 * @i: Position that is starting in buffer.
 * @len: The buffers length.
 *
 * Return: void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

if (info->cmd_buf_type == CMD_OR)
{
	if (!info->status)
	{
		buf[i] = 0;
		j = len;
	}
}

*p = j;

/**
 * replace_alias - In a tokenized string, it replaces an alias.
 * @info: Struct parameter.
 *
 * Return: 1 if it it replaced o/w 0.
 */
int replace_alias(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - In the tokenized string it replaces the vars.
 * @info: Struct parameter.
 *
 * Return: If replaced 1, o/w 0.
 */
int replace_vars(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_strcmp(info->argv[i], "$?"))
		{
			replace_string(&(info->argv[i]),
				_strdup(convert_number(info->status, 10, 0)))
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			replace_string(&(info->argv[i]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replace_string(&(info->argv[i]),
				_strdup(_strchr(node->str, '=') +1));
			continue;
		}
		replace_string(&info->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * replace_string _ The string, it replaces it.
 * @old: Old string adress.
 * @new: The string that is new.
 *
 * Return: If replaced 1, o/w 0.
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

