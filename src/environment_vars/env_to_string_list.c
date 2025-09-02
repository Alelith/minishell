/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_string_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 10:45:57 by bvarea-k          #+#    #+#             */
/*   Updated: 2025/09/02 10:54:35 by bvarea-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**env_to_string_list(t_env *env_list)
{
	t_env	*current;
	char	*tmp;
	char	**envp;
	int		size;

	size = 0;
	current = env_list;
	while (current)
	{
		size++;
		current = current->next;
	}
	envp = callocation(size + 1, sizeof(char *));
	if (!envp)
		return (NULL);
	current = env_list;
	size = 0;
	while (current)
	{
		if (current->pair.value)
		{
			tmp = str_join(current->pair.key, "=");
			envp[size] = str_join(tmp, current->pair.value);
			free(tmp);
		}
		else
			envp[size] = str_join(current->pair.key, "=");
		if (!envp[size])
			return (NULL);
		size++;
		current = current->next;
	}
	envp[size] = NULL;
	return (envp);
}
