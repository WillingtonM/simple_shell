#include "shell.h"


/**
 * un_setenv - Remove environment variable
 * @data: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: String environment var property
 * Return: Returns 1 on delete, otherwise returns 0
 */
int un_setenv(data_shell *data, char *var)
{
	list_t *node = data->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			data->env_changed = _delete_node_at_index(&(data->env), i);
			i = 0;
			node = data->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (data->env_changed);
}

/**
 * _setenv - Initialize new or mofify existing environment variable
 * @data: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: String environment var value
 *  Return: 0
 */
int _setenv(data_shell *data, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = data->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			data->env_changed = 1;
			return (0);
		}
		node = node->next;
	}

	_add_node_end(&(data->env), buf, 0);

	free(buf);
	data->env_changed = 1;

	return (0);
}

/**
 * get_environ - returns string array copy of environ
 * @data: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: 0
 */
char **get_environ(data_shell *data)
{
	if (!data->environ || data->env_changed)
	{
		data->environ = list_to_strings(data->env);
		data->env_changed = 0;
	}

	return (data->environ);
}
