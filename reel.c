#include "shell.h"

/**
 * re_alloc - reallocates a memory block
 * @ptr: Pointer to previously allocated block
 * @old_s: unsigned int
 * @new_s: unsigned int
 *
 * Return: void
 */
void *re_alloc(void *ptr, unsigned int old_s, unsigned int new_s)
{
	unsigned int min_s, i;
	char *c;

	if (!ptr)
	{
		return (malloc(new_s));
	}
	if (!new_s)
	{
		free(ptr);
		return (NULL);
	}
	if (new_s == old_s)
		return (ptr);

	c = malloc(new_s);
	if (!c)
		return (NULL);

	min_s = old_s < new_s ? old_s : new_s;
	for (i = 0; i < min_s; i++)
		c[i] = ((char *)ptr)[i];

	free(ptr);
	return (c);
}

/**
 **set_mem - fills a memory.
 *@m: Memory area pointer.
 *@f: char
 *@n: unsigned int
 *Return: char
 */
char *set_mem(char *m, char f, size_t n)
{
	size_t i;

	if (m == NULL)
		return (NULL);

	for (i = 0; i < n; i++)
		m[i] = f;

	return (m);
}

/**
 * ffree - Frees pointer to pointer to string
 * @sp: The string of strings.
 */
void ffree(char **sp)
{
	char **b = sp;

	if (sp == NULL)
	{
		puts_fd(2, "pointer is null\n");
		return;
	}
	while (*sp != NULL)
	{
		free(*sp);
		sp++;
	}
	free(b);
}
