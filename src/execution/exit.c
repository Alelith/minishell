/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 13:16:10 by bvarea-k          #+#    #+#             */
/*   Updated: 2025/09/10 08:59:26 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_exec(t_shell shell)
{
	printf(CLOSE_BANNER);
	free_env(shell.env_list);
	free_commands(shell.commands, shell.cmd_length);
	exit(0);
}
