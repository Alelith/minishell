/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_compare_n.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:35:54 by acesteve          #+#    #+#             */
/*   Updated: 2025/08/20 16:31:55 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "survival_lib.h"

int	str_compare_n(const char *s1, const char *s2, size_t n)
{
	size_t	s1len;
	size_t	s2len;

	s1len = str_len(s1);
	s2len = str_len(s2);
	if (!s1 || !s2 || n == 0)
		return (0);
	if (s1len > s2len && s2len < n)
		return (mem_compare(s1, s2, s2len + 1));
	else if (s1len <= s2len && s1len < n)
		return (mem_compare(s1, s2, s1len + 1));
	return (mem_compare(s1, s2, n));
}
