#include "shell.h"

/**
 * print_error - prints error message
 * @data: Parameter & return data struct
 * @estr: string containing specified error type
 *
 * Return: Returns 0 if no numbers in string, converted number otherwise
 *        returns -1 on error
 */
void print_error(data_shell *data, char *estr)
{
	e_puts(data->fname);
	e_puts(": ");
	print_d(data->line_count, STDERR_FILENO);
	e_puts(": ");
	e_puts(data->argv[0]);
	e_puts(": ");
	e_puts(estr);
}

/**
 * print_d - function prints a decimal number
 * @input: the input
 * @fd: Filedescriptor to write to
 *
 * Return: Returns number of characters printed
 */
int print_d(int input, int fd)
{
	int j, count = 0;
	int (*__putchar)(char) = _putchar;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = e_putchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (j = 1000000000; j > 1; j /= 10)
	{
		if (_abs_ / j)
		{
			__putchar('0' + current / j);
			count++;
		}
		current %= j;
	}
	__putchar('0' + current);
	count++;

	return (count);
}


/**
 * remove_comments - function replaces first instance of '#' with '\0'
 * @buff: address of the string to modify
 *
 * Return: Always 0;
 */
void remove_comments(char *buff)
{
	int j;

	for (j = 0; buff[j] != '\0'; j++)
		if (buff[j] == '#' && (!j || buff[j - 1] == ' '))
		{
			buff[j] = '\0';
			break;
		}
}

/**
 * convert_number - converter function, clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: Returns string
 */
char *convert_number(long int num, int base, int flags)
{
	char sign = 0;
	static char buffer[50];
	static char *array;
	unsigned long n = num;
	char *ptr;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do {
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * _erratoi - converts string to integer
 * @str: string to be converted
 *
 * Return: Returns 0 if no numbers in string, returns converted number
 *       returns -1 on error
 */
int _erratoi(char *str)
{
	unsigned long int result = 0;
	int j = 0;

	if (*str == '+')
		str++; /* TODO: why does this make main return 255? */
	for (j = 0; str[j] != '\0'; j++)
	{
		if (str[j] >= '0' && str[j] <= '9')
		{
			result *= 10;
			result += (str[j] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}
