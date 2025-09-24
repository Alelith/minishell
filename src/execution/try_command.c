/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 12:13:03 by acesteve          #+#    #+#             */
/*   Updated: 2025/09/24 11:26:38 by bvarea-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	switch_commands(t_shell *shell, int index, char *line)
{
	if (str_compare_all(shell->commands[index].args[0], "echo"))
		return (echo(shell->commands[index]));
	else if (str_compare_all(shell->commands[index].args[0], "exit"))
		return (exit_exec(*shell, line));
	else if (str_compare_all(shell->commands[index].args[0], "cd"))
		return (cd(shell, shell->commands[index]));
	else if (str_compare_all(shell->commands[index].args[0], "pwd"))
		return (pwd());
	else if (str_compare_all(shell->commands[index].args[0], "export"))
		return (export(shell->commands[index], shell->env_list,
				shell->env_list_cpy));
	else if (str_compare_all(shell->commands[index].args[0], "unset"))
		return (unset(shell->commands[index], &shell->env_list));
	else if (str_compare_all(shell->commands[index].args[0], "env"))
		return (env(shell->env_list));
	else if (str_compare_all(shell->commands[index].args[0], "clear"))
		print_open_banner();
	else
		return (execute(shell->commands[index], shell->env_list));
	return (0);
}

static void	close_and_free_pipes(int **pipes, t_shell shell)
{
	int	i;

	i = 0;
	while (i < shell.cmd_length - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		free(pipes[i++]);
	}
}

static int	*close_and_free(t_shell shell, int **pipes, int *pids)
{
	int	i;
	int	*statuses;

	i = 0;
	if ((shell.cmd_length == 1 && !is_builtin(shell.commands[i].args[0]))
		|| shell.cmd_length > 1)
	{
		statuses = malloc(shell.cmd_length * sizeof(int));
		if (!statuses)
			return (0);
	}
	else
		statuses = 0;
	close_and_free_pipes(pipes, shell);
	free(pipes);
	i = 0;
	if ((shell.cmd_length == 1 && !is_builtin(shell.commands[i].args[0]))
		|| shell.cmd_length > 1)
		while (i++ < shell.cmd_length)
			waitpid(pids[i - 1], &statuses[i - 1], 0);
	free(pids);
	free_commands(shell.commands, shell.cmd_length);
	return (statuses);
}

static int	fork_and_execute(t_shell *shell, int **pipes, char *line, int *pids)
{
	int	j;
	int	i;
	int	err;

	i = 0;
	err = 0;
	while (i < shell->cmd_length)
	{
		handle_heredoc(&shell->commands[i]);
		if (shell->commands[i].infile == -1)
		{
			write(1, "\n", 1);
			return (1);
		}
		if (shell->commands[i].args && shell->commands[i].args[0]
			&& is_builtin(shell->commands[i].args[0])
			&& shell->cmd_length == 1)
		{
			if (shell->commands[i].infile != STDIN_FILENO)
				dup2(shell->commands[i].infile, STDIN_FILENO);
			if (shell->commands[i].outfile != STDOUT_FILENO)
				dup2(shell->commands[i].outfile, STDOUT_FILENO);
			err = switch_commands(shell, i, line);
			if (str_compare_all(shell->commands[i].args[0], "exit"))
			{
				free(pipes);
				free(pids);
			}
			return (err);
		}
		pids[i] = fork();
		if (pids[i] == 0)
		{
			set_signals_child();
			if (shell->commands[i].infile != STDIN_FILENO)
				dup2(shell->commands[i].infile, STDIN_FILENO);
			else if (i > 0)
				dup2(pipes[i - 1][0], STDIN_FILENO);
			if (shell->commands[i].outfile != STDOUT_FILENO)
				dup2(shell->commands[i].outfile, STDOUT_FILENO);
			else if (i < shell->cmd_length - 1)
				dup2(pipes[i][1], STDOUT_FILENO);
			j = 0;
			while (j < shell->cmd_length - 1)
			{
				close(pipes[j][0]);
				close(pipes[j][1]);
				j++;
			}
			err = switch_commands(shell, i, line);
			if (shell->env_list)
				free_env(shell->env_list);
			if (shell->env_list_cpy)
				free_env(shell->env_list_cpy);
			free_commands(shell->commands, shell->cmd_length);
			free(line);
			exit(err);
		}
		i++;
	}
	return (err);
}

int	try_command(t_shell *shell, char *line)
{
	int		**pipes;
	pid_t	*pids;
	char	*temp;
	int		err;
	int		*statuses;
	int		i;

	i = 0;
	pipes = NULL;
	pids = NULL;
	if (line && *line)
		add_history(line);
	temp = line;
	line = str_trim(line, " \t\n\r");
	free (temp);
	shell->cmd_length = 0;
	shell->commands = tokenize(line, &shell->cmd_length, *shell);
	err = 0;
	if (shell->cmd_length > 0)
	{
		if (any_has_error(shell->commands, shell->cmd_length))
		{
			free_commands(shell->commands, shell->cmd_length);
			free(line);
			return (1);
		}
		pipes = (int **)malloc(sizeof(int *) * (shell->cmd_length - 1));
		while (i < shell->cmd_length - 1)
		{
			pipes[i] = (int *)malloc(sizeof(int) * 2);
			pipe(pipes[i++]);
		}
		pids = (pid_t *)malloc(sizeof(pid_t) * shell->cmd_length);
		err = fork_and_execute(shell, pipes, line, pids);
		statuses = close_and_free(*shell, pipes, pids);
		i = 0;
		while (statuses && i < shell->cmd_length)
			if (statuses[i++] != 0 && err == 0)
				err = statuses[i - 1];
	}
	free(line);
	return (err);
}
