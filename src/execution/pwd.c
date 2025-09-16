/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 13:34:51 by bvarea-k          #+#    #+#             */
/*   Updated: 2025/09/16 09:16:21 by bvarea-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != false)
	{
		printf("%s\n", cwd);
		return (1);
	}
	print_comm_err("pwd: error retrieving current directory", "");
	return (0);
}
