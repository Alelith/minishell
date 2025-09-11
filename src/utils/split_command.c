/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 18:15:08 by acesteve          #+#    #+#             */
/*   Updated: 2025/09/11 16:05:20 by acesteve         ###   ########.fr       */
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

static char	*get_word(char *line, const char *delimiters, int *index)
{
	int	word_len;
	
	word_len = 0;
	if (str_search_char(delimiters, '\n') == 0)
		line++;
	while (line[word_len] && !is_fromset(line[word_len], delimiters))
		word_len++;
	*index = *index + word_len;
	return (str_substring(line, 0, word_len));
		
}

//TODO: Si hay dos cadenas seguidas sin espacio se toma como una sola cadena
char	**split_command(char *line, t_env *env)
{
	const char *delimiters[5] = {" \n\t\r", "'", "\""};
	int		argc;
	char	*tmp;
	char	**args;
	int		i;

	argc = 0;
	args = 0;
	i = 0;
	while (line && i < str_len(line) && line[i])
	{
		if (line[i] && !is_space(line[i]))
		{
			args = reallocation(args, (argc + 1) * sizeof(char *), argc * sizeof(char *));
			if (line[i] == '"')
				args[argc++] = get_word(&line[i], delimiters[2], &i);
			else if (line[i] == '\'')
				args[argc++] = get_word(&line[i], delimiters[1], &i);
			else
				args[argc++] = get_word(&line[i], delimiters[0], &i);
		}
		if (line[i])
			i++;
	}
	args = reallocation(args, (argc + 1) * sizeof(char *), argc * sizeof(char *));
	return (args);
}
