/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 11:45:52 by bvarea-k          #+#    #+#             */
/*   Updated: 2025/09/10 09:19:45 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export(t_command cmd, t_env *env)
{
	char	*key;
	char	*value;

	key = get_key(cmd.args[1]);
	value = get_value(cmd.args[1]);
	if (exists_env(key, env))
		return (update_env(env, key, value));
	return (add_env(&env, key, value));
}
