/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 11:45:52 by bvarea-k          #+#    #+#             */
/*   Updated: 2025/10/13 14:16:32 by bvarea-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	save_var(t_command cmd, t_env *env, t_env *env_cpy)
{
	char	*key;
	char	*value;

	key = get_key(cmd.args[1]);
	value = 0;
	if (str_search_char(cmd.args[1], '=') != NULL)
	{
		value = get_value(cmd.args[1]);
		if (exists_env(key, env))
			update_env(env, key, value);
		else
			add_env(&env, str_duplicate(key), str_duplicate(value));
	}
	if (exists_env(key, env_cpy))
		update_env(env_cpy, key, value);
	else
		add_env(&env_cpy, key, value);
}

int	export(t_command cmd, t_env *env, t_env *env_cpy)
{
	if (cmd.args_c > 1)
		save_var(cmd, env, env_cpy);
	else
		print_sorted_env(env_cpy);
	return (0);
}
