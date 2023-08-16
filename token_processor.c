#include "shell.h"

/**
 * tokenize - Separates the input string into an array of tokens,
 * using a specified delimiter.
 * @data: Pointer to the program's data.
 * Return: Array of token strings.
 */
void tokenize(data_of_program *data)
{
	char *delimiter = " \t";
	int outer_index = 0, token_count = 2, length;
	int inner_index;

	length = calculate_string_length(data->input_line);
	if (length && data->input_line[length - 1] == '\n')
		data->input_line[length - 1] = '\0';
	for (; data->input_line[outer_index]; outer_index++)
	{
		for (inner_index = 0; delimiter[inner_index]; inner_index++)
		{
			if (data->input_line[outer_index] == delimiter[inner_index])
				token_count++;
		}
	}
	data->tokens = malloc(token_count * sizeof(char *));
	if (!data->tokens)
	{
		perror(data->program_name);
		exit(errno);
	}
	outer_index = 0;
	data->tokens[outer_index] = duplicate_string(custom_strtok
			(data->input_line, delimiter));
	data->command_name = duplicate_string(data->tokens[0]);
	while (data->tokens[outer_index++])
	{
		data->tokens[outer_index] = duplicate_string(custom_strtok(NULL, delimiter));
	}
}
