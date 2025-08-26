/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 12:28:43 by acesteve          #+#    #+#             */
/*   Updated: 2025/08/26 13:06:35 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_commands(t_command *commands, short length)
{
	while (length--)
	{
		while (commands[length].args_c--)
			free(commands[length].args[commands[length].args_c]);
		if (commands[length].name)
			free(commands[length].name);
		if (commands[length].flag)
			free(commands[length].flag);
		if (commands[length].args)
			free(commands[length].args);
		if (commands[length].redirections)
			free(commands[length].redirections);
	}
	free(commands);
}
