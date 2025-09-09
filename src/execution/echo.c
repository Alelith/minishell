/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 09:32:45 by acesteve          #+#    #+#             */
/*   Updated: 2025/09/09 12:13:53 by bvarea-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(t_command command)
{
	int	flag;
	int	i;

	if (command.args_c > 0 && str_compare_n(command.args[0], "-", 1))
		flag = 1;
	else
		flag = 0;
	i = 0;
	while (i < command.args_c)
	{
		write(1, command.args[i], str_len(command.args[i]));
		i++;
	}
	if (!flag)
		write(1, "\n", 1);
	return (1);
}
