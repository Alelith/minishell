/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 12:13:03 by acesteve          #+#    #+#             */
/*   Updated: 2025/10/20 10:07:26 by bvarea-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	reserve_all(t_shell *shell, int ***pipes, int **pids)
{
	*pipes = reserve_pipes(shell);
	*pids = (pid_t *)malloc(sizeof(pid_t) * shell->cmd_length);
	if (!pids)
		free(pipes);
}

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
