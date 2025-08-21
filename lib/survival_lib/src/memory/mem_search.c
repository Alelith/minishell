/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_search.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:36:44 by acesteve          #+#    #+#             */
/*   Updated: 2025/08/20 18:10:25 by acesteve         ###   ########.fr       */
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
	return (NULL);
}
