/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 11:43:29 by bvarea-k          #+#    #+#             */
/*   Updated: 2025/09/01 11:32:41 by bvarea-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*int	env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		write(1, envp[i], str_len(envp[i]));
		write(1, "\n", 1);
		i++;
	}
	return (1);
}*/

int	env(t_env **env_list)
{
	while (*env_list)
	{
		write(1, (*env_list)->pair.key, str_len((*env_list)->pair.key));
		write(1, "=", 1);
		write(1, (*env_list)->pair.value, str_len((*env_list)->pair.value));
		write(1, "\n", 1);
		env_list = &(*env_list)->next;
	}
	return (1);
}
