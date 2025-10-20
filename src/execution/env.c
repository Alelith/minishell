/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 11:43:29 by bvarea-k          #+#    #+#             */
/*   Updated: 2025/10/20 10:19:36 by bvarea-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env(t_command cmd, t_env *env_list)
{
	t_env	*current;

	if (cmd.args_c > 1)
	{
		print_comm_err("env: Too many arguments", "");
		return (1);
	}
	current = env_list;
	while (current)
	{
		printf("%s=%s\n", current->pair.key, current->pair.value);
		current = current->next;
	}
	return (0);
}
