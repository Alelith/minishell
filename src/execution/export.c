/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 11:45:52 by bvarea-k          #+#    #+#             */
/*   Updated: 2025/10/17 18:09:24 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	save_env(char *key, char *value, t_env **env)
{
	if (exists_env(key, *env))
		update_env(*env, key, value);
	else
		add_env(env, str_duplicate(key), str_duplicate(value));
}

static int	is_valid_key(char *key)
{
	while (key && *key)
	{
		if (!is_alphabetic(*key) && *key != '_')
			return (0);
		key++;
	}
	return (1);
}

static int	save_var(t_command cmd, t_env **env, t_env **env_cpy)
{
	int		i;
	char	*key;
	char	*value;
	int		result;

	i = 0;
	while (++i < cmd.args_c)
	{
		key = get_key(cmd.args[i]);
		value = 0;
		if (is_valid_key(key) && str_search_char(cmd.args[i], '=') != NULL)
		{
			value = get_value(cmd.args[i]);
			save_env(key, value, env);
		}
		result = 0;
		if (!is_valid_key(key))
			result = print_comm_err("Invalid identifier: ", cmd.args[i]);
		else
			save_env(key, value, env_cpy);
		free(key);
		if (value)
			free(value);
	}
	return (result);
}

int	export(t_command cmd, t_env **env, t_env **env_cpy)
{
	if (cmd.args_c > 1)
		return (save_var(cmd, env, env_cpy));
	else
		return (print_sorted_env(*env_cpy));
}
