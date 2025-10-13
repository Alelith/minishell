/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 18:15:08 by acesteve          #+#    #+#             */
/*   Updated: 2025/10/14 00:22:06 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_until(char *line, const char *delimiters)
{
	int	res;

	res = 0;
	while (line[res] && !is_from_set(line[res], delimiters))
		res++;
	return (res);
}

static int	count_while(char *line, const char *delimiters)
{
	int	res;

	res = 0;
	while (line[res] && is_from_set(line[res], delimiters))
		res++;
	return (res);
}

static char	*get_value_from_env(char **line, t_shell *shell)
{
	char	*res;
	char	*tmp;
	int		size;

	tmp = 0;
	if (*(*line + 1) == '?')
	{
		*line = *line + 2;
		return (int_to_str(shell->last_exitcod));
	}
	else
	{
		size = count_until(*line + 1, " \t\n\r\"\'<>|$");
		tmp = str_substring(*line, 1, size);
		res = search_env(shell->env_list, tmp);
		free (tmp);
		*line = *line + size + 1;
		return (str_duplicate(res));
	}
}

static char	*get_token(char **line, const char *delimiters, char type
		, t_shell *shell)
{
	int		size;
	char	*tmp;
	char	*res;
	char	*old_res;

	res = 0;
	if (**line == '\'' || **line == '\"')
		*line = *line + 1;
	while (**line && !is_from_set(**line, delimiters))
	{
		if (**line == '$' && shell && (type == '\"' || type == ' '))
			tmp = get_value_from_env(line, shell);
		else
		{
			tmp = str_substring(*line, 0, 1);
			(*line)++;
		}
		old_res = res;
		res = str_join(res, tmp);
		free(old_res);
		free(tmp);
	}
	if (**line && !isspace(**line))
	{
		if (**line == '\"')
			tmp = get_token(line, "\"", '\"', shell);
		else if (**line == '\'')
			tmp = get_token(line, "\'", '\'', shell);
		else if (type != '<' && type != '>' && type != '|')
			tmp = get_token(line, " \t\n\r\'\"<>|", ' ', shell);
		else if (type == '<')
		{
			size = count_while(*line, "<");
			tmp = str_substring(*line, 0, size);
			*line = *line + size;
		}
		else if (type == '>')
		{
			size = count_while(*line, ">");
			tmp = str_substring(*line, 0, size);
			*line = *line + size;
		}
		else if (type == '|')
		{
			size = count_while(*line, "|");
			tmp = str_substring(*line, 0, size);
			*line = *line + size;
		}
		old_res = res;
		res = str_join(res, tmp);
		free(old_res);
		free(tmp);
	}
	return (res);
}

t_token	*split_command(char *line, t_shell *shell)
{
	char	type;
	char	*tmp;
	int		argc;
	t_token	*args;

	argc = 0;
	args = 0;
	while (line && *line)
	{
		tmp = 0;
		while (*line && isspace(*line))
			line++;
		type = *line;
		if (*line == '\"')
			tmp = get_token(&line, "\"", '\"', shell);
		else if (*line == '\'')
			tmp = get_token(&line, "\'", '\'', shell);
		else if (*line == '<')
			tmp = get_token(&line, "<", '<', shell);
		else if (*line == '>')
			tmp = get_token(&line, ">", '>', shell);
		else if (*line == '|')
			tmp = get_token(&line, "|", '|', shell);
		else if (*line)
			tmp = get_token(&line, " \t\n\r\'\"<>|", ' ', shell);
		if (tmp)
		{
			args = reallocation(args, sizeof(t_token) * (argc + 1),
					sizeof(t_token) * argc);
			args[argc].token = tmp;
			if (type == '\'' || type == '\"')
				args[argc].is_literal = true;
			else
				args[argc].is_literal = false;
			argc++;
		}
	}
	args = reallocation(args, sizeof(t_token) * (argc + 1),
			sizeof(t_token) * argc);
	return (args);
}
