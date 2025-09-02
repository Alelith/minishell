/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 12:19:16 by bvarea-k          #+#    #+#             */
/*   Updated: 2025/09/02 10:23:02 by bvarea-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_env(t_env *env_list, const char *key, const char *value)
{
	t_env	*current;

	current = env_list;
	while (current)
	{
		if (str_compare_all(current->pair.key, key))
		{
			free(current->pair.key);
			free(current->pair.value);
			current->pair.key = (char *) key;
			current->pair.value = (char *) value;
			return (1);
		}
		current = current->next;
	}
	return (0);
}
