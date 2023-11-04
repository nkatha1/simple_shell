#include "shell.h"

/**
 * bfree - The pointer, it frees it and the adress it NULLs it.
 * @p: Pointer adress to free.
 *
 * Return: If freed 1, 0 o/w.
 */
int bfree(void **p)
{
	if (p && *p)
	{
		free(*p);
		*p = NULL;
		return (1);
	}
	return (0);
}
