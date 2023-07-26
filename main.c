#include "shell.h"
/**
 * main - main function
 * @argc : argument count
 * @argv : array of arguments
 * Return : no.
 */
int main(int argc, char *argv[])
{
	 FILE *file = NULL;
	 char input[MAX_COMMAND_LENGTH];
	 char current_directory[MAX_COMMAND_LENGTH];
	 char *commands[MAX_ARGUMENTS];
	 char *token;
	 char *arguments[MAX_ARGUMENTS];
	 char *expanded_input;
	 char *dir, *name, *value;
	 int num_commands = 0;
	 int i, j;
	 int status;
	 int exit_status;
	 int argc_count;
	 int command_success;
	 int num_aliases = 0;
	 pid_t pid;

	 if (argc > 2)
	 {
		 fprintf(stderr, "Usage: %s [filename]\n", argv[0]);
		 return (EXIT_FAILURE);
	 }
	 if (argc == 2)
	 {
		 file = fopen(argv[1], "r");
		 if (file == NULL)
		 {
			 perror("File open error");
			 return (EXIT_FAILURE);
		 }
	 }
	 while (1)
	 {
		 if (file == NULL)
		 {
			 printf("($) ");
			 fflush(stdout);
			 if (fgets(input, sizeof(input), stdin) == NULL)
			 {
				 printf("\n");
				 break;
			 }
		 }
		 else {
			 if (fgets(input, sizeof(input), file) == NULL)
			 {
				 break;
			 }
			 input[strcspn(input, "\n")] = '\0';
		 }
		 if (input[0] == '#')
		 {
			 continue;
		 }
	 expanded_input = replace_variables(input);
	 token = strtok(expanded_input, ";");
	 while (token != NULL && num_commands < MAX_ARGUMENTS - 1)
	 {
		 commands[num_commands] = token;
		 num_commands++;
		 token = strtok(NULL, ";");
	 }
	 commands[num_commands] = NULL;
	 free(expanded_input);
	 for (i = 0; i < num_commands; i++)
	 {
		 argc_count = tokenize_input(commands[i], arguments);
		 if (arguments[0] == NULL)
		 {
			 continue;
		 }
		 if (strcmp(arguments[0], "exit") == 0)
		 {
			 if (argc_count > 1)
			 {
				 exit_status = atoi(arguments[1]);
				 exit(exit_status);
			 }
			 else {
				 exit(EXIT_SUCCESS);
			 
			 }
			 if (strcmp(arguments[0], "env") == 0)
			 {
				 print_environment();
				 continue;
			 }
			 if (strcmp(arguments[0], "setenv") == 0)
			 {
				 if (argc_count != 3)
				 {
					 fprintf(stderr, "Error: Invalid syntax. Usage: setenv VARIABLE VALUE\n");
				 }
				 else {
					 if (setenv(arguments[1], arguments[2], 1) != 0)
					 {
						 fprintf(stderr, "Error: Failed to set environment variable\n");
					 }
				 }
				 continue;
			 }
			 if (strcmp(arguments[0], "unsetenv") == 0)
			 {
				 if (argc_count != 2)
				 {
					 fprintf(stderr, "Error: Invalid syntax. Usage: unsetenv VARIABLE\n");
				 }
				 else {
					 if (unsetenv(arguments[1]) != 0)
					 {
						 fprintf(stderr, "Error: Failed to unset environment variable\n");
					 }
				 }
				 continue;
			 }
			 if (strcmp(arguments[0], "cd") == 0)
			 {
				 dir = NULL;
				 if (argc_count == 1)
				 {
					 dir = getenv("HOME");
				 }
				 else if (strcmp(arguments[1], "-") == 0)
				 {
					 dir = getenv("OLDPWD");
					 printf("%s\n", dir);
				 }
				 else {
					 dir = arguments[1];
				 }
				 if (chdir(dir) == -1)
				 {
					 perror("cd");
				 }
				 else {
					 getcwd(current_directory, sizeof(current_directory));
					 setenv("OLDPWD", getenv("PWD"), 1);
					 setenv("PWD", current_directory, 1);
				 }
				 continue;
			 }
			 if (strcmp(arguments[0], "alias") == 0)
			 {
				 if (argc_count == 1)
				 {
					 print_aliases();
				 } else {
					 for (j = 1; j < argc_count; j++)
					 {
						 print_alias(arguments[j]);
					 }
				 }
				 continue;
			 }
			 if (strchr(arguments[0], '=') != NULL)
			 {
				 name = strtok(arguments[0], "=");
				 value = strtok(NULL, "=");
				 add_alias(name, value);
				 continue;
			 }
			 if (check_command_exist(arguments[0]) == 0)
			 {
				 fprintf(stderr, "Error: Command not found\n");
				 continue;
			 }
			 pid = fork();
			 if (pid == -1)
			 {
				 perror("fork");
				 continue;
			 }
			 else if (pid == 0)
			 {
				 execvp(arguments[0], arguments);
				 perror("execvp");
				 exit(EXIT_FAILURE);
			 } else {
				 waitpid(pid, &status, 0);
				 command_success = WIFEXITED(status) && WEXITSTATUS(status) == 0;
			 }
			 if (command_success && i + 1 < num_commands && strcmp(commands[i + 1], "&&") == 0)
			 {
				 i++;
			 }
			 else if (!command_success && i + 1 < num_commands && strcmp(commands[i + 1], "||") == 0)
			 {
				 i++;
			 }
		 }
	 }
	 for ( i = 0; i < num_aliases; i++)
	 {
		 free(aliases[i].name);
		 free(aliases[i].value);
	 }
	 if (file != NULL)
	 {
		 fclose(file);
	 }
	 return (EXIT_SUCCESS);
	 }
	 return (0);
}
