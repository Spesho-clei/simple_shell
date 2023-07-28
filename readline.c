#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

char *read_line(void)
{
    char *line = NULL;
    size_t bufsize = 0; /* Use size_t for bufsize*/

    if (getline(&line, &bufsize, stdin) == -1)
    {
        if (feof(stdin)) /* End of file (Ctrl+D in Linux/Unix)*/
        {
            exit(EXIT_SUCCESS);
        }
        else
        {
            perror("read_line");
            exit(EXIT_FAILURE);
        }
    }

    return line;
}
