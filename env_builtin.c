#include "shell.h"

/**
 * print_environment - function to print env variables
 * Return : nothing
 */

void print_environment()
{
	extern char **environ;
	char **env_var = environ;

	while (*env_var != NULL) {
		printf("%s\n", *env_var);
		env_var++;
	}
}
