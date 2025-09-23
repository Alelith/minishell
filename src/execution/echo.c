/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 09:32:45 by acesteve          #+#    #+#             */
/*   Updated: 2025/09/23 10:49:49 by bvarea-k         ###   ########.fr       */
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
	while (i < command.args_c - 1)
	{
		printf("%s ", command.args[i]);
		i++;
	}
	if (command.args[i])
		printf("%s", command.args[i]);
	if (!flag)
		printf("\n");
	return (0);
}
