#include "shell.h"

int execute_command(char **args)
{
	char *home_dir;

    if (args[0] == NULL) {
        /* Empty command */
        return 1;
    }

    /* Check for built-in commands */
    if (strcmp(args[0], "cd") == 0) {
        if (args[1] == NULL) {
            /* Handle 'cd' without arguments (change to home directory) */
            home_dir = getenv("HOME");
            if (home_dir != NULL) {
                chdir(home_dir);
            } else {
                perror("cd");
            }
        } else {
            /* Handle 'cd' with arguments */
            if (chdir(args[1]) != 0) {
                perror("cd");
            }
        }
        return 1;
    } else if (strcmp(args[0], "exit") == 0) {
        /* Handle 'exit' command */
        return 0;
    }

    /* If the command is not a built-in command, try to execute it externally */
    return launch_process(args);
}
