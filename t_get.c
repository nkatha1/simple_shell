#include "shell.h"

/**
 * input_buf - The chained commands buffers.
 * @info : The struct parameter.
 * @b : Buffer adress.
 * @len: Var len adress.
 *
 * Return: The bytes to read.
 */
ssize_t input_buf(info_t *info, char **b, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /*if in the buff nothing is left, fill it in*/
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*b);
		*b = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(b, &len_p, stdin);
#else
		r = _getline(info, b, &len_p);
#endif
		if (r > 0)
		{
			if ((*b)[r - 1] == '\n')
			{
				(*b)[r - 1] = '\0'; /* trailing whitespaces removed */
				r--;
			}
			info->linecount_flag = 1;
			remove_comments(*b);
			build_history_list(info, *b, info->histcount++);
			/* if (_strchr(*b, ';')) is tis a command chain */
			{
				*len = r;
				info->cmd_buf = b;
			}
		}
	}
	return (r);
}

/**
 * get_input - A line minus the newline it gets it.
 * @info: The struct parameter.
 *
 * Return: Returns the bytes to read.
 */
ssize_t get_input(info_t *info)
{
	static char *buf; /* ';' chain command buffer */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &len);
	if (r == -1) /* END OF FACTOR */
		return (-1);
	if (len)	/* we have commands left in the chain buffer */
	{
		j = i; /* new iterator init to curr buf position */
		p = buf + i; /* the pointer to return it gets it */

		check_chain(info, buf, &j, i, len);
		while (j < len) /* end */
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past nulled ';'' */
		if (i >= len) /* has it reached end of buffer? */
		{
			i = len = 0; /*position and length it resets it */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* back to the current command pointer it pass back it */
		return (_strlen(p)); /* To the current command it returns it */
	}

	*buf_p = buf; /* pass back buffer from getline else not a chain */
	return (r); /* length of buff from _getline it returns it */
}

/**
 * read_buf - The buffer it reads it.
 * @info: Struct parameter.
 * @b: The buffer.
 * @i: The size.
 *
 * Return: It returns r.
 */
ssize_t read_buf(info_t *info, char *b, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, b, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _getline - Next line of input from STDIN it gets it.
 * @info: The struct parameter.
 * @pt: Pointer buffer adress, NULL or preallocated.
 * @length: Preallocated size pointer if not NULL
 *
 * Return: s
 */
int _getline(info_t *info, char **pt, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *pt;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);
	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*pt = p;
	return (s);
}

/**
 * sigintHandler - The ctrl-c  it blocks it.
 * @sig_num: Signal numb.
 *
 * Return: It returns void.
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

