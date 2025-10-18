/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 16:41:56 by bvarea-k          #+#    #+#             */
/*   Updated: 2025/10/18 09:45:25 by acesteve         ###   ########.fr       */
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
	return (0);
}
