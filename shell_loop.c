#include "shell.h"

/**
 * find_cmd - finds command in PATH
 * @data: Data struct
 *
 * Return: Returns void
 */
void find_cmd(data_shell *data)
{
	int i, k;
	char *path = NULL;

	data->path = data->argv[0];
	if (data->linecount_flag == 1)
	{
		data->line_count++;
		data->linecount_flag = 0;
	}

	for (i = 0, k = 0; data->arg[i]; i++)
		if (!is_delimeter(data->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(data, get_env(data, "PATH="), data->argv[0]);
	if (path)
	{
		data->path = path;
		fork_cmd(data);
	}
	else
	{
		if ((interactive(data) || get_env(data, "PATH=") ||
			data->argv[0][0] == '/') && is_cmd(data, data->argv[0]))
			fork_cmd(data);
		else if (*(data->arg) != '\n')
		{
			data->status = 127;
			print_error(data, "not found\n");
		}
	}
}

/**
 * find_builtin - finds builtin command
 * @data: Data struct
 *
 * Return: Returns -1 if builtin not found,
 */
int find_builtin(data_shell *data)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", my_exit},
		{"env", my_env},
		{"help", my_help},
		{"history", my_history},
		{"setenv", my_setenv},
		{"unsetenv", my_unsetenv},
		{"cd", my_cd},
		{"alias", my_alias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(data->argv[0], builtintbl[i].type) == 0)
		{
			data->line_count++;
			built_in_ret = builtintbl[i].func(data);
			break;
		}
	return (built_in_ret);
}

/**
 * fork_cmd - forks a exec thread to run cmd
 * @data: Data struct
 *
 * Return: returns void
 */
void fork_cmd(data_shell *data)
{
	pid_t chld_pid;

	chld_pid = fork();
	if (chld_pid == -1)
	{
		perror("Error:");
		return;
	}

	if (chld_pid == 0)
	{
		if (execve(data->path, data->argv, get_environ(data)) == -1)
		{
			free_data(data, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(data->status));
		if (WIFEXITED(data->status))
		{
			data->status = WEXITSTATUS(data->status);
			if (data->status == 126)
				print_error(data, "Permission denied\n");
		}
	}
}

/**
 * hsh - main shell loop
 * @data: Data struct
 * @avect: the argument vector from main()
 *
 * Return: Returns 0 on success, returns  1 if error, or the error code
 */
int hsh(data_shell *data, char **avect)
{
	int builtin_return = 0;
	ssize_t ro = 0;

	while (ro != -1 && builtin_return != -2)
	{
		clear_data(data);
		if (interactive(data))
			_puts("$ ");
		e_putchar(BUFFER_FLUSH);
		ro = get_input(data);
		if (ro != -1)
		{
			set_data(data, avect);
			builtin_return = find_builtin(data);
			if (builtin_return == -1)
				find_cmd(data);
		}
		else if (interactive(data))
			_putchar('\n');
		free_data(data, 0);
	}
	write_history(data);
	free_data(data, 1);
	if (!interactive(data) && data->status)
		exit(data->status);
	if (builtin_return == -2)
	{
		if (data->err_num == -1)
			exit(data->status);
		exit(data->err_num);
	}

	return (builtin_return);
}
