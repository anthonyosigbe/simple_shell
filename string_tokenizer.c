#include "shell.h"

/**
 * custom_strtok - Splits a string into tokens using specified delimiters.
 * @line: Pointer to the input string.
 * @delimiter: Pointer to the string containing delimiter characters.
 * Return: A pointer to the next token, or NULL if no more tokens.
 */
char *custom_strtok(char *line, char *delimiter)
{
	int delim_index;
	static char *str;
	char *copystr;

	if (line != NULL)
		str = line;

	for (; *str != '\0'; str++)
	{
		for (delim_index = 0; delimiter[delim_index] != '\0'; delim_index++)
		{
			if (*str == delimiter[delim_index])
				break;
		}
		if (delimiter[delim_index] == '\0')
			break;
	}

	copystr = str;

	if (*copystr == '\0')
		return (NULL);

	for (; *str != '\0'; str++)
	{
		for (delim_index = 0; delimiter[delim_index] != '\0'; delim_index++)
		{
			if (*str == delimiter[delim_index])
			{
				*str = '\0';
				str++;
				return (copystr);
			}
		}
	}

	return (copystr);
}

