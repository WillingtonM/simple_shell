#include "shell.h"

/**
 * read_bufer - buffer reader
 * @data: param struct
 * @buff: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_bufer(data_shell *data, char *buff, size_t *i)
{
	ssize_t rd = 0;

	if (*i)
		return (0);
	rd = read(data->readfd, buff, READ_BUFFER_SIZE);
	if (rd >= 0)
		*i = rd;
	return (rd);
}

/**
 * input_buff - buffers chained commands
 * @data: param struct
 * @buff: buffer address
 * @len: len var address
 *
 * Return: read bytes
 */
ssize_t input_buff(data_shell *data, char **buff, size_t *len)
{
	size_t len_pt = 0;

	ssize_t rd = 0;

	if (!*len)
	{
		free(*buff);
		*buff = NULL;
		signal(SIGINT, sigint_handler);
#if USEget_line
		rd = getline(buff, &len_pt, stdin);
#else
		rd = get_line(data, buff, &len_pt);
#endif

		if (rd > 0)
		{
			if ((*buff)[rd - 1] == '\n')
			{
				(*buff)[rd - 1] = '\0';
				rd--;
			}
			data->linecount_flag = 1;
			remove_comments(*buff);
			build_history_list(data, *buff, data->histcount++);
			/* if (_strchr(*buff, ';')) is this command chain? */
			{
				*len = rd;
				data->cmd_buf = buff;
			}
		}
	}
	return (rd);
}

/**
 * sigint_handler - blocks ctrl-C
 * @sig_numb: signal number
 *
 * Return: void
 */
void sigint_handler(__attribute__((unused))int sig_numb)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUFFER_FLUSH);
}

/**
 * get_line - gets next line of input from STDIN
 * @data: Param struct
 * @ptr:  Pointer address to buffer, which is preallocated or NULL
 * @length: Preallocated ptr buffer size, if not NULL
 *
 * Return: returns s
 */
int get_line(data_shell *data, char **ptr, size_t *length)
{
	static char buff[READ_BUFFER_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_bufer(data, buff, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buff + i, '\n');
	k = c ? 1 + (unsigned int)(c - buff) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buff + i, k - i);
	else
		_strncpy(new_p, buff + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * get_input - gets line minus newline
 * @data: param struct
 *
 * Return: return buffer length from get_line()
 */
ssize_t get_input(data_shell *data)
{
	static char *buff;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buff_p = &(data->arg), *p;

	_putchar(BUFFER_FLUSH);
	r = input_buff(data, &buff, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buff + i;

		check_chain(data, buff, &j, i, len);
		while (j < len)
		{
			if (is_chain(data, buff, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			data->cmd_buf_type = CMD_NORM;
		}

		*buff_p = p;
		return (_strlen(p));
	}

	*buff_p = buff;

	return (r);
}
