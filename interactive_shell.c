#include "shell.h"

/**
 * main - Initializes program variables.
 * @argc: Number of command line values.
 * @argv: Command line values.
 * @env: Environment variables.
 * using if statement
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

