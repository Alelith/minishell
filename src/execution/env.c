/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 11:43:29 by bvarea-k          #+#    #+#             */
/*   Updated: 2025/09/01 12:56:09 by bvarea-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env(t_env *env_list)
{
	t_env	*current;

	current = env_list;
	while (current)
	{
		write(1, current->pair.key, str_len(current->pair.key));
		write(1, "=", 1);
		write(1, current->pair.value, str_len(current->pair.value));
		write(1, "\n", 1);
		current = current->next;
	}
	return (1);
}
