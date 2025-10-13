/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 11:29:19 by acesteve          #+#    #+#             */
/*   Updated: 2025/10/13 21:11:52 by acesteve         ###   ########.fr       */
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

static int	handle_redirection(char **tokens, int *i)
{
	if (!tokens[*i + 1] || str_compare_all(tokens[*i + 1], "|"))
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

static int	handle_last_error(int expect_cmd, char *line)
{
	if (expect_cmd && str_len(line))
	{
		printf("Syntax error: command expected after pipe\n");
		return (0);
	}
	return (1);
}

static int	process_tokens(char **tokens)
{
	int	i;
	int	expect_cmd;

	i = 0;
	expect_cmd = 1;
	while (tokens[i])
	{
		if (str_compare_all(tokens[i], "|"))
		{
			if (!handle_pipe(&expect_cmd))
				return (0);
		}
		else if (is_redir_token(tokens[i]))
		{
			if (!handle_redirection(tokens, &i))
				return (0);
		}
		else
			expect_cmd = 0;
		i++;
	}
	return (expect_cmd);
}

int	check_command_line(char *line)
{
	char	**tokens;
	int		expect_cmd;
	int		i;

	if (!check_quotes(line))
		return (0);
	tokens = split_command(line, 0);
	expect_cmd = process_tokens(tokens);
	if (tokens[0] == 0)
	{
		free(tokens);
		return (1);
	}
	i = 0;
	while (tokens[i])
		free(tokens[i++]);
	free(tokens);
	return (handle_last_error(expect_cmd, line));
}

/*int	check_command_line(char *line)
{
	char	**tokens;
	int		i;
	int		expect_cmd;

	if (!check_quotes(line))
		return (0);
	i = 0;
	tokens = split_command(line, 0);
	expect_cmd = 1;
	while (tokens[i])
	{
		if (strcmp(tokens[i], "|") == 0)
		{
			if (!handle_pipe(&expect_cmd))
				return (0);
		}
		else if (is_redir_token(tokens[i]))
		{
			if (!handle_redirection(tokens, &i))
				return (0);
		}
		else
			expect_cmd = 0;
		i++;
	}
	if (tokens[0] == 0)
	{
		free(tokens);
		return (1);
	}
	i = 0;
	while (tokens[i])
		free(tokens[i++]);
	free(tokens);
	return (handle_last_error(expect_cmd, line));
}*/
