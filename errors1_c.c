#include "shell.h"

/**
 * _erratoi - converts a string to an integer
 * @strIn: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int _erratoi(char *strIn)
{
	int x = 0;
	unsigned long int resultant = 0;

	if (*strIn == '+')
		strIn++;  /* TODO: why does this make main return 255? */
	for (x = 0;  strIn[x] != '\0'; x++)
	{
		if (strIn[x] >= '0' && strIn[x] <= '9')
		{
			resultant *= 10;
			resultant += (strIn[x] - '0');
			if (resultant > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (resultant);
}

/**
 * print_error - prints an error message
 * @info_p: the parameter & return info struct
 * @errString: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void print_error(info_t *info_p, char *errString)
{
	_eputs(info_p->fname);
	_eputs(": ");
	print_d(info_p->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info_p->argv[0]);
	_eputs(": ");
	_eputs(errString);
}

/**
 * print_d - function prints a decimal (integer) number (bases 10)
 * @input1: the input
 * @filedesc: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int print_d(int input1, int filedesc)
{
	int (*__putchar)(char) = _putchar;
	int x, count = 0;
	unsigned int _abs1_, curr1;

	if (filedesc == STDERR_FILENO)
		__putchar = _eputchar;
	if (input1 < 0)
	{
		_abs1_ = -input1;
		__putchar('-');
		count++;
	}
	else
		_abs1_ = input1;
	curr1 = _abs1_;
	for (x = 1000000000; x > 1; x /= 10)
	{
		if (_abs1_ / x)
		{
			__putchar('0' + curr1 / x);
			count++;
		}
		curr1 %= x;
	}
	__putchar('0' + curr1);
	count++;

	return (count);
}

/**
 * convert_number - converter function, a clone of itoa
 * @num1: number
 * @bases: bases
 * @flagF: argument flagF
 *
 * Return: string
 */
char *convert_number(long int num1, int bases, int flagF)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long m = num1;

	if (!(flagF & CONVERT_UNSIGNED) && num1 < 0)
	{
		m = -num1;
		sign = '-';

	}
	array = flagF & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[m % bases];
		m /= bases;
	} while (m != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - function replaces first instance of '#' with '\0'
 * @strMod: address of the string to modify
 *
 * Return: Always 0;
 */
void remove_comments(char *strMod)
{
	int x;

	for (x = 0; strMod[x] != '\0'; x++)
		if (strMod[x] == '#' && (!x || strMod[x - 1] == ' '))
		{
			strMod[x] = '\0';
			break;
		}
}
