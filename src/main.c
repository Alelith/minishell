/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 10:56:34 by bvarea-k          #+#    #+#             */
/*   Updated: 2025/08/28 12:55:17 by bvarea-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

int	main(int argc, char *argv[], char *envp[])
{
	int			i;
	t_command	*commands;
	char		*temp;
	char		*line;
	//char		**env_cpy;
	short		length;

	if (argc > 1 || argv[1])
	{
		write(2, "No arguments needed\n", 20);
		return (1);
	}
	i = 0;
	line = 0;
	length = 0;
	while (*envp)
	{
		write(1, *envp, ft_strlen(*envp));
		write(1, "\n", 1);
		envp++;
	}
	while (1)
	{
		write(1, "conchita~> ", 12);
		line = get_next_line(0);
		if (line == NULL)
		{
			write(2, "Error reading line\n", 20);
			return (1);
		}
		temp = line;
		line = str_trim(line, "\n");
		free (temp);
		if (!str_compare_all(line, "\n"))
		{
			length = 0;
			i = 0;
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
					write(1, "export command not implemented yet\n", 36);
				else if (str_compare_all(commands[i].name, "unset"))
					write(1, "unset command not implemented yet\n", 35);
				else if (str_compare_all(commands[i].name, "env"))
					write(1, "env command not implemented yet\n", 32);
				else
				{
					write(2, "Command not found: ", 19);
					write(2, commands[i].name, ft_strlen(commands[i].name));
					write(2, "\n", 1);
					break ;
				}
				i++;
			}
			free_commands(commands, length);
		}
		free(line);
	}
}
