/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 13:38:36 by bvarea-k          #+#    #+#             */
/*   Updated: 2025/10/19 18:52:12 by bvarea-k         ###   ########.fr       */
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
			&& str_compare_all(command.args[1], "~")))
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
		return (NULL);
	}
	return (path);
}

static int	handle_cd_error(char *path, char *current_path, char *arg)
{
	print_comm_err("cd: cannot access file or directory: ", arg);
	if (current_path)
		free(current_path);
	if (path)
		free(path);
	return (1);
}

static int	execute_cd(t_command command, char **path,
	char **current_path, t_shell *shell)
{
	if (str_compare_all(command.args[1], "-") || str_compare_all(*path, ".."))
	{
		if (*path)
			free(*path);
		*path = str_duplicate(shell->last_path);
		while (access(*path, F_OK) != 0)
		{
			free(*path);
			shell->last_path = get_last_path(shell->last_path);
			*path = str_duplicate(shell->last_path);
		}
		if (str_len(*path) == 0)
		{
			free(*path);
			*path = str_duplicate("/");
		}
	}
	if (chdir(*path))
		return (handle_cd_error(*path, *current_path, command.args[1]));
	if (*current_path)
	{
		free(shell->last_path);
		shell->last_path = str_duplicate(*current_path);
	}
	return (0);
}

int	cd(t_shell *shell, t_command command)
{
	char	*current_path;
	char	*path;

	current_path = get_current_path();
	path = 0;
	if (command.args_c == 1 || (command.args_c == 2
			&& !str_compare_n(command.args[1], "/", 1)))
		path = resolve_cd_path(command, current_path);
	else if (command.args_c == 2 && !str_compare_all(command.args[1], "-"))
		path = str_duplicate(command.args[1]);
	else
	{
		free(current_path);
		return (print_comm_err("cd: too many arguments", ""));
	}
	if (execute_cd(command, &path, &current_path, shell))
		return (1);
	free(path);
	free(current_path);
	return (0);
}
