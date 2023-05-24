#include "shell.h"

/**
 * _atoi - converts string to integer
 * @str: String to be converted
 * Return: returns 0 if no digit in string, otherwise returnns converted digit
 */
int _atoi(char *str)
{
	int i, output, sign, flag;

	unsigned int res;

	sign = 1;
	flag = 0;
	res = 0;

	for (i = 0; str[i] != '\0' && flag != 2; i++)
	{
		if (str[i] == '-')
			sign *= -1;

		if (str[i] >= '0' && str[i] <= '9')
		{
			flag = 1;
			res *= 10;
			res += (str[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -res;
	else
		output = res;

	return (output);
}

/**
 * is_delimeter - checks if character is a delimeter
 * @chr: charater to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delimeter(char chr, char *delim)
{
	while (*delim)
		if (*delim++ == chr)
			return (1);
	return (0);
}

/**
 * _isalpha - check alphabetic character
 * @chr: character to input
 *
 * Return: returns 1 if chr is alphabetic, otherwise 0
 */
int _isalpha(int chr)
{
	if ((chr >= 'a' && chr <= 'z') || (chr >= 'A' && chr <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * interactive - returns true if shell is interactive mode
 * @data: struct address
 *
 * Return: returns 1 if mode is interactive, otherwise return 0
 */
int interactive(data_shell *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}
