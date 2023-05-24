#include "shell.h"

/**
 * replace_string - replaces string
 * @old_str: address of old string
 * @new_str: new string
 *
 * Return: Returns 1 if replaced, otherwise 0
 */
int replace_string(char **old_str, char *new_str)
{
	free(*old_str);
	*old_str = new_str;
	return (1);
}

/**
 * is_chain - test if current char in buffer is a chain delimeter
 * @data: Parameter struct
 * @buff: Char buffer
 * @pt: Address of current position in buff
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain(data_shell *data, char *buff, size_t *pt)
{
	size_t j = *pt;

	if (buff[j] == '|' && buff[j + 1] == '|')
	{
		buff[j] = 0;
		j++;
		data->cmd_buf_type = CMD_OR;
	}
	else if (buff[j] == '&' && buff[j + 1] == '&')
	{
		buff[j] = 0;
		j++;
		data->cmd_buf_type = CMD_AND;
	}
	else if (buff[j] == ';')
	{
		buff[j] = 0;
		data->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*pt = j;
	return (1);
}



/**
 * replace_alias - replaces an aliases in tokenized string
 * @data: Parameter struct
 *
 * Return: Returns 1 if replaced, otherwise 0
 */
int replace_alias(data_shell *data)
{
	int i;
	char *pt;
	list_t *node;

	for (i = 0; i < 10; i++)
	{
		node = _node_starts_with(data->alias, data->argv[0], '=');
		if (!node)
			return (0);
		free(data->argv[0]);
		pt = _strchr(node->str, '=');
		if (!pt)
			return (0);
		pt = _strduplc(pt + 1);
		if (!pt)
			return (0);
		data->argv[0] = pt;
	}

	return (1);
}

/**
 * replace_vars - replaces vars in the tokenized string
 * @data: Parameter struct
 *
 * Return: Returns 1 if replaced, otherwise 0
 */
int replace_vars(data_shell *data)
{
	list_t *node;
	int j;

	for (j = 0; data->argv[j]; j++)
	{
		if (data->argv[j][0] != '$' || !data->argv[j][1])
			continue;

		if (!_strcmp(data->argv[j], "$?"))
		{
			replace_string(&(data->argv[j]),
				_strduplc(convert_number(data->status, 10, 0)));
			continue;
		}
		if (!_strcmp(data->argv[j], "$$"))
		{
			replace_string(&(data->argv[j]),
				_strduplc(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = _node_starts_with(data->env, &data->argv[j][1], '=');
		if (node)
		{
			replace_string(&(data->argv[j]),
				_strduplc(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&data->argv[j], _strduplc(""));

	}
	return (0);
}

/**
 * check_chain - checks if we should continue chaining based on last status
 * @data: parameter struct
 * @buff: Char buffer
 * @p: Address of current position in buff
 * @i: starting position in buf
 * @len: Returns buff length
 *
 * Return: Void
 */
void check_chain(data_shell *data, char *buff, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (data->cmd_buf_type == CMD_AND)
	{
		if (data->status)
		{
			buff[i] = 0;
			j = len;
		}
	}
	if (data->cmd_buf_type == CMD_OR)
	{
		if (!data->status)
		{
			buff[i] = 0;
			j = len;
		}
	}

	*p = j;
}
