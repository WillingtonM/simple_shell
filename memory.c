#include "shell.h"

/**
 * bfree - frees pointer and NULLs address
 * @ptr: Address of pointer to free
 *
 * Return: Returns 1 if freed, otherwise returns 0.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
