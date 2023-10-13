#include "shell.h"

/**
 **_strncpy - A string it copies it.
 *@des: String destination copied to.
 *@sr: String source.
 *@n: Chars to be copied amount.
 *Return: String that is concentated.
 */
char *_strncpy(char *des, char *sr, int n)
{
	int i, j;
	char *s = des;

	i = 0;
	while (sr[i] != ' \0' && i < n - 1)
	{
		
