#include "main.h"

/**
 * _putchar - Appends the character c to stdout.
 * @c: The character to print.
 * Return: On success - 1.
 */
int _putchar(char c)
{
	return write(1, &c, 1);
}

/**
 * _strcmp - Compares two strings.
 * @s1: Pointer to the first string.
 * @s2: Pointer to the second string.
 * Return: 0 if they are equal, otherwise a positive value.
 */
int _strcmp(char *s1, char *s2)
{
	int i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return s1[i] - s2[i];
		i++;
	}
	return 0;
}

/**
 * c_atoi - Converts a string to an integer.
 * @s: The string to convert.
 * Return: The converted integer if successful, -1 if the string contains non-numbers.
 */
int c_atoi(char *s)
{
	int i = 0;
	unsigned int num = 0;

	while (s[i] != '\0')
	{
		if (s[i] >= '0' && s[i] <= '9')
			num = num * 10 + (s[i] - '0');
		else
			return -1;
		i++;
	}

	return num;
}

/**
 * _strcpy - Copies the string pointed to by src,
 * plus the null byte terminated (\0),
 * to the buffer pointed to by dest.
 * @dest: The buffer to copy source to.
 * @src: The source to copy.
 * Return: The copy of the original string.
 */
char *_strcpy(char *dest, char *src)
{
	int i;
	for (i = 0; src[i] != '\0'; i++)
		dest[i] = src[i];
	dest[i] = '\0';
	return dest;
}
