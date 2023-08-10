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

/* DATA CONTAINERS FOR STRUCTURES */

/**
 * struct info - Holds program data
 * @program_name: Name of the executable
 * @input_line: Pointer to input read using _getline
 * @command_name: Pointer to the first user-typed command
 * @exec_counter: Number of executed commands
 * @file_descriptor: File descriptor for command input
 * @tokens: Pointer to array of tokenized input
 * @env: Copy of the environment variables
 * @alias_list: Array of pointers with aliases
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
#endif 
