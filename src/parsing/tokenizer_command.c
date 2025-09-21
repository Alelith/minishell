/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 11:44:24 by acesteve          #+#    #+#             */
/*   Updated: 2025/09/21 11:44:47 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	proccess_command(char *token, t_command *cmd)
{
	void	*tmp;

	tmp = reallocation(cmd->args, (cmd->args_c + 1) * sizeof(t_command),
			(cmd->args_c) * sizeof(t_command));
	cmd->args = tmp;
	cmd->args[cmd->args_c] = token;
	cmd->args_c++;
}
