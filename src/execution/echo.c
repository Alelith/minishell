/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 09:32:45 by acesteve          #+#    #+#             */
/*   Updated: 2025/08/27 16:21:20 by bvarea-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(t_command command)
{
	int	flag;
	int	i;

	if (command.flag)
		flag = 1;
	else
		flag = 0;
	i = 0;
	while (i < command.args_c)
	{
		//TODO: cambiar a write o printf
		print_format(i != command.args_c - 1 ? "%s " : "%s", command.args[i]);
		i++;
	}
	if (!flag)
		print_format("\n");
	return (1);
}
