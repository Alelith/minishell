/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 10:56:34 by bvarea-k          #+#    #+#             */
/*   Updated: 2025/10/20 10:45:07 by bvarea-k         ###   ########.fr       */
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
	char	*cwd;

	shell->env_list = set_env(envp);
	shell->env_list_cpy = set_env(envp);
	shell->std_in = dup(STDIN_FILENO);
	shell->std_out = dup(STDOUT_FILENO);
	print_open_banner();
	shell->cmd_length = 0;
	shell->last_exitcod = 0;
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		shell->last_path = str_duplicate(cwd);
		free(cwd);
	}
	else
		shell->last_path = NULL;
	set_signals_main();
}

int	main(int argc, char *argv[], char *envp[])
{
	t_shell		shell;
	char		*line;

	if (argc > 1 || argv[1])
		return (print_comm_err("No arguments needed", ""));
	initialize_shell(&shell, envp);
	while (1)
	{
		switch_flag(1);
		set_signals_main();
		line = readline("minishell~> ");
		if (line == NULL)
		{
			print_close_banner();
			free_t_shell(&shell);
			break ;
		}
		switch_flag(0);
		if (check_command_line(line))
			shell.last_exitcod = try_command(&shell, line);
		else
			free(line);
	}
	return (0);
}
