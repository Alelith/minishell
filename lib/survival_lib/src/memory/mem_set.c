/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:16:55 by acesteve          #+#    #+#             */
/*   Updated: 2025/09/16 09:15:12 by bvarea-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "survival_lib.h"

void	*mem_set(void *s, int c, size_t n)
{
	char	*src;

	src = (char *) s;
	while (n > 0)
	{
		src[n - 1] = c;
		n--;
	}
	return (s);
}
