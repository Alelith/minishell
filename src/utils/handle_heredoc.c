/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 16:28:20 by acesteve          #+#    #+#             */
/*   Updated: 2025/09/23 17:32:23 by bvarea-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_heredoc(t_command *cmd)
{
	int		pipefd[2];
	pid_t	pid;
	int		status;

	if (!cmd->heredoc_eof)
		return ;
	if (pipe(pipefd) == -1)
		return ;
	pid = fork();
	if (pid == -1)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		return ;
	}
	if (pid == 0)
	{
		char *line = NULL;
		signal(SIGINT, SIG_DFL);
		close(pipefd[0]);
		while (1)
		{
			line = readline("heredoc>");
			if (!line)
			{
				close(pipefd[1]);
				exit(130);
			}
			if (str_compare_all(line, cmd->heredoc_eof))
			{
				free(line);
				break;
			}
			write(pipefd[1], line, str_len(line));
			write(pipefd[1], "\n", 1);
			free(line);
		}
		close(pipefd[1]);
		exit(0);
	}
	close(pipefd[1]);
	set_signals_main();
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		close(pipefd[0]);
		cmd->infile = -1;
	}
	else
	{
		cmd->infile = pipefd[0];
	}
}
