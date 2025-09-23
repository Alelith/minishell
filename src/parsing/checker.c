/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 11:29:19 by acesteve          #+#    #+#             */
/*   Updated: 2025/09/23 17:38:56 by bvarea-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "survival_lib.h"
#include "minishell.h"

static int	handle_pipe(char **tokens, int i, int *expect_cmd)
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

int	check_command_line(char *line)
{
	char	**tokens;
	int		i;
	int		expect_cmd;

	i = 0;
	tokens = split_command(line, 0);
	expect_cmd = 1;
	while (tokens[i])
	{
		if (strcmp(tokens[i], "|") == 0)
			if (!handle_pipe(tokens, i, &expect_cmd))
				return (0);
		else if (is_redir_token(tokens[i]))
			if (!handle_redirections(tokens, &i))
				return (0);
		else
			expect_cmd = 0;
		i++;
	}
	if (expect_cmd)
	{
		printf("Syntax error: command expected after pipe\n");
		return (0);
	}
	return (1);
}
