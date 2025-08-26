/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 23:15:38 by acesteve          #+#    #+#             */
/*   Updated: 2025/08/26 13:01:38 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "survival_lib.h"
#include <stdlib.h>

static int	word_count(char const *s, char delimiter)
{
	int	isdelimiter;
	int	wordcount;

	isdelimiter = 1;
	wordcount = 0;
	while (s && *s)
	{
		if (*s == delimiter)
			isdelimiter = 1;
		else if (isdelimiter && *s != delimiter)
		{
			isdelimiter = 0;
			wordcount++;
		}
		s++;
	}
	return (wordcount);
}

static int	process_word(char **result, char *str, char c, int i)
{
	int next = 0;
	while (str[next] != c && str[next])
		next++;
	result[i] = str_substring(str, 0, next);
	if (!result[i] || result[i][0] == 0)
	{
		while (i--)
			free(result[i]);
		free(result);
		return -1;
	}
	return next;
}

static void	*fill_arr(char **result, char *str, int wordcount, char c)
{
	int i = 0;
	int next = 0;
	while (wordcount-- && str && *str)
	{
		next = process_word(result, str, c, i);
		if (next == -1)
			return (NULL);
		if (str[next] == '\0')
			str += next;
		else
			str += next + 1;
		while (*str == c)
			str++;
		i++;
	}
	result[i] = NULL;
	return (result);
}

char	**str_split(char const *s, char c)
{
	int		wordcount;
	char	set[2];
	char	*cleanstr;
	char	**result;

	wordcount = word_count(s, c);
	set[0] = c;
	set[1] = 0;
	cleanstr = str_trim(s, set);
	if (!cleanstr)
		return (NULL);
	result = malloc(sizeof(char *) * (wordcount + 1));
	if (!result)
	{
		free(cleanstr);
		return (NULL);
	}
	result = fill_arr(result, cleanstr, wordcount, c);
	free(cleanstr);
	return (result);
}
