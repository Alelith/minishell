/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 10:56:34 by bvarea-k          #+#    #+#             */
/*   Updated: 2025/09/09 17:35:04 by acesteve         ###   ########.fr       */
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
	write(1, OPEN_BANNER, str_len(OPEN_BANNER));
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
		set_signals_main();
		line = readline("littlepussy~> ");
		if (line == NULL)
		{
			write(2, "\n", 1);
			break;
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
				if (str_compare_all(shell.commands[i].args[0], "echo"))
					echo(shell.commands[i]);
				else if (str_compare_all(shell.commands[i].args[0], "exit"))
				{
					free(line);
					exit_exec(shell);
				}
				else if (str_compare_all(shell.commands[i].args[0], "cd"))
					cd(shell.commands[i]);
				else if (str_compare_all(shell.commands[i].args[0], "pwd"))
					pwd();
				else if (str_compare_all(shell.commands[i].args[0], "export"))
					export(shell.commands[i], shell.env_list);
				else if (str_compare_all(shell.commands[i].args[0], "unset"))
					unset(shell.commands[i], &shell.env_list);
				else if (str_compare_all(shell.commands[i].args[0], "env"))
					env(shell.env_list);
				else if (str_compare_all(shell.commands[i].args[0], "clear"))
					printf(OPEN_BANNER);
				else
					execute(shell.commands[i], shell.env_list);
				i++;
			}
			free_commands(shell.commands, shell.cmd_length);
		}
		free(line);
	}
}


