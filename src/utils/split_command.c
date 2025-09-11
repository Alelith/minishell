/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 18:15:08 by acesteve          #+#    #+#             */
/*   Updated: 2025/09/11 13:50:51 by bvarea-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_fromset(char c, char *set)
{
	while (set && *set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

static char	*get_word(char *line, const char *delimiters)
{
	
}

//TODO: Si hay dos cadenas de literales seguidas sin espacio se toma como una sola cadena
char	**split_command(char *line, t_env *env)
{
	const char **delimiters = {" \n\t\r", "'", "\""};
	int		word_len;
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
			args[argc++] = get_word();	
		}
		if (line[i])
			i++;
	}
	args = reallocation(args, (argc + 1) * sizeof(char *), argc * sizeof(char *));
	return (args);
}
