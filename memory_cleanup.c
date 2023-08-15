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

/**
 * free_all_data - Deallocate all fields within the data structure.
 * @data: Pointer to the program's data structure.
 *
 * Description: This function liberates memory that was previously,
 * allocated for different fields of the data structure.
 * These fields encompass file descriptors, recurring data,
 * environment variables, and alias lists.
 *
 * Return: 0.
 */

void free_all_data(data_of_program *data)
{
	if (data->file_descriptor != 0)
	{
		if (close(data->file_descriptor))
			perror(data->program_name);
	}
	free_recurring_data(data);
	free_directory_array(data->env);
	free_directory_array(data->alias_list);
}

/**
 * free_directory_array - Deallocate an array of pointers,
 * and the individual pointers.
 * @array: Array of pointers to be deallocated.
 *
 * Description: This function releases memory for each individual pointer,
 * within the array and subsequently releases the,
 * memory occupied by the array.
 *
 * Return: 0.
 */

void free_directory_array(char **array)
{
	int index;

	if (array != NULL)
	{
		for (index = 0; array[index]; index++)
			free(array[index]);
		free(array);
		array = NULL;
	}
}
