/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   any_has_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 10:45:42 by bvarea-k          #+#    #+#             */
/*   Updated: 2025/09/17 10:49:05 by bvarea-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	any_has_error(t_command *cmd, unsigned short cmd_count)
{
	unsigned short	i;

	i = 0;
	while (i < cmd_count)
	{
		if (cmd[i].has_error)
			return (1);
		i++;
	}
	return (0);
}
