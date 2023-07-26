#include "main.h"

/**
 * _strlen - Returns string length
 * @s: Pointer to the string.
 * Return: String length
 */
int _strlen(char *s)
{
	int length = 0;
	while (s[length] != '\0')
	{
		length++;
	}
	return length;
}

/**
 * _strcat - Concatenates two strings.
 * @dest: Destination string.
 * @src: Source string to be appended.
 * Return: Pointer to the destination string.
 */
char *_strcat(char *dest, char *src)
{
	char *destAddress = dest;
	while (*destAddress != '\0')
	{
		destAddress++;
	}

	while (*src != '\0')
	{
		*destAddress = *src;
		src++;
		destAddress++;
	}
	*destAddress = '\0';

	return dest;
}

/**
 * _check_white_space - Counts whitespace characters within a string.
 * @s: Pointer to the string.
 * Return: Number of whitespace characters.
 */
unsigned int _check_white_space(char *s)
{
	unsigned int count = 0;
	while (*s != '\0')
	{
		if (*s == ' ' || *s == '\t' || *s == '\n')
		{
			count++;
		}
		s++;
	}
	return count;
}

/**
 * _strtotokens - Splits a string into tokens based on whitespace characters.
 * @str: Pointer to the string.
 * Return: Array of tokens.
 */
char **_strtotokens(char *str)
{
	int i = 0;
	const char delimiters[] = " \t\n";
	unsigned int spaces = _check_white_space(str);
	char **tokens = malloc(sizeof(char *) * (spaces + 1));
	char *token;

	if (!tokens)
	{
		free(tokens);
		fprintf(stderr, "Error: Allocation error\n");
		exit(1);
	}

	token = strtok(str, delimiters);

	while (token != NULL)
	{
		tokens[i] = token;
		token = strtok(NULL, delimiters);
		i++;
	}
	tokens[i] = NULL;

	return tokens;
}

/**
 * _puts - Prints a string followed by a newline character.
 * @str: Pointer to the string.
 */
void _puts(char *str)
{
	while (*str != '\0')
	{
		_putchar(*str);
		str++;
	}
	_putchar('\n');
}
