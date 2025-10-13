/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_search_set.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:34:53 by acesteve          #+#    #+#             */
/*   Updated: 2025/10/13 11:55:13 by bvarea-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "survival_lib.h"

char	*str_search_set(const char *s, const char *set)
{
	while (set && *set)
	{
		if (str_search_char(s, *set))
			return (str_search_char(s, *set));
		set++;
	}
	return (0);
}
