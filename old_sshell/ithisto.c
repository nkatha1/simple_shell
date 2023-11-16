#include "shell.h"

/**
 * renum_hist - renumbers history.
 * @info: Pointer to struct
 *
 * Return: int
 */
int renum_hist(info_t *info)
{
	int n;
	list_t *node = info->hist;

	n = 0;
	while (node)
	{
		node->num = n++;
		node = node->next;
	}
	return (info->histcount = n);
}

/**
 * read_hist - reads file history.
 * @info: pointer to struct
 *
 * Return: int.
 */
int read_hist(info_t *info)
{
	struct stat st;
	int n, fd, count, form;
	ssize_t len, size = 0;
	char *buffer = NULL;
	char *file = get_hist(info);

	if (!file)
		return (0);

	fd = open(file, O_RDWR);
	free(file);

	if (fd == -1)
		return (0);

	if (!fstat(fd, &st))
		size = st.st_size;
	if (size < 2)
	{
		return (0);
	}
	buffer = malloc(sizeof(char) * (size + 1));
	if (!buffer)
	{
		return (0);
	}

	len = read(fd, buffer, size);
	buffer[size] = 0;
	if (len <= 0)
	{
		return (free(buffer), 0);
	}
	close(fd);

	count = 0;
	form = 0;
	for (n = 0; n < size; n++)
		if (buffer[n] == '\n')
		{
			buffer[n] = 0;
			create_history(info, buffer + form, count++);
			form = n + 1;
		}
	if (form != n)
		create_history(info, buffer + form, count++);

	free(buffer);
	info->histcount = count;
	while (info->histcount-- >= HIST_MAX)
	{
		delete_node(&(info->hist), 0);
	}
	renum_hist(info);
	return (info->histcount);
}
/**
 * w_history - writes history
 * @info: pointer to struct
 *
 * Return: int
 */
int w_history(info_t *info)
{
	list_t *node = NULL;
	ssize_t fd;
	char *file;

	file = get_hist(info);
	if (!file)
		return (-1);

	fd = open(file, O_CREAT |O_TRUNC | O_RDWR, 0664);
	free(file);
	if (fd == -1)
		return (-1);

	for (node = info->hist; node; node = node->next)
	{
		puts_fd(fd, node->str);
		putc_fd(fd, '\n');
	}
	putc_fd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * get_hist - get history file
 * @info: pointer to struct
 *
 * Return: char
 */
char *get_hist(info_t *info)
{
	char *s;
	char *buffer;
	size_t buffer_size;

	s = get_env(info, "HOME=");
	if (!s)
		return (NULL);

	buffer_size = str_len(s) + str_len(HIST_FILE) + 2;
	buffer = malloc(sizeof(char) * buffer_size);
	if (!buffer)
		return (NULL);

	buffer[0] = 0;
	str_cpy(buffer, s);
	str_cat(buffer, "/");
	str_cat(buffer, HIST_FILE);
	buffer[buffer_size - 1] = '\0';

	return (buffer);
}

/**
 * create_history - creates history list
 * @info: Pointer to struct.
 * @buffer: The buffer.
 * @count: number of lines
 *
 * Return: Int
 */
int create_history(info_t *info, char *buffer, int count)
{
	list_t *node = NULL;

	if (info->hist)
		node = info->hist;
	add_node(&node, buffer, count);

	if (info->hist == NULL)
		info->hist = node;
	return (0);
}
