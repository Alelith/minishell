/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 11:43:29 by bvarea-k          #+#    #+#             */
/*   Updated: 2025/09/16 09:16:18 by bvarea-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env(t_env *env_list)
{
	t_env	*current;

	current = env_list;
	while (current)
	{
		printf("%s=%s\n", current->pair.key, current->pair.value);
		current = current->next;
	}
	return (1);
}
