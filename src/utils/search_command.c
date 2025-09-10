/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 09:21:48 by bvarea-k          #+#    #+#             */
/*   Updated: 2025/09/10 09:48:19 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
}

static int	permissions_check(char *path)
{
	if (access(path, X_OK) != 0)
	{
		write(2, "You don't have permissions to execute this file: ", 49);
		write(2, path, str_len(path));
		write(2, "\n", 1);
		return (0);
	}
	return (1);
}

char	*search_command(char *command, char *exec_paths)
{
	int		i = 0;
	char	*tmp;
	char	*result;
	char	**paths = str_split(exec_paths, ':');

	if ((str_compare_n(command, "/", 1) || str_compare_n(command, "./", 2)
			|| str_compare_n(command, "../", 3)) && !access(command, F_OK))
	{
		if (permissions_check(command))
		{
			free_paths(paths);
			return (command);
		}
		free_paths(paths);
		return (0);
	}
	while (paths[i])
	{
		tmp = str_join(paths[i], "/");
		result = str_join(tmp, command);
		free(tmp);
		if (access(result, F_OK) == 0)
		{
			if (permissions_check(result))
			{
				free_paths(paths);
				return (result);
			}
			free(result);
			break ;
		}
		free(result);
		i++;
	}
	free_paths(paths);
	return (0);
}
