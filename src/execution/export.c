/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 11:45:52 by bvarea-k          #+#    #+#             */
/*   Updated: 2025/09/10 13:30:35 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	save_var(t_command cmd, t_env *env, t_env *env_cpy)
{
	char	*key;
	char	*value;

	key = get_key(cmd.args[1]);
	value = 0;
	if (str_search_char(cmd.args[1], '=') > 0)
	{
		value = get_value(cmd.args[1]);
		if (exists_env(key, env))
			update_env(env, key, value);
		add_env(&env, str_duplicate(key), str_duplicate(value));
	}
	if (exists_env(key, env_cpy))
		update_env(env_cpy, key, value);
	add_env(&env_cpy, key, value);
	return (0);
}

static int	print_copies(t_env *env_cpy)
{
	while (env_cpy)
	{
		if (env_cpy->pair.value)
			print_export(env_cpy->pair.key, env_cpy->pair.value);
		else
			print_export(env_cpy->pair.key, 0);
		env_cpy = env_cpy->next;
	}
	return (0);
}

int	export(t_command cmd, t_env *env, t_env *env_cpy)
{
	if (cmd.args_c > 1)
		save_var(cmd, env, env_cpy);
	else
		print_copies(env_cpy);
	return (0);
}
