/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 09:21:48 by bvarea-k          #+#    #+#             */
/*   Updated: 2025/09/10 17:22:11 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*make_res(char	*path, char *command)
{
	char	*tmp;
	char	*result;

	tmp = str_join(path, "/");
	result = str_join(tmp, command);
	free(tmp);
	return (result);
}

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
		print_comm_err("You don't have permissions to execute this file: ",
			path);
		return (0);
	}
	return (1);
}

static char	*check_path(char *result, char **paths)
{
	if (access(result, F_OK) == 0)
	{
		if (permissions_check(result))
		{
			free_paths(paths);
			return (result);
		}
	}
	free(result);
	return (0);
}

char	*search_command(char *command, char *exec_paths)
{
	int		i;
	char	*result;
	char	**paths;

	if ((str_compare_n(command, "/", 1) || str_compare_n(command, "./", 2)
			|| str_compare_n(command, "../", 3)) && !access(command, F_OK))
	{
		if (permissions_check(command))
			return (str_duplicate(command));
		return (0);
	}
	if (!exec_paths)
		return (0);
	i = 0;
	paths = str_split(exec_paths, ':');
	while (paths[i])
	{
		result = check_path(make_res(paths[i], command), paths);
		if (result)
			return (result);
		i++;
	}
	free_paths(paths);
	return (0);
}
