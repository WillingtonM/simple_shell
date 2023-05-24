#include "shell.h"

/**
 * duplc_chars - duplicates characters
 * @pathstr: PATH string
 * @start: Starting index
 * @stop: Stopping index
 *
 * Return: Returns pointer to new buffer
 */
char *duplc_chars(char *pathstr, int start, int stop)
{
	static char buff[READ_BUFFER_SIZE];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buff[k++] = pathstr[i];
	buff[k] = 0;
	return (buff);
}

/**
 * find_path - finds this cmd in the PATH string
 * @data: Data struct
 * @pathstr: PATH string
 * @cmd: cmd to find
 *
 * Return: Returns full path of cmd if found otherwise NULL
 */
char *find_path(data_shell *data, char *pathstr, char *cmd)
{
	int j = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(data, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[j] || pathstr[j] == ':')
		{
			path = duplc_chars(pathstr, curr_pos, j);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(data, path))
				return (path);
			if (!pathstr[j])
				break;
			curr_pos = j;
		}
		j++;
	}
	return (NULL);
}

/**
 * is_cmd - determines if a file is executable command
 * @data: Data struct
 * @path: path to file
 *
 * Return: Returns 1 if true, Return 0 otherwise
 */
int is_cmd(data_shell *data, char *path)
{
	struct stat st;

	(void)data;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}

	return (0);
}
