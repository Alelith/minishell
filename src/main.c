/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 10:56:34 by bvarea-k          #+#    #+#             */
/*   Updated: 2025/09/18 11:39:16 by bvarea-k         ###   ########.fr       */
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
		export(shell.commands[index], shell.env_list, shell.env_list_cpy);
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

	if (line && *line)
		add_history(line);
	temp = line;
	line = str_trim(line, " \t\n\r");
	free (temp);
	if (!str_compare_all(line, "\n"))
	{
		shell.cmd_length = 0;
		i = 0;
		shell.commands = tokenize(line, &shell.cmd_length, shell);
		while (i < shell.cmd_length
			&& !any_has_error(shell.commands, shell.cmd_length))
		{
			dup2(shell.commands[i].infile, STDIN_FILENO);
			dup2(shell.commands[i].outfile, STDOUT_FILENO);
			switch_commands(shell, i, line);
			dup2(shell.std_in, STDIN_FILENO);
			dup2(shell.std_out, STDOUT_FILENO);
			i++;
		}
		free_commands(shell.commands, shell.cmd_length);
	}
	free(line);
}

static void	free_t_shell(t_shell *shell)
{
	if (shell->env_list)
		free_env(shell->env_list);
	if (shell->env_list_cpy)
		free_env(shell->env_list_cpy);
	exit(0);
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
	shell.env_list_cpy = set_env(envp);
	shell.std_in = dup(STDIN_FILENO);
	shell.std_out = dup(STDOUT_FILENO);
	print_open_banner();
	shell.cmd_length = 0;
	set_signals_main();
	while (1)
	{
		line = readline("minishell~> ");
		if (line == NULL)
		{
			printf("\n");
			free_t_shell(&shell);
			break ;
		}
		try_command(shell, line);
	}
}
