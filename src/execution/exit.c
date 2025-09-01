/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 13:16:10 by bvarea-k          #+#    #+#             */
/*   Updated: 2025/09/01 13:37:06 by bvarea-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_exec(t_shell shell)
{
	printf("\033[0;95mExiting conchita\n\033[0;39m");
	free_env(shell.env_list);
	free_commands(shell.commands, shell.cmd_length);
	exit(0);
}
