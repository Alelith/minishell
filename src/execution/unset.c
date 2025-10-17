/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 16:41:56 by bvarea-k          #+#    #+#             */
/*   Updated: 2025/10/17 22:26:49 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset(t_command cmd, t_env **env_list)
{
	if (cmd.args == 2)
		return (delete_env(env_list, cmd.args[1]));
	else
		return (0);
}
