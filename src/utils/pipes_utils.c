/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 19:29:47 by acesteve          #+#    #+#             */
/*   Updated: 2025/09/20 19:31:03 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_pipes(int **pipes, int num)
{
	int idx;

	idx = 0;
	while (idx < num)
	{
		free(pipes[idx]);
		idx++;
	}
}

void close_pipes(int **pipes, int num)
{
	int idx;

	idx = 0;
	while (idx < num)
	{
		close(pipes[idx][0]);
		close(pipes[idx][1]);
		idx++;
	}
}

void create_pipes(int **pipes, int num)
{
    int idx;

    idx = 0;
    while (idx < num)
    {
        pipes[idx] = (int *)malloc(sizeof(int) * 2);
        pipe(pipes[idx]);
        idx++;
    }
}
