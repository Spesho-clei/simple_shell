#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **split_line(char *line)
{
    int bufsize = MAX_ARGS;
    int position = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    char *token;

    if (!tokens)
    {
        perror("split_line: allocation error");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, DELIMITERS);
    while (token != NULL)
    {
        tokens[position] = token;
        position++;

        if (position >= bufsize)
        {
            bufsize += MAX_ARGS;
            tokens = realloc(tokens, bufsize * sizeof(char *));
            if (!tokens)
            {
                perror("split_line: reallocation error");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, DELIMITERS);
    }
    tokens[position] = NULL;
    return tokens;
}
