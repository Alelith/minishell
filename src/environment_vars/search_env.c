/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 11:49:30 by bvarea-k          #+#    #+#             */
/*   Updated: 2025/09/04 11:58:28 by bvarea-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*search_env(t_env *envs, const char *key)
{
	t_env	*curr;
	
	curr = envs;
	while (curr)
	{
		if (str_compare_all(curr->pair.key, key))
			return (curr->pair.value);
		curr = curr->next;
	}
	return (0);
}
