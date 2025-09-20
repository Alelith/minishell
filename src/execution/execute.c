/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 10:41:15 by bvarea-k          #+#    #+#             */
/*   Updated: 2025/09/20 11:32:49 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute(t_command command, t_env *env_list)
{
	int		i;
	char	*path;
	char	**envp;

	i = 0;
	envp = env_to_string_list(env_list);
	if (!envp || command.args_c == 0 || str_len(command.args[0]) == 0)
		return (-1);
	path = search_command(command.args[0], search_env(env_list, "PATH"));
	if (path)
	{
		if (execve(path, command.args, envp) == -1)
			print_comm_err("Error executing command: ", path);
		free(path);
	}
	else
		print_comm_err("Command not found: ", command.args[0]);
	while (envp[i])
		free(envp[i++]);
	free(envp);
	return (0);
}
