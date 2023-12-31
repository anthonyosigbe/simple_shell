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
	data->tokens[0] = concatenate_strings(duplicate_string("/"),
	data->command_name);
	if (!data->tokens[0])
		return (2);

	directories = generate_path_tokens(data); /* Search in the PATH */

	if (!directories || !directories[0])
	{
		errno = 127;
		return (127);
	}

	for (index = 0; directories[index]; index++)
	{ /* Append the command_name to each directory in the PATH */
		directories[index] = concatenate_strings(directories[index],
				data->tokens[0]);
		ret_code = validate_file(directories[index]);
		if (ret_code == 0 || ret_code == 126)
		{
			errno = 0;
			free(data->tokens[0]);
			data->tokens[0] = duplicate_string(directories[index]);
			free_directory_array(directories);
			return (ret_code);
		}
	}

	free(data->tokens[0]);
	data->tokens[0] = NULL;
	free_directory_array(directories);
	return (ret_code);
}
/**
 * generate_path_tokens - Tokenize the PATH environment variable
 * into directories.
 *
 * @data: Pointer to the program's data structure.
 *
 * This function splits the PATH environment variable into individual
 * directory paths and returns them as an array.
 *
 * Return: An array of directory paths or NULL if PATH is not set.
 */
char **generate_path_tokens(data_of_program *data)
{
	int index = 0;
	int counter_directories = 2;
	char **tokens = NULL;
	char *PATH;

	/* Get the value of the PATH environment variable */
	PATH = get_environment_key("PATH", data);
	if ((PATH == NULL) || PATH[0] == '\0')
	{
		return (NULL);
	}

	PATH = duplicate_string(PATH);

	/* Count the number of directories in the PATH */
	for (index = 0; PATH[index]; index++)
	{
		if (PATH[index] == ':')
			counter_directories++;
	}

	/* Reserve space for the array of pointers */
	tokens = malloc(sizeof(char *) * counter_directories);

	/* Tokenize and duplicate each directory path */
	index = 0;
	tokens[index] = duplicate_string(custom_strtok(PATH, ":"));
	while (tokens[index++])
	{
		tokens[index] = duplicate_string(custom_strtok(NULL, ":"));
	}

	free(PATH);
	PATH = NULL;
	return (tokens);
}

/**
 * validate_file - Validate if a file exists, is not a directory, and has
 * execution permissions.
 *
 * @full_path: Pointer to the full file name.
 *
 * This function checks whether the specified file exists, is not a directory,
 * and has execution permissions.
 *
 * Return: 0 on success, or an error code if the file doesn't meet criteria.
 */
int validate_file(char *full_path)
{
	struct stat sb;

	if (stat(full_path, &sb) != -1)
	{
		if (S_ISDIR(sb.st_mode) || access(full_path, X_OK))
		{
			errno = 126;
			return (126);
		}
		return (0);
	}
	/* If the file doesn't exist */
	errno = 127;
	return (127);
}
