/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 18:15:08 by acesteve          #+#    #+#             */
/*   Updated: 2025/09/16 13:39:41 by bvarea-k         ###   ########.fr       */
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

static char	*get_enval(char *token, t_env *env)
{
	char	*dollar;
	char	*tmp;
	char	*tmp_delete;
	char	*res;

	dollar = str_search_char(token, '$');
	res = str_substring(token, 0, str_len(token) - str_len(dollar));
	while (dollar)
	{
		tmp = search_env(env, dollar + 1);
		tmp_delete = res;
		res = str_join(res, tmp);
		free(tmp_delete);
		while (dollar && *dollar && !is_space(*dollar))
			dollar++;
		tmp = str_substring(dollar, 0,
				str_len(dollar) - str_len(str_search_char(dollar, '$')));
		tmp_delete = res;
		res = str_join(res, tmp);
		free(tmp_delete);
		free(tmp);
		dollar = str_search_char(dollar, '$');
	}
	free(token);
	return (res);
}

static char	*get_word(char *line, const char *delimiters, int *index,
						t_env *env)
{
	int		word_len;
	char	*tmp;
	char	*to_delete;
	char	*res;

	word_len = 0;
	tmp = 0;
	while (line[word_len] && !is_fromset(line[word_len], delimiters))
		word_len++;
	if (word_len == 0 && (*line == '|'))
		word_len++;
	while (word_len == 0 && (line[word_len] == '<'))
		word_len++;
	while (word_len == 0 && (line[word_len] == '>'))
		word_len++;
	*index = *index + word_len;
	res = str_substring(line, 0, word_len);
	if ((delimiters[0] == '\'' && line[word_len] == '\'')
		|| (delimiters[0] == '"' && line[word_len] == '"'))
	{
		*index = *index + 1;
		word_len++;
	}
	if (line[word_len] && !is_space(line[word_len]) && !is_redirection(line[word_len]) && !is_redirection(line[word_len - 1]))
	{
		if (line[word_len] == '"' || line[word_len] == '\'')
		{
			*index = *index + 1;
			if (line[word_len] == '"')
				tmp = get_word(&line[word_len + 1], "\"", index, env);
			else if (line[word_len] == '\'')
				tmp = get_word(&line[word_len + 1], "'", index, 0);
		}
		else
			tmp = get_word(&line[word_len], " \n\t\r\"'|<>", index, env);
	}
	to_delete = res;
	res = str_join(res, tmp);
	if (tmp)
		free(tmp);
	free(to_delete);
	if (env)
		res = get_enval(res, env);
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
			args = reallocation(args, (argc + 1) * sizeof(char *),
					argc * sizeof(char *));
			if (line[i] == '"')
				args[argc++] = get_word(&line[++i], "\"", &i, env);
			else if (line[i] == '\'')
				args[argc++] = get_word(&line[++i], "'", &i, 0);
			else
				args[argc++] = get_word(&line[i], " \n\t\r'\"'|<>", &i, env);
		}
		else if (line[i])
			i++;
	}
	args = reallocation(args, (argc + 1) * sizeof(char *),
			argc * sizeof(char *));
	print_str_lst(args);
	return (args);
}
