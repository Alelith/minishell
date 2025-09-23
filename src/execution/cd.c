/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 13:38:36 by bvarea-k          #+#    #+#             */
/*   Updated: 2025/09/23 10:46:05 by bvarea-k         ###   ########.fr       */
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

	if (command.args_c == 1 || (command.args_c == 2
			&& str_compare_all(command.args[0], "~"))
			|| !current_path)
	{
		path = str_duplicate(getenv("HOME"));
		if (!path)
		{
			free(current_path);
			print_comm_err("cd: HOME not set", "");
			return (NULL);
		}
	}
	else if (command.args_c == 2)
		path = str_join(current_path, command.args[1]);
	else
	{
		free(current_path);
		print_comm_err("cd: too many arguments", "");
		return (NULL);
	}
	return (path);
}

static int	handle_cd_error(char *path, char *current_path, char *arg)
{
	print_comm_err("cd: no such file or directory: ", arg);
	if (current_path)
		free(current_path);
	if (path)
		free(path);
	return (1);
}

int	cd(t_command command)
{
	char	*current_path;
	char	*path;

	current_path = 0;
	path = 0;
	if (command.args_c == 1 || (command.args_c == 2
		&& !str_compare_n(command.args[1], "/", 1)))
	{
		current_path = get_current_path();
		path = resolve_cd_path(command, current_path);
	}
	else if (command.args_c == 2)
		path = str_duplicate(command.args[1]);
	else
		return (1);
	if (chdir(path))
		return (handle_cd_error(path, current_path, command.args[1]));
	if (current_path)
		free(current_path);
	if (path)
		free(path);
	return (0);
}
