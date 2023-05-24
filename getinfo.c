#include "shell.h"

/**
 * clear_data - initializes data_shell struct
 * @data: struct address
 */
void clear_data(data_shell *data)
{
	data->arg = NULL;
	data->argv = NULL;
	data->path = NULL;
	data->argc = 0;
}

/**
 * set_data - initializes data_shell struct
 * @data: Struct address
 * @avect: Argument vector
 */
void set_data(data_shell *data, char **avect)
{
	int i = 0;

	data->fname = avect[0];
	if (data->arg)
	{
		data->argv = strtow(data->arg, " \t");
		if (!data->argv)
		{

			data->argv = malloc(sizeof(char *) * 2);
			if (data->argv)
			{
				data->argv[0] = _strdup(data->arg);
				data->argv[1] = NULL;
			}
		}
		for (i = 0; data->argv && data->argv[i]; i++)
			;
		data->argc = i;

		replace_alias(data);
		replace_vars(data);
	}
}

/**
 * free_data - frees data_shell struct fields
 * @data: struct address
 * @all: true if freeing all fields
 */
void free_data(data_shell *data, int all)
{
	ffree(data->argv);
	data->argv = NULL;
	data->path = NULL;
	if (all)
	{
		if (!data->cmd_buf)
			free(data->arg);
		if (data->env)
			free_list(&(data->env));
		if (data->history)
			free_list(&(data->history));
		if (data->alias)
			free_list(&(data->alias));
		ffree(data->environ);
			data->environ = NULL;
		bfree((void **)data->cmd_buf);
		if (data->readfd > 2)
			close(data->readfd);
		_putchar(BUFFER_FLUSH);
	}
}
