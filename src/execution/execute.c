/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 10:41:15 by bvarea-k          #+#    #+#             */
/*   Updated: 2025/09/02 11:11:37 by bvarea-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute(t_command command, t_env *env_list)
{
	int		i;
	char	*path;
	char	**envp;

	i = 0;
	path = str_substring(command.name, 1, str_len(command.name));
	if (!path)
		return (-1);
	envp = env_to_string_list(env_list);
	if (!envp)
	{
		free(path);
		return (-1);
	}
	if (execve(path, command.args, envp) == -1)
	{
		printf("Error executing command: %s; path: %s\n", command.name, path);
	}
	while (envp[i])
		free(envp[i++]);
	free(envp);
	free(path);
	return (0);
}
