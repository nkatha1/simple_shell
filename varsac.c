#include "shell.h"
/**
 * replace_str - function that replaces string
 * @former: pointer to pointer to old string
 * @current: pointer to string
 *
 * Return: int
 */
int replace_str(char **former, char *current)
{
	char *new_str = str_dup(current);

	if (!new_str)
		return (-1);

	free(*former);
	*former = new_str;
	return (0);
}

/**
 * chain_delim - tests if current character is a chain delimeter
 * @info: pointer to Struct
 * @buffer: pointer to memory area
 * @n: current position adress.
 *
 * Return: Int
 */
int chain_delim(info_t *info, char *buffer, size_t *n)
{
	size_t j = *n;

	if (buffer[j] == '&' && buffer[j + 1] == '&')
	{
		buffer[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buffer[j] == '|' && buffer[j + 1]  == '|')
	{
		buffer[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buffer[j] == ';')
	{
		buffer[j] = '\0';
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*n = j;
	return (1);
}
/**
 * rep_alias - replaces alias
 * @info: pointer to struct
 *
 * Return: int
 */
int rep_alias(info_t *info)
{
	list_t *node;
	char *c;
	int n;

	for (n = 0; n < ALIAS_REPLACE_LIMIT; n++)
	{
		node = node_start(info->alias, info->argv[0], '=');
		if (node == NULL)
			return (1);

		free(info->argv[0]);

		c = str_chr(node->str, '=');
		if (c == NULL)
			return (1);

		c = str_dup(c + 1);
		if (c == NULL)
			return (1);
		info->argv[0] = c;
	}
	return (0);
}

/**
 * checkchain - checks if we should continue chaining
 * @info: pointer to struct
 * @buffer: pointer to string
 * @n: pointer to address
 * @i: starting buffer position
 * @len: length of buffer
 */
void checkchain(info_t *info, char *buffer, size_t *n, size_t i, size_t len)
{
	size_t j = *n;

	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buffer[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buffer[i] = 0;
			j = len;
		}
	}
	*n = j;
}
/**
 * rep_variables - replaces the variables.
 * @info: pointer to struct
 *
 * Return: Int
 */
int rep_variables(info_t *info)
{
	list_t *node;
	int i;
	char *convert_status;
	char *pid_str, *val;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!str_cmp(info->argv[i], "$?"))
		{
			convert_status = str_dup(convert_num(info->status, 10, 0));
			if (convert_status == NULL)
				return (1);
			replace_str(&(info->argv[i]), convert_status);
			continue;
		}
		if (!str_cmp(info->argv[i], "$$"))
		{
			pid_str = str_dup(convert_num(getpid(), 10, 0));
			if (pid_str == NULL)
				return (1);
			replace_str(&(info->argv[i]), pid_str);
			continue;
		}
		node = node_start(info->env, &info->argv[i][1], '=');
		if (node)
		{
			val = str_dup(str_chr(node->str, '=') + 1);
			if (val == NULL)
				return (1);
			replace_str(&(info->argv[i]), val);
			continue;
		}
		perror("Error: Unrecognized variable");
		replace_str(&info->argv[i], str_dup(""));
	}
	return (0);
}
