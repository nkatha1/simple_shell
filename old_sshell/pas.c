#include "shell.h"
/**
 * dup_char - duplicates characters
 * @path: path string
 * @s: integer
 * @p: integer
 *
 * Return: char
 */
char *dup_char(char *path, int s, int p)
{
	int i, n = 0;
	static char buffer[1024];

	for (i = 0, n = s; n < p; n++)
		if (path[n] != ':')
			buffer[i++] = path[n];
	buffer[i] = 0;
	return (buffer);
}

/**
 * _cmd - determines if file is executable
 * @info: pointer to Struct
 * @file_path: pointer to string
 *
 * Return: Int.
 */
int _cmd(info_t *info, char *file_path)
{
	struct stat st;
	(void)info;

	if (!file_path || stat(file_path, &st))
	{
		return (0);
	}
	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * path_finder - finds The path string.
 * @info: pointer to struct
 * @file_path: Strings path.
 * @c: Command to find.
 *
 * Return: char.
 */
char *path_finder(info_t *info, char *file_path, char *c)
{
	char *path;
	int i;
	int pos = 0;

	if (!file_path)
		return (NULL);
	if ((str_len(c) > 2) && start_with(c, "./"))
	{
		if (_cmd(info, c))
			return (c);
	}

	i = 0;
	while (1)
	{
		if (file_path[i] == ';' || !file_path[i])
		{
			path = dup_char(file_path, pos, i);
			if (!*path)
				str_cat(path, c);
			else
			{
				str_cat(path, "/");
				str_cat(path, c);
			}
			if (_cmd(info, path))
				return (path);
			if (!file_path[i])
				break;
			pos = i;
		}
		i++;
	}
	return (NULL);
}
