/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 13:38:36 by bvarea-k          #+#    #+#             */
/*   Updated: 2025/08/27 17:06:06 by bvarea-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Diferencia entre getcwd y getenv: 
//getcwd: saber dónde estás.
//getenv: leer rutas definidas en variables de entorno (char * ?)

int	cd(t_command command)
{
	char	*current_path;
	char	*new_path;
	
	current_path = getcwd(NULL, 0); //Should we use it in pwd in case the path is too long?
	//Might need to free it later.
	if (!current_path)
	{
		perror("");
		return (1);
	}
	
	/*opendir(command.args[1]); Check if the current directory is accessible*/
	if (chdir(command.args[1]) != 0)
		return (1);
	return (0);
}
