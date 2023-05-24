#include "shell.h"

/**
 * print_list - prints all elements of list_t linked list
 * @hn: pointer to first node
 *
 * Return: Returns size of list
 */
size_t print_list(const list_t *hn)
{
	size_t j = 0;

	while (hn)
	{
		_puts(convert_number(hn->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(hn->str ? hn->str : "(nil)");
		_puts("\n");
		hn = hn->next;
		j++;
	}
	return (j);
}

/**
 * list_len - determines length of linked list
 * @hn: pointer to first node
 *
 * Return: Returns size of list
 */
size_t list_len(const list_t *hn)
{
	size_t j = 0;

	while (hn)
	{
		hn = hn->next;
		j++;
	}
	return (j);
}

/**
 * list_to_strings - returns array of strings of list->str
 * @head: pointer to first node
 *
 * Return: returns array of strings
 */
char **list_to_strings(list_t *head)
{
	size_t j, i = list_len(head);
	list_t *node = head;
	char *str;
	char **strs;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);

	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}

/**
 * _get_node_index - gets the index of node
 * @head: Pointer to list head
 * @node: Pointer to the node
 *
 * Return: Returns index of node or -1
 */
ssize_t _get_node_index(list_t *head, list_t *node)
{
	size_t j = 0;

	while (head)
	{
		if (head == node)
			return (j);
		head = head->next;
		j++;
	}

	return (-1);
}

/**
 * _node_starts_with - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: String to match
 * @chr: Next character after prefix to match
 *
 * Return: Returns match node or null
 */
list_t *_node_starts_with(list_t *node, char *prefix, char chr)
{
	char *pt = NULL;

	while (node)
	{
		pt = starts_with(node->str, prefix);
		if (pt && ((chr == -1) || (*pt == chr)))
			return (node);
		node = node->next;
	}

	return (NULL);
}
