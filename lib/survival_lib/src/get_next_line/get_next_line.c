/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:59:18 by acesteve          #+#    #+#             */
/*   Updated: 2025/08/25 10:14:59 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "survival_lib.h"
#include <fcntl.h>

static void	clean_buffer(char *buffer)
{
	while (*buffer)
		*buffer++ = 0;
}

static char	*init_buffer(char *buffer)
{
	if (!buffer)
	{
		buffer = callocation(BUFFER_SIZE + 1, 1);
		if (!buffer)
			return (0);
	}
	return (buffer);
}

static char	*processbuffer(char **buffer, char *result)
{
	if (str_len(*buffer) > 0)
	{
		//result = str_join(result, *buffer);
		if (str_chr(*buffer, '\n') >= *buffer)
		//TODO: Change str_rest to str_substring
			*buffer;
		else
			clean_buffer(*buffer);
	}
	return (result);
}

static char	*read_and_append(int fd, char **buffer, char *result)
{
	while (read(fd, *buffer, BUFFER_SIZE) > 0)
	{
		//result = str_join(result, *buffer);
		if (str_chr(*buffer, '\n') >= 0)
		{
			*buffer;
			return (result);
		}
		clean_buffer(*buffer);
	}
	return (result);
}

char	*get_next_line(int fd)
{
	static char	*buffer = 0;
	char		*result;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		if (buffer)
			free(buffer);
		buffer = 0;
		return (0);
	}
	buffer = init_buffer(buffer);
	if (!buffer)
		return (0);
	result = 0;
	result = processbuffer(&buffer, result);
	if (str_len(buffer) == 0)
		result = read_and_append(fd, &buffer, result);
	else
		return (result);
	if (result && str_len(result) > 0)
		return (result);
	free(buffer);
	buffer = 0;
	return (0);
}
