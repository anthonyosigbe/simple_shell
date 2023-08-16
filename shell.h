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

/** interactive_shell.c **/

/* Initialize the program data struct */
void initialize_data(data_of_program *data,
	int argc, char *argv[], char **env);

/* Print the prompt on a new line */
void handle_ctrl_c(int opr __attribute__((unused)));

/* Creates an infinite loop displaying the prompt */
void run_shell_loop(char *prompt, data_of_program *data);

/** command_executor.c **/

/* Execute a command with its full path */
int execute_command(data_of_program *data);

/** list_operations.c **/

/* Execute built-in commands if matched */
int execute_builtin_list(data_of_program *data);

/*** variable_expansions.c ***/

/* Expand variables */
void expand_variables(data_of_program *data);

/* Expand aliases */
void expand_alias(data_of_program *data);

/* Append a string to the end of the buffer */
int add_to_buffer(char *buffer, char *string_to_add);


/*** OUTPUT DISPLAY UTILITIES ***/

/* print_utilities.c */

/* Print a string to standard output */
int print_string(char *string);

/* Print a string to standard error */
int print_to_stderr(char *string);

/* Print an error message to standard error */
int print_error_message(int error_code, data_of_program *data);


/*** ENVIRONMENT VARIABLE CONFIGURATION ***/

/** env_control.c **/

/* Print the current environment */
void print_environment(data_of_program *data);

/* Retrieve the value of an environment variable */
char *get_environment_key(char *name, data_of_program *data);

/* Update the value of an environment variable */
int set_environment_key(char *key, char *value, data_of_program *data);

/* Remove a key from the environment */
int remove_environment_key(char *key, data_of_program *data);

/* operations_env.c */

/* Display the shell's environment */
int environment_builtin(data_of_program *data);

/* Create or update an environment variable */
int set_environment(data_of_program *data);

/* Delete an environment variable */
int unset_environment(data_of_program *data);

/*** INTRINSIC FUNCTIONS ***/

/* operations_env.c */

/* Display the shell's environment */
int display_environment(data_of_program *data);

/* Create or update an environment variable */
int set_environment(data_of_program *data);

/* Delete an environment variable */
int unset_environment(data_of_program *data);

/*** additional_functions.c ***/

/* Terminate the shell */
int exit_builtin(data_of_program *data);

/* Change the current directory */
int change_directory(data_of_program *data);

/* Set the working directory */
int set_working_directory(data_of_program *data, char *new_directory);

/* Display help information */
int help_builtin(data_of_program *data);

/* Set, unset, and show aliases */
int alias_builtin(data_of_program *data);

/* readline.c */

/* Read a line from standard input */
int read_line(data_of_program *data);

/* Split lines using logical operators if present */
int separate_logical_ops(char *command_array[], int i, char operator_array[]);

/* path_search.c */

/* Search for a program in the PATH */
int find_in_path(data_of_program *data);

/* Generate an array of path directories */
char **generate_path_tokens(data_of_program *data);

/*** STRING MANIPULATION TOOLS ***/

/* alias_operations.c */

/* Print the list of aliases */
int display_aliases(data_of_program *data, char *alias);

/* Retrieve an alias name */
char *get_alias_name(data_of_program *data, char *alias);

/* Set an alias name */
int set_alias_name(char *alias_string, data_of_program *data);

/*** AUXILIARY MEMORY MANAGEMENT ***/

/* memory_cleanup.c */

/* Free fields required for each loop */
void free_recurring_data(data_of_program *data);

/* Free all data fields */
void free_all_data(data_of_program *data);

/* Free memory allocated for directories */
void free_directory_array(char **directories);

/* string_utilities.c */

/* Calculate the length of a string */
int calculate_string_length(char *string);

/* Duplicate a string */
char *duplicate_string(char *string);

/* Compare two strings */
int compare_strings(char *string1, char *string2, int length);

/* Concatenate two strings */
char *concatenate_strings(char *string1, char *string2);

/* Reverse a string */
void reverse_string(char *string);

/* numeric_operations.c */

/* Convert from integer to string */
void convert_long_to_string(long number, char *string, int base);
#endif
