/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 13:33:37 by bvarea-k          #+#    #+#             */
/*   Updated: 2025/09/21 11:59:02 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*tokenize(char *input, unsigned short *len, t_shell shell)
{
	int			i;
	char		**tokens;
	t_command	*result;

	i = 0;
	if (str_len(input) == 0)
		return (0);
	result = init_command();
	*len = 1;
	tokens = get_tokens(input, shell);
	while (tokens && tokens[i])
	{
		if (is_pipe_token(tokens[i]))
		{
			free(tokens[i]);
			result = reallocation(result, (*len + 1) * sizeof(t_command),
					*len * sizeof(t_command));
			result[*len].outfile = 1;
			*len = *len + 1;
		}
		else if (is_redir_token(tokens[i]))
		{
			proccess_redir(tokens, i, &result[*len - 1]);
			i = i + 1;
		}
		else
			proccess_command(tokens[i], &result[*len - 1]);
		i = i + 1;
	}
	free(tokens);
	return (result);
}
