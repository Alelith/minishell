/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bnum_to_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 23:00:35 by acesteve          #+#    #+#             */
/*   Updated: 2025/08/25 09:52:14 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "survival_lib.h"

static int	bnum_len(int num, int base)
{
	int	len;

	len = 0;
	if (num == 0)
		return (1);
	while (num > 0)
	{
		num /= base;
		len++;
	}
	return (len);
}

char	*bnum_to_str(int number, int base, int is_upper)
{
	const char	*digits;
	char		*result;
	int			i;
	int			length;

	if (is_upper)
		digits = "0123456789ABCDEF";
	else
		digits = "0123456789abcdef";
	length = bnum_len(number, base);
	i = length - 1;
	result = (char *)malloc(length + 1);
	if (!result)
		return (0);
	if (number == 0)
		result[i--] = '0';
	while (number > 0)
	{
		result[i--] = digits[number % base];
		number /= base;
	}
	result[length] = '\0';
	return (result);
}
