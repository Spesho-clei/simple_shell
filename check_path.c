#include "shell.h"

/**
 * check_command_exist - function to search for the command
 * in the directories specified by the PATH environment variable
 * @command : pointer
 * Return : 0 (command not found)
 */
int check_command_exist(const char *command)
{
	char *path_env;
	char *path_copy;
	char *path;

	path_env = getenv("PATH");

	if (path_env == NULL)
		return (0);
	path_copy = strdup(path_env);
	if (path_copy == NULL)
		return (0);
	path = strtok(path_copy, ":");
	while (path != NULL) {
		char full_path[MAX_COMMAND_LENGTH];
		snprintf(full_path, sizeof(full_path), "%s/%s", path, command);
		if (access(full_path, X_OK) == 0) {
			free(path_copy);
			return (1);
		}
		path = strtok(NULL, ":");
	}
	free(path_copy);
	return (0);
}
