/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 10:56:34 by bvarea-k          #+#    #+#             */
/*   Updated: 2025/08/27 13:46:03 by bvarea-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>


int	main(void)
{
	int			i;
	t_command	*commands;
	char		*temp;
	char		*line;
	short		length;

	i = 0;
	line = 0;
	length = 0;
	while (1)
	{
		print_format("%s", "conchita~> ");
		line = get_next_line(0);
		if (line == NULL)
		{
			print_format("Error reading line\n");
			return (1);
		}
		temp = line;
		line = str_trim(line, "\n");
		free (temp);
		if (!str_compare_all(line, "\n"))
		{
			//Check
			length = 0;
			commands = tokenize(line, &length);
			while (i < length)
			{
				if (str_compare_all(commands[i].name, "echo"))
					echo(commands[i]);
				else if (str_compare_all(commands[i].name, "exit"))
				{
					free(line);
					free_commands(commands, length);
					exit_exec();
				}
				else if (str_compare_all(commands[i].name, "cd"))
					cd(commands[i]);
				else if (str_compare_all(commands[i].name, "pwd"))
					pwd();
				else if (str_compare_all(commands[i].name, "export"))
					print_format("export command not implemented yet\n");
				else if (str_compare_all(commands[i].name, "unset"))
					print_format("unset command not implemented yet\n");
				else if (str_compare_all(commands[i].name, "env"))
					print_format("env command not implemented yet\n");
				else
				{
					print_format("Command not found: %s\n", commands[i].name);
					break ;
				}
				i++;
			}
			//Exec
			free_commands(commands, length);
		}
		free(line);
	}
}
