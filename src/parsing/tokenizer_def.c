/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_def.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 13:33:37 by bvarea-k          #+#    #+#             */
/*   Updated: 2025/09/09 16:52:29 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*tokenize(char *input, unsigned short *len)
{
	int			i;
	char		**tokens;
	t_command	*result;
	
	i = 0;
	*len = 1;
	result = callocation(1, sizeof(t_command));
	tokens = str_split(input, ' ');
	while (tokens[i])
	{
		if (!str_compare_all(tokens[i], "|"))
		{
			result[*len - 1].args = reallocation(result[*len - 1].args, (result[*len - 1].args_c + 1) * sizeof(t_command), (result[*len - 1].args_c) * sizeof(t_command));
			result[*len - 1].args[result[*len - 1].args_c] = tokens[i];
			result[*len - 1].args_c++;
		}
		else
		{
			free(tokens[i]);
			result = reallocation(result, *len + 1, *len);
			*len += 1;
		}
		i++;
	}
	free(tokens);
	return (result);
}
