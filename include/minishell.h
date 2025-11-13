/**
 * @mainpage Minishell Documentation
 * 
 * @section intro_sec Introduction
 * Minishell is a lightweight UNIX shell implementation that provides core
 * shell functionality including command execution, piping, redirection,
 * environment variable management, and built-in commands.
 * 
 * @section features_sec Features
 * - Command parsing and tokenization
 * - Piping and I/O redirection (input, output, append, heredoc)
 * - Environment variable management
 * - Built-in commands (echo, cd, pwd, export, unset, env, exit)
 * - Signal handling (Ctrl-C, Ctrl-D, Ctrl-\\)
 * - Command execution with PATH resolution
 * 
 * @section architecture_sec Architecture
 * The project is organized into modular components:
 * - Parsing: Token extraction and command line parsing
 * - Execution: Command execution and built-in implementations
 * - Environment: Environment variable manipulation and storage
 * - Utils: Helper functions for string manipulation and validation
 * 
 * @section implementation_sec Implementation
 * The shell uses a linked list structure for environment variables and
 * dynamically allocates command structures for parsed input. It leverages
 * the readline library for interactive input and history management.
 * 
 * @section dependencies_sec Dependencies
 * - readline library (readline/readline.h, readline/history.h)
 * - POSIX system calls (unistd.h, sys/wait.h, sys/stat.h)
 * - Survival library (custom utility functions)
 * 
 * @section install_sec Installation
 * Build the project using the provided Makefile:
 * @code
 * make
 * @endcode
 * 
 * @section usage_sec Usage
 * Run the executable to start an interactive shell session:
 * @code
 * ./minishell
 * @endcode
 * 
 * @section links_sec Related Links
 * - GitHub Repository: https://github.com/Alelith/minishell
 * - Survival Library documentation: https://alelith.github.io/survival_lib-documentation/
 * 
 * @section contrib_sec Contributing
 * Contributions are welcome. Please ensure code follows the existing style,
 * includes appropriate Doxygen comments, and passes compilation without
 * warnings. Test all fractal types before submitting changes.
 *
 * @section license_sec License
 * This project is licensed under the GNU General Public License v3 (GPL3).
 * See LICENSE file for full terms. Any derivative work must be distributed
 * under the same GPL3 license with source code availability.
 */

/**
 * @file minishell.h
 * @brief Main header file for the Minishell project
 * 
 * @author Lilith Estévez Boeta y Begoña Varea Kuhn
 * @date 2025-08-21
 */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "survival_lib.h"
# include <unistd.h>
# include <fcntl.h>
# include <dirent.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/types.h>
# include <sys/stat.h>

typedef struct s_env	t_env;

/**
 * @enum e_redir
 * @brief File redirection types for command I/O
 * 
 * Defines the types of file redirections supported by the shell for
 * managing input and output streams of commands.
 */
typedef enum e_redir
{
	INPUT,     ///< Input redirection (<)
	OUTPUT,    ///< Output redirection with truncation (>)
	OVERWRITE  ///< Output redirection with append (>>)
}	t_redir;

/**
 * @struct s_command
 * @brief Represents a single parsed command with its arguments and I/O
 * 
 * Contains all information needed to execute a command including
 * arguments, file descriptors for redirection, heredoc delimiter,
 * and error status.
 */
typedef struct s_command
{
	int		args_c;       ///< Number of arguments
	char	**args;       ///< Array of argument strings
	int		infile;       ///< File descriptor for input redirection
	int		outfile;      ///< File descriptor for output redirection
	char	*heredoc_eof; ///< EOF delimiter for heredoc (<<)
	int		has_error;    ///< Error flag for command validation
}	t_command;

/**
 * @struct s_key_value
 * @brief Key-value pair structure for environment variables
 * 
 * Stores a single environment variable as a key-value pair.
 */
typedef struct s_key_value
{
	char	*key;   ///< Environment variable name
	char	*value; ///< Environment variable value
}	t_key_value;

/**
 * @struct s_env
 * @brief Linked list node for environment variables
 * 
 * Represents a node in the environment variable linked list,
 * containing a key-value pair and a pointer to the next node.
 */
struct s_env
{
	t_key_value	pair; ///< Key-value pair for this environment variable
	t_env		*next; ///< Pointer to next environment variable node
};

/**
 * @struct s_token
 * @brief Represents a parsed token from command line input
 * 
 * Stores a token extracted from the command line with information
 * about whether it should be treated as a literal string.
 */
typedef struct s_token
{
	bool	is_literal; ///< True if token is a quoted literal
	char	*token;     ///< Token string content
}	t_token;

/**
 * @struct s_shell
 * @brief Main shell state structure
 * 
 * Contains all global state for the shell including environment
 * variables, parsed commands, standard I/O descriptors, and
 * execution status information.
 */
typedef struct s_shell
{
	t_env			*env_list;     ///< Environment variables list
	t_env			*env_list_cpy; ///< Copy of environment for export
	t_command		*commands;     ///< Array of parsed commands
	unsigned short	cmd_length;    ///< Number of commands in pipeline
	int				std_out;       ///< Saved stdout descriptor
	int				std_in;        ///< Saved stdin descriptor
	char			*last_path;    ///< Last working directory path
	int				last_exitcod;  ///< Exit code of last command
}	t_shell;

/**
 * @defgroup parsing_module Parsing Module
 * @brief Command line parsing and tokenization functions
 * 
 * @details This module handles the parsing of user input into executable
 * commands. It performs tokenization, quote handling, variable expansion,
 * and command structure creation.
 * 
 * @section parsing_features_sec Features
 * - Token extraction with quote and escape handling
 * - Environment variable expansion
 * - Command and argument separation
 * - Pipe and redirection detection
 * 
 * @section parsing_usage_sec Usage
 * Start with tokenize() to parse a command line string into command
 * structures. Use split_command() for token-level parsing.
 */

/**
 * @ingroup parsing_module
 * @{
 */
t_token		*split_command(char *line, t_shell *shell);
char		*get_word(char *line, const char *delimiters, int *index,
				t_shell *shell);
char		*handle_word_join(char *line, int *index,
				t_shell *shell, int word_len);
t_command	*tokenize(char *input, unsigned short *len, t_shell shell);
void		free_commands(t_command *commands, unsigned short length);
t_command	*init_command(void);
t_token		*get_tokens(char *input, t_shell shell);
int			is_pipe_token(char *token);
int			is_redir_token(char *token);
void		proccess_command(char *token, t_command *cmd);
int			check_file(char *file, t_redir redir_type);
void		proccess_redir(t_token *tokens, int index, t_command *cmd);
int			check_command_line(char *line);
char		*get_token(char **line, const char *delimiters, char type,
				t_shell *shell);
void		switch_assign_tmp(char **line, char **tmp, t_shell *shell);
void		increment_args(t_token **args, int *argc, char *tmp, char type);
/** @} */

/**
 * @defgroup environment_module Environment Module
 * @brief Environment variable management functions
 * 
 * @details This module provides a complete interface for managing
 * environment variables using a linked list structure. It supports
 * operations for creation, modification, deletion, and querying of
 * environment variables.
 * 
 * @section env_features_sec Features
 * - Dynamic environment variable storage
 * - Key-value pair manipulation
 * - Environment list duplication
 * - Conversion to string array format
 * 
 * @section env_usage_sec Usage
 * Initialize with set_env() to create the environment list from the
 * system environment. Use search_env() to query values and update_env()
 * or add_env() to modify variables.
 */

/**
 * @ingroup environment_module
 * @{
 */
int			update_env(t_env *env_list, const char *key, const char *value);
t_env		*set_env(char **envp);
int			add_env(t_env **env_list, char *key, char *value);
char		*get_key(char *envp);
char		*get_value(char *envp);
void		free_env(t_env *env_list);
int			exists_env(char *key, t_env *env);
int			delete_env(t_env **env_list, char *key);
char		**env_to_string_list(t_env *env_list);
char		*search_env(t_env *envs, const char *key);
/** @} */

/**
 * @defgroup builtins_module Built-in Commands Module
 * @brief Built-in shell command implementations
 * 
 * @details This module implements the standard shell built-in commands
 * that are executed directly by the shell process rather than forking
 * external programs.
 * 
 * @section builtins_features_sec Features
 * - echo: Display text with optional newline suppression (-n)
 * - cd: Change working directory with HOME and OLDPWD support
 * - pwd: Print current working directory
 * - export: Set or display environment variables
 * - unset: Remove environment variables
 * - env: Display all environment variables
 * - exit: Exit shell with optional status code
 * 
 * @section builtins_usage_sec Usage
 * Each built-in receives a t_command structure with parsed arguments.
 * Return values indicate success (0) or error (non-zero).
 */

/**
 * @ingroup builtins_module
 * @{
 */
int			echo(t_command command);
int			exit_exec(t_shell shell, char *line);
int			pwd(t_command cmd);
int			cd(t_shell *shell, t_command command);
int			env(t_command cmd, t_env *env_list);
int			export(t_command cmd, t_env **env, t_env **env_cpy);
int			unset(t_command cmd, t_env **env_list, t_env **env_cpy);
int			is_builtin(char *cmd);
/** @} */

/**
 * @defgroup execution_module Execution Module
 * @brief Command execution and process management functions
 * 
 * @details This module handles the execution of both built-in and
 * external commands. It manages process forking, piping, signal
 * handling, and PATH resolution.
 * 
 * @section exec_features_sec Features
 * - External command execution via execve
 * - PATH environment variable resolution
 * - Process creation and management
 * - Signal handling (SIGINT, SIGQUIT)
 * - Command validation
 * 
 * @section exec_usage_sec Usage
 * Use execute() for external commands and try_command() as the main
 * entry point for command execution logic including built-in detection.
 */

/**
 * @ingroup execution_module
 * @{
 */
int			execute(t_command command, t_env *env_list);
char		*search_command(char *command, char *exec_paths);
void		set_signals_main(void);
void		set_signals_child(void);
void		switch_flag(int i);
int			try_command(t_shell *shell, char *line);
/** @} */

/**
 * @defgroup command_utils_module Command Utilities Module
 * @brief Helper functions for command execution and pipeline management
 * 
 * @details This module provides utility functions for managing command
 * execution flow, pipe creation, process forking, and resource cleanup
 * in pipeline scenarios.
 * 
 * @section cmdutil_features_sec Features
 * - Pipeline execution with multiple commands
 * - Pipe file descriptor management
 * - Built-in and fork execution routing
 * - Process ID tracking and cleanup
 * 
 * @section cmdutil_usage_sec Usage
 * These functions are primarily used by the main execution logic to
 * handle complex command pipelines and resource management.
 */

/**
 * @ingroup command_utils_module
 * @{
 */
int			switch_commands(t_shell *shell, int index, char *line);
void		close_and_free_pipes(int **pipes, t_shell shell);
int			*close_and_free(t_shell shell, int **pipes, int *pids);
void		free_and_exit(t_shell *shell, char *line, int err);
void		execute_fork(t_shell *shell, int i, int **pipes, char *line);
void		execute_builtin(t_shell *shell, int i, int *err, char *line);
void		finish_execute(int i, t_shell *shell, int **pipes, int *pids);
int			is_builtin_candidate(t_shell *shell, int i);
int			fork_and_execute(t_shell *shell, int **pipes,
				char *line, int *pids);
/** @} */

/**
 * @defgroup output_module Output Module
 * @brief Output formatting and display functions
 * 
 * @details This module handles formatted output for the shell including
 * banners, error messages, and special display formatting for commands
 * like export.
 * 
 * @section output_features_sec Features
 * - ASCII banner display
 * - Sorted environment variable display
 * - Error message formatting
 * - Export command output formatting
 * 
 * @section output_usage_sec Usage
 * These functions are called by built-ins and the main shell loop to
 * provide formatted output to the user.
 */

/**
 * @ingroup output_module
 * @{
 */
void		print_open_banner(void);
void		print_close_banner(void);
int			print_comm_err(const char *message, const char *comm);
void		print_export(const char *key, const char *value);
int			print_sorted_env(t_env *env);
/** @} */

/**
 * @defgroup utils_module Utility Functions Module
 * @brief General utility functions for validation and manipulation
 * 
 * @details This module provides miscellaneous utility functions used
 * throughout the shell for validation, string manipulation, and
 * special input handling.
 * 
 * @section utils_features_sec Features
 * - Command type identification (built-in, redirection)
 * - Error checking across command arrays
 * - Heredoc input handling
 * - Path manipulation
 * - String splitting utilities
 * 
 * @section utils_usage_sec Usage
 * These functions are called by various modules to perform common
 * operations and validations.
 */

/**
 * @ingroup utils_module
 * @{
 */
int			is_redirection(char c);
int			any_has_error(t_command *cmd, unsigned short cmd_count);
void		handle_heredoc(t_command *cmd);
char		*get_last_path(char *this_path);
int			count_until(char *line, const char *delimiters);
int			count_while(char *line, const char *delimiters, int max);
char		*get_value_from_env(char **line, t_shell *shell);
void		free_and_assign(char **res, char *tmp);
void		process_result(char **line, char **res, t_shell *shell, char type);
void		process_redir_pipe(char *set, char **tmp, char **line, int max);
void		increment_if_quote(char **line);
/** @} */

#endif
