#include "shell.h"

/**
 *_eputs - prints an input string
 * @strIn: the string to be printed
 *
 * Return: Nothing
 */
void _eputs(char *strIn)
{
	int x = 0;

	if (!strIn)
		return;
	while (strIn[x] != '\0')
	{
		_eputchar(strIn[x]);
		x++;
	}
}

/**
 * _eputchar - writes the character d to stderr
 * @d: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char d)
{
	static int x;
	static char buf[WRITE_BUF_SIZE];

	if (d == BUF_FLUSH || x >= WRITE_BUF_SIZE)
	{
		write(2, buf, x);
		x = 0;
	}
	if (d != BUF_FLUSH)
		buf[x++] = d;
	return (1);
}

/**
 * _putfd - writes the character d to given filedesc
 * @d: The character to print
 * @filedesc: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char d, int filedesc)
{
	static int x;
	static char buf[WRITE_BUF_SIZE];

	if (d == BUF_FLUSH || x >= WRITE_BUF_SIZE)
	{
		write(filedesc, buf, x);
		x = 0;
	}
	if (d != BUF_FLUSH)
		buf[x++] = d;
	return (1);
}

/**
 *_putsfd - prints an input string
 * @strIn: the string to be printed
 * @filedesc: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int _putsfd(char *strIn, int filedesc)
{
	int x = 0;

	if (!strIn)
		return (0);
	while (*strIn)
	{
		x += _putfd(*strIn++, filedesc);
	}
	return (x);
}
