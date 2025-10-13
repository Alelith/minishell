/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 18:15:08 by acesteve          #+#    #+#             */
/*   Updated: 2025/10/13 21:27:42 by acesteve         ###   ########.fr       */
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
		else
			tmp = get_token(line, " \t\n\r\'\"<>|", ' ', shell);
		old_res = res;
		res = str_join(res, tmp);
		free(old_res);
		free(tmp);
	}
	return (res);
}

char	**split_command(char *line, t_shell *shell)
{
	char	*tmp;
	int		argc;
	char	**args;

	argc = 0;
	args = 0;
	while (line && *line)
	{
		tmp = 0;
		while (*line && isspace(*line))
			line++;
		if (*line == '\"')
			tmp = get_token(&line, "\"", '\"', shell);
		else if (*line == '\'')
			tmp = get_token(&line, "\'", '\'', shell);
		else if (*line)
			tmp = get_token(&line, " \t\n\r\'\"<>|", ' ', shell);
		if (tmp)
		{
			args = reallocation(args, sizeof(char *) * (argc + 1), sizeof(char *) * argc);
			args[argc] = tmp;
			argc++;
		}
	}
	args = reallocation(args, sizeof(char *) * (argc + 1), sizeof(char *) * argc);
	return (args);
}
