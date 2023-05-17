#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

/**
 * execute_command - Executes the given command using execve.
 * @command: The command to execute.
 */
void execute_command(char *command)
{
	execve(command, &command, NULL);
	perror("Execve error");
	exit(EXIT_FAILURE);
}

/**
 * handle_child_process - Handles the logic for the child process.
 * @buffer: The input command line buffer.
 */
void handle_child_process(char *buffer)
{
	char *command = strtok(buffer, " ");

	execute_command(command);
}

/**
 * handle_eof - Handles the end-of-file condition (Ctrl+D).
 */
void handle_eof(void)
{
	printf("\n");
	exit(EXIT_SUCCESS);
}

/**
 * main - Entry point of the shell program.
 *
 * Return: Always 0.
 */
int main(void)
{
	char buffer[BUFFER_SIZE];
	ssize_t bytes_read;
	pid_t pid;

	while (1)
	{
		printf("#cisfun$ ");

		bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE);

		if (bytes_read == 0)
		{
			handle_eof();
		}

		buffer[bytes_read - 1] = '\0';

		pid = fork();

		if (pid == -1)
		{
			perror("Fork error");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			handle_child_process(buffer);
		}
		else
		{
			wait(NULL);
		}
	}

	return (0);
}
