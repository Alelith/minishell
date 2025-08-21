/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 10:31:40 by acesteve          #+#    #+#             */
/*   Updated: 2025/08/21 11:46:26 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*comando flag arg | comando flag arg*/

t_command	*parse_commands(char *input, int *len)
{
	int			i;
	int			is_first;
	char		**all;
	t_command	*result;

	i = 0;
	*len = 1;
	all = str_split(input, ' ');
	result = callocation(1, sizeof(t_command));
	is_first = 1;
	while (all[i])
	{
		if (str_compare_all(all[i], "|"))
		{
			result = reallocation(result, (*len + 1) * sizeof(t_command), *len * sizeof(t_command));
			(*len)++;
			is_first = 1;
			free(all[i]);
		}
		else if (is_first)
		{
			result[*len - 1].name = all[i];
			is_first = 0;
		}
		else if (str_search_char(all[i], '-'))
			result[*len - 1].flag = all[i];
		else
		{
			result[*len - 1].args = reallocation(result[*len - 1].args,
					(result[*len - 1].argsc + 1) * sizeof(t_command), result[*len - 1].argsc * sizeof(t_command));
			result[*len - 1].args[result[*len - 1].argsc] = all[i];
			result[*len - 1].argsc++;
		}
		i++;
	}
}
