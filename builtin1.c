#include "shell.h"



/**
 * unset_alias - sets alias to string
 * @data: parameter struct
 * @str: String alias
 *
 * Return: Returns 0 on success, otherwise 1 on error
 */
int unset_alias(data_shell *data, char *str)
{
	char *pt, c;
	int ret;

	pt = _strchr(str, '=');
	if (!pt)
		return (1);
	c = *pt;
	*pt = 0;
	ret = _delete_node_at_index(&(data->alias),
		_get_node_index(data->alias, _node_starts_with(data->alias, str, -1)));
	*pt = c;

	return (ret);
}

/**
 * set_alias - sets alias to string
 * @data: parameter struct
 * @str: String alias
 *
 * Return: Returns 0 on success, returns 1 on error
 */
int set_alias(data_shell *data, char *str)
{
	char *pt;

	pt = _strchr(str, '=');
	if (!pt)
		return (1);
	if (!*++pt)
		return (unset_alias(data, str));

	unset_alias(data, str);
	return (_add_node_end(&(data->alias), str, 0) == NULL);
}

/**
 * my_history - displays history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @data: Structure containing potential arguments
 *
 * Return: Returns 0 always
 */
int my_history(data_shell *data)
{
	print_list(data->history);
	return (0);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Returns 0 on success, returns 1 on error
 */
int print_alias(list_t *node)
{
	char *pt = NULL, *a = NULL;

	if (node)
	{
		pt = _strchr(node->str, '=');
		for (a = node->str; a <= pt; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(pt + 1);
		_puts("'\n");
		return (0);
	}

	return (1);
}

/**
 * my_alias - mimics the alias builtin (man alias)
 * @data: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int my_alias(data_shell *data)
{
	int j = 0;
	char *pt = NULL;
	list_t *node = NULL;

	if (data->argc == 1)
	{
		node = data->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (j = 1; data->argv[j]; j++)
	{
		pt = _strchr(data->argv[j], '=');
		if (pt)
			set_alias(data, data->argv[j]);
		else
			print_alias(_node_starts_with(data->alias, data->argv[j], '='));
	}

	return (0);
}


