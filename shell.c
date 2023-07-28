#include "shell.h"

#define HISTORY_MAX_LINES 100

int history_lines = 0;
char *history[HISTORY_MAX_LINES] = {NULL};

int execute_command(char **args)
{
    if (args[0] == NULL) {
        return 1; /* Empty command*/
    }

    /* Handle built-in commands*/
    if (strcmp(args[0], "cd") == 0) {
        if (args[1] == NULL) {
            fprintf(stderr, "shell: expected argument to \"cd\"\n");
        } else {
            if (chdir(args[1]) != 0) {
                perror("shell");
            }
        }
        return 1;
    } else if (strcmp(args[0], "exit") == 0) {
        return 0;
    }

    /* Handle command substitution*/
    if (handle_substitution(args))
        return 1;

    /* Handle environment variable expansion*/
    if (handle_variable_expansion(args))
        return 1;

    /* Handle input/output redirection and pipes*/
    if (handle_redirection(args))
        return 1;

    return launch_process(args);
}

int launch_process(char **args)
{
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0) {
        /* Child process*/
        if (execvp(args[0], args) == -1) {
            perror("shell");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        /* Error forking*/
        perror("shell");
    } else {
        /* Parent process*/
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}
char *expand_env_var(char *input)
{
    if (input[0] == '$')
    {
        char *env_var_name = input + 1;
        char *env_var_value = getenv(env_var_name);
        if (env_var_value)
        {
            return strdup(env_var_value);
        }
        else
        {
            fprintf(stderr, "Environment variable '%s' not found\n", env_var_name);
        }
    }
    return input;
}
int main(void)
{
    char *line;
    char **args;
    int status;

    do
    {
        print_prompt();
        line = read_line();
        args = split_line(line);
        char **expanded_args = malloc(BUFFER_SIZE * sizeof(char *));
        if (!expanded_args)
        {
            perror("main: allocation error");
            exit(EXIT_FAILURE);
        }
        for (int i = 0; args[i] != NULL; i++)
        {
            expanded_args[i] = expand_env_var(args[i]);
        }
        status = execute_command(expanded_args);

        free(line);
        free(args);
        free(expanded_args);
    } while (status);

    return 0;
}

int execute_pipeline(char ***commands)
{
    int pipes[2];
    int in = 0;
    pid_t pid;

    for (int i = 0; commands[i] != NULL; i++)
    {
        if (pipe(pipes) < 0)
        {
            perror("execute_pipeline");
            exit(EXIT_FAILURE);
        }

        if ((pid = fork()) == -1)
        {
            perror("execute_pipeline");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
            dup2(in, 0);
            if (commands[i + 1]) /* If not the last command, redirect output*/
            {
                dup2(pipes[1], 1); /* Set output to the next command*/
            }
            close(pipes[0]);
            execvp(commands[i][0], commands[i]);
            perror("execute_pipeline");
            exit(EXIT_FAILURE);
        }
        else
        {
            /* Parent process*/
            wait(NULL);
            close(pipes[1]);
            in = pipes[0]; /* Save the input for the next command*/
        }
    }

    return 1; /* Continue the shell*/
}

void save_history(char *line)
{
    if (history_lines >= HISTORY_MAX_LINES) {
        free(history[0]);
        for (int i = 1; i < HISTORY_MAX_LINES; i++) {
            history[i - 1] = history[i];
        }
        history_lines--;
    }
    history[history_lines] = strdup(line);
    history_lines++;

    FILE *fp = fopen(HISTORY_FILE, "a");
    if (fp) {
        fprintf(fp, "%s\n", line);
        fclose(fp);
    }
}

void load_history(void)
{
    FILE *fp = fopen(HISTORY_FILE, "r");
    if (fp) {
        char *line = NULL;
        size_t len = 0;
        ssize_t read;

        while ((read = getline(&line, &len, fp)) != -1) {
            if (history_lines >= HISTORY_MAX_LINES) {
                free(history[0]);
                for (int i = 1; i < HISTORY_MAX_LINES; i++) {
                    history[i - 1] = history[i];
                }
                history_lines--;
            }
            history[history_lines] = strdup(line);
            history_lines++;
        }

        fclose(fp);
        if (line) {
            free(line);
        }
    }
}
void free_args(char **args)
{
    if (!args)
        return;

    for (int i = 0; args[i]; i++) {
        free(args[i]);
    }
    free(args);
}
