/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 10:41:15 by bvarea-k          #+#    #+#             */
/*   Updated: 2025/09/10 09:22:34 by acesteve         ###   ########.fr       */
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
	if (!envp || command.args_c == 0)
		return (-1);
	path = search_command(command.args[0], search_env(env_list, "PATH"));
	if (path)
	{
		int pid = fork();
		if (pid == 0 && execve(path, command.args, envp) == -1)
			printf("Error executing command: %s\n", path);
		if (pid > 0)
			waitpid(pid, 0, 0);
		free(path);
	}
	else
	{
		printf("Command not found: %s\n", command.args[0]);
	}
	while (envp[i])
		free(envp[i++]);
	free(envp);
	return (0);
}
