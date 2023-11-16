#include "shell.h"

/**
 * freemem - The pointer, it frees it and the adress it NULLs it.
 * @p: Pointer adress to free.
 *
 * Return: int
 */
int freemem(void **p)
{
	if (p != NULL && *p != NULL)
	{
		free(*p);
		*p = NULL;
		return (1);
	}
	return (0);
}
