#include "main.h"

/**
 * _printenv - Prints variables within environment.
 * Return: void.
 */
void _printenv(void)
{
	int i = 0;

	while (environ[i])
	{
		_puts(environ[i]);
		i++;
	}
}

/**
 * _isBuiltIn - Tests whether token is a built-in command.
 * @str: Pointer to the string.
 * Return: 0 if true, else 1.
 */
int _isBuiltIn(char *str)
{
	if ((_strcmp(str, "env")) == 0)
		return 0;
	if ((_strcmp(str, "exit")) == 0)
		return 0;
	if ((_strcmp(str, "setenv")) == 0)
		return 0;
	if ((_strcmp(str, "unsetenv")) == 0)
		return 0;
	return 1;
}

/**
 * _executeBuiltIn - Runs a built-in function.
 * @tokens: Double pointer to the tokens.
 * Return: 0 if success.
 */
int _executeBuiltIn(char **tokens)

{
    if ((_strcmp(tokens[0], "env")) == 0)
    {
        _printenv();
        return 0;
    }
    if ((_strcmp(tokens[0], "setenv")) == 0)
    {
        if (tokens[1] && tokens[2])
        {
            _setenv(tokens[1], tokens[2]);
            return 0;
        }
        printf("Usage: setenv var_name var_value\n");
        return 0;
    }
    if ((_strcmp(tokens[0], "cd")) == 0)
    {
       char *directory = tokens[1];
       int cd_result = change_directory(directory);
        return cd_result == 0 ? 0 : 1;
    }
    if (_strcmp(tokens[0], "unsetenv") == 0)
    {
        if (tokens[1])
        {
            _unsetenv(tokens[1]);
            return 0;
        }
        printf("Usage: unsetenv VAR_NAME\n");
        return 0;
    }

    /* Will never reach here because of _isBuiltin() check in _execute() */
    return 1;
}

/**
 * _exitSimpleShell - Initiates shell exit and frees memory.
 * @tokens: Double pointer to the tokens.
 * @line: Pointer to the string from getLine().
 * Return: void.
 */
void _exitSimpleShell(char **tokens, char *line)
{
	int status;

	if (tokens[1] != NULL)
	{
		status = atoi(tokens[1]);
		if (status >= 0)
		{
			free(line);
			free(tokens);
			exit(status);
		}
		write(STDERR_FILENO, "Exit: illegal exit status: ", 28);
		write(STDERR_FILENO, tokens[1], 1);
		write(STDERR_FILENO, "\n", 1);
	}
	else
	{
		free(line);
		free(tokens);
		exit(0);
	}
}
