/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 16:41:56 by bvarea-k          #+#    #+#             */
/*   Updated: 2025/10/20 10:25:56 by bvarea-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset(t_command cmd, t_env **env_list, t_env **env_cpy)
{
	if (cmd.args_c == 2)
	{
		delete_env(env_list, cmd.args[1]);
		delete_env(env_cpy, cmd.args[1]);
	}
	else if (cmd.args_c == 1)
		return (print_comm_err("unset: not enough arguments", ""));
	return (0);
}
