#include "shell.h"

/**
 * un_setenv - An environment variable, it removes it.
 * @info: Potential arguments structure,that is used to mantain a 
 *        prototype function that is constant.
 * Return: It returns 1 on delete, o/w 0.
 * @v: The env variable property string.
 */
int un_setenv(info_t *info, char *v)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node->str, v);
		if (p && *p == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * _getenviron - The string arrray copy of our environ, it returns it.
 * @info: Potential arguments structure, that is used to manatain a 
 *        prototype function that is constant.
 * Return : It is always 0.
 */
char **_geteenviron(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}
	
	return (info->environ);
}

/**
 * set_env - A new environment variable it starts it,
 *           or it does some changes to an existing one.
 * @info: Potential arguments structure, that is used to manatain a 
 *        prototype function that is constant.
 * @v: Env property's string variable.
 * @vl: Env propery's string value.
 * Return: It is always 0.
 */
int set_env(info_t *info, char *v, char *vl)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!v || !vl)
		return (0);

	buf = malloc(_strlen(v) + _strlen(vl) + 2);
	if ( !buf)
		return (1);
	_strcpy(buf, v);
	_strcat(buf, "=");
	_strcat(buf, vl);
	node = info->env;
	while (node)
	{
		p = starts_with(node->str, v);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
	     

