/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 18:15:08 by acesteve          #+#    #+#             */
/*   Updated: 2025/09/12 12:34:10 by acesteve         ###   ########.fr       */
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
	while (line[word_len] && !is_fromset(line[word_len], delimiters))
		word_len++;
	*index = *index + word_len + 1;
	//if (line[index] == )
	return (str_substring(line, 0, word_len));
		
}

//TODO: Si hay dos cadenas seguidas sin espacio se toma como una sola cadena
char	**split_command(char *line, t_env *env)
{
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
				args[argc++] = get_word(&line[++i], "\"", &i);
			else if (line[i] == '\'')
				args[argc++] = get_word(&line[++i], "'", &i);
			else
				args[argc++] = get_word(&line[i], " \n\t\r", &i);
		}
		else if (line[i])
			i++;
	}
	args = reallocation(args, (argc + 1) * sizeof(char *), argc * sizeof(char *));
	return (args);
}
