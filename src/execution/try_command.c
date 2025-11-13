/**
 * @file try_command.c
 * @brief Main command execution coordinator and pipeline manager
 * 
 * @author Lilith Estévez Boeta y Begoña Varea Kuhn
 * @date 2025-09-21
 */

#include "minishell.h"

/**
 * @brief Checks if any commands have parsing errors
 * 
 * @details Validates all parsed commands for errors and cleans up
 * resources if errors are found.
 * 
 * @ingroup execution_module
 * 
 * @param[in,out] shell Shell state structure
 * @param[in] line Command line string to free on error
 * @return 1 if errors found, 0 otherwise
 */
static int	there_is_error(t_shell *shell, char *line)
{
	if (any_has_error(shell->commands, shell->cmd_length))
	{
		free_commands(shell->commands, shell->cmd_length);
		free(line);
		return (1);
	}
	return (0);
}

/**
 * @brief Collects exit statuses from executed commands
 * 
 * @details Closes pipes, frees resources, and gathers exit statuses
 * from all commands in the pipeline. Returns the first non-zero status.
 * 
 * @ingroup execution_module
 * 
 * @param[in] shell Shell state structure
 * @param[in,out] pipes Array of pipe file descriptors
 * @param[in] pids Array of process IDs
 * @param[in] err Initial error code
 * @return First non-zero exit status, or 0 if all succeeded
 */
static int	get_statuses_err(t_shell *shell, int **pipes, int *pids, int err)
{
	int	i;
	int	*statuses;

	statuses = close_and_free(*shell, pipes, pids);
	i = 0;
	while (statuses && i < shell->cmd_length)
		if (statuses[i++] != 0 && err == 0)
			err = statuses[i - 1];
	free(statuses);
	return (err);
}

/**
 * @brief Allocates and initializes pipe file descriptors
 * 
 * @details Creates an array of pipes for inter-process communication
 * in command pipelines. Allocates one pipe for each adjacent command
 * pair.
 * 
 * @ingroup execution_module
 * 
 * @param[in] shell Shell state structure with command count
 * @return Array of pipe file descriptor pairs, or NULL on error
 */
static int	**reserve_pipes(t_shell *shell)
{
	int	i;
	int	**pipes;

	i = 0;
	pipes = (int **)malloc(sizeof(int *) * (shell->cmd_length - 1));
	if (!pipes)
		return (0);
	while (i < shell->cmd_length - 1)
	{
		pipes[i] = (int *)malloc(sizeof(int) * 2);
		if (!pipes[i])
		{
			while (--i >= 0)
				free(pipes[i]);
			free(pipes);
			return (0);
		}
		pipe(pipes[i++]);
	}
	return (pipes);
}

/**
 * @brief Allocates pipes and process ID arrays
 * 
 * @details Reserves memory for pipe file descriptors and process ID
 * tracking for pipeline execution.
 * 
 * @ingroup execution_module
 * 
 * @param[in] shell Shell state structure
 * @param[out] pipes Pointer to pipes array
 * @param[out] pids Pointer to process ID array
 */
static void	reserve_all(t_shell *shell, int ***pipes, int **pids)
{
	*pipes = reserve_pipes(shell);
	*pids = (pid_t *)malloc(sizeof(pid_t) * shell->cmd_length);
	if (!pids)
		free(pipes);
}

/**
 * @brief Main command execution entry point
 * 
 * @details Coordinates the entire command execution flow including:
 * - Command line parsing and tokenization
 * - Pipeline setup with pipe creation
 * - Fork and execution of commands
 * - Status collection and cleanup
 * Adds command to history and handles all error cases.
 * 
 * @ingroup execution_module
 * 
 * @param[in,out] shell Shell state structure
 * @param[in] line Command line string from readline
 * @return Exit status of the last command, or error code
 */
int	try_command(t_shell *shell, char *line)
{
	int		**pipes;
	pid_t	*pids;
	char	*temp;
	int		err;

	pipes = 0;
	pids = 0;
	if (line && *line)
		add_history(line);
	temp = line;
	line = str_trim(line, " \t\n\r");
	free (temp);
	shell->cmd_length = 0;
	shell->commands = tokenize(line, &shell->cmd_length, *shell);
	err = 0;
	if (shell->cmd_length > 0)
	{
		if (there_is_error(shell, line))
			return (1);
		reserve_all(shell, &pipes, &pids);
		err = get_statuses_err(shell, pipes, pids,
				fork_and_execute(shell, pipes, line, pids));
	}
	free(line);
	return (err);
}
