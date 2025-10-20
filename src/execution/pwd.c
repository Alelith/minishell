/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 13:34:51 by bvarea-k          #+#    #+#             */
/*   Updated: 2025/10/20 10:20:36 by bvarea-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(t_command cmd)
{
	char	cwd[2048];

	if (cmd.args_c > 1)
	{
		print_comm_err("pwd: Too many arguments", "");
		return (1);
	}
	if (getcwd(cwd, sizeof(cwd)) != false)
	{
		printf("%s\n", cwd);
		return (0);
	}
	print_comm_err("pwd: error retrieving current directory", "");
	return (0);
}
