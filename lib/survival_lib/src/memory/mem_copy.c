/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_copy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:19:01 by acesteve          #+#    #+#             */
/*   Updated: 2025/09/16 09:15:09 by bvarea-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "survival_lib.h"

void	*mem_copy(void *dest, const void *src, size_t n)
{
	char	*d;
	char	*s;

	if (!dest && !src && n > 0)
		return (NULL);
	d = (char *)dest;
	s = (char *)src;
	while (n--)
		*d++ = *s++;
	return (dest);
}
