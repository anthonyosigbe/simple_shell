#include "shell.h"

/**
 * exit_builtin - Terminate the program with the specified status.
 * @data: Pointer to the program's data structure.
 *
 * Return: Zero on success, or a specific number if specified in arguments.
 */
int exit_builtin(data_of_program *data)
{
	int index;

	if (data->tokens[1] != NULL)
	{
	/* If an argument for exit exists, check if it's a numeric value */
	for (index = 0; data->tokens[1][index]; index++)
	{
	if ((data->tokens[1][index] < '0' || data->tokens[1][index] > '9')
		&& data->tokens[1][index] != '+')
	{
		errno = 2;
	return (2);
	}
	}
	errno = convert_to_integer(data->tokens[1]);
	}
	free_all_data(data);
	exit(errno);
}
/**
 * change_directory - Change the current working directory.
 * @data: Pointer to the program's data structure.
 *
 * Return: Zero on success, or a specific number if specified in arguments.
 */
int change_directory(data_of_program *data)
{
	char *dir_home = get_environment_key("HOME", data), *dir_old = NULL;
	char old_dir[128] = {0};
	int error_code = 0;

	if (data->tokens[1])
	{
		if (compare_strings(data->tokens[1], "-", 0))
		{
			dir_old = get_environment_key("OLDPWD", data);
			if (dir_old)
				error_code = set_working_directory(data, dir_old);
			print_string(get_environment_key("PWD", data));
			print_string("\n");

			return (error_code);
		}
		else
		{
			return (set_working_directory(data, data->tokens[1]));
		}
	}
	else
	{
		if (!dir_home)
			dir_home = getcwd(old_dir, 128);

		return (set_working_directory(data, dir_home));
	}
	return (0);
}
/**
 * set_working_directory - Set the working directory.
 * @data: Pointer to the program's data structure.
 * @new_directory: Path to be set as the working directory.
 *
 * Return: Zero on success, or a specific number if specified in arguments.
 */
int set_working_directory(data_of_program *data, char *new_directory)
{
	char old_dir[128] = {0};
	int err_code = 0;

	getcwd(old_dir, 128);

	if (!compare_strings(old_dir, new_directory, 0))
	{
		err_code = chdir(new_directory);
		if (err_code == -1)
		{
			errno = 2;
			return (3);
		}
		set_environment_key("PWD", new_directory, data);
	}
	set_environment_key("OLDPWD", old_dir, data);
	return (0);
}

/**
 * help_builtin - Display help information about shell commands.
 * @data: Pointer to the program's data structure.
 *
 * Return: Zero on success, or a specific number if specified in arguments.
 */
int help_builtin(data_of_program *data)
{
	int index, length = 0;
	char *messages[6] = {NULL};

	messages[0] = HELP_MESSAGE;

	/* Validate arguments */
	if (data->tokens[1] == NULL)
	{
		print_string(messages[0] + 6);
		return (1);
	}
	if (data->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}
	messages[1] = HELP_EXIT_MESSAGE;
	messages[2] = HELP_ENV_MESSAGE;
	messages[3] = HELP_SETENV_MESSAGE;
	messages[4] = HELP_UNSETENV_MESSAGE;
	messages[5] = HELP_CD_MESSAGE;

	for (index = 0; messages[index]; index++)
	{
		/* Print the length of the string */
		length = calculate_string_length(data->tokens[1]);
		if (compare_strings(data->tokens[1], messages[index], length))
		{
			print_string(messages[index] + length + 1);
			return (1);
		}
	}
	/* If no match found, print error and return 0 */
	errno = EINVAL;
	perror(data->command_name);
	return (0);
}
/**
 * alias_builtin - Add, remove, or show aliases.
 * @data: Pointer to the program's data structure.
 *
 * Return: Zero on success, or a specific number if specified in arguments.
 */
int alias_builtin(data_of_program *data)
{
	int index = 0;

	/* If there are no arguments, display all aliases */
	if (data->tokens[1] == NULL)
		return (display_aliases(data, NULL));

	while (data->tokens[++index])
	{
		/* If there are arguments, set or print each alias */
		if (count_char_occurrences(data->tokens[index], "="))
			set_alias_name(data->tokens[index], data);
		else
			display_aliases(data, data->tokens[index]);
	}

	return (0);
}

