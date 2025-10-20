/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 19:29:47 by acesteve          #+#    #+#             */
/*   Updated: 2025/10/20 10:08:38 by bvarea-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_pipes(int **pipes, int num)
{
	int	idx;

	idx = 0;
	while (idx < num)
	{
		free(pipes[idx]);
		idx++;
	}
}

void	close_pipes(int **pipes, int num)
{
	int	idx;

	idx = 0;
	while (idx < num)
	{
		close(pipes[idx][0]);
		close(pipes[idx][1]);
		idx++;
	}
}

void	create_pipes(int **pipes, int num)
{
	int	idx;

	idx = 0;
	while (idx < num)
	{
		pipes[idx] = (int *)malloc(sizeof(int) * 2);
		if (!pipes[idx])
		{
			while (--idx > 0)
				free(pipes[idx]);
			return ;
		}
		pipe(pipes[idx]);
		idx++;
	}
}
