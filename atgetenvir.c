#include "shell.h"
/**
 * un_setenv - unsets An environment variable
 * @info: pointer to struct
 * @c: pointer to string
 *
 * Return: int
 */
int un_setenv(info_t *info, char *c)
{
	size_t n = 0;
	char *s;
	list_t *node = info->env;

	if (!c || !node)
		return (0);

	while (node != NULL)
	{
		s = start_with(node->str, c);
		if (s && *s == '=')
		{
			info->change_env = delete_node(&(info->env), n);
			return (1);
		}
		node = node->next;
		n++;
	}
	return (0);
}

/**
 * **_getenviron - The string arrray copy of our environ, it returns it.
 * @info: pointer to struct
 *
 * Return : char
 */
char **_getenviron(info_t *info)
{
	char **new_env;

	if (!info)
		return (NULL);

	if (info->change_env || !info->environ)
	{
		new_env = list_strings(info->env);
		if (new_env != NULL)
		{
			free(info->environ);
			info->environ = new_env;
			info->change_env = 0;
		}
		else
		{
			perror("list_strings failed");
			return (NULL);
		}
	}
	return (info->environ);
}

/**
 * set_env - sets an environment variable.
 * @info: Pointer to struct
 * @c: pointer to string
 * @v: pointer to string
 * .
 * Return: int
 */
int set_env(info_t *info, char *c, char *v)
{
	list_t *node = info->env;
	char *buffer = NULL;
	char *s;

	if (!c || !v)
		return (-1);

	buffer = malloc(str_len(v) + str_len(c) + 2);
	if (buffer == NULL)
		return (-1);

	str_cpy(buffer, c);
	str_cat(buffer, "=");
	str_cat(buffer, v);

	while (node)
	{
		s = start_with(node->str, c);
		if (s && *s == '=')
		{
			free(node->str);
			node->str = str_dup(buffer);
			free(buffer);
			info->change_env = 1;
			return (1);
		}
		node = node->next;
	}
	add_node(&(info->env), strdup(buffer), 0);
	free(buffer);
	info->change_env = 1;
	return (0);
}
