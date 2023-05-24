#include "shell.h"

/**
 * __add_node_end - adds node to end of list
 * @head: address of pointer to head node
 * @str: str field of node
 * @numb: node index used by history
 *
 * Return: Returns size list
 */
list_t *__add_node_end(list_t **head, const char *str, int numb)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t));

	if (!new_node)
		return (NULL);

	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = numb;

	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}

	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;

	return (new_node);
}

/**
 * _add_node - adds a node to the start of the list
 * @head: Address of pointer to head node
 * @str: String field of node
 * @numb: Node index used by history
 *
 * Return: returns size of list
 */
list_t *_add_node(list_t **head, const char *str, int numb)
{
	list_t *new_head;

	if (!head)
		return (NULL);

	new_head = malloc(sizeof(list_t));

	if (!new_head)
		return (NULL);

	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = numb;

	if (str)
	{
		new_head->str = _strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;

	*head = new_head;

	return (new_head);
}

/**
 * print_list_str - prints only str element of list_t linked list
 * @h_n: Pointer to first node
 *
 * Return: returns size of list
 */
size_t print_list_str(const list_t *h_n)
{
	size_t j = 0;

	while (h_n)
	{
		_puts(h_n->str ? h_n->str : "(nil)");
		_puts("\n");
		h_n = h_n->next;
		j++;
	}
	return (j);
}


/**
 * free_list - frees all nodes of list
 * @h_ptr: Address of pointer to head node
 *
 * Return: Returns void
 */
void free_list(list_t **h_ptr)
{
	list_t *node, *next_node, *head;

	if (!h_ptr || !*h_ptr)
		return;
	head = *h_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}

	*h_ptr = NULL;
}

/**
 * _delete_node_at_index - deletes node at given index
 * @head: Address of pointer to first node
 * @ind: index of node to delete
 *
 * Return: Returns 1 on success, on fail return 0
 */
int _delete_node_at_index(list_t **head, unsigned int ind)
{
	unsigned int j = 0;
	list_t *node, *prev_node;

	if (!head || !*head)
		return (0);

	if (!ind)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (j == ind)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		j++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}
