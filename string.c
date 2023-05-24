#include "shell.h"

/**
 * _strcmp - performs lexicogarphic comparison of two strangs.
 * @str1: 1st string
 * @str2: 2nd string
 *
 * Return: negative if str1 < str2, positive if str1 > str2, 0 if str1 = str2
 */
int _strcmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * _strlen - returns length of string
 * @str: String length to check
 *
 * Return: Return integer string length
 */
int _strlen(char *str)
{
	int j = 0;

	if (!str)
		return (0);

	while (*str++)
		j++;
	return (j);
}

/**
 * _strcat - concatenates two strings
 * @dest: Destination buffer
 * @src: Source buffer
 *
 * Return: pointer to destination buffer
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}

/**
 * starts_with - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: Returns address of next char of haystack otherwise NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}
