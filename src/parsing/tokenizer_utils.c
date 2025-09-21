/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 11:49:06 by acesteve          #+#    #+#             */
/*   Updated: 2025/09/21 11:51:28 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*init_command(void)
{
	t_command	*cmd;

	cmd = callocation(1, sizeof(t_command));
	cmd[0].outfile = 1;
	return (cmd);
}

char	**get_tokens(char *input, t_shell shell)
{
	char	**tokens;

	tokens = split_command(input, shell.env_list);
	return (tokens);
}

int	is_pipe_token(char *token)
{
	if (str_compare_all(token, "|"))
		return (1);
	return (0);
}

int	is_redir_token(char *token)
{
	if (str_compare_all(token, ">"))
		return (1);
	if (str_compare_all(token, "<"))
		return (1);
	if (str_compare_all(token, ">>"))
		return (1);
	if (str_compare_all(token, "<<"))
		return (1);
	return (0);
}
