#include "shell.h"

/**
 * *_memset - The constant byte mem it fills it.
 * @m: Memory area pointer.
 * @c: To fill with *m byte.
 * @n: Bytes amount to be filled with.
 * Return: Memory area pointer m.
 */
char *_memset(char *m, char c, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		m[i] = c;
	return (m);
}

/**
 * ffree - The string of strings it frees it.
 * @vv: The string of strings.
 */
void ffree(char **vv)
{
	char **a = vv;

	if (!vv)
		return;
	while (*vv)
		free(*vv++);
	free(a);
}

/**
 * _realloc - The mem block it reallocates it.
 * @ptr: Mallocated prev block pointer.
 * @old_size: Previoius block byte size.
 * @new_size: New block byte size.
 *
 * Return: Nameen ol'block pointer.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}

