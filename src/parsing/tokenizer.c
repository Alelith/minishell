/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 13:33:37 by bvarea-k          #+#    #+#             */
/*   Updated: 2025/09/16 09:16:26 by bvarea-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	proccess_command(char *token, t_command *comm)
{
	comm->args = reallocation(comm->args,
			(comm->args_c + 1) * sizeof(t_command),
			(comm->args_c) * sizeof(t_command));
	comm->args[comm->args_c] = token;
	comm->args_c++;
}

t_command	*tokenize(char *input, unsigned short *len, t_shell shell)
{
	int			i;
	char		**tokens;
	t_command	*result;

	i = 0;
	if (str_len(input) == 0)
		return (0);
	*len = 1;
	result = callocation(1, sizeof(t_command));
	tokens = split_command(input, shell.env_list);
	while (tokens && tokens[i])
	{
		if (!str_compare_all(tokens[i], "|"))
			proccess_command(tokens[i], &result[*len - 1]);
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
