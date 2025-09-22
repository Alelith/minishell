/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 12:13:03 by acesteve          #+#    #+#             */
/*   Updated: 2025/09/22 15:40:44 by acesteve         ###   ########.fr       */
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

static void	close_and_free(t_shell shell, int **pipes, int *pids)
{
	int	i;

	i = 0;
	while (i < shell.cmd_length - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		free(pipes[i++]);
	}
	free(pipes);
	i = 0;
	if ((shell.cmd_length == 1 && !is_builtin(shell.commands[i].args[0])) || shell.cmd_length > 1)
		while (i < shell.cmd_length)
			waitpid(pids[i++], NULL, 0);
	free(pids);
	free_commands(shell.commands, shell.cmd_length);
}

static void	fork_and_execute(t_shell shell, int **pipes, char *line, int *pids)
{
	int	j;
	int	i;

	i = 0;
	while (i < shell.cmd_length)
	{
		handle_heredoc(&shell.commands[i]);
		if (shell.commands[i].infile == -1)
		{
			write(1, "\n", 1);
			return ;
		}
		if (shell.commands[i].args && shell.commands[i].args[0]
			&& is_builtin(shell.commands[i].args[0])
			&& shell.cmd_length == 1)
		{
			if (shell.commands[i].infile != STDIN_FILENO)
				dup2(shell.commands[i].infile, STDIN_FILENO);
			if (shell.commands[i].outfile != STDOUT_FILENO)
				dup2(shell.commands[i].outfile, STDOUT_FILENO);
			switch_commands(shell, i, line);
			if (str_compare_all(shell.commands[i].args[0], "exit"))
			{
				free(pipes);
				free(pids);
			}
			break ;
		}
		pids[i] = fork();
		if (pids[i] == 0)
		{
			set_signals_child();
			if (shell.commands[i].infile != STDIN_FILENO)
				dup2(shell.commands[i].infile, STDIN_FILENO);
			else if (i > 0)
				dup2(pipes[i - 1][0], STDIN_FILENO);
			if (shell.commands[i].outfile != STDOUT_FILENO)
				dup2(shell.commands[i].outfile, STDOUT_FILENO);
			else if (i < shell.cmd_length - 1)
				dup2(pipes[i][1], STDOUT_FILENO);
			j = 0;
			while (j < shell.cmd_length - 1)
			{
				close(pipes[j][0]);
				close(pipes[j][1]);
				j++;
			}
			switch_commands(shell, i, line);
			if (shell.env_list)
				free_env(shell.env_list);
			if (shell.env_list_cpy)
				free_env(shell.env_list_cpy);
			free_commands(shell.commands, shell.cmd_length);
			free(line);
			exit(0);
		}
		i++;
	}
}

void	try_command(t_shell shell, char *line)
{
	int		**pipes;
	pid_t	*pids;
	char	*temp;
	int		i;

	i = 0;
	pipes = NULL;
	pids = NULL;
	if (line && *line)
		add_history(line);
	temp = line;
	line = str_trim(line, " \t\n\r");
	free (temp);
	shell.cmd_length = 0;
	shell.commands = tokenize(line, &shell.cmd_length, shell);
	g_is_on_prompt = 0;
	if (shell.cmd_length > 0)
	{
		if (any_has_error(shell.commands, shell.cmd_length))
		{
			free_commands(shell.commands, shell.cmd_length);
			free(line);
			return ;
		}
		pipes = (int **)malloc(sizeof(int *) * (shell.cmd_length - 1));
		while (i < shell.cmd_length - 1)
		{
			pipes[i] = (int *)malloc(sizeof(int) * 2);
			pipe(pipes[i++]);
		}
		pids = (pid_t *)malloc(sizeof(pid_t) * shell.cmd_length);
		fork_and_execute(shell, pipes, line, pids);
		close_and_free(shell, pipes, pids);
	}
	free(line);
}
