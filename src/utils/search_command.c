/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 09:21:48 by bvarea-k          #+#    #+#             */
/*   Updated: 2025/09/04 12:33:08 by bvarea-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	permissions_check(char *path)
{
	if (access(path, X_OK))
	{
		write(2, "You don't have permissions to execute this file: ", 49);
		write(2, path, str_len(path));
		write(2, "\n", 1);
		return (0);
	}
	return (1);
}

int	search_command(char *command, char *exec_paths)
{
	int		i = 0;
	char	**paths = str_split(exec_paths, ':');

	while (paths[i])
	{
		if (str_compare_n(command + 1, paths[i], str_len(paths[i])))
		{
			if (!access(command, F_OK))
			{
				if (permissions_check(command))
					return (1);
				return (0);
			}
		}
		i++;
	}
	return (0);
}
