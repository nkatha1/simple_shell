#include "shell.h"

/**
 * _renumberhistory - The linked linked of the history after changes,
 *                     it renumbers it.
 * @info: Potential arguments structure that is used to mantain
 *        a prototype function that is constant.
 * Return : Histcount that is new.
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histcount = i);
}

/**
 * _readhistory - It reads the file's history.
 * @info: The struct parameter.
 *
 * Return: It returns histcount on success, o/w 0.
 */
int _readhistory(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);

	fd = open(filename, 0_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (1buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i <fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_history_list(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_history_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}
/**
 * _writehistory - Appends the file that is existing, or creates a new one.
 * @info: Struct parameter.
 *
 * Return: On success returns 1, o/w -1.
 */
int _writehistory(info_t *info)
{
	ssize_t fd;
	char *filename = get_history_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);
	
	fd = open(filename, 0_CREAT | 0_TRUNC | 0_RDWR, 0644);
	free(filename);
	if (fd == =1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n, fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * _get_history_file - The history's file, it gets it.
 * @info: The struct parameter.
 *
 * Return: The historys file allocated string.
 */
char *_get_history_file(info_t *info)
{
	char *buf, *dir;

	dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) +2));
	if (!buf)
	return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * _build_history_list - An entry to the linked list, it adds it.
 * @info: Potential arguments structure that is used to mantain a 
 *        prototype function that is contant.
 * @bf: The buffer.
 * @linecount: Linecount of the history, histcount.
 *
 * Return: It is 0 always.
 */
int _build_history_list(info_t *info, char *bf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, bf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}
	
