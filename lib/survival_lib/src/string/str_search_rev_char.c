/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_search_rev_char.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:35:15 by acesteve          #+#    #+#             */
/*   Updated: 2025/09/16 09:15:39 by bvarea-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "survival_lib.h"

char	*str_search_rev_char(const char *s, int c)
{
	const char	*ini_s;

	ini_s = s;
	c = c % 256;
	s += str_len(s) - 1;
	if (c == '\0')
		return ((char *)s + 1);
	while (s >= ini_s)
	{
		if (*s == c)
			return ((char *)s);
		s--;
	}
	return (0);
}
