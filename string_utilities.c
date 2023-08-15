#include "shell.h"

/**
 * calculate_string_length - computes the length of a string.
 * @string: pointer to the string.
 * Return: length of the string.
 */
int calculate_string_length(char *string)
{
	int length = 0;

	if (string == NULL)
	return (0);

	while (string[length++] != '\0')
	{
	}
	return (--length);
}

/**
 * duplicate_string - duplicates a string.
 * @string: string to be duplicated.
 * Return: pointer to the duplicated string.
 */
char *duplicate_string(char *string)
{
	char *result;
	int length, i;

	if (string == NULL)
	return (NULL);

	length = calculate_string_length(string) + 1;

	result = malloc(sizeof(char) * length);

	if (result == NULL)
	{
	errno = ENOMEM;
	perror("Error");
	return (NULL);
	}
	for (i = 0; i < length ; i++)
	{
	result[i] = string[i];
	}

	return (result);
}

/**
 * compare_strings - Compares two strings.
 * @string1: First string or the shorter one.
 * @string2: Second string or the longer one.
 * @length: Number of characters to be compared; 0 for infinite.
 * Return: 1 if the strings are equal, 0 if different.
 */
int compare_strings(char *string1, char *string2, int length)
{
	int iterator;

	if (string1 == NULL && string2 == NULL)
	return (1);

	if (string1 == NULL || string2 == NULL)
	return (0);

	if (length == 0) /* infinite length */
	{
	if (calculate_string_length(string1) != calculate_string_length(string2))
	return (0);
	for (iterator = 0; string1[iterator]; iterator++)
	{
	if (string1[iterator] != string2[iterator])
	return (0);
	}
	return (1);
	}
	else /* if there is a specified number of characters to be compared */
	{
	for (iterator = 0; iterator < length ; iterator++)
	{
	if (string1[iterator] != string2[iterator])
	return (0);
	}
	return (1);
	}
}

/**
 * concatenate_strings - concatenates two strings.
 * @string1: First string to be concatenated.
 * @string2: Second string to be concatenated.
 * Return: pointer to the concatenated string.
 */
char *concatenate_strings(char *string1, char *string2)
{
	char *result;
	int length1 = 0, length2 = 0;

	if (string1 == NULL)
	string1 = "";
	length1 = calculate_string_length(string1);

	if (string2 == NULL)
	string2 = "";
	length2 = calculate_string_length(string2);

	result = malloc(sizeof(char) * (length1 + length2 + 1));
	if (result == NULL)
	{
	errno = ENOMEM;
	perror("Error");
	return (NULL);
	}

	/* copy string1 */
	for (length1 = 0; string1[length1] != '\0'; length1++)
	result[length1] = string1[length1];
	free(string1);

	/* copy string2 */
	for (length2 = 0; string2[length2] != '\0'; length2++)
	{
	result[length1] = string2[length2];
	length1++;
	}

	result[length1] = '\0';
	return (result);
}

/**
 * reverse_string - reverses a string.
 * @string: pointer to the string.
 * Return: void.
 */
void reverse_string(char *string)
{
	int i = 0, length = calculate_string_length(string) - 1;
	char hold;

	while (i < length)
	{
	hold = string[i];
	string[i++] = string[length];
	string[length--] = hold;
	}
}

