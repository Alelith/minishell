/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 11:11:18 by bvarea-k          #+#    #+#             */
/*   Updated: 2025/10/14 13:30:42 by bvarea-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_redir_pipe(char *set, char **tmp, char **line)
{
	int	size;

	size = count_while(*line, set);
	*tmp = str_substring(*line, 0, size);
	*line = *line + size;
}

void	increment_if_quote(char **line)
{
	if (**line == '\'' || **line == '\"')
		*line = *line + 1;
}

char	*get_token(char **line, const char *delimiters, char type,
			t_shell *shell)
{
	char	*tmp;
	char	*res;

	tmp = 0;
	res = 0;
	increment_if_quote(line);
	while (**line && !is_from_set(**line, delimiters))
		process_result(line, &res, shell, type);
	increment_if_quote(line);
	if (**line && !isspace(**line))
	{
		if (**line == '\"')
			tmp = get_token(line, "\"", '\"', shell);
		else if (**line == '\'')
			tmp = get_token(line, "\'", '\'', shell);
		else if (type != '<' && type != '>' && type != '|')
			tmp = get_token(line, " \t\n\r\'\"<>|", ' ', shell);
		else if (type == '<')
			process_redir_pipe("<", &tmp, line);
		else if (type == '>')
			process_redir_pipe(">", &tmp, line);
		else if (type == '|')
			process_redir_pipe("|", &tmp, line);
		free_and_assign(&res, tmp);
	}
	return (res);
}

void	switch_assign_tmp(char **line, char **tmp, t_shell *shell)
{
	if (**line == '\"')
		*tmp = get_token(line, "\"", '\"', shell);
	else if (**line == '\'')
		*tmp = get_token(line, "\'", '\'', shell);
	else if (**line == '<')
		*tmp = get_token(line, "<", '<', shell);
	else if (**line == '>')
		*tmp = get_token(line, ">", '>', shell);
	else if (**line == '|')
		*tmp = get_token(line, "|", '|', shell);
	else if (**line)
		*tmp = get_token(line, " \t\n\r\'\"<>|", ' ', shell);
}

void	increment_args(t_token **args, int *argc, char *tmp, char type)
{
	*args = reallocation(*args, sizeof(t_token) * (*argc + 1),
			sizeof(t_token) * *argc);
	(*args)[*argc].token = tmp;
	if (type == '\'' || type == '\"')
		(*args)[*argc].is_literal = true;
	else
		(*args)[*argc].is_literal = false;
	*argc = *argc + 1;
}
