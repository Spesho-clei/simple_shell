#include "main.h"
#include <fcntl.h>
#include <unistd.h>

/**
 * _executeBuiltIn - Execute built-in shell commands.
 * @tokens: Array of strings containing the command and its arguments.
 * Return: 1 if the command is a built-in, 0 otherwise.
 */
int _executeBuiltIn(char **tokens)
{
    /* Implementation of _executeBuiltIn function */
    /* ... (Your implementation here)*/
    /* Remove the unused parameter warning*/
    (void)tokens;
    return 0;
}

/**
 * _execute - Function for file execution.
 * @tokens: Split string into tokens from stdin.
 * @args: Program arguments.
 * Return: 0 if success, otherwise -1.
 */
int _execute(char **tokens, char *args)
{
    char *input_file = NULL, *output_file = NULL;
    int input_fd = -1, output_fd = -1;
    int background = 0;
    char *path;
    pid_t child_pid;
    int status;
    int i;
    int j;

    /* Check for background process '&' at the end of the command */
    i = 0;
    while (tokens[i] != NULL)
    {
        if (strcmp(tokens[i], "&") == 0)
        {
            tokens[i] = NULL;
            background = 1;
            break;
        }
        i++;
    }

    /* Check for input/output redirection */
    for (i = 0; tokens[i] != NULL; i++)
    {
        if (strcmp(tokens[i], "<") == 0)
        {
            input_file = tokens[i + 1];
            input_fd = open(input_file, O_RDONLY);
            if (input_fd < 0)
            {
                perror("Error: Unable to open input file");
                return -1;
            }
            /* Remove "<" and the input file from tokens */
            for (j = i; tokens[j + 2] != NULL; j++)
                tokens[j] = tokens[j + 2];
            tokens[j] = NULL;
            break;
        }
        else if (strcmp(tokens[i], ">") == 0)
        {
            output_file = tokens[i + 1];
            output_fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (output_fd < 0)
            {
                perror("Error: Unable to open output file");
                return -1;
            }
            /* Remove ">" and the output file from tokens */
            for (j = i; tokens[j + 2] != NULL; j++)
                tokens[j] = tokens[j + 2];
            tokens[j] = NULL;
            break;
        }
    }

    if (background)
    {
        /* Remove the ampersand from the arguments */
        tokens[i - 1] = NULL;
    }

    /* If path wasn't entered (such as ls, pwd,) */
    path = path_builder(tokens);
    if (path != NULL)
    {
        status = execute2(tokens, path, args);
        free(path);
        if (input_fd >= 0)
            close(input_fd);
        if (output_fd >= 0)
            close(output_fd);
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
        /* Input redirection */
        if (input_fd >= 0)
        {
            dup2(input_fd, STDIN_FILENO);
            close(input_fd);
        }
        /* Output redirection */
        if (output_fd >= 0)
        {
            dup2(output_fd, STDOUT_FILENO);
            close(output_fd);
        }

        if (execve(tokens[0], tokens, NULL) == -1)
        {
            char err_msg[100];
            sprintf(err_msg, "%s: No such file or directory\n", tokens[0]);
            write(STDERR_FILENO, err_msg, strlen(err_msg));
            free(tokens);
            exit(EXIT_FAILURE);
        }
        return EXIT_SUCCESS;
    }

    /* Parent process */
    if (!background)
    {
        waitpid(child_pid, &status, 0);
    }
    return 0;
}
