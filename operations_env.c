#include "shell.h"

/**
 * display_environment - Present the current shell environment.
 * @data: Pointer to the program's data structure.
 * using if else and for loop
 * Return: Zero on success, or a non-zero number if specified as arguments.
 */
int display_environment(data_of_program *data)
{
	int index;
	char cpname[50] = {'\0'};
	char *var_copy = NULL;

	/* If no arguments are provided */
	if (data->tokens[1] == NULL)
		print_environment(data);
	else
	{
		for (index = 0; data->tokens[1][index]; index++)
		{
			/* Check for the presence of '=' character */
			if (data->tokens[1][index] == '=')
			{
				var_copy = calculate_string_length(get_environment_key(cpname, data));
				if (var_copy != NULL)
					set_environment_key(cpname, data->tokens[1] + index + 1, data);

				print_environment(data);

				if (get_environment_key(cpname, data) == NULL)
				{
					print_string(data->tokens[1]);
					print_string("\n");
				}
				else
				{
					set_environment_key(cpname, var_copy, data);
					free(var_copy);
				}
				return (0);
			}
			cpname[index] = data->tokens[1][index];
		}
		errno = 2;
		perror(data->command_name);
		errno = 127;
	}
	return (0);
}
/**
 * set_environment - Modify the environment variable.
 * @data: Pointer to the program's data structure.
 *
 * Return: Zero on success, or a non-zero number if specified as arguments.
 */

int set_environment(data_of_program *data)
{
	/* Validate provided arguments */
	if (data->tokens[1] == NULL || data->tokens[2] == NULL)
	return (0);
	if (data->tokens[3] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
	return (5);
	}

	/* Set the environment variable */
		set_environment_key(data->tokens[1], data->tokens[2], data);

	return (0);
}


/**
 * unset_environment - Clear the specified environment variable.
 * @data : Pointer to the program's data structure.
 * using if statement
 * Return: Zero on success, or a non-zero number if provided as arguments.
 */

int unset_environment(data_of_program *data)
{
	/* Validate provided arguments */
	if (data->tokens[1] == NULL)
		return (0);
	if (data->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}

	/* Remove the environment variable */
	remove_environment_key(data->tokens[1], data);

	return (0);
}

