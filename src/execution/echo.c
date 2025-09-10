/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 09:32:45 by acesteve          #+#    #+#             */
/*   Updated: 2025/09/10 11:31:36 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(t_command command)
{
	int	flag;
	int	i;

	if (command.args_c > 0 && str_compare_n(command.args[1], "-n", 2))
		flag = 1;
	else
		flag = 0;
	if (flag)
		i = 2;
	else
		i = 1;
	while (i < command.args_c)
	{
		write(1, command.args[i], str_len(command.args[i]));
		i++;
	}
	if (!flag)
		write(1, "\n", 1);
	return (1);
}
