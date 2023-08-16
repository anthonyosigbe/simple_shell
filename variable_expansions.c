#include "shell.h"

/**
 * expand_variables - Expand variables within the input line.
 * @data: Pointer to the program's data structure.
 *
 * Description: This function modifies the input line by expanding variables,
 * such as $? and $$, into their corresponding values.
 */

void expand_variables(data_of_program *data)
{
	int index, j;
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

	if (data->input_line == NULL)
		return;
	add_to_buffer(line, data->input_line);
	for (index = 0; line[index]; index++)
	{
		if (line[index] == '#')
			line[index--] = '\0';
		else if (line[index] == '$' && line[index + 1] == '?')
		{
			line[index] = '\0';
			convert_long_to_string(errno, expansion, 10);
			add_to_buffer(line, expansion);
			add_to_buffer(line, data->input_line + index + 2);
		}
		else if (line[index] == '$' && line[index + 1] == '$')
		{
			line[index] = '\0';
			convert_long_to_string(getpid(), expansion, 10);
			add_to_buffer(line, expansion);
			add_to_buffer(line, data->input_line + index + 2);
		}
		else if (line[index] == '$' && (line[index + 1] == ' ' ||
					line[index + 1] == '\0'))
			continue;
		else if (line[index] == '$')
		{
			for (j = 1; line[index + j] && line[index + j] != ' '; j++)
				expansion[j - 1] = line[index + j];
			temp = get_environment_key(expansion, data);
			line[index] = '\0', expansion[0] = '\0';
			add_to_buffer(expansion, line + index + j);
			if (temp)
				add_to_buffer(line, temp);
			else
				add_to_buffer(line, "1");
			add_to_buffer(line, expansion);
		}
	}
	if (!compare_strings(data->input_line, line, 0))
	{
		free(data->input_line);
		data->input_line = duplicate_string(line);
	}
}

/**
 * expand_alias - Expand aliases within the input line.
 * @data: Pointer to the program's data structure.
 *
 * This function expands aliases present in the input line
 * to their corresponding values.
 */
void expand_alias(data_of_program *data)
{
	int index, j, wasEnlarged = 0;
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

	if (data->input_line == NULL)
		return;
	add_to_buffer(line, data->input_line);
	for (index = 0; line[index]; index++)
	{
		for (j = 0; line[index + j] && line[index + j] != ' '; j++)
			expansion[j] = line[index + j];
		expansion[j] = '\0';
		temp = get_alias_name(data, expansion);
		if (temp)
		{
			expansion[0] = '\0';
			add_to_buffer(expansion, line + index + j);
			line[index] = '\0';
			add_to_buffer(line, temp);
			line[calculate_string_length(line)] = '\0';
			add_to_buffer(line, expansion);
			wasEnlarged = 1;
		}
		break;
	}
	if (wasEnlarged)
	{
		free(data->input_line);
		data->input_line = duplicate_string(line);
	}
}

/**
 * add_to_buffer - Append a string at the end of the buffer.
 * @buffer: Buffer to be filled.
 * @str_to_add: String to be copied into the buffer.
 *
 * Return: The length of the updated buffer.
 */

int add_to_buffer(char *buffer, char *str_to_add)
{
	int length, index;

	length = calculate_string_length(buffer);
	for (index = 0; str_to_add[index]; index++)
	{
		buffer[length + index] = str_to_add[index];
	}
	buffer[length + index] = '\0';
	return (length + index);
}
