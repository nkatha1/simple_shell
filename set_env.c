#include "shell.h"
/**
 * un_setenv - deletes env variable
 * @v: variable to be deleted
 *
 * Return: int
 */
int un_setenv(char *v)
{
	if (unsetenv(v) != 0)
	{
		fprintf(stderr, "failed to unset variable %s\n", v);
		return (1);
	}
	return (0);
}
/**
 * set_env - sets env variable
 * @v: variable to be set
 * @val: value to set
 *
 * Return: int
 */
int set_env(char *v, char *val)
{
	if (setenv(v, val, 1) != 0)
	{
		fprintf(stderr, "failed to set variable %s\n", v);
		return (1);
	}
	return (0);
}
