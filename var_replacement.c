#include "shell.h"
/**
 * *replace_variables - function to handle the
 * variable replacement for $? and $$
 * @input : pointer
 * Return : char
 */
char *replace_variables(char *input)
{
	char *output = (char *)malloc(MAX_COMMAND_LENGTH);
	int out_pos = 0;
	int in_pos = 0;
	int input_length = strlen(input);
	int last_exit_status = 0;
	char exit_status_str[4];
	char process_id_str[16];

	while (in_pos < input_length)
	{
		if (input[in_pos] == '$')
		{
			in_pos++;
			if (input[in_pos] == '?')
			{
				snprintf(exit_status_str, sizeof(exit_status_str), "%d", last_exit_status);
				strcat(output, exit_status_str);
				out_pos += strlen(exit_status_str);
			}
			else if (input[in_pos] == '$')
			{
				snprintf(process_id_str, sizeof(process_id_str), "%d", getpid());
				strcat(output, process_id_str);
				out_pos += strlen(process_id_str);
			}
			else {
				output[out_pos] = '$';
				out_pos++;
				continue;
			}
		} else {
			output[out_pos] = input[in_pos];
			out_pos++;
		}
		in_pos++;
	}
	output[out_pos] = '\0';
	return (output);
}
