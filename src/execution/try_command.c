/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 12:13:03 by acesteve          #+#    #+#             */
/*   Updated: 2025/09/24 13:20:26 by bvarea-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	try_command(t_shell *shell, char *line, int i)
{
	int		**pipes;
	pid_t	*pids;
	char	*temp;
	int		err;
	int		*statuses;

	pipes = NULL;
	pids = NULL;
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
		if (any_has_error(shell->commands, shell->cmd_length))
		{
			free_commands(shell->commands, shell->cmd_length);
			free(line);
			return (1);
		}
		pipes = (int **)malloc(sizeof(int *) * (shell->cmd_length - 1));
		while (i < shell->cmd_length - 1)
		{
			pipes[i] = (int *)malloc(sizeof(int) * 2);
			pipe(pipes[i++]);
		}
		pids = (pid_t *)malloc(sizeof(pid_t) * shell->cmd_length);
		err = fork_and_execute(shell, pipes, line, pids);
		statuses = close_and_free(*shell, pipes, pids);
		i = 0;
		while (statuses && i < shell->cmd_length)
			if (statuses[i++] != 0 && err == 0)
				err = statuses[i - 1];
	}
	free(line);
	return (err);
}
