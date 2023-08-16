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
	buffer_add(line, data->input_line);
	for (i = 0; line[i]; i++)
	{
		if (line[i] == '#')
			line[i--] = '\0';
		else if (line[i] == '$' && line[i + 1] == '?')
		{
			line[i] = '\0';
			convert_long_to_string(errno, expansion, 10);
			buffer_add(line, expansion);
			buffer_add(line, data->input_line + i + 2);
		}
		else if (line[i] == '$' && line[i + 1] == '$')
		{
			line[i] = '\0';
			convert_long_to_string(getpid(), expansion, 10);
			buffer_add(line, expansion);
			buffer_add(line, data->input_line + i + 2);
		}
		else if (line[i] == '$' && (line[i + 1] == ' ' || line[i + 1] == '\0'))
			continue;
		else if (line[i] == '$')
		{
			for (j = 1; line[i + j] && line[i + j] != ' '; j++)
				expansion[j - 1] = line[i + j];
			temp = get_environment_key(expansion, data);
			line[i] = '\0', expansion[0] = '\0';
			buffer_add(expansion, line + i + j);
			if (temp)
				buffer_add(line, temp);
			else
				buffer_add(line, "1");
			buffer_add(line, expansion);
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
	buffer_add(line, data->input_line);
	for (i = 0; line[i]; i++)
	{
		for (j = 0; line[i + j] && line[i + j] != ' '; j++)
			expansion[j] = line[i + j];
		expansion[j] = '\0';
		temp = get_alias_name(data, expansion);
		if (temp)
		{
			expansion[0] = '\0';
			buffer_add(expansion, line + i + j);
			line[i] = '\0';
			buffer_add(line, temp);
			line[calculate_string_length(line)] = '\0';
			buffer_add(line, expansion);
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
 * buffer_add - Append a string at the end of the buffer.
 * @buffer: Buffer to be filled.
 * @str_to_add: String to be copied into the buffer.
 *
 * Return: The length of the updated buffer.
 */
int buffer_add(char *buffer, char *str_to_add)
{
	int length, index;

	length = calculate_string_length(buffer);
	for (i = 0; str_to_add[i]; i++)
	{
		buffer[length + i] = str_to_add[i];
	}
	buffer[length + i] = '\0';
	return (length + i);
}
