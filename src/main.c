/**
 * @file main.c
 * @brief Main entry point and shell initialization for minishell
 * 
 * @author Lilith Estévez Boeta y Begoña Varea Kuhn
 * @date 2025-08-20
 */

#include "minishell.h"

/**
 * @brief Frees all shell resources and exits the program
 * 
 * @details Deallocates the environment variable lists and terminates
 * the shell with exit code 0.
 * 
 * @ingroup execution_module
 * 
 * @param[in,out] shell Pointer to shell state structure
 */
static void	free_t_shell(t_shell *shell)
{
	if (shell->env_list)
		free_env(shell->env_list);
	if (shell->env_list_cpy)
		free_env(shell->env_list_cpy);
	exit(0);
}

/**
 * @brief Initializes the shell state and environment
 * 
 * @details Sets up the shell structure by loading environment variables,
 * duplicating file descriptors for stdin/stdout, displaying the welcome
 * banner, and initializing the working directory path.
 * 
 * @ingroup execution_module
 * 
 * @param[out] shell Pointer to shell structure to initialize
 * @param[in] envp Environment variables array from main
 */
static void	initialize_shell(t_shell *shell, char **envp)
{
	char	*cwd;

	shell->env_list = set_env(envp);
	shell->env_list_cpy = set_env(envp);
	shell->std_in = dup(STDIN_FILENO);
	shell->std_out = dup(STDOUT_FILENO);
	print_open_banner();
	shell->cmd_length = 0;
	shell->last_exitcod = 0;
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		shell->last_path = str_duplicate(cwd);
		free(cwd);
	}
	else
		shell->last_path = NULL;
	set_signals_main();
}

/**
 * @brief Main entry point for the minishell program
 * 
 * @details Initializes the shell, enters the main read-eval-print loop,
 * reads commands from the user via readline, validates and executes them,
 * and handles exit conditions. The loop continues until EOF (Ctrl-D) is
 * received.
 * 
 * @ingroup execution_module
 * 
 * @param[in] argc Argument count (must be 1, no arguments accepted)
 * @param[in] argv Argument vector (not used)
 * @param[in] envp Environment variables array
 * @return Exit status code (0 on success, error code otherwise)
 */
int	main(int argc, char *argv[], char *envp[])
{
	t_shell		shell;
	char		*line;

	if (argc > 1 || argv[1])
		return (print_comm_err("No arguments needed", ""));
	initialize_shell(&shell, envp);
	while (1)
	{
		switch_flag(1);
		set_signals_main();
		line = readline("minishell~> ");
		if (line == NULL)
		{
			print_close_banner();
			free_t_shell(&shell);
			break ;
		}
		switch_flag(0);
		if (check_command_line(line))
			shell.last_exitcod = try_command(&shell, line);
		else
			free(line);
	}
	return (0);
}
