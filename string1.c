#include "shell.h"

/**
 * _strcpy - copies a string
 * @dest_str: the destination
 * @src1: the source
 *
 * Return: pointer to destination
 */
char *_strcpy(char *dest_str, char *src1)
{
	int x = 0;

	if (dest_str == src1 || src1 == 0)
		return (dest_str);
	while (src1[x])
	{
		dest_str[x] = src1[x];
		x++;
	}
	dest_str[x] = 0;
	return (dest_str);
}

/**
 * _strdup - duplicates a string
 * @str_dup: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *str_dup)
{
	int length = 0;
	char *ret;

	if (str_dup == NULL)
		return (NULL);
	while (*str_dup++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str_dup;
	return (ret);
}

/**
 *_puts - prints an input string
 *@str_dup: the string to be printed
 *
 * Return: Nothing
 */
void _puts(char *str_dup)
{
	int x = 0;

	if (!str_dup)
		return;
	while (str_dup[x] != '\0')
	{
		_putchar(str_dup[x]);
		x++;
	}
}

/**
 * _putchar - writes the character char_print to stdout
 * @char_print: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char char_print)
{
	static int x;
	static char buf[WRITE_BUF_SIZE];

	if (char_print == BUF_FLUSH || x >= WRITE_BUF_SIZE)
	{
		write(1, buf, x);
		x = 0;
	}
	if (char_print != BUF_FLUSH)
		buf[x++] = char_print;
	return (1);
}
