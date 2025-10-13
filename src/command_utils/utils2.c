/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 13:21:01 by bvarea-k          #+#    #+#             */
/*   Updated: 2025/10/13 16:36:11 by bvarea-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	finish_execute(int i, t_shell *shell, int **pipes, int *pids)
{
	if (str_compare_all(shell->commands[i].args[0], "exit"))
	{
		free(pipes);
		free(pids);
	}
}

int	is_builtin_candidate(t_shell *shell, int i)
{
	return (shell->commands[i].args && shell->commands[i].args[0]
		&& is_builtin(shell->commands[i].args[0])
		&& shell->cmd_length == 1);
}

int	fork_and_execute(t_shell *shell, int **pipes, char *line, int *pids)
{
	int	i;
	int	err;

	i = 0;
	err = 0;
	while (i < shell->cmd_length)
	{
		if (shell->commands[i].infile == -1)
		{
			write(1, "\n", 1);
			return (1);
		}
		if (is_builtin_candidate(shell, i))
		{
			handle_heredoc(&shell->commands[i]);
			execute_builtin(shell, i, &err, line);
			finish_execute(i, shell, pipes, pids);
			return (err);
		}
		pids[i] = fork();
		if (pids[i] == 0)
		{
			handle_heredoc(&shell->commands[i]);
			set_signals_child();
			execute_fork(shell, i, pipes, line);
		}
		i++;
	}
	return (err);
}
