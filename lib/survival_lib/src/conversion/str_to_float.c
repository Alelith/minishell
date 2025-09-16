/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_to_float.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 22:25:29 by acesteve          #+#    #+#             */
/*   Updated: 2025/09/16 09:14:57 by bvarea-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static float	parse_decimal(const char **nptr)
{
	float	result;
	float	decimal_place;

	result = 0.0f;
	decimal_place = 0.1f;
	while (**nptr && **nptr >= '0' && **nptr <= '9')
	{
		result += (**nptr - '0') * decimal_place;
		decimal_place *= 0.1f;
		(*nptr)++;
	}
	return (result);
}

float	str_to_float(const char *nptr)
{
	int		sign;
	float	result;

	sign = 1;
	result = 0.0f;
	if (*nptr == '-')
	{
		sign = -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	while (*nptr && *nptr >= '0' && *nptr <= '9')
	{
		result = (result * 10.0f) + (*nptr - '0');
		nptr++;
	}
	if (*nptr == '.')
	{
		nptr++;
		result += parse_decimal(&nptr);
	}
	return (result * sign);
}
