#include "shell.h"

int validate_file(char *full_path);

/**
 * find_in_path - Search for a program within the PATH directories.
 * @data: Pointer to the program's data structure.
 *
 * This function searches for the specified program in the directories
 * listed in the PATH environment variable.
 * using if and for loop
 * Return: 0 if the program is found, an error code otherwise.
 */
int find_in_path(data_of_program *data)
{
	int index = 0, ret_code = 0;
	char **directories;

	if (!data->command_name)
		return (2);

	/** If the command_name is a full_path or an executable in the same path */
	if (data->command_name[0] == '/' || data->command_name[0] == '.')
		return (validate_file(data->command_name));

	free(data->tokens[0]);
	data->tokens[0] = str_concat(str_duplicate("/"), data->command_name);
	if (!data->tokens[0])
		return (2);

	directories = generate_path_tokens(data); /* Search in the PATH */

	if (!directories || !directories[0])
	{
		errno = 127;
		return (127);
	}

	for (i = 0; directories[i]; i++)
	{ /* Append the command_name to each directory in the PATH */
		directories[i] = str_concat(directories[i], data->tokens[0]);
		ret_code = validate_file(directories[i]);
		if (ret_code == 0 || ret_code == 126)
		{
			errno = 0;
			free(data->tokens[0]);
			data->tokens[0] = str_duplicate(directories[i]);
			free_array_of_pointers(directories);
			return (ret_code);
		}
	}

	free(data->tokens[0]);
	data->tokens[0] = NULL;
	free_array_of_pointers(directories);
	return (ret_code);
}

