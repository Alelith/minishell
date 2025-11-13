/**
 * @file utils2.c
 * @brief Built-in execution and process management utilities
 * 
 * @author Lilith Estévez Boeta y Begoña Varea Kuhn
 * @date 2025-09-24
 */

#include "minishell.h"

/**
 * @brief Executes a built-in command with I/O redirection
 * 
 * @details Sets up file descriptor redirections for the built-in command,
 * executes it, and restores the original stdin/stdout. Used for built-in
 * commands that need I/O redirection without forking.
 * 
 * @ingroup command_utils_module
 * 
 * @param[in,out] shell Shell state structure
 * @param[in] i Command index to execute
 * @param[out] err Pointer to store command exit status
 * @param[in] line Original command line
 */
void	execute_builtin(t_shell *shell, int i, int *err, char *line)
{
	if (shell->commands[i].infile != STDIN_FILENO)
		dup2(shell->commands[i].infile, STDIN_FILENO);
	if (shell->commands[i].outfile != STDOUT_FILENO)
		dup2(shell->commands[i].outfile, STDOUT_FILENO);
	*err = switch_commands(shell, i, line);
	dup2(shell->std_in, STDIN_FILENO);
	dup2(shell->std_out, STDOUT_FILENO);
}

/**
 * @brief Finalizes command execution and cleanup
 * 
 * @details Handles special post-execution tasks for specific commands.
 * Currently handles cleanup for the exit command by freeing pipes and
 * process ID arrays.
 * 
 * @ingroup command_utils_module
 * 
 * @param[in] i Command index that was executed
 * @param[in] shell Shell state structure
 * @param[in] pipes Array of pipe file descriptors
 * @param[in] pids Array of process IDs
 */
void	finish_execute(int i, t_shell *shell, int **pipes, int *pids)
{
	if (str_compare_all(shell->commands[i].args[0], "exit"))
	{
		free(pipes);
		free(pids);
	}
}

/**
 * @brief Checks if command should be executed as built-in
 * 
 * @details Determines if a command qualifies for built-in execution
 * without forking. A command is a built-in candidate if it has valid
 * arguments, is recognized as a built-in, and is the only command in
 * the pipeline.
 * 
 * @ingroup command_utils_module
 * 
 * @param[in] shell Shell state structure
 * @param[in] i Command index to check
 * @return 1 if command is built-in candidate, 0 otherwise
 */
int	is_builtin_candidate(t_shell *shell, int i)
{
	return (shell->commands[i].args && shell->commands[i].args[0]
		&& is_builtin(shell->commands[i].args[0])
		&& shell->cmd_length == 1);
}

/**
 * @brief Forks and executes all commands in the pipeline
 * 
 * @details Iterates through all commands, determining whether to execute
 * as built-in or fork a child process. Handles heredocs, I/O redirection
 * errors, and signal setup for child processes. Returns immediately for
 * built-in commands, otherwise returns after all forks complete.
 * 
 * @ingroup command_utils_module
 * 
 * @param[in,out] shell Shell state structure
 * @param[in] pipes Array of pipe file descriptors
 * @param[in] line Original command line
 * @param[out] pids Array to store child process IDs
 * @return Exit status (0 for forked commands, built-in status otherwise)
 * @retval 1 if input redirection error detected
 */
int	fork_and_execute(t_shell *shell, int **pipes, char *line, int *pids)
{
	int	i;
	int	err;

	i = 0;
	err = 0;
	while (i < shell->cmd_length)
	{
		if (shell->commands[i].infile == -1)
			return (1);
		if (is_builtin_candidate(shell, i))
		{
			handle_heredoc(&shell->commands[i]);
			execute_builtin(shell, i, &err, line);
			finish_execute(i, shell, pipes, pids);
			return (err);
		}
		pids[i] = fork();
		if (pids[i++] == 0)
		{
			handle_heredoc(&shell->commands[i - 1]);
			set_signals_child();
			execute_fork(shell, i - 1, pipes, line);
		}
	}
	return (err);
}

/**
 * @brief Frees resources and exits child process
 * 
 * @details Cleanup function called before exiting a child process.
 * Frees command structures and command line, then exits with the
 * provided error code.
 * 
 * @ingroup command_utils_module
 * 
 * @param[in] shell Shell state structure
 * @param[in] line Command line to free
 * @param[in] err Exit code to use
 */
void	free_and_exit(t_shell *shell, char *line, int err)
{
	free_commands(shell->commands, shell->cmd_length);
	free(line);
	exit(err);
}
