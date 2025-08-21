/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_search_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:40:40 by acesteve          #+#    #+#             */
/*   Updated: 2025/08/20 11:41:07 by bvarea-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "survival_lib.h"

char	*str_search_str(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	little_len;

	i = 0;
	j = 0;
	little_len = str_len(little);
	if (little_len == 0)
		return ((char *) big);
	while (i < len && big[i])
	{
		if (big[i] == little[0])
		{
			while (j < little_len && i + j < len
				&& big[i + j] == little[j])
				j++;
			if (j == little_len)
				return ((char *)&big[i]);
		}
		j = 0;
		i++;
	}
	return (NULL);
}
