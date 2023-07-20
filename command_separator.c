#include "shell.h"

/**
 * execute_command - function to execute each
 * command separately
 * @command : pointer
 * Return : 1 if command succeeded otherwise
 * return 0
 */

int execute_command(char *command)
{
	char *arguments[MAX_ARGUMENTS];
	char current_directory[MAX_COMMAND_LENGTH];
	int arg_count = tokenize_input(command, arguments);
	int exit_status;
	char *dir;
	int status;

	if (arguments[0] == NULL)
	{
		return (1);
	}
	if (strcmp(arguments[0], "exit") == 0)
	{
		if (arg_count > 1)
		{
			exit_status = atoi(arguments[1]);
			exit(exit_status);
		}
		else {
			exit(EXIT_SUCCESS);
		}
	}
	if (strcmp(arguments[0], "env") == 0)
	{
		print_environment();
		return (1);
	}
	if (strcmp(arguments[0], "setenv") == 0)
	{
		if (arg_count != 3)
		{
			fprintf(stderr, "Error: Invalid syntax. Usage: setenv VARIABLE VALUE\n");
		}
		else {
			if (setenv(arguments[1], arguments[2], 1) != 0)
			{
				fprintf(stderr, "Error: Failed to set environment variable\n");
			}
		}
		return (1);
	}
	if (strcmp(arguments[0], "unsetenv") == 0)
	{
		if (arg_count != 2)
		{
			fprintf(stderr, "Error: Invalid syntax. Usage: unsetenv VARIABLE\n");
		}
		else {
			if (unsetenv(arguments[1]) != 0)
			{
				fprintf(stderr, "Error: Failed to unset environment variable\n");
			}
		}
		return (1);
	}
	if (strcmp(arguments[0], "cd") == 0)
	{
		dir = NULL;
		if (arg_count == 1)
		{
			dir = getenv("HOME");
		}
		else if (strcmp(arguments[1], "-") == 0)
		{
			dir = getenv("OLDPWD");
			printf("%s\n", dir);
		}
		else {
			dir = arguments[1];
		}
		if (chdir(dir) == -1)
		{
			perror("cd");
		}
		else {
			getcwd(current_directory, sizeof(current_directory));
			setenv("OLDPWD", getenv("PWD"), 1);
			setenv("PWD", current_directory, 1);
		}
		return (1)
	}
	if (check_command_exist(arguments[0]) == 0)
	{
		fprintf(stderr, "Error: Command not found\n");
		return (0);
	}
	pid_t pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (0);
	}
	else if (pid == 0)
	{
		execvp(arguments[0], arguments);
		perror("execvp");
		exit(EXIT_FAILURE);
	}
	else {
		waitpid(pid, &status, 0);
        return WIFEXITED(status) && WEXITSTATUS(status) == (0);
	}
}
