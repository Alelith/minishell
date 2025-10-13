/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 13:33:37 by bvarea-k          #+#    #+#             */
/*   Updated: 2025/10/13 13:45:35 by bvarea-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	declare_vars_tokenize(int *i, char ***tokens, t_command **result)
{
	*i = 0;
	*tokens = 0;
	*result = 0;
}

static void	handle_pipe_token(char **tokens, int i, t_command **result,
	unsigned short *len)
{
	free(tokens[i]);
	*result = reallocation(*result, (*len + 1) * sizeof(t_command),
			*len * sizeof(t_command));
	(*result)[*len].outfile = 1;
	*len = *len + 1;
}

static void	handle_redir_token(char **tokens, int *i, t_command **result,
	unsigned short *len)
{
	proccess_redir(tokens, *i, &result[0][*len - 1]);
	*i = *i + 1;
}

t_command	*tokenize(char *input, unsigned short *len, t_shell shell)
{
	int			i;
	char		**tokens;
	t_command	*result;

	i = 0;
	if (str_len(input) == 0)
		return (0);
	declare_vars_tokenize(&i, &tokens, &result);
	result = init_command();
	*len = 1;
	tokens = get_tokens(input, shell);
	while (tokens && tokens[i])
	{
		if (is_pipe_token(tokens[i]))
			handle_pipe_token(tokens, i, &result, len);
		else if (is_redir_token(tokens[i]))
			handle_redir_token(tokens, &i, &result, len);
		else
			proccess_command(tokens[i], &result[*len - 1]);
		i++;
	}
	free(tokens);
	return (result);
}
