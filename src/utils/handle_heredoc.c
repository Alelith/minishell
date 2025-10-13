/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 16:28:20 by acesteve          #+#    #+#             */
/*   Updated: 2025/10/13 13:54:37 by bvarea-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	write_and_free(int *pipefd, char *line)
{
	write(pipefd[1], line, str_len(line));
	write(pipefd[1], "\n", 1);
	free(line);
}

static void	close_and_waitpid(int *pipefd, int pid, int *status)
{
	close(pipefd[1]);
	waitpid(pid, status, 0);
}

static void	throw_heredoc(int pid, int *pipefd, t_command *cmd)
{
	char	*line;

	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		close(pipefd[0]);
		while (1)
		{
			line = readline(">");
			if (!line)
			{
				free(cmd->heredoc_eof);
				close(pipefd[1]);
				exit(130);
			}
			if (str_compare_all(line, cmd->heredoc_eof))
			{
				free(cmd->heredoc_eof);
				free(line);
				break ;
			}
			write_and_free(pipefd, line);
		}
		close(pipefd[1]);
		exit(0);
	}
}

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
	throw_heredoc(pid, pipefd, cmd);
	close_and_waitpid(pipefd, pid, &status);
	if (pid != 0)
		free(cmd->heredoc_eof);
	cmd->infile = pipefd[0];
}
