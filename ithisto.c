#include "shell.h"

/**
 * renum_hist - renumbers history.
 * @info: Pointer to struct
 *
 * Return : int
 */
int renum_hist(info_t *info)
{
	int n;
	list_t *node = info->hist;

	n = 0;
	while (node != NULL)
	{
		node->num = n++;
		node = node->next;
	}
	info->histcount = n;
	return (n);
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
	char *buffer = NULL
	char *file = get_hist(info);

	if (file == NULL)
		return (0);

	fd = open(file, 0_RDWR);
	free(file);

	if (fd == -1)
		return (0);

	if (fstat(fd, &st) == -1)
		return (0);

	size = st.st_size;
	if (size < 2)
	{
		close(fd);
		return (0);
	}
	buffer = malloc(size + 1);
	if (buffer == NULL)
	{
		close(fd);
		return (0);
	}

	len = read(fd, buffer, size);
	if (len <= 0)
	{
		close(fd);
		free(buffer);
		return (0);
	}
	buffer[len] = '\0';
	close(fd);

	count = 0;
	form = 0;
	for (n = 0; n < len; n++)
		if (buffer[n] == '\n')
		{
			buffer[n] = '\0';
			build_hist(info, buffer + form, count++);
			form = n + 1;
		}
	if (form != n)
		build_hist(info, buffer + form, count++);

	free(buffer);
	info->histcount = count;
	while (info->histcount >= HIST_MAX)
	{
		delete_node(&(info->hist), 0);
		info->histcount--;
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
	int fd;
	char *file;

	file = get_hist(info);
	if (file == NULL)
		return (-1);

	fd = open(file, O_CREAT | O_RDWR, 0664);
	if (fd == -1)
		return (-1);
	free(file);

	for (node = info->hist; node; node = node->next)
	{
		puts_fd(node->str, fd);
		put_fd('\n', fd);
	}
	put_fd(BUF_FLUSH, fd);
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

	s = get_env(info, "HOME=");
	if (s == NULL)
		return (NULL);

	buffer = malloc(sizeof(char) * (str_len(s) + str_len(HIST_FILE) + 2));
	if (buffer == NULL)
		return (NULL);

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
