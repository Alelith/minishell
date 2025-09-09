/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 12:28:43 by acesteve          #+#    #+#             */
/*   Updated: 2025/09/09 16:40:09 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_commands(t_command *commands, unsigned short length)
{
	while (length--)
	{
		while (commands[length].args_c--)
			free(commands[length].args[commands[length].args_c]);
		if (commands[length].args)
			free(commands[length].args);
	}
	free(commands);
}
