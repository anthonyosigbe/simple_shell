#include "shell.h"

/**
 * read_line - Read a single line from the prompt.
 * @data: Pointer to the program's data structure.
 * using if ,for, do and while loop
 * Return: The number of bytes read.
 */
int read_line(data_of_program *data)
{
	char buff[BUFFER_SIZE] = {'\0'};
	static char *array_commands[10] = {NULL};
	static char array_operators[10] = {'\0'};
	ssize_t bytes_read;
	size_t i = 0;

	/* Check if there are no more commands in the array */
	/* and evaluate logical operators if they are present */
	if (!array_commands[0] || (array_operators[0] == '&' && errno != 0) ||
	    (array_operators[0] == '|' && errno == 0))
	{
		/* Clear allocated memory in the array if it exists */
		for (i = 0; array_commands[i]; i++)
		{
			free(array_commands[i]);
			array_commands[i] = NULL;
		}

		/* Read from the file descriptor into the buffer */
		bytes_read = read(data->file_descriptor, &buff, BUFFER_SIZE - 1);
		if (bytes_read == 0)
			return (-1);

		/* Split lines based on '\n' or ';' */
		i = 0;
		do {
			array_commands[i] = duplicate_string(custom_strtok(i ? NULL : buff, "\n;"));
			i = check_logic_ops(array_commands, i, array_operators);
		} while (array_commands[i++]);
	}

	data->input_line = array_commands[0];
	for (i = 0; array_commands[i]; i++)
	{
		array_commands[i] = array_commands[i + 1];
		array_operators[i] = array_operators[i + 1];
	}

	return (calculate_string_length(data->input_line));
}

