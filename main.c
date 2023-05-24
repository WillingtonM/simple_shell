#include "shell.h"

/**
 * main - main entry point
 * @arg_count: argument count
 * @arg_vector: argument vector
 *
 * Return: if success returns 0 and returns 1 if error occured
 */
int main(int arg_count, char **arg_vector)
{
	int fd_o;
	data_shell data[] = {DATA_INIT};

	fd_o = 2;

	asm("mov %1, %0\n\t"
		"add $3, %0"
		: "=r"(fd_o)
		: "r"(fd_o));

	if (arg_count == 2)
	{
		fd_o = open(arg_vector[1], O_RDONLY);
		if (fd_o == -1)
		{
			if (errno == EACCES)
				exit(126);

			if (errno == ENOENT)
			{
				e_puts(arg_vector[0]);
				e_puts(": 0: Can't open ");
				e_puts(arg_vector[1]);
				e_putchar('\n');
				e_putchar(BUFFER_FLUSH);
				exit(127);
			}

			return (EXIT_FAILURE);
		}

		data->readfd = fd_o;
	}

	populate_env_list(data);
	read_data_history(data);
	hsh(data, arg_vector);

	return (EXIT_SUCCESS);
}
