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
				/* Create a temporary copy of the variable value */
				var_copy = calculate_string_length(get_environment_key(cpname, data));
				if (var_copy != NULL)
					set_environment_key(cpname, data->tokens[1] + index + 1, data);

				/* Print the environment */
				print_environment(data);

				if (get_environment_key(cpname, data) == NULL)
				{
					/* Print the variable if it's absent in the environment*/
					print_string(data->tokens[1]);
					print_string("\n");
				}
				else
				{
					/* Restore the previous value of the variable */
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

