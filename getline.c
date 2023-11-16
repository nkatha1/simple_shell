#include "shell.h"
/**
 * get_line - gets input from stamdard input
 * @info: pointer to struct
 * @ptr: pointer to pointer to string
 * @len: pointer to unsigned int
 *
 * Return: int
 */
int get_line(info_t *info, char **ptr, size_t *len)
{
	size_t t;
	static size_t n, l;
	static char buffer[READ_BUF_SIZE];
	char *c = NULL;
	char *ptr1 = NULL;
	char *s;
	ssize_t j = 0, i = 0;

	c = *ptr;
	if (len && c)
		i = *len;
	if (n == l)
		n = l = 0;

	j = buff_read(info, buffer, &l);
	if (j == -1 || (j == 0 && l == 0))
		return (-1);

	s = str_chr(buffer + n, '\n');
	t = s ? 1 + (size_t)(s - buffer) : l;

	ptr1 = re_alloc(c, i, i ? i + t : t + 1);
	if (!ptr1)
		return (c ? free(c), -1 : -1);

	if (c)
		strn_cat(ptr1, buffer + n, t - n);
	else
		strn_cpy(ptr1, buffer + n, t - n + 1);
	
	i += t - n;
	n = t;
	c = ptr1;

	if (len)
		*len = i;
	*ptr = c;
	return (i);
}
/**
 * buff_read - reads buffer
 * @info: pointer to struct
 * @buffer: storage memory
 * @n: size_t
 *
 * Return: size_t
 */
ssize_t buff_read(info_t *info, char *buffer, size_t *n)
{
	ssize_t i;

	if (!n)
		return (0);

	i = read(info->readfd, buffer, READ_BUF_SIZE);
	if (i >= 0)
	{
		*n = i;
	}
	return (i);
}
/**
 * buff_input - saves commands chained together
 * @buffer:vpointer to string pointer
 * @info: pointer to struct
 * @n: pointer to a size_t
 *
 * Return: ssize_t
 */
ssize_t buff_input(info_t *info, char **buffer, size_t *n)
{
	size_t i = 0;
	ssize_t r = 0;

	if (!*n)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, sigintHandler);

#if USE_GETLINE
		r = getline(buffer, &i, stdin);
#else
		r = get_line(info, buffer, &i);
#endif

		if (r > 0)
		{
			if ((*buffer)[r - 1] == '\n')
			{
				(*buffer)[r - 1] = '\0';
				r--;
			}
			info->linecount_flag = 1;
			replace_comments(*buffer);
			create_history(info, *buffer, info->histcount++);

			if (str_chr(*buffer, ';'))
			{
				*n = r;
				info->cmd_buf = buffer;
			}
		}
	}
	return (r);
}
/**
 * sigintHandler - block control c
 * @num: signal number
 */
void sigintHandler(__attribute__((unused))int num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
/**
 * get_form - gets iput format
 * @info: pointer to struct
 *
 * Return: ssize_t
 */
ssize_t get_form(info_t *info)
{
	static size_t i = 0, j = 0, k = 0;
	static char *buffer = NULL;
	ssize_t r = 0;
	char **c = &(info->arg);
	char *s;

	_putchar(BUF_FLUSH);

	r = buff_input(info, &buffer, &k);
	if (r == -1)
		return (-1);

	if (k)
	{
		j = i;
		s = buffer + i;

		checkchain(info, buffer, &j, i, k);
		while (j < k)
		{
			if (chain_delim(info, buffer, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= k)
		{
			i = k = 0;
			info->cmd_buf_type = CMD_NORM;
		}
		*c = s;
		return (str_len(s));
	}
	*c = buffer;
	return (r);
}
