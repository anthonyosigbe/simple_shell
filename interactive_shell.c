#include "shell.h"

/**
 * main - Initializes program variables.
 * @argc: Number of command line values.
 * @argv: Command line values.
 * @env: Environment variables.
 * Return: Zero on success.
 */
int main(int argc, char *argv[], char *env[])
{
	data_of_program data_struct = {NULL}, *data = &data_struct;
	char *prompt = "";

	initialize_data(data, argc, argv, env);

	signal(SIGINT, handle_ctrl_c);

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
	{
		/* Running in the terminal, interactive mode */
		errno = 2;
		prompt = PROMPT_MSG;
	}
	errno = 0;
	run_shell_loop(prompt, data);
	return (0);
}
/**
 * handle_ctrl_c - Handles SIGINT signal (ctrl + c).
 * @opr: Unused option.
 */
void handle_ctrl_c(int opr __attribute__((unused)))
{
	print_string("\n");
	print_string(PROMPT_MSG);
}

/**
 * initialize_data - Initializes program data structure.
 * @data: Pointer to data structure.
 * @argv: Array of program arguments.
 * using if and else statement
 * @env: Environment variables.
 * @argc: Number of command line values.
 */
void initialize_data(data_of_program *data, int argc, char *argv[], char **env)
{
	int i = 0;

	data->program_name = argv[0];
	data->input_line = NULL;
	data->command_name = NULL;
	data->exec_counter = 0;

	if (argc == 1)
		data->file_descriptor = STDIN_FILENO;
	else
	{
		data->file_descriptor = open(argv[1], O_RDONLY);
		if (data->file_descriptor == -1)
		{
			print_to_stderr(data->program_name);
			print_to_stderr(": 0: Can't open ");
			print_to_stderr(argv[1]);
			print_to_stderr("\n");
			exit(127);
		}
	}
	data->tokens = NULL;
	data->env = malloc(sizeof(char *) * 50);
	if (env)
	{
		for (i = 0; env[i]; i++)
		{
			data->env[i] = duplicate_string(env[i]);
		}
	}
	data->env[i] = NULL;
	env = data->env;

	data->alias_list = malloc(sizeof(char *) * 20);
	for (i = 0; i < 20; i++)
	{
		data->alias_list[i] = NULL;
	}
}
/**
 * run_shell_loop - Infinite loop for running the shell.
 * @prompt: Prompt to be printed.
 * using if and while loop
 * @data: Pointer to program data.
 */
void run_shell_loop(char *prompt, data_of_program *data)
{
	int error_code = 0, string_len = 0;

	while (++(data->exec_counter))
	{
		print_string(prompt);
		error_code = string_len = read_line(data);

		if (error_code == EOF)
		{
			free_all_data(data);
			exit(errno);
		}
		if (string_len >= 1)
		{
			expand_alias(data);
			expand_variables(data);
			tokenize(data);
			if (data->tokens[0])
			{
				error_code = execute_command(data);
				if (error_code != 0)
					print_error_message(error_code, data);
			}
			free_recurring_data(data);
		}
	}
}

