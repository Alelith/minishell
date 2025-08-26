/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgo <bgo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 10:31:40 by acesteve          #+#    #+#             */
/*   Updated: 2025/08/26 17:34:31 by bgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_redirection(char *tokens, t_command **result, short *len)
{
	t_command	*temp;
	int			type;

	temp = &(*result)[*len - 1];
	if (str_compare_all(tokens, "<"))
		type = INPUT;
	else if (str_compare_all(tokens, ">"))
		type = OUTPUT;
	else if (str_compare_all(tokens, "<<"))
		type = DELIMITED;
	else
		type = APPEND;
	temp->redirections = reallocation(temp->redirections,
			(temp->redirections_c + 1) * sizeof(t_redirection),
			temp->redirections_c * sizeof(t_redirection));
	temp->redirections[temp->redirections_c++] = type;
	free(tokens);
}

void	handle_command_or_pipe(char *tokens,
	t_command **result, short *len, int *is_first)
{
	if (str_compare_all(tokens, "|"))
	{
		*is_first = 1;
		free(tokens);
	}
	else if (*is_first)
	{
		*result = reallocation(*result,
				(*len + 1) * sizeof(t_command),
				(*len) * sizeof(t_command));
		set_zero(&(*result)[*len], sizeof(t_command));
		(*result)[*len].name = tokens;
		(*len)++;
		*is_first = 0;
	}
	else if (str_compare_n(tokens, "-", 1))
		(*result)[*len - 1].flag = tokens;
}

void	handle_quoted_arg(char **tokens,
	int *i, t_command **res, short *len, int *is_quoted)
{
	t_command	*temp;
	char		*temp_str;

	temp = &(*res)[*len - 1];
	if (*is_quoted)
	{
		temp_str = temp->args[temp->args_c - 1];
		temp->args[temp->args_c - 1]
			= str_join(temp_str, tokens[*i]);
		free(temp_str);
		if (str_search_char(tokens[*i], '"'))
			*is_quoted = 0;
	}
	else
	{
		temp->args = reallocation(temp->args,
				(temp->args_c + 1) * sizeof(char *),
				temp->args_c * sizeof(char *));
		temp->args[temp->args_c++] = tokens[*i];
		*is_quoted = 1;
	}
}

void	handle_regular_arg(char *token, t_command **result, short *len)
{
	t_command	*temp;

	temp = &(*result)[*len - 1];
	temp->args = reallocation(temp->args,
			(temp->args_c + 1) * sizeof(char *),
			temp->args_c * sizeof(char *));
	temp->args[temp->args_c++] = token;
}

t_command	*tokenize(char *input, short *len)
{
	t_command	*result;
	int			i;
	int			is_first;
	int			is_quoted;
	char		**tokens;

	i = 0;
	is_first = 1;
	is_quoted = 0;
	tokens = str_split(input, ' ');
	result = 0;
	while (tokens[i])
	{
		if (is_redirection_token(tokens[i]))
			handle_redirection(tokens[i], &result, len);
		else if (should_handle_as_command(tokens[i], is_first))
			handle_command_or_pipe(tokens[i], &result, len, &is_first);
		else if (starts_with_quote(tokens[i]))
			handle_quoted_arg(tokens, &i, &result, len, &is_quoted);
		else if (is_quoted)
			handle_quoted_arg(tokens, &i, &result, len, &is_quoted);
		else
			handle_regular_arg(tokens[i], &result, len);
		i++;
	}
	free(tokens);
	return (result);
}



/*t_command	*tokenize(char *input, short *len)
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
}*/
