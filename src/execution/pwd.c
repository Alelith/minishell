/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 13:34:51 by bvarea-k          #+#    #+#             */
/*   Updated: 2025/09/01 09:18:46 by bvarea-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != false)
	{
		write(1, cwd, str_len(cwd));
		write(1, "\n", 1);
		return (0);
	}
	write(2, "pwd: error retrieving current directory\n", 40);
	return (1);
}
