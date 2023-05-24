#include "shell.h"


/**
 **_strchr - locates character in string
 *@str: String to be parsed
 *@chr: Character to look for
 *Return: Returns s, a pointer to the memory area s
 */
char *_strchr(char *str, char chr)
{
	do {
		if (*str == chr)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}

/**
 * *_strncat - concatenates two strings
 * @dest: first string
 * @src: Second string
 * @n_cnt: Byte count to be maximally used
 *
 * Return: Returns concatenated string
 */
char *_strncat(char *dest, char *src, int n_cnt)
{
	int i = 0, j = 0;
	char *s = dest;

	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n_cnt)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n_cnt)
		dest[i] = '\0';
	return (s);
}

/**
 * *_strncpy - copies a string
 * @dest: the destination string to be copied to
 * @src: Source string
 * @n_cnt: Count of characters to be copied
 *
 * Return: Returns concatenated string
 */
char *_strncpy(char *dest, char *src, int n_cnt)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n_cnt - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n_cnt)
	{
		j = i;
		while (j < n_cnt)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}
