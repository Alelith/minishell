/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 11:49:30 by bvarea-k          #+#    #+#             */
/*   Updated: 2025/09/10 11:27:58 by acesteve         ###   ########.fr       */
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
