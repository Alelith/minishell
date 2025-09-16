/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 13:16:10 by bvarea-k          #+#    #+#             */
/*   Updated: 2025/09/16 09:16:20 by bvarea-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_exec(t_shell shell, char *line)
{
	print_close_banner();
	free(line);
	free_env(shell.env_list);
	free_env(shell.env_list_cpy);
	free_commands(shell.commands, shell.cmd_length);
	exit(0);
}
