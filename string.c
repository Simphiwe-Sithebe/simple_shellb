#include "shell.h"

/**
 * _strlen - returns the length of a string
 * @s_lenght: the string whose length to check
 *
 * Return: integer length of string
 */
int _strlen(char *s_lenght)
{
	int i = 0;

	if (!s_lenght)
		return (0);

	while (*s_lenght++)
		i++;
	return (i);
}

/**
 * _strcmp - performs lexicogarphic comparison of two strangs.
 * @str1: the first strang
 * @str2: the second strang
 *
 * Return: negative if str1 < str2, positive if str1 > str2, zero if str1 == str2
 */
int _strcmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * starts_with - checks if str_find starts with str_search
 * @str_search: string to search
 * @str_find: the substring to find
 *
 * Return: address of next char of str_search or NULL
 */
char *starts_with(const char *str_search, const char *str_find)
{
	while (*str_find)
		if (*str_find++ != *str_search++)
			return (NULL);
	return ((char *)str_search);
}

/**
 * _strcat - concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
