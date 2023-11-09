#include "shell.h"

/**
 * sw - If needle starts with haystack it chacks it.
 * @hs: The searched string.
 * @ndl: The substring to be found.
 *
 * Return: Next characters adress of hs or NULL.
 */
char *sw(const char *hs, const char *ndl)
{
	while (*ndl)
		if (*ndl++ != *hs++)
			return (NULL);
	return ((char *)hs);
}

/**
 * _strlen - The leng of the str it returns it.
 * @tl: String whose length is to be checked.
 *
 * Return: Strings integers length
 */
int _strlen(char *tl)
{
	int i = 0;

	if (!tl)
		return (0);

	while (*s++)
		i++;
	return (i);
}

/**
 * _cst - The two strings, its concentates them.
 * @db: Buffers destination.
 * @sc: Buffers source.
 *
 * Return: Destination buffers pointer.
 */
char *_cst(char *db, char *sc)
{
	char *ret = db;

	while (*db)
		db++;
	while (*sc)
		*db++ = *sc++;
	*db = *sc;
	return (ret);
}

/**
 *_strcmp - It does the comparison of two strings hence it 
            it performs the lexicographic.
 *@fs: The strang that is the first.
 *@fb: The strang that is second.
 *
 * Return: s1<s2 is negative, s1>s2 positive, s1 == s2 positive.
 */
int _strcmp(char *fs, char *fb)
{
	while (*fs && *fb)
	{
		if (*fs != *fb)
			return (*fs - *fb);
		fs++;
		fb++;
	}
	if (*fa == *fb)
		return (0);
	else
		return (*fa < *fb ? -1 : 1);
}

