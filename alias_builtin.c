#include "shell.h"
typedef struct {
    char *name;
    char *value;
} Alias;

Alias aliases[MAX_ALIASES];
int num_aliases = 0;

/**
 * print_aliases - function to print all aliases
 * Return : nothing
 */
void print_aliases()
{
	int i;

	for ( i = 0; i < num_aliases; i++)
	{
		printf("alias %s='%s'\n", aliases[i].name, aliases[i].value);
	}
}

/**
 * print_alias - function to print a specific
 * alias given its name
 * @name : pointer
 * Return : nothing
 */
void print_alias(const char *name)
{
	int i;

	for ( i = 0; i < num_aliases; i++)
	{
		if (strcmp(aliases[i].name, name) == 0)
		{
			printf("alias %s='%s'\n", aliases[i].name, aliases[i].value);
			return;
		}
	}
}

/**
 * add_alias - function to adds a new alias or
 * updates an existing one
 * @name : pointer
 * @value : pointer
 * Return :nothing
 */
void add_alias(const char *name, const char *value)
{
	int i;

	for ( i = 0; i < num_aliases; i++)
	{
		if (strcmp(aliases[i].name, name) == 0)
		{
			free(aliases[i].value);
			aliases[i].value = strdup(value);
			return;
		}
	}
	if (num_aliases < MAX_ALIASES)
	{
		aliases[num_aliases].name = strdup(name);
		aliases[num_aliases].value = strdup(value);
		num_aliases++;
	}
	else {
		fprintf(stderr, "Error: Maximum number of aliases reached\n");
	}
}
