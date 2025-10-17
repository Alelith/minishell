/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_duplicate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:16:25 by acesteve          #+#    #+#             */
/*   Updated: 2025/10/17 17:33:39 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "survival_lib.h"
#include <stdlib.h>

char	*str_duplicate(const char *s)
{
	char	*result;

	if (!s)
		return (0);
	result = malloc(str_len(s) + 1);
	if (!result)
		return (NULL);
	str_copy(result, s, str_len(s) + 1);
	return (result);
}
