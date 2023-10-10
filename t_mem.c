#include "shell.h"

/**
 * bfree - A pointer it frees it and the adress it NULL.
 * @ptr: To be freed adress of the pntr.
 *
 * Return: If freed 1, 0 o/w.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

