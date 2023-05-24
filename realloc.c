#include "shell.h"

/**
 * ffree - frees a string of strings
 * @pp: string of strings
 *
 * Return: void
 */
void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * _realloc - reallocates a block of memory
 * @ptr: Pointer to previous malloc'ated block
 * @old_size: Byte size of previous block
 * @new_size: Byte size of new block
 *
 * Return: Returns pointer to da ol'block nameen.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *pt;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	pt = malloc(new_size);
	if (!pt)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		pt[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (pt);
}

/**
 * *_memset - fills memory with constant byte
 * @s: Pointer to the memory area
 * @b: byte to fill *s with
 * @n: Count of bytes to fill
 *
 * Return: Returns (s) a pointer to memory area s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int j;

	for (j = 0; j < n; j++)
		s[j] = b;
	return (s);
}
