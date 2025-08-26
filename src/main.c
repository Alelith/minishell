/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 10:56:34 by bvarea-k          #+#    #+#             */
/*   Updated: 2025/08/26 13:14:59 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>


int	main(void)
{
	t_command	*commands;
	char		*line;
	short		length;

	line = 0;
	length = 0;
	while (1)
	{
		if (line)
			free(line);
		print_format("%s", "conchita~> ");
		line = get_next_line(0);
		if (line == NULL)
		{
			print_format("Error reading line\n");
			return (1);
		}
		if (!str_compare_all(line, "\n"))
		{
			//Check
			commands = tokenize(line, &length);
			//Exec
			free_commands(commands, length);
		}
	}
}
