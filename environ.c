#include "shell.h"



/**
 * get_env - gets the value of an environ variable
 * @data: Structure containing potential arguments
 * @name: environment var name
 *
 * Return: Returns value
 */
char *get_env(data_shell *data, const char *name)
{
	list_t *node = data->env;
	char *pt;

	while (node)
	{
		pt = starts_with(node->str, name);
		if (pt && *pt)
			return (pt);
		node = node->next;
	}
	return (NULL);
}

/**
 * my_setenv - Initialize a new or modify existing environment variable
 * @data: Structure containing potential arguments
 *  Return: Returns 0 always
 */
int my_setenv(data_shell *data)
{
	if (data->argc != 3)
	{
		e_puts("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(data, data->argv[1], data->argv[2]))
		return (0);
	return (1);
}

/**
 * populate_env_list - populates environment linked list
 * @data: Structure containing potential arguments
 * Return: Returns 0 always
 */
int populate_env_list(data_shell *data)
{
	list_t *node = NULL;
	size_t j;

	for (j = 0; environ[j]; j++)
		_add_node_end(&node, environ[j], 0);
	data->env = node;

	return (0);
}

/**
 * my_unsetenv - Remove  environment variable
 * @data: Structure containing potential arguments
 *  Return: Returns 0 always
 */
int my_unsetenv(data_shell *data)
{
	int j;

	if (data->argc == 1)
	{
		e_puts("Too few arguements.\n");
		return (1);
	}
	for (j = 1; j <= data->argc; j++)
		un_setenv(data, data->argv[j]);

	return (0);
}



/**
 * my_env - prints current environment
 * @data: Structure containing potential arguments
 * Return: reurns  0 always
 */
int my_env(data_shell *data)
{
	print_list_str(data->env);
	return (0);
}
