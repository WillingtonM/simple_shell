#include "shell.h"

/**
 * _strduplc - duplicates a string
 * @str: String to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_strduplc(const char *str)
{
	char *ret;
	int length = 0;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}

/**
 * _strcpy - copies a string
 * @dest: Destination
 * @src: Source
 *
 * Return: Returns pointer to destination
 */
char *_strcpy(char *dest, char *src)
{
	int j = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[j])
	{
		dest[j] = src[j];
		j++;
	}
	dest[j] = 0;
	return (dest);
}

/**
 * _putchar - writes the character c to stdout
 * @chr: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char chr)
{
	static int j;
	static char buff[WRITE_BUF_SIZE];

	if (chr == BUFFER_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(1, buff, j);
		j = 0;
	}
	if (chr != BUFFER_FLUSH)
		buff[j++] = chr;
	return (1);
}

/**
 *_puts - prints an input string
 *@str: String to be printed
 *
 * Return: Returns void
 */
void _puts(char *str)
{
	int j = 0;

	if (!str)
		return;
	while (str[j] != '\0')
	{
		_putchar(str[j]);
		j++;
	}
}
