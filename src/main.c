/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 10:56:34 by bvarea-k          #+#    #+#             */
/*   Updated: 2025/08/26 09:45:51 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "survival_lib.h"
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>


int	main(int argc, char **argv)
{
	char	*line;

	if (argc < 1)
		return (0);
	line = 0;
	while (1)
	{
		if (line)
			free(line);
		print_format("%s", "minicher~> ");
		line = get_next_line(0);
		if (line == NULL)
		{
			print_format("Error reading line\n");
			return (1);
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
