/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 10:41:15 by bvarea-k          #+#    #+#             */
/*   Updated: 2025/09/23 10:55:12 by bvarea-k         ###   ########.fr       */
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
		return (1);
	path = search_command(command.args[0], search_env(env_list, "PATH"));
	if (path)
	{
		if (execve(path, command.args, envp) == -1)
			return (print_comm_err("Error executing command: ", path));
		free(path);
	}
	else
		return (print_comm_err("Command not found: ", command.args[0]));
	while (envp[i])
		free(envp[i++]);
	free(envp);
	return (0);
}
