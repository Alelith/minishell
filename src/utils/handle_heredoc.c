/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 16:28:20 by acesteve          #+#    #+#             */
/*   Updated: 2025/09/21 16:46:13 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_heredoc(t_command *cmd)
{
	int		pipefd[2];
	char	*line;

	line = NULL;
	if (!cmd->heredoc_eof)
		return ;
	if (pipe(pipefd) == -1)
		return ;
	while (1)
	{
		line = readline("heredoc>");
		if (str_compare_all(line, cmd->heredoc_eof))
			break ;
		write(pipefd[1], line, str_len(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	close(pipefd[1]);
	cmd->infile = pipefd[0];
}
