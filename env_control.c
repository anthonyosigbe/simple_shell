#include "shell.h"

/**
 * get_environment_key - Retrieve the value of an environment variable.
 * @key: The environment variable to retrieve.
 * @data: Pointer to the program's data structure.
 *
 * Return: A pointer to the variable's value, or NULL if it doesn't exist.
 */
char *get_environment_key(char *key, data_of_program *data)
{
	int index, keyLength = 0;

	/* Validate the arguments */
	if (key == NULL || data->env == NULL)
		return (NULL);

	/* Determine the length of the requested variable */
	keyLength = calculate_string_length(key);

	for (index = 0; data->env[index]; index++)
	{
		/* Iterate through the environment and check for variable match */
		if (compare_strings(key, data->env[index], keyLength) &&
				data->env[index][keyLength] == '=')
		{
			/* Return the value of the key NAME= when found */
			return (data->env[index] + keyLength + 1);
		}
	}
	/* Return NULL if the key was not found */
	return (NULL);
}

/**
 * set_environment_key - Set or overwrite the value of an environment variable.
 * @key: The name of the variable to set.
 * @value: The new value to set.
 * @data: Pointer to the program's data structure.
 *
 * Return: 1 if any of the parameters are NULL, 2 on error, or 0 on success.
 */
int set_environment_key(char *key, char *value, data_of_program *data)
{
	int index, keyLength = 0, isNewKey = 1;

	/* Validate the arguments */
	if (key == NULL || value == NULL || data->env == NULL)
		return (1);
	/* Determine the length of the variable to be set */
	keyLength = calculate_string_length(key);
	for (index = 0; data->env[index]; index++)
	{
		/* Iterate through the environment and check for variable match */
		if (compare_strings(key, data->env[index], keyLength) &&
				data->env[index][keyLength] == '=')
		{
			/* If the key already exists, free the variable and create anew */
			isNewKey = 0;
			free(data->env[index]);
			break;
		}
	}
	/* Create a string of the form key=value */
	data->env[index] = concatenate_strings(duplicate_string(key), "=");
	data->env[index] = concatenate_strings(data->env[index], value);

	if (isNewKey)
	{
		/* If the variable is new, place it at the end of the list */
		data->env[index + 1] = NULL;
	}
	return (0);
}

/**
 * remove_environment_key - Remove a key from the environment.
 * @key: The key to remove.
 * @data: Pointer to the program's data structure.
 *
 * Return: 1 if the key was removed, 0 if the key does not exist.
 */
int remove_environment_key(char *key, data_of_program *data)
{
	int index, keyLength = 0;

	/* Validate the arguments */
	if (key == NULL || data->env == NULL)
		return (0);
	/* Determine the length of the variable to be removed */
	keyLength = str_length(key);
	for (index = 0; data->env[index]; index++)
	{
		/* Iterate through the environment and check for variable match */
		if (compare_strings(key, data->env[index], keyLength) &&
				data->env[index][keyLength] == '=')
		{
			/* If the key exists, remove it */
			free(data->env[index]);
			/* Shift other keys one position down */
			index++;
			for (; data->env[index]; index++)
			{
				data->env[index - 1] = data->env[index];
			}
			/* Set NULL at the new end of the list */
			data->env[index - 1] = NULL;
			return (1);
		}
	}
	return (0);
}
/**
 * print_environment - Print the current environment variables.
 * @data: Pointer to the program's data structure.
 *
 * Return: Nothing.
 */

void print_environment(data_of_program *data)
{
	int index;

	for (index = 0; data->env[index]; index++)
	{
		print_string(data->env[index]);
		print_string("\n");
	}
}
