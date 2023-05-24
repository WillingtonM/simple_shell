#include "shell.h"

/**
 * **strtow2 - splits string into words
 * @str: Input string
 * @delim: Delimeter
 * Return: Returns a pointer to array of strings, otherwise NULL on fail
 */
char **strtow2(char *str, char delim)
{
	char **sz;
	int i, j, k, m, num_words = 0;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != delim && str[i + 1] == delim) ||
			(str[i] != delim && !str[i + 1]) || str[i + 1] == delim)
			num_words++;
	if (num_words == 0)
		return (NULL);
	sz = malloc((1 + num_words) * sizeof(char *));
	if (!sz)
		return (NULL);
	for (i = 0, j = 0; j < num_words; j++)
	{
		while (str[i] == delim && str[i] != delim)
			i++;
		k = 0;
		while (str[i + k] != delim && str[i + k] && str[i + k] != delim)
			k++;
		sz[j] = malloc((k + 1) * sizeof(char));
		if (!sz[j])
		{
			for (k = 0; k < j; k++)
				free(sz[k]);
			free(sz);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			sz[j][m] = str[i++];
		sz[j][m] = 0;
	}

	sz[j] = NULL;

	return (sz);
}

/**
 * **strtow - splits a string into words. Repeat delimiters are ignored
 * @str: Input string
 * @t: Delimeter string
 * Return: Returns a pointer to array of strings, otherwise NULL on fail
 */
char **strtow(char *str, char *t)
{
	char **sz;
	int i, j, k, m, num_words = 0;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!t)
		t = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!is_delimeter(str[i], t) && (is_delimeter(str[i + 1], t) || !str[i + 1]))
			num_words++;

	if (num_words == 0)
		return (NULL);
	sz = malloc((1 + num_words) * sizeof(char *));
	if (!sz)
		return (NULL);
	for (i = 0, j = 0; j < num_words; j++)
	{
		while (is_delimeter(str[i], t))
			i++;
		k = 0;
		while (!is_delimeter(str[i + k], t) && str[i + k])
			k++;
		sz[j] = malloc((k + 1) * sizeof(char));
		if (!sz[j])
		{
			for (k = 0; k < j; k++)
				free(sz[k]);
			free(sz);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			sz[j][m] = str[i++];
		sz[j][m] = 0;
	}

	sz[j] = NULL;

	return (sz);
}


