#include "shell.h"

/**
 * execute_command - Execute a command along with its full path variables.
 * @data: Pointer to the program's data structure.
 * Return: 0 on success, -1 on failure.
 */
int execute_command(data_of_program *data)
{
	int outcome = 0, status;
	pid_t pid;

	outcome = execute_builtin_list(data);
	if (outcome != -1)
	{
		return (outcome);
	}
	outcome = find_in_path(data);
	if (outcome)
	{
		return (outcome);
	}
	else
	{
			pid = fork();
		if (pid == -1)
		{
			perror(data->command_name);
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			outcome = execve(data->tokens[0], data->tokens, data->env);
			if (outcome == -1)
			{
				perror(data->command_name), exit(EXIT_FAILURE);
			}
		}
		else
		{
			wait(&status);
			if (WIFEXITED(status))
			{
				errno = WEXITSTATUS(status);
			}
			else if (WIFSIGNALED(status))
			{
				errno = 128 + WTERMSIG(status);
			}
		}
	}
	return (0);
}
