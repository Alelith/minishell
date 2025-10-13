/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 10:41:15 by bvarea-k          #+#    #+#             */
/*   Updated: 2025/10/13 12:00:57 by bvarea-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_all_spaces(char *str)
{
	while (str && *str)
	{
		if (!is_from_set(*str, " \n\t\r"))
			return (0);
		str++;
	}
	return (1);
}

int	execute(t_command command, t_env *env_list)
{
	char	*path;
	char	**envp;
	int		err_code;
	int		i;

	i = 0;
	err_code = 0;
	envp = env_to_string_list(env_list);
	if (!envp)
		return (1);
	path = search_command(command.args[0], search_env(env_list, "PATH"));
	if (path)
	{
		if (!is_all_spaces(path) && execve(path, command.args, envp) == -1)
			err_code = print_comm_err("Error executing command: ", path);
		free(path);
	}
	else
		err_code = print_comm_err("Command not found: ", command.args[0]);
	while (envp[i])
		free(envp[i++]);
	free(envp);
	return (err_code);
}
