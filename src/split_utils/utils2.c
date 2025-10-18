/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 11:11:18 by bvarea-k          #+#    #+#             */
/*   Updated: 2025/10/18 09:10:28 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_redir_pipe(char *set, char **tmp, char **line, int max)
{
	int	size;

	size = count_while(*line, set, max);
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
	if ((type == '\'' && **line == '\'') || (type == '\"' && **line == '\"'))
		increment_if_quote(line);
	if (**line && !isspace(**line))
	{
		if (**line == '\"')
			tmp = get_token(line, "\"", '\"', shell);
		else if (**line == '\'')
			tmp = get_token(line, "\'", '\'', shell);
		else if (!is_from_set(**line, "<>|"))
			tmp = get_token(line, " \t\n\r\'\"<>|", ' ', shell);
		if (tmp)
			free_and_assign(&res, tmp);
	}
	if (!res)
		res = str_duplicate("");
	return (res);
}

void	switch_assign_tmp(char **line, char **tmp, t_shell *shell)
{
	if (**line == '\"')
		*tmp = get_token(line, "\"", '\"', shell);
	else if (**line == '\'')
		*tmp = get_token(line, "\'", '\'', shell);
	else if (**line == '<')
		process_redir_pipe("<", tmp, line, 2);
	else if (**line == '>')
		process_redir_pipe(">", tmp, line, 2);
	else if (**line == '|')
		process_redir_pipe("|", tmp, line, 1);
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
