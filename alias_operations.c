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

/**
 * get_alias_name - Retrieve the value of an alias.
 * @data: Pointer to the program's data structure.
 * @alias: Name of the requested alias.
 *
 * Return: Pointer to the alias value, or NULL if not found.
 */
char *get_alias_name(data_of_program *data, char *alias)
{
	int index, alias_length;

	/* Validate the arguments */
	if (alias == NULL || data->alias_list == NULL)
		return (NULL);

	alias_length = calculate_string_length(alias);
	for (index = 0; data->alias_list[index]; index++)
	{
		/* Iterate through the alias list and check for matching alias names */
		if (compare_strings(alias, data->alias_list[index], alias_length) &&
				data->alias_list[index][alias_length] == '=')
		{
			/* Return the value of the alias */
			return (data->alias_list[index] + alias_length + 1);
		}
	}
	/* Return NULL if alias not found */
	return (NULL);
}
