/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 10:41:15 by bvarea-k          #+#    #+#             */
/*   Updated: 2025/09/09 13:32:41 by bvarea-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute(t_command command, t_env *env_list)
{
	int		i;
	char	*path;
	char	**envp;
	char *argv[] = {"/bin/ls", "-la", NULL};

	i = 0;
	if (!command.name)
		return (-1);
	envp = env_to_string_list(env_list);
	if (!envp)
		return (-1);
	path = search_command(command.name, search_env(env_list, "PATH"));
	print_format("%s\n", command.args[0]);
	int pid = fork();
	if (pid == 0 && path && execve(path, argv, envp) == -1)
		printf("Error executing command: %s\n", path);
	if (pid > 0)
		waitpid(pid, 0, 0);
	if (path)
		free(path);
	while (envp[i])
		free(envp[i++]);
	free(envp);
	return (0);
}
