#ifndef SHELL_HEADER
#define SHELL_HEADER

#include <stdio.h> /* Required for printf */
#include <unistd.h> /* Required for fork, execve */
#include <stdlib.h>
#include <string.h> /* Required for strtok */
#include <stddef.h>
#include <errno.h> /* Required for errno and perror */
#include <sys/types.h> /* Required for type pid */
#include <sys/wait.h> /* Required for wait */
#include <sys/stat.h> /* Required for use of stat function */
#include <signal.h> /* Required for signal management */
#include <fcntl.h> /* Required for open files */

/* CONSTANTS-UTILITIES */

#include "utilities.h" /* Required for message, help, and prompt constants */

/*** DATA CONTAINERS FOR STRUCTURES ***/

/**
 * struct info - Stores program information
 * @program_name:  Executable's name
 * @input_line: Pointer to input obtained using readline.c
 * @command_name: Pointer to the initial user-entered command
 * @exec_counter: Count of executed commands
 * @file_descriptor: Command input file descriptor
 * @tokens: Pointer to an array of tokenized input
 * @env: Replication of environment variables
 * @alias_list: Array of pointers containing aliases
 */

typedef struct info
{
	char *program_name;
	char *input_line;
	char *command_name;
	int exec_counter;
	int file_descriptor;
	char **tokens;
	char **env;
	char **alias_list;
} data_of_program;

/**
 * struct builtins - Holds built-in commands
 * @builtin: Name of the built-in
 * @function: Associated function for each built-in
 */
typedef struct builtins
{
	char *builtin;
	int (*function)(data_of_program *data);
} builtins;

/*** PRIMARY FUNCTIONS ***/
/* Initialize the program data struct */
void initialize_data(data_of_program *data,
	int argc, char *argv[], char **env);

/* command_executor.c */

/* Execute a command with its full path */
int execute_command(data_of_program *data);

/*** OUTPUT DISPLAY UTILITIES ***/

/* print_utilities.c */

/* Print a string to standard output */
int print_string(char *string);

/* Print a string to standard error */
int print_to_stderr(char *string);

/* Print an error message to standard error */
int print_error_message(int error_code, data_of_program *data);

#endif
