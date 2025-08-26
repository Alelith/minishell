/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 10:31:40 by acesteve          #+#    #+#             */
/*   Updated: 2025/08/26 13:10:49 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*tokenize(char *input, short *len)
{
	t_command	*result;
	int			i;
	int			is_first;
	int			is_quoted;
	char		*temp_str;
	char		**tokens;
	t_command	*temp;

	i = 0;
	is_first = 1;
	is_quoted = 0;
	tokens = str_split(input, ' ');
	result = 0;
	while (tokens[i])
	{
		if (str_compare_all(tokens[i], "<"))
		{
			temp = &result[*len - 1];
			temp->redirections = reallocation(temp->redirections, (temp->redirections_c + 1) * sizeof(t_redirection), temp->redirections_c * sizeof(t_redirection));
			temp->redirections[temp->redirections_c++] = INPUT;
			free(tokens[i]);
		}
		else if (str_compare_all(tokens[i], ">"))
		{
			temp = &result[*len - 1];
			temp->redirections = reallocation(temp->redirections, (temp->redirections_c + 1) * sizeof(t_redirection), temp->redirections_c * sizeof(t_redirection));
			temp->redirections[temp->redirections_c++] = OUTPUT;
			free(tokens[i]);
		}
		else if (str_compare_all(tokens[i], "<<"))
		{
			temp = &result[*len - 1];
			temp->redirections = reallocation(temp->redirections, (temp->redirections_c + 1) * sizeof(t_redirection), temp->redirections_c * sizeof(t_redirection));
			temp->redirections[temp->redirections_c++] = DELIMITED;
			free(tokens[i]);
		}
		else if (str_compare_all(tokens[i], ">>"))
		{
			temp = &result[*len - 1];
			temp->redirections = reallocation(temp->redirections, (temp->redirections_c + 1) * sizeof(t_redirection), temp->redirections_c * sizeof(t_redirection));
			temp->redirections[temp->redirections_c++] = APPEND;
			free(tokens[i]);
		}
		else if (is_first)
		{
			result = reallocation(result, (*len + 1) * sizeof(t_command), (*len) * sizeof(t_command));
			result[*len].name = tokens[i];
			(*len)++;
			is_first = 0;
		}
		else if (str_compare_n(tokens[i], "-", 1))
			result[*len - 1].flag = tokens[i];
		else if (str_compare_all(tokens[i], "|"))
		{
			is_first = 1;
			free(tokens[i]);
		}
		else if (str_search_char(tokens[i], '"') == tokens[i])
		{
			temp = &result[*len - 1];
			temp->args = reallocation(temp->args, (temp->args_c + 1) * sizeof(char *), temp->args_c * sizeof(char *));
			temp->args[temp->args_c++] = tokens[i];
			is_quoted = 1;
		}
		else if (is_quoted)
		{
			temp = &result[*len - 1];
			temp_str = temp->args[temp->args_c - 1];
			temp->args[temp->args_c - 1] = str_join(temp_str, tokens[i]);
			free(temp_str);
			if (str_search_char(tokens[i], '"'))
				is_quoted = 0;
		}
		else
		{
			temp = &result[*len - 1];
			temp->args = reallocation(temp->args, (temp->args_c + 1) * sizeof(char *), temp->args_c * sizeof(char *));
			temp->args[temp->args_c++] = tokens[i];
		}
		i++;
	}
	free(tokens);
	return (result);
}
