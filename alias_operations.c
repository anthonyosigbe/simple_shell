#include "shell.h"

/**
 * display_aliases - Display, add, or remove aliases.
 * @data: Pointer to the program's data structure.
 * @alias: Name of the alias to be displayed.
 *
 * Return: Zero on success, or a non-zero number if declared in arguments.
 */
int display_aliases(data_of_program *data, char *alias)
{
	int index, j, alias_length;
	char buffer[250] = {'\0'};

	if (data->alias_list)
	{
		alias_length = calculate_string_length(alias);
		for (index = 0; data->alias_list[index]; index++)
		{
			if (!alias || (compare_strings(data->alias_list[index], lias, alias_length)
						&& data->alias_list[index][alias_length] == '='))
			{
				for (j = 0; data->alias_list[index][j]; j++)
				{
					buffer[j] = data->alias_list[index][j];
					if (data->alias_list[index][j] == '=')
						break;
				}
				buffer[j + 1] = '\0';
				buffer_add(buffer, "'");
				buffer_add(buffer, data->alias_list[index] + j + 1);
				buffer_add(buffer, "'\n");
				print_string(buffer);
			}
		}
	}
	return (0);
}
