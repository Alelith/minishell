/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_substring.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:34:16 by acesteve          #+#    #+#             */
/*   Updated: 2025/08/20 11:42:01 by bvarea-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "survival_lib.h"
#include <stdlib.h>

char	*str_substring(char const *s, unsigned int start, size_t len)
{
	unsigned int	srclen;
	char			*result;

	srclen = str_len(s);
	if (start > srclen)
		return (str_duplicate(""));
	if (len > srclen - start)
		len = srclen - start;
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	str_copy(result, &s[start], len + 1);
	return (result);
}
