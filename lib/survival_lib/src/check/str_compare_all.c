/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_compare_all.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:35:54 by acesteve          #+#    #+#             */
/*   Updated: 2025/09/16 09:14:46 by bvarea-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "survival_lib.h"

int	str_compare_all(const char *s1, const char *s2)
{
	size_t	s1len;
	size_t	s2len;

	s1len = str_len(s1);
	s2len = str_len(s2);
	if (!s1 || !s2 || s1len != s2len)
		return (0);
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (0);
		s1++;
		s2++;
	}
	return (1);
}
