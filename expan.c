#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *expand_env_var(char *input)
{
	char *var_value;
	char *var_name;
    char *result = malloc(BUFFER_SIZE);
    if (!result)
    {
        perror("expand_env_var: allocation error");
        exit(EXIT_FAILURE);
    }

    var_value = NULL;
    var_name = strtok(input, "$");
    if (var_name)
    {
        var_value = getenv(var_name);
    }

    if (var_value)
    {
        sprintf(result, "%s%s", var_value, strtok(NULL, ""));
    }
    else
    {
        strcpy(result, input);
    }

    return result;
}
