/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_to_uint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 22:51:20 by acesteve          #+#    #+#             */
/*   Updated: 2025/08/24 22:52:50 by acesteve         ###   ########.fr       */
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
