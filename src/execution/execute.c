/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 10:41:15 by bvarea-k          #+#    #+#             */
/*   Updated: 2025/09/10 11:26:04 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute(t_command command, t_env *env_list)
{
	int		i;
	int		pid;
	char	*path;
	char	**envp;

	i = 0;
	envp = env_to_string_list(env_list);
	if (!envp || command.args_c == 0)
		return (-1);
	path = search_command(command.args[0], search_env(env_list, "PATH"));
	if (path)
	{
		pid = fork();
		if (pid == 0 && execve(path, command.args, envp) == -1)
			print_comm_err("Error executing command: ", path);
		if (pid > 0)
			waitpid(pid, 0, 0);
		free(path);
	}
	else
		print_comm_err("Command not found: ", command.args[0]);
	while (envp[i])
		free(envp[i++]);
	free(envp);
	return (0);
}
