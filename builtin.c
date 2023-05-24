#include "shell.h"

/**
 * my_help - change current directory of process
 * @data: Structure containing potential arguments
 *
 * Return: Returns 0 always
 */
int my_help(data_shell *data)
{
	char **arg_array;

	arg_array = data->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array);

	return (0);
}

/**
 * my_exit - exits the shell
 * @data: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if data.argv[0] != "exit"
 */
int my_exit(data_shell *data)
{
	int exit_chk;

	if (data->argv[1])  /* If there is an exit arguement */
	{
		exit_chk = _erratoi(data->argv[1]);
		if (exit_chk == -1)
		{
			data->status = 2;
			print_error(data, "Illegal number: ");
			e_puts(data->argv[1]);
			e_putchar('\n');
			return (1);
		}
		data->err_num = _erratoi(data->argv[1]);
		return (-2);
	}
	data->err_num = -1;
	return (-2);
}

/**
 * my_cd - changes current directory of process
 * @data: Structure containing potential arguments.
 *
 *  Return: Return 0 always
 */
int my_cd(data_shell *data)
{
	int chdir_return;
	char *s, *dir, buff[READ_BUFFER_SIZE];

	s = getcwd(buff, READ_BUFFER_SIZE);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!data->argv[1])
	{
		dir = get_env(data, "HOME=");
		if (!dir)
			chdir_return = /* TODO: */
				chdir((dir = get_env(data, "PWD=")) ? dir : "/");
		else
			chdir_return = chdir(dir);
	}
	else if (_strcmp(data->argv[1], "-") == 0)
	{
		if (!get_env(data, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(get_env(data, "OLDPWD=")), _putchar('\n');
		chdir_return = /* TODO: */
			chdir((dir = get_env(data, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_return = chdir(data->argv[1]);
	if (chdir_return == -1)
	{
		print_error(data, "can't cd to ");
		e_puts(data->argv[1]), e_putchar('\n');
	}
	else
	{
		_setenv(data, "OLDPWD", get_env(data, "PWD="));
		_setenv(data, "PWD", getcwd(buff, READ_BUFFER_SIZE));
	}
	return (0);
}
