/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 11:10:35 by bvarea-k          #+#    #+#             */
/*   Updated: 2025/10/14 13:30:30 by bvarea-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_until(char *line, const char *delimiters)
{
	int	res;

	res = 0;
	while (line[res] && !is_from_set(line[res], delimiters))
		res++;
	return (res);
}

int	count_while(char *line, const char *delimiters)
{
	int	res;

	res = 0;
	while (line[res] && is_from_set(line[res], delimiters))
		res++;
	return (res);
}

char	*get_value_from_env(char **line, t_shell *shell)
{
	char	*res;
	char	*tmp;
	int		size;

	tmp = 0;
	if (*(*line + 1) == '?')
	{
		*line = *line + 2;
		return (int_to_str(shell->last_exitcod));
	}
	else
	{
		if (*(*line + 1) == '\0')
		{
			*line = *line + 1;
			return (str_duplicate(""));
		}
		size = count_until(*line + 1, " \t\n\r\"\'<>|$");
		tmp = str_substring(*line, 1, size);
		res = search_env(shell->env_list, tmp);
		*line = *line + size + 1;
		if (!res)
			return (str_duplicate(""));
		return (free (tmp), str_duplicate(res));
	}
}

void	free_and_assign(char **res, char *tmp)
{
	char	*old_res;

	old_res = *res;
	*res = str_join(*res, tmp);
	free(old_res);
	free(tmp);
}

void	process_result(char **line, char **res, t_shell *shell, char type)
{
	char	*tmp;

	if (**line == '$' && shell && (type == '\"' || type == ' '))
		tmp = get_value_from_env(line, shell);
	else
	{
		tmp = str_substring(*line, 0, 1);
		(*line)++;
	}
	free_and_assign(res, tmp);
}
