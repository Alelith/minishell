/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 09:32:45 by acesteve          #+#    #+#             */
/*   Updated: 2025/08/27 10:09:42 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(t_command command)
{
	int	flag;
	int	i;

	flag = command.flag ? 1 : 0;
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
