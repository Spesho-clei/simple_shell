#include "shell.h"

int main(void)
{
    char *line;
    char **args;
    int status;

    load_history();

    do {
        printf("$ ");
        line = read_line();
        save_history(line);
        args = split_line(line);
        status = execute_command(args);

        free(line);
        free(args);
    } while (status);

    return EXIT_SUCCESS;
}
