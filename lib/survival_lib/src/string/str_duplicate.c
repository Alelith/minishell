/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_duplicate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:16:25 by acesteve          #+#    #+#             */
/*   Updated: 2025/08/20 11:39:49 by bvarea-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "survival_lib.h"
#include <stdlib.h>

char	*str_duplicate(const char *s)
{
	char	*result;

	result = malloc(str_len(s) + 1);
	if (!result)
		return (NULL);
	str_copy(result, s, str_len(s) + 1);
	return (result);
}
