#include "shell.h"

/**
 * _strlen - The string's length it returns it.
 * @l: Lenth of the string which is going to be checked.
 *
 * Return: The strings integers length.
 */
int _strlen(char *l)
{
	int i = 0;

	if (!l)
		return (0);

	while (*l++)
		i++;
	return (i);
}

/**
 * _strcmp - Comparison of two str lexicographic it perfoms it.
 * @sa: Strang that is first.
 * @sb: Strang that is second.
 *
 * Return : If sa <sb, it returns negative, sa >sb positive , sa == sb zero.
 */
int_strcmp(char *sa, char sb)
{
	while (*sa && *sb)
	{
		if (*sa != *sb)
			return (*sa - *sb);
		sa++;
		sb++;
	}
	if (*sa == *sb)
		return (0);
	else
		return (*sa < *sb ? -1 : 1);
}

/**
 * starts_with - If the needle starts with haystack it checks that.
 * @hs: The string to be searched.
 * @nd : Sub string to look for.
 *
 * Return : Next character adress haystack or NULL.
 */
char *starts_with(const char *hs, const char *nd)
{
	while (*nd)
		if (*nd++ != *hs++)
			return (NULL);
	return ((char *)hs);
}

/**
 * _strcat _ The two strings it links them.
 * @db: Buffers destination.
 * @sb: Buffers source.
 *
 * Return: The destination buffer pointer.
 */
char *_strcat(char *db, char *sb)
{
	char *ret = db;

	while (*db)
		db++;
	while (*sb)
		*dest++ = *sb++;
	*db = *sb;
	return (ret);
}
