/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 13:16:10 by bvarea-k          #+#    #+#             */
/*   Updated: 2025/10/12 16:49:02 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_exec(t_shell shell, char *line)
{
	int	exit_cod;
	
	exit_cod = 0;
	if (shell.cmd_length > 1)
		exit (0);
	print_close_banner();
	if (shell.commands[0].args_c > 1)
	{
		exit_cod = str_to_int(shell.commands[0].args[1]);
		if (exit_cod == 0 && !str_compare_all(shell.commands[0].args[1], "0"))
			exit_cod = 2;
	}
	free(line);
	free_env(shell.env_list);
	free_env(shell.env_list_cpy);
	free_commands(shell.commands, shell.cmd_length);
	exit(exit_cod);
}
