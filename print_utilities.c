#include "shell.h"

/**
 * print_string - writes an array of characters to standard output
 * @string: pointer to the array of characters
 * Return: the number of bytes written
 * On error, -1 is returned, and errno is set appropriately.
 */

int print_string(char *string)
{
	return (write(STDOUT_FILENO, string, calculate_string_length(string)));
}

/**
 * print_to_stderr - writes an array of characters to standard error
 * @string: pointer to the array of characters
 * Return: the number of bytes written
 * On error, -1 is returned, and errno is set appropriately.
 */

int print_to_stderr(char *string)
{
	return (write(STDERR_FILENO, string, calculate_string_length(string)));
}

/**
 * print_error_message - writes an array of characters to standard error
 * @error_code: error code to print
 * @data: a pointer to the program's data
 * Return: the number of bytes written
 * On error, -1 is returned, and errno is set appropriately.
 */

int print_error_message(int error_code, data_of_program *data)
{
	char exec_counter_str[10] = {'\0'};

	long_to_string((long)data->exec_counter, exec_counter_str, 10);
	if (error_code == 2 || error_code == 3)
	{
		print_to_stderr(data->program_name);
		print_to_stderr(": ");
		print_to_stderr(exec_counter_str);
		print_to_stderr(": ");
		print_to_stderr(data->tokens[0]);

		if (error_code == 2)
			print_to_stderr(": Illegal number: ");
		else
			print_to_stderr(": can't cd to ");
		print_to_stderr(data->tokens[1]);
		print_to_stderr("\n");
	}
	else if (error_code == 127)
	{
		print_to_stderr(data->program_name);
		print_to_stderr(": ");
		print_to_stderr(exec_counter_str);
		print_to_stderr(": ");
		print_to_stderr(data->command_name);
		print_to_stderr(": not found\n");
	}
	else if (error_code == 126)
	{
		print_to_stderr(data->program_name);
		print_to_stderr(": ");
		print_to_stderr(exec_counter_str);
		print_to_stderr(": ");
		print_to_stderr(data->command_name);
		print_to_stderr(": Permission denied\n");
	}
	return (0);
}
