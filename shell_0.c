#include <stddef.h>
#include <stdbool.h>
#include <ctype.h>

/**
 * count_words - Counts the number of words in a string.
 * @str: The input string.
 *
 * Return: The number of words in @str.
 */
size_t count_words(const char *str)
{
	size_t count = 0;
	int i;
	bool in_word = false;

	if (str == NULL)
		return (0);

	for (i = 0; str[i] != '\0'; i++)
	{
		if (isspace(str[i]))
		{
			in_word = false;
		}
		else if (!in_word)
		{
			count++;
			in_word = true;
		}
	}

	return (count);
}
