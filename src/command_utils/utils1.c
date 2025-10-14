/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 13:20:05 by bvarea-k          #+#    #+#             */
/*   Updated: 2025/10/14 11:38:20 by bvarea-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	switch_commands(t_shell *shell, int index, char *line)
{
	if (str_compare_all(shell->commands[index].args[0], "echo"))
		return (echo(shell->commands[index]));
	else if (str_compare_all(shell->commands[index].args[0], "exit"))
		return (exit_exec(*shell, line));
	else if (str_compare_all(shell->commands[index].args[0], "cd"))
		return (cd(shell, shell->commands[index]));
	else if (str_compare_all(shell->commands[index].args[0], "pwd"))
		return (pwd());
	else if (str_compare_all(shell->commands[index].args[0], "export"))
		return (export(shell->commands[index], &shell->env_list,
				&shell->env_list_cpy));
	else if (str_compare_all(shell->commands[index].args[0], "unset"))
		return (unset(shell->commands[index], &shell->env_list));
	else if (str_compare_all(shell->commands[index].args[0], "env"))
		return (env(shell->env_list));
	else if (str_compare_all(shell->commands[index].args[0], "clear"))
		print_open_banner();
	else
		return (execute(shell->commands[index], shell->env_list));
	return (0);
}

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
