#include "main.h"

/**
 * _execute - Function for file execution.
 * @tokens: Split string into tokens from stdin.
 * @args: Program arguments.
 * Return: 0 if success, otherwise -1.
 */
int _execute(char **tokens, char *args)
{
	char *err1, *err2, *err3;
	pid_t child_pid;
	int status;
	char *path;

	/* Tests if the first token is a built-in command */
	if (_isBuiltIn(tokens[0]) == 0)
	{
		status = _executeBuiltIn(tokens);
		return status;
	}

	/* If path wasn't entered (such as ls, pwd,) */
	path = path_builder(tokens);
	if (path != NULL)
	{
		status = execute2(tokens, path, args);
		free(path);
		return status;
	}

	/* If path was entered (e.g., /bin/ls) */
	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error: ");
		return -1;
	}
	if (child_pid == 0)
	{
		if (execve(tokens[0], tokens, NULL) == -1)
		{
			err1 = _strcat(tokens[0], ": No such file or directory\n");
			err2 = _strcat(args, ":");
			err3 = _strcat(err2, err1);
			write(STDERR_FILENO, err3, _strlen(err3));
			free(tokens);
			exit(EXIT_FAILURE);
		}
		return EXIT_SUCCESS;
	}

	wait(&status);
	return 0;
}
