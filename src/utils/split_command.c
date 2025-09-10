/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 18:15:08 by acesteve          #+#    #+#             */
/*   Updated: 2025/09/10 19:06:47 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**split_command(char *line, t_env *env)
{
	int		is_quoted;
	int		is_doublequoted;
	int		word_len;
	int		res_len;
	char	**res;
	
	res = 0;
	res_len = 0;
	while (line && *line)
	{
		word_len = 0;
		if (*line == '\'')
		{
			is_quoted = 1;
			line++;
		}
		else if (*line == '"')
		{
			is_doublequoted = 1;
			line++;
		}
		while (line && line[word_len] && (!is_space(line[word_len]) || is_quoted || is_doublequoted))
		{
			if ((is_quoted || is_doublequoted) && (line[word_len] == '\'' || line[word_len] == '"'))
				break ;
			word_len++;
		}
		res = reallocation(res, res_len + 1, res)
	}
}
