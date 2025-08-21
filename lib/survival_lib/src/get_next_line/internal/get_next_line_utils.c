/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:03:05 by acesteve          #+#    #+#             */
/*   Updated: 2025/06/11 15:59:53 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

int	ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

unsigned long	ft_strlen(char *s)
{
	unsigned long	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	*ft_calloc(unsigned long nmemb, unsigned long size)
{
	int		len;
	char	*result;

	len = nmemb * size;
	result = malloc(len);
	if (!result)
		return (0);
	while (len--)
		result[len] = 0;
	return (result);
}

char	*ft_strrest(char *s, int start)
{
	int		i;
	char	*result;

	i = 0;
	result = ft_calloc(BUFFER_SIZE + 1, 1);
	if (!result)
		return (0);
	while (s && s[start])
		result[i++] = s[start++];
	free(s);
	return (result);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	char	*result;
	char	*s1_trash;

	i = 0;
	if (!s1)
	{
		s1 = ft_calloc(1, 1);
		if (!s1)
			return (0);
	}
	result = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 2, 1);
	if (!result)
		return (0);
	s1_trash = s1;
	while (s1 && *s1)
		result[i++] = *s1++;
	while (s2 && *s2 && *s2 != '\n')
		result[i++] = *s2++;
	result[i] = *s2;
	free(s1_trash);
	return (result);
}
