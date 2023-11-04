#include "shell.h"

/**
 * is_cmd - If the file is a command that is executable, it determines it.
 * @info: Struct info.
 * @path: The fil's path.
 *
 * Return: If it is true 1, 0 o/w.
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars _ The characters, it duplicates them.
 * @pathstr: String's path.
 * @start: Index that is starting.
 * @stop: Index that is stopping.
 *
 * Return: The new buffer's pointer.
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i <stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}

/**
 * find_path - The path string cmd it finds it.
 * @info: Struct info
 * @pathstr: Strings path.
 * @cmd: Cmd to find.
 *
 * Return: If found, it returns the full path of the cmd or NULL.
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int i + 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ';')
		{
			path = dup_chars(pathstr, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
