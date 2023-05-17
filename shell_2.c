#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024
#define MAX_ARGS 64

/**
 * execute_command - Executes the given command using execve.
 * @command: The command to execute.
 * @args: The arguments for the command.
 * @path: The PATH environment variable.
 *
 * Return: None.
 */
void execute_command(char *command, char *args[], char *path)
{
	char *token, *full_path;
	char *arguments[MAX_ARGS];
	int i;

	token = strtok(path, ":");
	while (token != NULL)
	{
		full_path = malloc(strlen(token) + strlen(command) + 2);
		if (full_path == NULL)
		{
			perror("Malloc error");
			exit(EXIT_FAILURE);
		}

		sprintf(full_path, "%s/%s", token, command);

		arguments[0] = full_path;

		for (i = 1; args[i - 1] != NULL; i++)
		{
			arguments[i] = args[i - 1];
		}
		arguments[MAX_ARGS - 1] = NULL;

		execve(full_path, arguments, NULL);

		free(full_path);

		token = strtok(NULL, ":");
	}

	fprintf(stderr, "Command not found: %s\n", command);
	exit(EXIT_FAILURE);
}

/**
 * handle_child_process - Handles the logic for the child process.
 * @buffer: The input command line buffer.
 * @path: The PATH environment variable.
 *
 * Return: None.
 */
void handle_child_process(char *buffer, char *path)
{
	char *command = strtok(buffer, " ");
	char *args[MAX_ARGS];

	int i;

	for (i = 0; command != NULL; i++)
	{
		args[i] = command;
		command = strtok(NULL, " ");
	}
	args[i] = NULL;

	execute_command(args[0], args + 1, path);
}

/**
 * handle_eof - Handles the end-of-file condition (Ctrl+D).
 *
 * Return: None.
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
	char *path = getenv("PATH");

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
			handle_child_process(buffer, path);
		}
		else
		{
			wait(NULL);
		}
	}

	return (0);
}
