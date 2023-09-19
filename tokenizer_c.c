#include "shell.h"

/**
 * **strtow - splits a string into words. Repeat delimiters are ignored
 * @str_in: the input string
 * @str_d: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strtow(char *str_in, char *str_d)
{
	int x, h, l, n, numwordd = 0;
	char **s;

	if (str_in == NULL || str_in[0] == 0)
		return (NULL);
	if (!str_d)
		str_d = " ";
	for (x = 0; str_in[x] != '\0'; x++)
		if (!is_delim(str_in[x], str_d) && (is_delim(str_in[x + 1], str_d) || !str_in[x + 1]))
			numwordd++;

	if (numwordd == 0)
		return (NULL);
	s = malloc((1 + numwordd) * sizeof(char *));
	if (!s)
		return (NULL);
	for (x = 0, h = 0; h < numwordd; h++)
	{
		while (is_delim(str_in[x], str_d))
			x++;
		l = 0;
		while (!is_delim(str_in[x + l], str_d) && str_in[x + l])
			l++;
		s[h] = malloc((l + 1) * sizeof(char));
		if (!s[h])
		{
			for (l = 0; l < h; l++)
				free(s[l]);
			free(s);
			return (NULL);
		}
		for (n = 0; n < l; n++)
			s[h][n] = str_in[x++];
		s[h][n] = 0;
	}
	s[h] = NULL;
	return (s);
}

/**
 * **strtow2 - splits a string into words
 * @str_in: the input string
 * @str_d: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *str_in, char str_d)
{
	int x, h, l, n, numwordd = 0;
	char **s;

	if (str_in == NULL || str_in[0] == 0)
		return (NULL);
	for (x = 0; str_in[x] != '\0'; x++)
		if ((str_in[x] != str_d && str_in[x + 1] == str_d) ||
		    (str_in[x] != str_d && !str_in[x + 1]) || str_in[x + 1] == str_d)
			numwordd++;
	if (numwordd == 0)
		return (NULL);
	s = malloc((1 + numwordd) * sizeof(char *));
	if (!s)
		return (NULL);
	for (x = 0, h = 0; h < numwordd; h++)
	{
		while (str_in[x] == str_d && str_in[x] != str_d)
			x++;
		l = 0;
		while (str_in[x + l] != str_d && str_in[x + l] && str_in[x + l] != str_d)
			l++;
		s[h] = malloc((l + 1) * sizeof(char));
		if (!s[h])
		{
			for (l = 0; l < h; l++)
				free(s[l]);
			free(s);
			return (NULL);
		}
		for (n = 0; n < l; n++)
			s[h][n] = str_in[x++];
		s[h][n] = 0;
	}
	s[h] = NULL;
	return (s);
}
