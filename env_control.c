#include "shell.h"

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
