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
			if (!alias || (compare_strings(data->alias_list[index], alias, alias_length)
						&& data->alias_list[index][alias_length] == '='))
			{
				for (j = 0; data->alias_list[index][j]; j++)
				{
					buffer[j] = data->alias_list[index][j];
					if (data->alias_list[index][j] == '=')
						break;
				}
				buffer[j + 1] = '\0';
				add_to_buffer(buffer, "'");
				add_to_buffer(buffer, data->alias_list[index] + j + 1);
				add_to_buffer(buffer, "'\n");
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

/**
 * set_alias_name - Add or override an alias.
 * @alias_string: Alias to be set in the format (name='value').
 * @data: Pointer to the program's data structure.
 *
 * Return: Zero on success, or a non-zero number if declared in arguments.
 */
int set_alias_name(char *alias_string, data_of_program *data)
{
	int index, j;
	char buffer[250] = {'\0'}, *temp = NULL;

	/* Validate the arguments */
	if (alias_string == NULL || data->alias_list == NULL)
		return (1);
	for (index = 0; alias_string[index]; index++)
	{
		if (alias_string[index] != '=')
			buffer[index] = alias_string[index];
		else
		{
			/* Search if the value of the alias is another alias */
			temp = get_alias_name(data, alias_string + index + 1);
			break;
		}
	}
	for (j = 0; data->alias_list[j]; j++)
	{
		if (compare_strings(buffer, data->alias_list[j], index) &&
				data->alias_list[j][index] == '=')
		{
			free(data->alias_list[j]);
			break;
		}
	}
	/* Add the alias */
	if (temp)
	{
		/* If the alias already exists, append the value */
		add_to_buffer(buffer, "=");
		add_to_buffer(buffer, temp);
		data->alias_list[j] = duplicate_string(buffer);
	}
	else
	{
		/* If the alias does not exist, create it */
		data->alias_list[j] = duplicate_string(alias_string);
	}
	return (0);
}
