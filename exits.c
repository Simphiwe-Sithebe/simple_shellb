#include "shell.h"

/**
 **_strncpy - copies a string
 *@descStr: the destination string to be copied to
 *@str2: the source string
 *@m: the amount of characters to be copied
 *Return: the concatenated string
 */
char *_strncpy(char *descStr, char *str2, int m)
{
	int x, k;
	char *s = descStr;

	x = 0;
	while (str2[x] != '\0' && x < m - 1)
	{
		descStr[x] = str2[x];
		x++;
	}
	if (x < m)
	{
		k = x;
		while (k < m)
		{
			descStr[k] = '\0';
			k++;
		}
	}
	return (s);
}

/**
 **_strncat - concatenates two strings
 *@descStr: the first string
 *@str2: the second string
 *@m: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *_strncat(char *descStr, char *str2, int m)
{
	int x, k;
	char *s = descStr;

	x = 0;
	k = 0;
	while (descStr[x] != '\0')
		x++;
	while (str2[k] != '\0' && k < m)
	{
		descStr[x] = str2[k];
		x++;
		k++;
	}
	if (k < m)
		descStr[x] = '\0';
	return (s);
}

/**
 **_strchr - locates a character in a string
 *@strSearch: the string to be parsed
 *@v: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *_strchr(char *strSearch, char v)
{
	do {
		if (*strSearch == v)
			return (strSearch);
	} while (*strSearch++ != '\0');

	return (NULL);
}
