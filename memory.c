void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *res;

	if (new_size == old_size)
		return (ptr);
	if (new_size == 0 && ptr)
	{
		free(ptr);
		return(NULL);
	}
	res = malloc(new_size);
	if (res == NULL)
		return (NULL);
	if (ptr == NULL)
	{
		fill_an_array(res, '\0', new_size);
		free (ptr);
	}
	else
	{
		mem_cpy(res, ptr, old_size);
		free(ptr);
	}
	return (res);
}

/**
 * free_all - Character pointer array it frees it
 * @input: The array pointer
 * @line: The character pointer
 * Return: Void
 */
void free_all(char **input, char *line)
{
	free(input);
	free(line);
	line = NULL;
	input = NULL;
}

/**
 * mem_cpy - Byte code from src destination
 * @dest: The destination pointer
 * @src: The source pointer
 * @n: The size (How much will you copy)
 * Return: Void pointer.
 */
char *mem_cpy(char *dest, char *src, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
	{
		dest[i] = src[i];
	}
	return (dest);
}

/**
 * fill_an_array - Constant byte array it fills it
 * @a: The void pointer
 * @n: The integer
 * @len: The length integer
 * Return: The void pointer
 */
void *fill_an_array(void *a, int n, unsigned int len)
{
	char *p = a;
	unsigned int i = 0;

	while (i < len)
	{
		*p = n;
		p++;
		i++;
	}
	return (a);
}

/**
 * cal_loc - array memory allocation for an array using malloc
 * @size: The size
 * Return: The void pointer
 */
void *cal_loc(unsigned int size)
{
	char *c;
	unsigned int i;

	if (size == 0)
	return (NULL);
	c = malloc(size);
	if (c == NULL)
	return (NULL);
	for (i = 0; i < size; i++)
	{
		c[i] = '\0';
	}
	return (c);
}


