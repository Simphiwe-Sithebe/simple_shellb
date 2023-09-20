#include "shell.h"

/**
 **_memset - fills memory with a constant byte
 *@a: the pointer to the memory area
 *@z: the byte to fill *a with
 *@v: the amount of bytes to be filled
 *Return: (a) a pointer to the memory area a
 */
char *_memset(char *a, char z, unsigned int v)
{
	unsigned int i;

	for (i = 0; i < v; i++)
		a[i] = z;
	return (a);
}

/**
 * ffree - frees a string of strings
 * @ps: string of strings
 */
void ffree(char **ps)
{
	char **a = ps;

	if (!ps)
		return;
	while (*ps)
		free(*ps++);
	free(a);
}

/**
 * _realloc - reallocates a block of memory
 * @ptr_prev: pointer to previous malloc'ated block
 * @prev_size: byte size of previous block
 * @size: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *_realloc(void *ptr_prev, unsigned int prev_size, unsigned int size)
{
	char *p;

	if (!ptr_prev)
		return (malloc(size));
	if (!size)
		return (free(ptr_prev), NULL);
	if (size == prev_size)
		return (ptr_prev);

	p = malloc(size);
	if (!p)
		return (NULL);

	prev_size = prev_size < size ? prev_size : size;
	while (prev_size--)
		p[prev_size] = ((char *)ptr_prev)[prev_size];
	free(ptr_prev);
	return (p);
}
