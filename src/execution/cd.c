/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 13:38:36 by bvarea-k          #+#    #+#             */
/*   Updated: 2025/09/01 09:28:06 by bvarea-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Diferencia entre getcwd y getenv: 
//getcwd: saber dónde estás.
//getenv: leer rutas definidas en variables de entorno (char * ?)

int	cd(t_command command)
{
	char	*current_path;
	char	*path;

	current_path = str_join(getcwd(0, 0), "/");
	if (!current_path)
		return (1);
	if (command.args_c == 0 || (command.args_c == 1
			&& str_compare_all(command.args[0], "~")))
	{
		path = str_duplicate(getenv("HOME"));
		if (!path)
		{
			free(current_path);
			write(2, "cd: HOME not set\n", 18);
			return (1);
		}
	}
	else if (command.args_c == 1)
		path = str_join(current_path, command.args[0]);
	else
	{
		free(current_path);
		write(2, "cd: too many arguments\n", 24);
		return (1);
	}
	if (chdir(path))
	{
		free(current_path);
		free(path);
		write(2, "cd: no such file or directory: ", 31);
		write(2, command.args[0], str_len(command.args[0]));
		write(2, "\n", 1);
		return (1);
	}
	free(current_path);
	free(path);
	return (0);
}
