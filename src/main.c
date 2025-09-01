/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 10:56:34 by bvarea-k          #+#    #+#             */
/*   Updated: 2025/09/01 13:24:23 by bvarea-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_shell		shell;
	int			i;
	char		*temp;
	char		*line;

	shell.env_list = set_env(envp);
	if (argc > 1 || argv[1])
	{
		write(2, "No arguments needed\n", 20);
		return (1);
	}
	i = 0;
	line = 0;
	shell.cmd_length = 0;
	while (1)
	{
		line = readline("conchita~> ");
		if (line == NULL)
		{
			write(2, "Error reading line\n", 20);
			return (1);
		}
		if (line && *line)
			add_history(line);
		temp = line;
		line = str_trim(line, "\n");
		free (temp);
		if (!str_compare_all(line, "\n"))
		{
			shell.cmd_length = 0;
			i = 0;
			shell.commands = tokenize(line, &shell.cmd_length);
			while (i < shell.cmd_length)
			{
				if (str_compare_all(shell.commands[i].name, "echo"))
					echo(shell.commands[i]);
				else if (str_compare_all(shell.commands[i].name, "exit"))
				{
					free(line);
					exit_exec();
				}
				else if (str_compare_all(shell.commands[i].name, "cd"))
					cd(shell.commands[i]);
				else if (str_compare_all(shell.commands[i].name, "pwd"))
					pwd();
				else if (str_compare_all(shell.commands[i].name, "export"))
					export(shell.commands[i], shell.env_list);
				else if (str_compare_all(shell.commands[i].name, "unset"))
					write(1, "unset command not implemented yet\n", 35);
				else if (str_compare_all(shell.commands[i].name, "env"))
					env(shell.env_list);
				else if (str_compare_all(shell.commands[i].name, "clear"))
					printf("\033c");
				else if (str_compare_n(shell.commands[i].name, "./", 2))
					write(1, "./ command not implemented yet\n", 31);
				else
				{
					write(2, "Command not found: ", 19);
					write(2, shell.commands[i].name, str_len(shell.commands[i].name));
					write(2, "\n", 1);
					break ;
				}
				i++;
			}
			free_commands(shell.commands, shell.cmd_length);
		}
		free(line);
	}
}


