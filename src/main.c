/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 10:56:34 by bvarea-k          #+#    #+#             */
/*   Updated: 2025/08/20 13:42:27 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "survival_lib.h"
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

/*void handle_sigquit(int sig)
{
	(void)sig;
	printf("\nminicher> ");
}*/

/*void handle_sigint(int sig)
{
	(void)sig;
	printf("minicher> ");
}*/

int	main(int argc, char **argv)
{
	char	*line;

	if (argc < 1)
		return (0);
	line = 0;
//	signal(SIGINT, handle_sigint);
	//signal(SIGQUIT, handle_sigquit);
	while (1)
	{
		if (line)
			free(line);
		write(1, "minicher~> ", 12);
		line = get_next_line(0);
		if (line == NULL)
		{
			printf("Error reading line\n");
			return (1);
		}
		if (str_compare(line, "exit\n", 5) == 0)
		{
			free(line);
			printf("Exiting minicher...\n");
			exit(0);
		}
		{
			free(line);
			continue;
		}
		write(1, line, str_len(line));
	}
}

/*int	main(int argc, char **argv)
{
	char	*line;

	if (argc < 1)
		return (0);
	line = 0;
	while (1)
	{
		if (line)
			free(line);
		printf("minicher> ");
		line = get_next_line(0);
		if (line == NULL)
		{
			printf("Error reading line\n");
			return (1);
		}
		printf("Read line: %s", line);
		free(line);
		exit(0);
	}
}*/
