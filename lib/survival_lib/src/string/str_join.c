/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_join.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:50:40 by acesteve          #+#    #+#             */
/*   Updated: 2025/08/20 11:40:10 by bvarea-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "survival_lib.h"
#include <stdlib.h>

char	*str_join(char const *s1, char const *s2)
{
	char	*result;

	result = malloc(str_len(s1) + str_len(s2) + 1);
	if (!result)
		return (NULL);
	str_copy(result, s1, str_len(s1) + 1);
	str_copy(&result[str_len(s1)], s2, str_len(s2) + 1);
	return (result);
}
