#include "shell.h"



/**
 * e_putchar - writes character c to stderr
 * @chr: Character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int e_putchar(char chr)
{
	static int j;
	static char buff[WRITE_BUF_SIZE];

	if (chr == BUFFER_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(2, buff, j);
		j = 0;
	}

	if (chr != BUFFER_FLUSH)
		buff[j++] = chr;

	return (1);
}

/**
 *puts_fd - prints an input string
 * @str: String to be printed
 * @fd: Filedescriptor to write to
 *
 * Return: Returns number of chars put
 */
int puts_fd(char *str, int fd)
{
	int j = 0;

	if (!str)
		return (0);
	while (*str)
	{
		j += put_fd(*str++, fd);
	}
	return (j);
}

/**
 * put_fd - writes character chr to given fd
 * @chr: The character to print
 * @fd: Filedescriptor to write to
 *
 * Return: Returns 1 on success, -1 on error, errno is set appropriately.
 */
int put_fd(char chr, int fd)
{
	static int j;
	static char buff[WRITE_BUF_SIZE];

	if (chr == BUFFER_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(fd, buff, j);
		j = 0;
	}
	if (chr != BUFFER_FLUSH)
		buff[j++] = chr;
	return (1);
}

/**
 *e_puts - prints an input string
 * @str: String to print
 *
 * Return: void
 */
void e_puts(char *str)
{
	int j = 0;

	if (!str)
		return;
	while (str[j] != '\0')
	{
		e_putchar(str[j]);
		j++;
	}
}
