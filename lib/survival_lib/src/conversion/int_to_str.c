/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_to_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 22:27:17 by acesteve          #+#    #+#             */
/*   Updated: 2025/09/16 09:14:56 by bvarea-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "survival_lib.h"

static int	int_len(int nbr)
{
	int	result;

	result = 0;
	if (nbr <= 0)
		result++;
	while (nbr != 0)
	{
		nbr /= 10;
		result++;
	}
	return (result);
}

char	*int_to_str(int n)
{
	int		length;
	int		sign;
	char	*result;

	length = int_len(n);
	sign = 1;
	result = malloc(length + 1);
	if (!result)
		return (NULL);
	result[length] = '\0';
	if (n < 0)
	{
		result[0] = '-';
		sign = -1;
	}
	if (n == 0)
		result[0] = 48;
	while (n != 0)
	{
		result[length - 1] = sign * (n % 10) + 48;
		n /= 10;
		length--;
	}
	return (result);
}
