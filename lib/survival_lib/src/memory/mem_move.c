/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_move.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:22:20 by acesteve          #+#    #+#             */
/*   Updated: 2025/09/16 09:15:10 by bvarea-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "survival_lib.h"

void	*mem_move(void *dest, const void *src, size_t n)
{
	char	*d;
	char	*s;

	if (!dest && !src && n > 0)
		return (NULL);
	d = (char *)dest;
	s = (char *)src;
	if (dest >= src && dest <= src + n)
	{
		while (n > 0)
		{
			d[n - 1] = s[n - 1];
			n--;
		}
	}
	else
		mem_copy(dest, src, n);
	return (dest);
}
