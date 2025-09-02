/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 10:29:27 by bvarea-k          #+#    #+#             */
/*   Updated: 2025/09/02 10:29:46 by bvarea-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	delete_env(t_env **env_list, char *key)
{
	t_env	*current;
	t_env	*previous;

	current = *env_list;
	previous = NULL;
	while (current)
	{
		if (str_compare_all(current->pair.key, key))
		{
			if (previous)
				previous->next = current->next;
			else
				*env_list = current->next;
			free(current->pair.key);
			free(current->pair.value);
			free(current);
			return (1);
		}
		previous = current;
		current = current->next;
	}
	return (0);
}
