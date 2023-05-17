#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "simpleshell.h"

#define BUFFER_SIZE 1024

/**
 * main - Entry point for the simple shell program.
 *
 * Return: Always 0.
 */
int main(void)
{
	char buffer[BUFFER_SIZE];

	while (1)
	{
	printf("$ ");
	fgets(buffer, BUFFER_SIZE, stdin);

	/* Exit the shell if Ctrl+D (EOF) is encountered */
	if (feof(stdin))
	{
		printf("\n");
		break;
	}

	/* Remove the newline character from the input */
	buffer[strcspn(buffer, "\n")] = '\0';

	if (fork() == 0)
	{
		/* Child process */
		char *args[2];

		args[0] = buffer;
		args[1] = NULL;
		execve(buffer, args, NULL);
		perror("execve error");
		exit(EXIT_FAILURE);
	}
	else
	{
		/* Parent process */
		wait(NULL);
	}
	}

	return (0);
}
