#include "shell.h"

/**
 * execute_builtin_list - Find a match and execute,
 * the corresponding builtin operation.
 * @data: Pointer to the program's data structure.
 *
 * Return: The return value of the executed function upon a match,
 * or -1 if no match is found.
 **/

int execute_builtin_list(data_of_program *data)
{
	int iterator;
	builtins options[] = {
		{"exit", exit_builtin},
		{"env", display_environment},
		{"help", help_builtin},
		{NULL, NULL}

	};

	/* Traverse the structure */
	for (iterator = 0; options[iterator].builtin != NULL; iterator++)
	{
		/* Check for a match between the given command and a builtin */
		if (compare_strings(options[iterator].builtin, data->command_name, 0))
		{
			/* Execute the associated function and return its return value */
			return (options[iterator].function(data));
		}
	}

	/* If no match found, return -1 */
	return (-1);
}
