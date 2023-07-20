#include "shell.h"

/**
 * tokenize_input - function that manually parses
 * the input string
 * @input :pointer to receive input string
 * @ arguments : array to store the command and
 * its arguments
 * Return :  number of arguments parsed
 */

int tokenize_input(char *input, char **arguments)
{
	int i = 0;
	char *token = strtok(input, " ");

	while (token != NULL && i < MAX_ARGUMENTS - 1)
	{
		arguments[i] = token;
		i++;
		token = strtok(NULL, " ");
	}
	arguments[i] = NULL;
	return (i);
}
