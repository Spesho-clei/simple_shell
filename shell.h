#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_ARGS 64
#define DELIMITERS " \t\n\r\a"
#define HISTORY_FILE ".shell_history"

int execute_command(char **args);
char *read_line(void);
char **split_line(char *line);
int launch_process(char **args);
int handle_redirection(char **args);
int handle_pipes(char **args);
int handle_substitution(char **args);
int handle_variable_expansion(char **args);
void save_history(char *line);
void load_history(void);
void free_args(char **args);
int execute_pipeline(char ***commands);
char *expand_env_var(char *input);
int main(void);
void handle_redirection(char **args);

#endif /* SHELL_H */