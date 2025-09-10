/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 10:56:34 by bvarea-k          #+#    #+#             */
/*   Updated: 2025/09/10 12:33:29 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	switch_commands(t_shell shell, int index, char *line)
{
	if (str_compare_all(shell.commands[index].args[0], "echo"))
		echo(shell.commands[index]);
	else if (str_compare_all(shell.commands[index].args[0], "exit"))
		exit_exec(shell, line);
	else if (str_compare_all(shell.commands[index].args[0], "cd"))
		cd(shell.commands[index]);
	else if (str_compare_all(shell.commands[index].args[0], "pwd"))
		pwd();
	else if (str_compare_all(shell.commands[index].args[0], "export"))
		export(shell.commands[index], shell.env_list);
	else if (str_compare_all(shell.commands[index].args[0], "unset"))
		unset(shell.commands[index], &shell.env_list);
	else if (str_compare_all(shell.commands[index].args[0], "env"))
		env(shell.env_list);
	else if (str_compare_all(shell.commands[index].args[0], "clear"))
		print_open_banner();
	else
		execute(shell.commands[index], shell.env_list);
}

static void	try_command(t_shell shell, char *line)
{
	char		*temp;
	int			i;

	set_signals_main();
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
			switch_commands(shell, i, line);
			i++;
		}
		free_commands(shell.commands, shell.cmd_length);
	}
	free(line);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_shell		shell;
	char		*line;

	if (argc > 1 || argv[1])
	{
		print_comm_err("No arguments needed", "");
		return (1);
	}
	shell.env_list = set_env(envp);
	print_open_banner();
	shell.cmd_length = 0;
	while (1)
	{
		line = readline("littlepussy~> ");
		if (line == NULL)
		{
			printf("\n");
			break ;
		}
		try_command(shell, line);
	}
}
