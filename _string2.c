#include "main.h"

/**
 * is_delim - Checks if a character is equal to delim.
 * @c: The character.
 * @delim: The delimiter string.
 * Return: 0 if no match, 1 if matched.
 */
int is_delim(char c, const char *delim)
{
	while (delim && *delim)
	{
		if (c == *delim)
			return 1;
		++delim;
	}
	return 0;
}

/**
 * _strtok - Mimics the strtok function.
 * @src: The source string.
 * @delim: The delimiter string.
 * Return: An individual token in array format.
 */
char *_strtok(char *src, const char *delim)
{
	static char *s;
	static unsigned int i;
	char *result = NULL;
	int is_space = 0;

	if (src)
	{
		s = src;
		for (i = 0; s[i]; i++)
		{
			if (is_delim(s[i], delim))
				s[i] = '\0';
		}
	}

	if (s == NULL || *s == '\0')
		return NULL;
	result = s;
	i = _strlen(s);
	if (s[i] == '\0' && _strlen(s) > 0)
		is_space = 1;
	s = s + _strlen(s) + is_space;
	return result;
}

/**
 * ctrlc - Control C handler.
 * @signum: The signal number received.
 * Return: Void.
 */
void ctrlc(int signum)
{
	(void)signum;
	write(STDOUT_FILENO, "\n#cisfun$ ", 10);
}

/**
 * get_line - Reads the user's command from stdin into a buffer.
 * @str: Pointer to the buffer.
 * Return: Number of characters read.
 */
ssize_t get_line(char **str)
{
	ssize_t i = 0, size = 0, t = 0, t2 = 0, n = 0;
	char buff[1024];

	while (t2 == 0 && (i = read(STDIN_FILENO, buff, 1024 - 1)))
	{
		if (i == -1)
			return -1;

		buff[i] = '\0';

		n = 0;
		while (buff[n] != '\0')
		{
			if (buff[n] == '\n')
				t2 = 1;
			n++;
		}

		if (t == 0)
		{
			i++;
			*str = malloc(sizeof(char) * i);
			*str = _strcpy(*str, buff);
			size = i;
			t = 1;
		}
		else
		{
			size += i;
			*str = _strcat(*str, buff);
		}
	}
	return size;
}

/**
 * _strdup - Duplicates a string.
 * @str: The string to duplicate.
 * Return: Pointer to the duplicated string within allocated memory.
 */
char *_strdup(char *str)
{
	char *duplicate_str;
	int i, len = 0;

	if (str == NULL)
		return NULL;

	while (str[len])
		len++;
	len++; /* add null terminator to length */

	duplicate_str = malloc(sizeof(char) * len);
	if (duplicate_str == NULL)
		return NULL;

	i = 0;
	while (i < len)
	{
		duplicate_str[i] = str[i];
		i++;
	}

	return duplicate_str;
}
