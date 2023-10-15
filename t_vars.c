#include "shell.h"

/**
 * is_chain - If the buffer character is a delimeyer chain,it tests so.
 * @info: Struct parameter.
 * @buf: Buffers character.
 * @p: Current position in buffer adress.
 *
 * Return: If chain delimeter, it returns 1, o/w returns 0.
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf [ j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf [j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';') /* found at the end of the command */
	{
		buf[j] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}
/**
 * check_chain - If chaining shoukd continue based on the last status it checks so.
 * @info: Buffers character.
 * @buf: Buffers character.
 * @p: Current position buffers adress.
 * @i: Position that is starting in the buffer.
 * @len: Buffers length.
 *
 * Return: It returns void.
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
	*p = j;

}

/**
 * replace_alias - In the tokenized string, it replaces an alias.
 * @info: Struct parameter.
 *
 * Return: If replaced, it returns 1, if o/w 0.
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
		free(info->argv[0];
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
 * replace_vars - The str that is tokenized it replaces it.
 * @info: Struct parameter.
 *
 * Return: Replaces 1 if its replaces if o/w 0.
 */
int replace_vars(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if(info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_strcmp(info->argv[i], "$?"))
		{
			replace_string(&(info->argv[i]),
				_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (_!strcmp(info->argv[i], "$$"))
		{
			replace_string(&(info->argv[i]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replace_string(&(info-.argv[i]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - The string it replaces it.
 * @old: The strings that is old adress.
 * @new: The str that is new.
 *
 * Return: If it is replaced, it returns 1, o/w 0.
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
