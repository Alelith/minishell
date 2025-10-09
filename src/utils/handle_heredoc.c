/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 16:28:20 by acesteve          #+#    #+#             */
/*   Updated: 2025/10/09 19:28:12 by acesteve         ###   ########.fr       */
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
		signal(SIGQUIT, SIG_DFL);
		close(pipefd[0]);
		while (1)
		{
			line = readline(">");
			if (!line)
			{
				close(pipefd[1]);
				exit(130);
			}
			if (str_compare_all(line, cmd->heredoc_eof))
			{
				free(line);
				break ;
			}
			write_and_free(pipefd, line);
		}
		close(pipefd[1]);
		exit(0);
	}
}

void	handle_heredoc(t_command *cmd, short is_from_builtin)
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
	if ((((status) & 0x7f) == 0 && ((status) & 0xff00) >> 8 == 130)
		|| is_from_builtin)
	{
		close(pipefd[0]);
		cmd->infile = -1;
	}
	else
		cmd->infile = pipefd[0];
}
