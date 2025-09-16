/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_to_uint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 22:51:20 by acesteve          #+#    #+#             */
/*   Updated: 2025/09/16 09:14:59 by bvarea-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned int	str_to_uint(const char *nptr)
{
	unsigned int	result;

	result = 0;
	while (*nptr)
	{
		result = result * 10 + (*nptr - '0');
		nptr++;
	}
	return (result);
}
