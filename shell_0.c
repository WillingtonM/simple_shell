#include <stdio.h>
#include "simpleshell.h"

/**
 * betty_check - Run betty-style.pl and betty-doc.pl on the given file.
 * @file: Name of the file to be checked.
 */
void betty_check(char *file)
{
	char command[100];

	sprintf(command, "betty-style.pl %s", file);
	system(command);

	sprintf(command, "betty-doc.pl %s", file);
	system(command);
}

/**
 * main - Entry point of the program.
 *
 * Return: Always 0.
 */
int main(void)
{
	char file[] = "shell.c";

	betty_check(file);

	return (0);
}
