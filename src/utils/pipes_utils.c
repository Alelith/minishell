/**
 * @file pipes_utils.c
 * @brief Pipe management utilities for command pipelines
 * 
 * @author Lilith Estévez Boeta y Begoña Varea Kuhn
 * @date 2025-09-20
 */

#include "minishell.h"

/**
 * @brief Frees array of pipe file descriptor pairs
 * 
 * @details Deallocates each pipe descriptor pair in the array. Does not
 * close the file descriptors; use close_pipes first if needed.
 * 
 * @ingroup utils_module
 * 
 * @param[in] pipes Array of pipe descriptor pairs
 * @param[in] num Number of pipes in the array
 */
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

/**
 * @brief Closes all pipe file descriptors
 * 
 * @details Closes both read and write ends of all pipes in the array.
 * Should be called before freeing pipes to prevent descriptor leaks.
 * 
 * @ingroup utils_module
 * 
 * @param[in] pipes Array of pipe descriptor pairs
 * @param[in] num Number of pipes in the array
 */
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

/**
 * @brief Creates array of pipes for command pipeline
 * 
 * @details Allocates and initializes num pipes for inter-process
 * communication. Each pipe gets a newly allocated int[2] array. If any
 * allocation fails, frees already allocated pipes and returns.
 * 
 * @ingroup utils_module
 * 
 * @param[out] pipes Array to store pipe descriptor pairs
 * @param[in] num Number of pipes to create
 */
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
