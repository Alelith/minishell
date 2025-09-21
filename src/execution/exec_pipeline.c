/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 19:30:10 by acesteve          #+#    #+#             */
/*   Updated: 2025/09/21 11:27:18 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_cmd(char *cmd, char *name)
{
	int	res;

	res = str_compare_all(cmd, name);
	return (res);
}

static void	exec_child(t_shell shell, int i, int **pipes, char *line)
{
	if (shell.commands[i].infile != STDIN_FILENO)
		dup2(shell.commands[i].infile, STDIN_FILENO);
	else if (i > 0)
		dup2(pipes[i - 1][0], STDIN_FILENO);
	if (shell.commands[i].outfile != STDOUT_FILENO)
		dup2(shell.commands[i].outfile, STDOUT_FILENO);
	else if (i < shell.cmd_length - 1)
		dup2(pipes[i][1], STDOUT_FILENO);
	close_pipes(pipes, shell.cmd_length - 1);
	exec_builtin(shell, i, line);
	free_commands(shell.commands, shell.cmd_length);
	free(line);
	exit(0);
}

static void	wait_all(pid_t *pids, int num)
{
	int	idx;

	idx = 0;
	while (idx < num)
	{
		waitpid(pids[idx], NULL, 0);
		idx++;
	}
}

int	exec_builtin(t_shell shell, int index, char *line)
{
	if (is_cmd(shell.commands[index].args[0], "echo"))
		return (echo(shell.commands[index]));
	else if (is_cmd(shell.commands[index].args[0], "exit"))
		return (exit_exec(shell, line));
	else if (is_cmd(shell.commands[index].args[0], "cd"))
		return (cd(shell.commands[index]));
	else if (is_cmd(shell.commands[index].args[0], "pwd"))
		return (pwd());
	else if (is_cmd(shell.commands[index].args[0], "export"))
		return (export(shell.commands[index], shell.env_list,
				shell.env_list_cpy));
	else if (is_cmd(shell.commands[index].args[0], "unset"))
		return (unset(shell.commands[index], &shell.env_list));
	else if (is_cmd(shell.commands[index].args[0], "env"))
		return (env(shell.env_list));
	else if (is_cmd(shell.commands[index].args[0], "clear"))
		print_open_banner();
	else
		return (execute(shell.commands[index], shell.env_list));
	return (0);
}

void	exec_pipeline(t_shell shell, char *line)
{
	int		**pipes;
	pid_t	*pids;
	int		i;

	pipes = (int **)malloc(sizeof(int *) * (shell.cmd_length - 1));
	create_pipes(pipes, shell.cmd_length - 1);
	pids = (pid_t *)malloc(sizeof(pid_t) * shell.cmd_length);
	i = 0;
	while (i < shell.cmd_length)
	{
		if (shell.commands[i].args && shell.commands[i].args[0]
			&& is_cmd(shell.commands[i].args[0], "exit")
			&& shell.cmd_length == 1)
			handle_exit(shell, i, line, pipes, pids);
		pids[i] = fork();
		if (pids[i] == 0)
			exec_child(shell, i, pipes, line);
		i++;
	}
	close_pipes(pipes, shell.cmd_length - 1);
	free_pipes(pipes, shell.cmd_length - 1);
	free(pipes);
	wait_all(pids, shell.cmd_length);
	free(pids);
	free_commands(shell.commands, shell.cmd_length);
}
