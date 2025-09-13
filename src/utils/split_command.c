/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 18:15:08 by acesteve          #+#    #+#             */
/*   Updated: 2025/09/13 09:18:50 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_fromset(char c, const char *set)
{
	while (set && *set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

static char	*get_word(char *line, const char *delimiters, int *index, t_env *env)
{
	int		word_len;
	char	*tmp;
	char	*to_delete;
	char	*res;
	
	word_len = 0;
	tmp = 0;
	while (line[word_len] && !is_fromset(line[word_len], delimiters))
		word_len++;
	*index = *index + word_len;
	if (delimiters[0] == '\'' || delimiters[0] == '"')
		*index = *index + 1;
	res = str_substring(line, 0, word_len);
	/*if (line[*index] && !is_space(line[*index]))
	{
		if (line[*index] == '"')
		{
			*index = *index + 1;
			if (line[*index - 1] == '"')
				tmp = get_word(&line[*index], "\"", index, env);
			else if (line[*index - 1] == '\'')
				tmp = get_word(&line[*index], "'", index, env);
		}
		else
			tmp = get_word(&line[*index], " \n\t\r", index, env);
	}
	to_delete = res;
	res = str_join(res, tmp);
	if (tmp)
		free(tmp);
	free(to_delete);*/
	return (res);
		
}

char	**split_command(char *line, t_env *env)
{
	int		argc;
	char	**args;
	int		i;

	argc = 0;
	args = 0;
	i = 0;
	while (line && line[i])
	{
		if (line[i] && !is_space(line[i]))
		{
			args = reallocation(args, (argc + 1) * sizeof(char *), argc * sizeof(char *));
			if (line[i] == '"')
				args[argc++] = get_word(&line[++i], "\"", &i, 0);
			else if (line[i] == '\'')
				args[argc++] = get_word(&line[++i], "'", &i, 0);
			else
				args[argc++] = get_word(&line[i], " \n\t\r'\"", &i, 0);
		}
		else if (line[i])
			i++;
	}
	args = reallocation(args, (argc + 1) * sizeof(char *), argc * sizeof(char *));
	return (args);
}
