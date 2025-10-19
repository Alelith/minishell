/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 09:32:45 by acesteve          #+#    #+#             */
/*   Updated: 2025/10/19 15:55:30 by bvarea-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_all_n(char *ptr)
{
	while (*ptr)
	{
		if (*ptr != 'n')
			return (0);
		ptr++;
	}
	return (1);
}

int	echo(t_command command)
{
	int	flag;
	int	i;

	flag = 0;
	i = 1;
	while (i < command.args_c && command.args[i] && command.args[i][0] == '-'
			&& is_all_n(&command.args[i][1]))
	{
		flag = 1;
		i++;
	}
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
