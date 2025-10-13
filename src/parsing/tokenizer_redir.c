/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 11:47:05 by acesteve          #+#    #+#             */
/*   Updated: 2025/10/14 00:15:08 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_file(char *file, t_redir redir_type)
{
	if (redir_type == OVERWRITE || redir_type == OUTPUT)
	{
		if (access(file, F_OK) == 0)
		{
			if (access(file, W_OK) == 0)
				return (1);
			else
				print_comm_err("Permission denied: ", file);
		}
		else
			return (1);
	}
	else if (redir_type == INPUT)
	{
		if (access(file, F_OK) == 0)
		{
			if (access(file, R_OK) == 0)
				return (1);
			else
				print_comm_err("Permission denied: ", file);
		}
		else
			print_comm_err("No such file or directory: ", file);
	}
	return (0);
}

void	proccess_redir(t_token *tokens, int index, t_command *cmd)
{
	if (str_compare_all(tokens[index].token, "<")
		&& check_file(tokens[index + 1].token, INPUT))
		cmd->infile = open(tokens[index + 1].token, O_RDONLY);
	else if (str_compare_all(tokens[index].token, ">")
		&& check_file(tokens[index + 1].token, OVERWRITE))
		cmd->outfile = open(tokens[index + 1].token,
				O_WRONLY | O_TRUNC | O_CREAT, 00777);
	else if (str_compare_all(tokens[index].token, ">>")
		&& check_file(tokens[index + 1].token, OUTPUT))
		cmd->outfile = open(tokens[index + 1].token,
				O_WRONLY | O_APPEND | O_CREAT, 00777);
	else if (str_compare_all(tokens[index].token, "<<"))
		cmd->heredoc_eof = str_duplicate(tokens[index + 1].token);
	else
		cmd->has_error = 1;
	free(tokens[index].token);
	free(tokens[index + 1].token);
}
