#include "shell.h"

/**
 * interactive - returns true if shell is interactive mode
 * @infoProv: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive(info_t *infoProv)
{
	return (isatty(STDIN_FILENO) && infoProv->readfd <= 2);
}

/**
 * is_delim - checks if character is a delimeter
 * @charCheck: the char to check
 * @delimString: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delim(char charCheck, char *delimString)
{
	while (*delimString)
		if (*delimString++ == charCheck)
			return (1);
	return (0);
}

/**
 *_isalpha - checks for alphabetic character
 *@charIn: The character to input
 *Return: 1 if c is alphabetic, 0 otherwise
 */

int _isalpha(int charIn)
{
	if ((charIn >= 'a' && charIn <= 'z') || (charIn >= 'A' && charIn <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - converts a string to an integer
 *@convert: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *convert)
{
	int i, sign1 = 1, flag1 = 0, output;
	unsigned int resultant = 0;

	for (i = 0;  convert[i] != '\0' && flag1 != 2; i++)
	{
		if (convert[i] == '-')
			sign1 *= -1;

		if (convert[i] >= '0' && convert[i] <= '9')
		{
			flag1 = 1;
			resultant *= 10;
			resultant += (convert[i] - '0');
		}
		else if (flag1 == 1)
			flag1 = 2;
	}

	if (sign1 == -1)
		output = -resultant;
	else
		output = resultant;

	return (output);
}

