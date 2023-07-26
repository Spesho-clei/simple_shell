#include "main.h"

/**
 * _setenv - updates environment variable.
 * @var_name: variable name
 * @var_value: variable value.
 * Return: 0 - success, otherwise -1.
 */
int _setenv(char *var_name, char *var_value)
{
	int i = 0;
	size_t name_len;
	char *var_new;

	name_len = _strlen(var_name);
	i = 0;
	/* updating an existing variable */
	while (environ[i])
	{
		if (strncmp(environ[i], var_name, name_len) == 0)
		{
			var_new = var_build(var_name, var_value);
			free(environ[i]);
			environ[i] = _strdup(var_new);
			free(var_new);
			return (0);
		}
		i++;
	}
	/* adding a totally new variable */
	var_new = var_build(var_name, var_value);
	environ[i] = _strdup(var_new);
	environ[i + 1] = NULL;
	free(var_new);

	return (0);
}

/**
 * var_build - Creates environment variable based on name and value.
 * @var_name: Variable name.
 * @var_value: Variable value.
 * Return: String having full environment variable.
 */
char *var_build(char *var_name, char *var_value)
{
	size_t var_len = _strlen(var_name) + _strlen(var_value) + 2;
	char *new_var = malloc(sizeof(char) * var_len);

	if (new_var == NULL)
	{
		perror("Error: Insufficient memory\n");
		return (NULL);
	}

	snprintf(new_var, var_len, "%s=%s", var_name, var_value);
	return (new_var);
}

/**
 * _unsetenv - Removes an environment variable.
 * @var_name: Variable name.
 * Return: 0 if successful, -1 otherwise.
 */
int _unsetenv(char *var_name)
{
	int i = 0;
	char **env_temp;
	size_t name_len;

	name_len = _strlen(var_name);
	while (environ[i])
	{
		if (strncmp(environ[i], var_name, name_len) == 0)
		{
			env_temp = environ;
			free(env_temp[i]);
			do {
				env_temp[i] = env_temp[i + 1];
				i++;
			} while (env_temp[i]);
		}
		i++;
	}
	return (0);
}
