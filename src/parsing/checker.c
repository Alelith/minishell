/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 11:29:19 by acesteve          #+#    #+#             */
/*   Updated: 2025/09/22 16:27:35 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "survival_lib.h"
#include "minishell.h"

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
        {
            if (expect_cmd)
            {
                printf("Syntax error: unexpected pipe\n");
                return (0);
            }
            expect_cmd = 1;
        }
        else if (is_redir_token(tokens[i]))
        {
            if (!tokens[i + 1] || strcmp(tokens[i + 1], "|") == 0)
            {
                printf("Syntax error: redirection without file/limiter\n");
                return (0);
            }
            i++; 
            expect_cmd = 0;
        }
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
