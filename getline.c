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

	if (len && *ptr)
		i = *len;
	if (n == l)
		n = l = 0;

	j = buff_read(info, buffer, &l);
	if (j == -1 || (j == 0 && l == 0))
		return (-1);

	s = str_chr(buffer + 1, '\n');
	t = s ? 1 + (size_t)(s - buffer) : l;

	ptr1 = re_alloc(c, i, i + t + 1);
	if (!ptr1)
	{
		if (c)
			free(c);
		return (-1);
	}
	
	strn_cat(ptr1, buffer + n, t - n);
	
	i += t - n;
	n = t;
	c = ptr1;

	if (len != NULL)
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
		return (-1);

	if (*n != 0)
		return (0);
	
	i = read(info->readfd, buffer, READ_BUF_SIZE);
	if (i < 0)
	{
		perror("Read failed");
		return (-1);
	}

	*n = i;
	return (i);
}
/**
 * buff_input - saves commands chained together
 * @buffer:vpointer to string pointer
 * *info: pointer to struct
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
		if (*buffer)
		{
			free(*buffer);
			*buffer = NULL;
		}

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
 * get_form - gets iput format
 * @info: pointer to struct
 *
 * Return: ssize_t
 */
ssize_t get_form(info_t *info)
{
	size_t i = 0, j = 0, k = 0;
	char *buffer = NULL;
	ssize_t r = 0;
	char **c = &(info->arg);
	char *s;

	_putchar(BUF_FLUSH);

	r = buff_input(info, &buffer, &k);
	if (r == -1)
		return (-1);

	if (k != 0)
	{
		j = i;
		s = buffer + i;
		
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
