/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 20:18:52 by bvarea-k          #+#    #+#             */
/*   Updated: 2025/10/09 19:23:35 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	env_list_size(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

static t_env	**env_to_array(t_env *env)
{
	int		i;
	int		size;
	t_env	**arr;

	size = env_list_size(env);
	arr = malloc(sizeof(t_env *) * (size + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (env)
	{
		arr[i++] = env;
		env = env->next;
	}
	arr[i] = NULL;
	return (arr);
}

static int	ascii_cmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

static void	sort_env_array(t_env **arr)
{
	int		i;
	int		sorted;
	t_env	*tmp;

	sorted = 0;
	while (!sorted)
	{
		sorted = 1;
		i = 0;
		while (arr[i + 1])
		{
			if (ascii_cmp(arr[i]->pair.key, arr[i + 1]->pair.key) > 0)
			{
				tmp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = tmp;
				sorted = 0;
			}
			i++;
		}
	}
}

void	print_sorted_env(t_env *env)
{
	t_env	**arr;
	int		i;

	arr = env_to_array(env);
	if (!arr)
		return ;
	sort_env_array(arr);
	i = 0;
	while (arr[i])
	{
		if (arr[i]->pair.value)
			print_export(arr[i]->pair.key, arr[i]->pair.value);
		else
			print_export(arr[i]->pair.key, 0);
		i++;
	}
	free(arr);
}
