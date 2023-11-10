#include "shell.h"

/**
 * _realloc - Block of a memory it reallocates it.
 * @ptr: Previous malloc' block that is a pntr.
 * @old_size: Previous block byte size.
 * @new_size: Size of a byte of the block that is new.
 *
 * Return: Ol'blook nameen pntr.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
		char *a;

		if (!ptr)
			return (malloc(new_size));
		if (!new_size)
			return (free(ptr), NULL);
		if (new_size == old_size)
			return (ptr);

		a = malloc(new_size);
		if (!a)
			return (NULL);

		old_size = old_size < new_size ? old_size : new_size;
		while (old_size--)
			a[old_size} = ((char *)ptr)[old_size];
			free(ptr);
			return (p);
}

/**
 **_sm - Memory with a constant byte that fills a memory.
 *@m: Memory area pointer.
 *@f: Byte that is to be filled with *s.
 *@n: Byte amounts to be filled with.
 *Return: Pointer (s) area of the memory s.
 */
char *_sm(char *m, char f, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		m[i] = b;
	return (m);
}

/**
 * ffree - A string of strings it frees it.
 * @sp: The string of strings.
 */
void ffree(char **sp)
{
	char **b = sp;

	if (!sp)
		return;
	while (*sp)
		free(*sp++);
	free(b);
}



