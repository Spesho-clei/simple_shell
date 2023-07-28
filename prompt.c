#include "shell.h"
#include <stdio.h>
#include <unistd.h>

void print_prompt(void)
{
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("%s$ ", cwd);
    }
    else
    {
        perror("getcwd");
        printf("$ ");
    }
}
