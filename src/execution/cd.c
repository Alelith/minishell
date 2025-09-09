/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 13:38:36 by bvarea-k          #+#    #+#             */
/*   Updated: 2025/09/09 12:23:52 by bvarea-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_current_path(void)
{
	char	*cwd;
	char	*current_path;

	cwd = getcwd(0, 0);
	if (!cwd)
		return (NULL);
	current_path = str_join(cwd, "/");
	free(cwd);
	return (current_path);
}

static char	*resolve_cd_path(t_command command, char *current_path)
{
	char	*path;

	if (command.args_c == 0 || (command.args_c == 1
			&& str_compare_all(command.args[0], "~")))
	{
		path = str_duplicate(getenv("HOME"));
		if (!path)
		{
			free(current_path);
			write(2, "cd: HOME not set\n", 18);
			return (NULL);
		}
	}
	else if (command.args_c == 1)
		path = str_join(current_path, command.args[0]);
	else
	{
		free(current_path);
		write(2, "cd: too many arguments\n", 24);
		return (NULL);
	}
	return (path);
}

static int	handle_cd_error(char *path, char *current_path, char *arg)
{
	free(current_path);
	free(path);
	write(2, "cd: no such file or directory: ", 31);
	write(2, arg, str_len(arg));
	write(2, "\n", 1);
	return (1);
}

int	cd(t_command command)
{
	char	*current_path;
	char	*path;

	current_path = get_current_path();
	if (!current_path)
		return (1);
	path = resolve_cd_path(command, current_path);
	if (!path)
		return (1);
	if (chdir(path))
		return (handle_cd_error(path, current_path, command.args[0]));
	free(current_path);
	free(path);
	return (0);
}
