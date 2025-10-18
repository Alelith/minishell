/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 11:29:19 by acesteve          #+#    #+#             */
/*   Updated: 2025/10/18 09:26:55 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "survival_lib.h"
#include "minishell.h"

static int	handle_pipe(int *expect_cmd)
{
	if (*expect_cmd)
	{
		printf("Syntax error: unexpected pipe\n");
		return (0);
	}
	*expect_cmd = 1;
	return (1);
}

static int	handle_redirection(t_token *tokens, int *i)
{
	if (!tokens[*i + 1].token || str_contains(tokens[*i + 1].token, "<>|"))
	{
		printf("Syntax error: redirection without file/limiter\n");
		return (0);
	}
	(*i)++;
	return (1);
}

static int	check_quotes(char *line)
{
	int	i;
	int	single_quote;
	int	double_quote;

	i = 0;
	single_quote = 0;
	double_quote = 0;
	while (line[i])
	{
		if (line[i] == '\'' && !double_quote)
			single_quote = !single_quote;
		else if (line[i] == '"' && !single_quote)
			double_quote = !double_quote;
		i++;
	}
	if (single_quote || double_quote)
	{
		printf("Syntax error: unclosed quotes\n");
		return (0);
	}
	return (1);
}

static int	process_tokens(t_token *tokens)
{
	int	i;
	int	expect_cmd;

	i = 0;
	expect_cmd = 1;
	while (tokens[i].token)
	{
		if (str_compare_all(tokens[i].token, "|") && !tokens[i].is_literal)
		{
			if (!handle_pipe(&expect_cmd))
				return (2);
		}
		else if (is_redir_token(tokens[i].token) && !tokens[i].is_literal)
		{
			if (!handle_redirection(tokens, &i))
				return (2);
		}
		else
			expect_cmd = 0;
		i++;
	}
	return (expect_cmd);
}

int	check_command_line(char *line)
{
	t_token	*tokens;
	int		err_code;
	int		i;

	if (!check_quotes(line))
		return (0);
	tokens = split_command(line, 0);
	err_code = process_tokens(tokens);
	if (tokens[0].token == 0)
	{
		free(tokens);
		return (0);
	}
	i = 0;
	while (tokens[i].token)
		free(tokens[i++].token);
	free(tokens);
	if (err_code == 1 && str_len(line))
	{
		printf("Syntax error: command expected after pipe\n");
		return (0);
	}
	else if (err_code == 2)
		return (0);
	return (1);
}
