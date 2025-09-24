/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 10:56:34 by bvarea-k          #+#    #+#             */
/*   Updated: 2025/09/24 12:49:15 by bvarea-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_t_shell(t_shell *shell)
{
	if (shell->env_list)
		free_env(shell->env_list);
	if (shell->env_list_cpy)
		free_env(shell->env_list_cpy);
	exit(0);
}

static void	initialize_shell(t_shell *shell, char **envp)
{
	shell->env_list = set_env(envp);
	shell->env_list_cpy = set_env(envp);
	shell->std_in = dup(STDIN_FILENO);
	shell->std_out = dup(STDOUT_FILENO);
	print_open_banner();
	shell->cmd_length = 0;
	shell->last_exitcod = 0;
	shell->last_path = str_duplicate(getcwd(0, 0));
	set_signals_main();
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
	initialize_shell(&shell, envp);
	while (1)
	{
		switch_flag(1);
		line = readline("minishell~> ");
		if (line == NULL)
		{
			printf("\n");
			free_t_shell(&shell);
			break ;
		}
		switch_flag(0);
		if (check_command_line(line))
			shell.last_exitcod = try_command(&shell, line, 0);
		else
			free(line);
	}
}
