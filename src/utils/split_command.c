/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 18:15:08 by acesteve          #+#    #+#             */
/*   Updated: 2025/10/14 11:12:43 by bvarea-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*split_command(char *line, t_shell *shell)
{
	char	type;
	char	*tmp;
	int		argc;
	t_token	*args;

	argc = 0;
	args = 0;
	while (line && *line)
	{
		tmp = 0;
		while (*line && isspace(*line))
			line++;
		type = *line;
		switch_assign_tmp(&line, &tmp, shell);
		if (tmp)
			increment_args(&args, &argc, tmp, type);
	}
	args = reallocation(args, sizeof(t_token) * (argc + 1),
			sizeof(t_token) * argc);
	return (args);
}
