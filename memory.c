#include "shell.h"

/**
 * bfree - frees a pointer and NULLs the address
 * @ptr_free: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int bfree(void **ptr_free)
{
	if (ptr_free && *ptr_free)
	{
		free(*ptr_free);
		*ptr_free = NULL;
		return (1);
	}
	return (0);
}
