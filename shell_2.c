#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include "simpleshell.h"

#define BUFFER_SIZE 1024
#define MAX_ARGS 64
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
	char *args[MAX_ARGS];
	char *token;
	int i = 0;
	/* Tokenize the input */
	token = strtok(buffer, " ");
	while (token != NULL && i < MAX_ARGS - 1)
	{
	args[i] = token;
	i++;
	token = strtok(NULL, " ");
	}
	args[i] = NULL;

	execve(args[0], args, NULL);
	perror("execve error");
	exit(EXIT_FAILURE);
	}
	else
	{
	wait(NULL);
	}
	}
	return (0);
}
