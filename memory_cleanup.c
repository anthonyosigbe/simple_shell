#include "shell.h"

/**
 * free_recurring_data - Release memory used for per-iteration fields.
 * @data: Pointer to the program's data structure.
 *
 * Description: This function deallocates memory that was previously,
 * allocated for the token array, input line, and command name,
 * fields within the data structure.
 *
 * Return: 0.
 */

void free_recurring_data(data_of_program *data)
{
	if (data->tokens)
		free_array_of_pointers(data->tokens);
	if (data->input_line)
		free(data->input_line);
	if (data->command_name)
		free(data->command_name);

	data->input_line = NULL;
	data->command_name = NULL;
	data->tokens = NULL;
}
