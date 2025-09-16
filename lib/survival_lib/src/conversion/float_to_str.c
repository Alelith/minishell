/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_to_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 22:26:52 by acesteve          #+#    #+#             */
/*   Updated: 2025/09/16 09:14:54 by bvarea-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "survival_lib.h"

static int	float_len(float num, int decimals)
{
	int		len;
	int		int_part;

	len = 0;
	if (num < 0.0f)
	{
		len++;
		num = -num;
	}
	int_part = (int)num;
	if (int_part == 0)
		len++;
	while (int_part > 0)
	{
		int_part /= 10;
		len++;
	}
	len++;
	len += decimals;
	return (len);
}

static void	fill_float_str(char *result, float number, int decimals, int length)
{
	int		i;
	int		int_part;
	float	frac_part;
	int		digit;	

	i = length - 1;
	int_part = (int)number;
	frac_part = number - int_part;
	while (decimals-- > 0)
	{
		frac_part *= 10.0f;
		digit = (int)frac_part;
		result[i--] = digit + '0';
		frac_part -= digit;
	}
	result[i--] = '.';
	if (int_part == 0)
		result[i--] = '0';
	while (int_part > 0)
	{
		result[i--] = (int_part % 10) + '0';
		int_part /= 10;
	}
}

char	*float_to_str(float number, int decimals)
{
	int		length;
	char	*result;

	length = float_len(number, decimals);
	result = malloc(length + 1);
	if (!result)
		return (0);
	result[length] = '\0';
	if (number < 0.0f)
	{
		result[0] = '-';
		number = -number;
	}
	fill_float_str(result, number, decimals, length);
	return (result);
}
