#include "shell.h"

/*
 * handle_redirection - handles input/output redirection for a command
 * @args: the command arguments
 * Returns 0 on success, -1 on failure
 */
int handle_redirection(char **args)
{
    int in = STDIN_FILENO; /* Default input */
    int out = STDOUT_FILENO; /* Default output */
    int i;

    for (i = 0; args[i] != NULL; i++)
    {
        if (strcmp(args[i], "<") == 0)
        {
            /* Input redirection */
            args[i] = NULL; /* Set the "<" to NULL */
            in = open(args[i + 1], O_RDONLY);
            if (in == -1)
            {
                perror("handle_redirection");
                return -1;
            }
            i++; /* Skip the input file name */
        }
        else if (strcmp(args[i], ">") == 0)
        {
            /* Output redirection */
            args[i] = NULL; /* Set the ">" to NULL */
            out = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
            if (out == -1)
            {
                perror("handle_redirection");
                return -1;
            }
            i++; /* Skip the output file name */
        }
        else if (strcmp(args[i], ">>") == 0)
        {
            /* Append output redirection */
            args[i] = NULL; /* Set the ">>" to NULL */
            out = open(args[i + 1], O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
            if (out == -1)
            {
                perror("handle_redirection");
                return -1;
            }
            i++; /* Skip the output file name */
        }
    }

    /* Set the input and output file descriptors for the command */
    dup2(in, STDIN_FILENO);
    dup2(out, STDOUT_FILENO);

    close(in);
    close(out);

    return 0;
}
