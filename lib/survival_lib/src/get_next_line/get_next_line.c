/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:59:18 by acesteve          #+#    #+#             */
/*   Updated: 2025/06/12 17:44:14 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

static void	ft_clean_buffer(char *buffer)
{
	while (*buffer)
		*buffer++ = 0;
}

static char	*ft_init_buffer(char *buffer)
{
	if (!buffer)
	{
		buffer = ft_calloc(BUFFER_SIZE + 1, 1);
		if (!buffer)
			return (0);
	}
	return (buffer);
}

static char	*ft_processbuffer(char **buffer, char *result)
{
	if (ft_strlen(*buffer) > 0)
	{
		result = ft_strjoin(result, *buffer);
		if (ft_strchr(*buffer, '\n') >= 0)
			*buffer = ft_strrest(*buffer, ft_strchr(*buffer, '\n') + 1);
		else
			ft_clean_buffer(*buffer);
	}
	return (result);
}

static char	*ft_read_and_append(int fd, char **buffer, char *result)
{
	while (read(fd, *buffer, BUFFER_SIZE) > 0)
	{
		result = ft_strjoin(result, *buffer);
		if (ft_strchr(*buffer, '\n') >= 0)
		{
			*buffer = ft_strrest(*buffer, ft_strchr(*buffer, '\n') + 1);
			return (result);
		}
		ft_clean_buffer(*buffer);
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
	buffer = ft_init_buffer(buffer);
	if (!buffer)
		return (0);
	result = 0;
	result = ft_processbuffer(&buffer, result);
	if (ft_strlen(buffer) == 0)
		result = ft_read_and_append(fd, &buffer, result);
	else
		return (result);
	if (result && ft_strlen(result) > 0)
		return (result);
	free(buffer);
	buffer = 0;
	return (0);
}
/*
int main()
{
	char *name = "test.txt";
	int fd = open(name, O_RDONLY);
	printf("%s", get_next_line(fd));
	printf("\n");
	printf("%s", get_next_line(fd));
	printf("\n");
	if (BUFFER_SIZE > 100) {
		char *temp;
		do {
			temp = get_next_line(fd);
			free(temp);
		} while (temp != NULL);
	}
	printf("%s", get_next_line(fd));
	printf("\n");
	close(fd);
	fd = open(name, O_RDONLY);
	printf("%s", get_next_line(fd));
	printf("\n");
	printf("%s", get_next_line(fd));
	printf("\n");
	printf("%s", get_next_line(fd));
	printf("\n");
	printf("%s", get_next_line(fd));
	printf("\n");
	printf("%s", get_next_line(fd));
	printf("\n Fin \n");
}*/
