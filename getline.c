#include "shell.h"

/**
 * custom_getline - function to reads characters
 * from the standard input into the buffer
 * @lineptr : pointer to a pointer
 * @n : pointer
 * @stream : pointer
 * Return : no. of characters read
 */
ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream)
{
	static char buffer[MAX_COMMAND_LENGTH];
	static size_t buffer_pos = 0;
	static ssize_t chars_read = 0;
	size_t i = 0;
	char c;

	if (buffer_pos == 0)
	{
		chars_read = read(fileno(stream), buffer, sizeof(buffer));
		if (chars_read == -1)
		{
			return (-1);
		}
	}
	for (; buffer_pos < (size_t)chars_read; buffer_pos++)
	{
		c = buffer[buffer_pos];
		if (c == '\n' || c == EOF)
		{
			(*lineptr)[i] = '\0';
			buffer_pos++;
			return (i);
		}
		(*lineptr)[i] = c;
		i++;
		if (i >= *n)
		{
			*n *= 2;
			*lineptr = realloc(*lineptr, *n);
			if (*lineptr == NULL)
			{
				return (-1);
			}
		}
	}
	buffer_pos = 0;
	return (i);
}
