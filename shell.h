#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGUMENTS 64
#define MAX_ALIASES 64

typedef struct {
    char *name;
    char *value;
} Alias;

Alias aliases[MAX_ALIASES];

int check_command_exist(const char *command);
int execute_command(char *command);
void add_alias(const char *name, const char *value);
void print_alias(const char *name);
void print_aliases();
char *replace_variables(char *input);
int tokenize_input(char *input, char **arguments);
ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream);
void print_environment();
int check_command_exist(const char *command);

#endif
