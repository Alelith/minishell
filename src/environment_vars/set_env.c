/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 09:40:04 by bvarea-k          #+#    #+#             */
/*   Updated: 2025/09/01 11:37:38 by bvarea-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*t_env	*set_env(char **envp)
{
	t_env	*env_list;
	t_env	*new_node;
	int		i;

	env_list = NULL;
	i = 0;
	while (envp[i])
	{
		new_node = malloc(sizeof(t_env));
		if (!new_node)
			return (NULL);
		new_node->pair.key = str_duplicate(get_key(envp[i]));
		new_node->pair.value = str_duplicate(get_value(envp[i]));
		new_node->next = env_list;
		env_list = new_node;
		i++;
	}
	return (env_list);
}*/

char	*get_key(char *envp)
{
	int		i;
	int		j;
	char	*key;

	i = 0;
	j = 0;
	while (envp[i] && envp[i] != '=')
		i++;
	key = malloc(i + 1);
	if (!key)
		return (NULL);
	while (j < i)
	{
		key[j] = envp[j];
		j++;
	}
	key[j] = '\0';
	return (key);
}

char	*get_value(char *envp)
{
	int	i;

	i = 0;
	while (envp[i] && envp[i] != '=')
		i++;
	if (envp[i] == '=')
		i++;
	return (str_duplicate(&envp[i]));
}

static void	add_env_node(t_env **env_list, t_env *new_node)
{
	t_env	*last_node;

	if (!*env_list)
		*env_list = new_node;
	else
	{
		last_node = *env_list;
		while (last_node->next)
			last_node = last_node->next;
		last_node->next = new_node;
	}
}

t_env	*set_env(char **envp)
{
	t_env	*env_list;
	t_env	*new_node;
	int		i;

	env_list = NULL;
	i = 0;
	while (envp[i])
	{
		new_node = malloc(sizeof(t_env));
		if (!new_node)
			return (NULL);
		new_node->pair.key = str_duplicate(get_key(envp[i]));
		new_node->pair.value = str_duplicate(get_value(envp[i]));
		new_node->next = NULL;
		add_env_node(&env_list, new_node);
		i++;
	}
	return (env_list);
}

int	update_env(t_env *env_list, const char *key, const char *value)
{
	t_env	*current;

	current = env_list;
	while (current)
	{
		if (str_compare_all(current->pair.key, key) == 0)
		{
			free(current->pair.value);
			current->pair.value = str_duplicate(value);
			return (1);
		}
		current = current->next;
	}
	return (0);
}
