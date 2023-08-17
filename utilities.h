#ifndef UTILITIES_HEADER
#define UTILITIES_HEADER

/* Message displayed as the shell prompt */
#define PROMPT_MSG " $ " /* Necessary for signal compatibility */

/* Macro for marking unused variables with an attribute */
#define UNUSED __attribute__((unused))

/* Size of the buffer for each read operation in _getline */
#define BUFFER_SIZE 1024

/* FORMATTED HELP MESSAGES */

#define HELP_CD_MSG "cd=\n"\
"cd:\tcd [dir]\n\n"\
"	Modify the active directory of the shell.\n\n"\
"	If the `cd` command is used without any arguments,\n"\
"	it will be understood in a certain way.\n"\
"	Similar to executing `cd $HOME`.\n"\
"	When the argument is set as ' - ', the command 'cd -'\n"\
"	will be understood in that context.\n"\
"       Like executing `cd $OLDPWD.`\n\n"


#define HELP_EXIT_MSG "exit=\n"\
"exit:\texit [STATUS]\n\n"\
"	Termination of the basic shell.\n\n"\
"	The shell is exited with a status of N.\n"\
"	If N is not provided, the exit status is used.\n"\
"	is that of the last command executed.\n\n"

#define HELP_ENV_MSG "env=\n"\
"env:\tenv\n\n"\
"	Display the environment variables.\n\n"\
"	The `env` command shows a comprehensive list of environment variables.\n\n"

#define HELP_SETENV_MSG "setenv=\n"\
"setenv:\tsetenv VARIABLE VALUE\n\n"\
"	Edit or append an environment variable.\n\n"\
"	Create a new environment variable or alter an existing one.\n"\
"	Display an error message when an incorrect number of arguments is provided.\n\n"

#define HELP_UNSETENV_MSG "unsetenv=\n"\
"unsetenv:\tunsetenv VARIABLE\n\n"\
"	The `unsetenv` function removes a single variable from the environment.\n\n"\
"	Display an error message when an incorrect number of arguments is provided.\n\n"

#define HELP_MSG "help=\n"\
"help:\thelp [BUILTIN_NAME]\n\n"\
"	Show details about built-in commands.\n\n"\
"	Provides concise overviews of built-in commands.\n"\
"	If `BUILTIN_NAME` is specified,\n"\
"	if `BUILTIN_NAME` is provided, it offers comprehensive assistance,\n"\
"	for all commands that match the specified `BUILTIN_NAME`\n"\
"	otherwise, it prints the list of help topics related to,\n"\
"	built-in commands.\n"\
"	Input parameters:\n\n"\
"	`BUILTIN_NAME` indicating a help topic.\n\n"\
"	cd\t[dir]\n"\
"	exit\t[status]\n"\
"	env\n"\
"	setenv\t[variable value]\n"\
"	unset\t[variable]\n"\
"	help\t[built_name]\n\n"

#endif
