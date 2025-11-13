/**
 * @file utils1.c
 * @brief Command execution utilities and pipe management
 * 
 * @author Lilith Estévez Boeta y Begoña Varea Kuhn
 * @date 2025-09-24
 */

#include "minishell.h"

/**
 * @brief Routes command execution to appropriate built-in or external handler
 * 
 * @details Implements a dispatcher that identifies the command type and
 * calls the corresponding built-in function or executes as external
 * command. Handles all built-ins: echo, exit, cd, pwd, export, unset,
 * env, and clear.
 * 
 * @ingroup command_utils_module
 * 
 * @param[in,out] shell Shell state structure
 * @param[in] index Command index in commands array
 * @param[in] line Original command line for exit command
 * @return Exit status of executed command
 */
int	switch_commands(t_shell *shell, int index, char *line)
{
	if (str_compare_all(shell->commands[index].args[0], "echo"))
		return (echo(shell->commands[index]));
	else if (str_compare_all(shell->commands[index].args[0], "exit"))
		return (exit_exec(*shell, line));
	else if (str_compare_all(shell->commands[index].args[0], "cd"))
		return (cd(shell, shell->commands[index]));
	else if (str_compare_all(shell->commands[index].args[0], "pwd"))
		return (pwd(shell->commands[index]));
	else if (str_compare_all(shell->commands[index].args[0], "export"))
		return (export(shell->commands[index], &shell->env_list,
				&shell->env_list_cpy));
	else if (str_compare_all(shell->commands[index].args[0], "unset"))
		return (unset(shell->commands[index], &shell->env_list,
				&shell->env_list_cpy));
	else if (str_compare_all(shell->commands[index].args[0], "env"))
		return (env(shell->commands[index], shell->env_list));
	else if (str_compare_all(shell->commands[index].args[0], "clear"))
		print_open_banner();
	else
		return (execute(shell->commands[index], shell->env_list));
	return (0);
}

/**
 * @brief Closes all pipe file descriptors and frees pipe array
 * 
 * @details Iterates through all pipes in a pipeline, closing both read
 * and write ends, and freeing the allocated memory for each pipe pair.
 * 
 * @ingroup command_utils_module
 * 
 * @param[in,out] pipes Array of pipe file descriptor pairs
 * @param[in] shell Shell state with command count information
 */
void	close_and_free_pipes(int **pipes, t_shell shell)
{
	int	i;

	i = 0;
	while (i < shell.cmd_length - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		free(pipes[i++]);
	}
}

/**
 * @brief Waits for child processes and collects exit statuses
 * 
 * @details Waits for all child processes to complete, handles SIGQUIT
 * signals, and converts wait status codes to standard exit codes.
 * Handles both normal exits and signal terminations.
 * 
 * @ingroup command_utils_module
 * 
 * @param[in] pids Array of process IDs to wait for
 * @param[out] statuses Array to store exit statuses
 * @param[in] count Number of processes to wait for
 */
static void	wait_for_children(int *pids, int *statuses, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		waitpid(pids[i], &statuses[i], 0);
		if ((statuses[i] & 0x7f) == SIGQUIT)
			printf("Quit (core dumped)\n");
		if (((statuses[i] & 0xff00) >> 8) != 0)
			statuses[i] = (statuses[i] & 0xff00) >> 8;
		else if (statuses[i] != 0)
			statuses[i] += 128;
		i++;
	}
}

/**
 * @brief Cleans up pipeline resources and waits for processes
 * 
 * @details Closes and frees all pipes, waits for child processes to
 * complete, collects exit statuses, and frees command structures.
 * Only waits for processes if commands were forked (non-builtins or
 * multiple commands).
 * 
 * @ingroup command_utils_module
 * 
 * @param[in] shell Shell state structure
 * @param[in,out] pipes Array of pipe file descriptors
 * @param[in] pids Array of child process IDs
 * @return Array of exit statuses for each command, or NULL for built-ins
 */
int	*close_and_free(t_shell shell, int **pipes, int *pids)
{
	int	i;
	int	*statuses;

	i = 0;
	if ((shell.cmd_length == 1 && !is_builtin(shell.commands[i].args[0]))
		|| shell.cmd_length > 1)
	{
		statuses = malloc(shell.cmd_length * sizeof(int));
		if (!statuses)
			return (0);
	}
	else
		statuses = 0;
	close_and_free_pipes(pipes, shell);
	free(pipes);
	i = 0;
	if ((shell.cmd_length == 1 && !is_builtin(shell.commands[i].args[0]))
		|| shell.cmd_length > 1)
		wait_for_children(pids, statuses, shell.cmd_length);
	free(pids);
	free_commands(shell.commands, shell.cmd_length);
	return (statuses);
}

/**
 * @brief Executes a command in a forked child process
 * 
 * @details Sets up file descriptor redirections for pipes and I/O
 * redirections, closes all pipe file descriptors, executes the command,
 * and exits the child process. Handles stdin from previous pipe or file,
 * and stdout to next pipe or file.
 * 
 * @ingroup command_utils_module
 * 
 * @param[in,out] shell Shell state structure
 * @param[in] i Command index to execute
 * @param[in] pipes Array of pipe file descriptors
 * @param[in] line Original command line
 */
void	execute_fork(t_shell *shell, int i, int **pipes, char *line)
{
	int	j;
	int	err;

	if (shell->commands[i].infile != STDIN_FILENO)
		dup2(shell->commands[i].infile, STDIN_FILENO);
	else if (i > 0)
		dup2(pipes[i - 1][0], STDIN_FILENO);
	if (shell->commands[i].outfile != STDOUT_FILENO)
		dup2(shell->commands[i].outfile, STDOUT_FILENO);
	else if (i < shell->cmd_length - 1)
		dup2(pipes[i][1], STDOUT_FILENO);
	j = 0;
	while (j < shell->cmd_length - 1)
	{
		close(pipes[j][0]);
		close(pipes[j][1]);
		j++;
	}
	err = switch_commands(shell, i, line);
	if (shell->env_list)
		free_env(shell->env_list);
	if (shell->env_list_cpy)
		free_env(shell->env_list_cpy);
	free_and_exit(shell, line, err);
}
