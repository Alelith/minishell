/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 18:15:08 by acesteve          #+#    #+#             */
/*   Updated: 2025/10/05 17:33:29 by bvarea-k         ###   ########.fr       */
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

static void	expand_var(char **res, char *dollar, t_shell *shell)
{
	char	*tmp;
	char	*tmp_delete;

	if (!str_compare_all(dollar, "$?"))
		tmp = search_env(shell->env_list, dollar + 1);
	else
		tmp = int_to_str(shell->last_exitcod);
	tmp_delete = *res;
	*res = str_join(*res, tmp);
	free(tmp_delete);
}

static char	*get_enval(char *token, t_shell *shell)
{
	char	*dollar;
	char	*tmp;
	char	*tmp_delete;
	char	*res;

	dollar = str_search_char(token, '$');
	res = str_substring(token, 0, str_len(token) - str_len(dollar));
	while (dollar)
	{
		expand_var(&res, dollar, shell);
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

static int	get_word_len(char *line, const char *delimiters)
{
	int		word_len;

	word_len = 0;
	while (line[word_len] && !is_fromset(line[word_len], delimiters))
		word_len++;
	if (word_len == 0 && (*line == '|'))
		word_len++;
	if (word_len == 0)
		while (line[word_len] == '<')
			word_len++;
	if (word_len == 0)
		while (line[word_len] == '>')
			word_len++;
	return (word_len);
}

char	*handle_word_join(char *line, int *index, t_shell *shell, int word_len)
{
	char	*tmp;

	tmp = 0;
	if (line[word_len] && !is_space(line[word_len])
		&& !is_redirection(line[word_len])
		&& !is_redirection(line[word_len - 1]))
	{
		if (line[word_len] == '"' || line[word_len] == '\'')
		{
			*index = *index + 1;
			if (line[word_len] == '"')
				tmp = get_word(&line[word_len + 1], "\"", index, shell);
			else if (line[word_len] == '\'')
				tmp = get_word(&line[word_len + 1], "'", index, 0);
		}
		else
			tmp = get_word(&line[word_len], " \n\t\r\"'|<>", index, shell);
	}
	return (tmp);
}

char	*get_word(char *line, const char *delimiters, int *index,
						t_shell *shell)
{
	int		word_len;
	char	*tmp;
	char	*to_delete;
	char	*res;

	word_len = get_word_len(line, delimiters);
	*index = *index + word_len;
	res = str_substring(line, 0, word_len);
	if ((delimiters[0] == '\'' && line[word_len] == '\'')
		|| (delimiters[0] == '"' && line[word_len] == '"'))
	{
		*index = *index + 1;
		word_len++;
	}
	tmp = handle_word_join(line, index, shell, word_len);
	to_delete = res;
	res = str_join(res, tmp);
	if (tmp)
		free(tmp);
	free(to_delete);
	if (shell)
		res = get_enval(res, shell);
	return (res);
}

static char	**proccess_line(char *line, int *argc, char **args, t_shell *shell)
{
	int		i;

	i = 0;
	while (line && line[i])
	{
		if (line[i] && !is_space(line[i]))
		{
			args = reallocation(args, (*argc + 1) * sizeof(char *),
					*argc * sizeof(char *));
			if (line[i] == '"')
				args[*argc] = get_word(&line[++i], "\"", &i, shell);
			else if (line[i] == '\'')
				args[*argc] = get_word(&line[++i], "'", &i, 0);
			else
				args[*argc] = get_word(&line[i], " \n\t\r'\"'|<>", &i, shell);
			*argc = *argc + 1;
		}
		else if (line[i])
			i++;
	}
	return (args);
}

char	**split_command(char *line, t_shell *shell)
{
	int		argc;
	char	**args;

	argc = 0;
	args = 0;
	args = proccess_line(line, &argc, args, shell);
	args = reallocation(args, (argc + 1) * sizeof(char *),
			argc * sizeof(char *));
	return (args);
}
