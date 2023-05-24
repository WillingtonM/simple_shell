#include "shell.h"



/**
 * write_history - creates or appends to existing file
 * @data: Parameter struct
 *
 * Return: Returns 1 on success, otherwise -1
 */
int write_history(data_shell *data)
{
	ssize_t fd_o;
	list_t *node = NULL;
	char *filename = get_history_file(data);

	if (!filename)
		return (-1);

	fd_o = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);

	free(filename);

	if (fd_o == -1)
		return (-1);

	for (node = data->history; node; node = node->next)
	{
		puts_fd(node->str, fd_o);
		put_fd('\n', fd_o);
	}

	put_fd(BUFFER_FLUSH, fd_o);
	close(fd_o);

	return (1);
}

/**
 * build_history_list - adds entry to history linked list
 * @data: Structure containing potential arguments. Used to maintain
 * @buff: buffer
 * @linecount: History linecount, histcount
 *
 * Return: 0
 */
int build_history_list(data_shell *data, char *buff, int linecount)
{
	list_t *node = NULL;

	if (data->history)
		node = data->history;
	_add_node_end(&node, buff, linecount);

	if (!data->history)
		data->history = node;

	return (0);
}

/**
 * read_data_history - reads history from file
 * @data: Parameter struct
 *
 * Return: Returns histcount on success, otherwise 0
 */
int read_data_history(data_shell *data)
{
	int i, last = 0, linecount = 0;
	ssize_t fd_o, rdlen, fsize = 0;
	struct stat st;
	char *buff = NULL, *filename = get_history_file(data);

	if (!filename)
		return (0);

	fd_o = open(filename, O_RDONLY);
	free(filename);
	if (fd_o == -1)
		return (0);
	if (!fstat(fd_o, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buff = malloc(sizeof(char) * (fsize + 1));
	if (!buff)
		return (0);
	rdlen = read(fd_o, buff, fsize);
	buff[fsize] = 0;
	if (rdlen <= 0)
		return (free(buff), 0);
	close(fd_o);
	for (i = 0; i < fsize; i++)
		if (buff[i] == '\n')
		{
			buff[i] = 0;
			build_history_list(data, buff + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_history_list(data, buff + last, linecount++);

	free(buff);
	data->histcount = linecount;
	while (data->histcount-- >= HIST_MAX)
		_delete_node_at_index(&(data->history), 0);
	renumber_history(data);
	return (data->histcount);
}

/**
 * renumber_history - renumbers history linked list after changes
 * @data: Structure containing potential arguments. Used to maintain
 *
 * Return: Returns new histcount
 */
int renumber_history(data_shell *data)
{
	int j = 0;
	list_t *node = data->history;

	while (node)
	{
		node->num = j++;
		node = node->next;
	}
	return (data->histcount = j);
}

/**
 * get_history_file - gets history file
 * @data: Parameter struct
 *
 * Return: Returns allocated string containg history file
 */

char *get_history_file(data_shell *data)
{
	char *dir, *buff;

	dir = get_env(data, "HOME=");
	buff = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!dir)
		return (NULL);

	if (!buff)
		return (NULL);

	buff[0] = 0;
	_strcpy(buff, dir);
	_strcat(buff, "/");
	_strcat(buff, HIST_FILE);

	return (buff);
}
