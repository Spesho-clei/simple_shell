#include "shell.h"

#define HISTORY_MAX_LINES 100

int history_lines = 0;
char *history[HISTORY_MAX_LINES] = {NULL};

int execute_command(char **args);

int launch_process(char **args)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid == 0)
    {
        /* Child process */
        if (execvp(args[0], args) == -1)
        {
            perror("shell");
        }
        exit(EXIT_FAILURE);
    }
    else if (pid < 0)
    {
        /* Error forking */
        perror("shell");
    }
    else
    {
        /* Parent process */
        do
        {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}

int execute_pipeline(char ***commands)
{
    int pipes[2];
    int in = 0;
    pid_t pid;
    int i;

    for (i = 0; commands[i] != NULL; i++)
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
            if (commands[i + 1]) /* If not the last command, redirect output */
            {
                dup2(pipes[1], 1); /* Set output to the next command */
            }
            close(pipes[0]);
            execvp(commands[i][0], commands[i]);
            perror("execute_pipeline");
            exit(EXIT_FAILURE);
        }
        else
        {
            /* Parent process */
            wait(NULL);
            close(pipes[1]);
            in = pipes[0]; /* Save the input for the next command */
        }
    }

    return 1; /* Continue the shell */
}

void save_history(char *line)
{
	FILE *fp;
	int i;

    if (history_lines >= HISTORY_MAX_LINES)
    {
        free(history[0]);
        for (i = 1; i < HISTORY_MAX_LINES; i++)
        {
            history[i - 1] = history[i];
        }
        history_lines--;
    }
    history[history_lines] = strdup(line);
    history_lines++;

    fp = fopen(HISTORY_FILE, "a");
    if (fp)
    {
        fprintf(fp, "%s\n", line);
        fclose(fp);
    }
}

void load_history(void)
{
    FILE *fp = fopen(HISTORY_FILE, "r");
    if (fp)
    {
        char *line = NULL;
        size_t len = 0;
        ssize_t read;
	int i;

        while ((read = getline(&line, &len, fp)) != -1)
        {
            if (history_lines >= HISTORY_MAX_LINES)
            {
                free(history[0]);
                for (i = 1; i < HISTORY_MAX_LINES; i++)
                {
                    history[i - 1] = history[i];
                }
                history_lines--;
            }
            history[history_lines] = strdup(line);
            history_lines++;
        }

        fclose(fp);
        if (line)
        {
            free(line);
        }
    }
}

void free_args(char **args)
{
	int i;

    if (!args)
        return;

    for (i = 0; args[i]; i++)
    {
        free(args[i]);
    }
    free(args);
}
