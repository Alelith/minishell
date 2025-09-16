/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 09:40:04 by bvarea-k          #+#    #+#             */
/*   Updated: 2025/09/16 09:16:09 by bvarea-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*set_env(char **envp)
{
	t_env	*env_list;
	int		i;
	char	*key;
	char	*value;

	env_list = NULL;
	i = 0;
	while (envp[i])
	{
		key = get_key(envp[i]);
		value = get_value(envp[i]);
		add_env(&env_list, key, value);
		i++;
	}
	return (env_list);
}
