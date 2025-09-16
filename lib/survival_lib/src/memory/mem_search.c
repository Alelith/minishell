/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_search.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:36:44 by acesteve          #+#    #+#             */
/*   Updated: 2025/09/16 09:15:11 by bvarea-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "survival_lib.h"

void	*mem_search(const void *s, int c, size_t n)
{
	unsigned char	*src;

	c = (unsigned char)c;
	src = (unsigned char *) s;
	while (n--)
	{
		if (*src == c)
			return (src);
		src++;
	}
	return (0);
}
