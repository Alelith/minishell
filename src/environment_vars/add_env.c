/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 12:24:51 by bvarea-k          #+#    #+#             */
/*   Updated: 2025/09/02 09:55:12 by bvarea-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_env(t_env **env_list, char *key, char *value)
{
	t_env	*last_node;
	t_env	*new_node;

	new_node = callocation(1, sizeof(t_env));
	if (!new_node)
		return (0);
	new_node->pair.key = NULL;
	new_node->pair.value = NULL;
	new_node->next = NULL;
	if (key)
		new_node->pair.key = key;
	if (value)
		new_node->pair.value = value;
	last_node = *env_list;
	while (last_node && last_node->next)
		last_node = last_node->next;
	if (!last_node)
		*env_list = new_node;
	else
		last_node->next = new_node;
	return (1);
}
