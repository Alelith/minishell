/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_contains.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 09:23:33 by acesteve          #+#    #+#             */
/*   Updated: 2025/10/18 09:25:16 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "survival_lib.h"

int	str_contains(char *str, char *set)
{
	while (str && *str)
	{
		if (is_from_set(*str, set))
			return (1);
		str++;
	}
	return (0);
}
