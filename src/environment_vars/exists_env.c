/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exists_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 10:02:44 by bvarea-k          #+#    #+#             */
/*   Updated: 2025/09/16 09:16:07 by bvarea-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exists_env(char *key, t_env *env)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (str_compare_all(current->pair.key, key))
			return (1);
		current = current->next;
	}
	return (0);
}
