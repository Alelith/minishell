/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 12:13:03 by acesteve          #+#    #+#             */
/*   Updated: 2025/09/21 12:18:21 by acesteve         ###   ########.fr       */
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

void	try_command(t_shell shell, char *line)
{
	int		num_cmds;
	int		**pipes;
	pid_t	*pids;
	char	*temp;
	int		i;

	num_cmds = 0;
	pipes = NULL;
	pids = NULL;
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
		num_cmds = shell.cmd_length;
		if (num_cmds > 0)
		{
			if (any_has_error(shell.commands, shell.cmd_length))
			{
				free_commands(shell.commands, shell.cmd_length);
				free(line);
				return ;
			}
			pipes = (int **)malloc(sizeof(int *) * (num_cmds - 1));
			for (i = 0; i < num_cmds - 1; i++)
			{
				pipes[i] = (int *)malloc(sizeof(int) * 2);
				pipe(pipes[i]);
			}
			pids = (pid_t *)malloc(sizeof(pid_t) * num_cmds);
			for (i = 0; i < num_cmds; i++)
			{
				if (shell.commands[i].args && shell.commands[i].args[0]
					&& str_compare_all(shell.commands[i].args[0], "exit")
					&& num_cmds == 1)
				{
					if (shell.commands[i].infile != STDIN_FILENO)
						dup2(shell.commands[i].infile, STDIN_FILENO);
					if (shell.commands[i].outfile != STDOUT_FILENO)
						dup2(shell.commands[i].outfile, STDOUT_FILENO);
					switch_commands(shell, i, line);
					free_commands(shell.commands, shell.cmd_length);
					free(pipes);
					free(pids);
					free(line);
					return ;
				}
				pids[i] = fork();
				if (pids[i] == 0)
				{
					if (shell.commands[i].infile != STDIN_FILENO)
						dup2(shell.commands[i].infile, STDIN_FILENO);
					else if (i > 0)
						dup2(pipes[i - 1][0], STDIN_FILENO);
					if (shell.commands[i].outfile != STDOUT_FILENO)
						dup2(shell.commands[i].outfile, STDOUT_FILENO);
					else if (i < num_cmds - 1)
						dup2(pipes[i][1], STDOUT_FILENO);
					for (int j = 0; j < num_cmds - 1; j++)
					{
						close(pipes[j][0]);
						close(pipes[j][1]);
					}
					switch_commands(shell, i, line);
					free_commands(shell.commands, shell.cmd_length);
					free(line);
					exit(0);
				}
			}
			for (i = 0; i < num_cmds - 1; i++)
			{
				close(pipes[i][0]);
				close(pipes[i][1]);
				free(pipes[i]);
			}
			free(pipes);
			for (i = 0; i < num_cmds; i++)
				waitpid(pids[i], NULL, 0);
			free(pids);
			free_commands(shell.commands, shell.cmd_length);
		}
	}
	free(line);
}
