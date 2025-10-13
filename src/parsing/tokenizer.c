/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 13:33:37 by bvarea-k          #+#    #+#             */
/*   Updated: 2025/10/14 00:13:26 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	declare_vars_tokenize(int *i, t_token **tokens, t_command **result)
{
	*i = 0;
	*tokens = 0;
	*result = 0;
}

static void	handle_pipe_token(t_token *tokens, int i, t_command **result,
	unsigned short *len)
{
	free(tokens[i].token);
	*result = reallocation(*result, (*len + 1) * sizeof(t_command),
			*len * sizeof(t_command));
	(*result)[*len].outfile = 1;
	*len = *len + 1;
}

static void	handle_redir_token(t_token *tokens, int *i, t_command **result,
	unsigned short *len)
{
	proccess_redir(tokens, *i, &result[0][*len - 1]);
	*i = *i + 1;
}

t_command	*tokenize(char *input, unsigned short *len, t_shell shell)
{
	int			i;
	t_token		*tokens;
	t_command	*result;

	i = 0;
	if (str_len(input) == 0)
		return (0);
	declare_vars_tokenize(&i, &tokens, &result);
	result = init_command();
	*len = 1;
	tokens = get_tokens(input, shell);
	while (tokens && tokens[i].token)
	{
		if (is_pipe_token(tokens[i].token) && !tokens[i].is_literal)
			handle_pipe_token(tokens, i, &result, len);
		else if (is_redir_token(tokens[i].token) && !tokens[i].is_literal)
			handle_redir_token(tokens, &i, &result, len);
		else
			proccess_command(tokens[i].token, &result[*len - 1]);
		i++;
	}
	free(tokens);
	return (result);
}
