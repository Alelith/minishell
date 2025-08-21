/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numlen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 21:56:21 by acesteve          #+#    #+#             */
/*   Updated: 2025/08/20 18:01:17 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	base_numlen(int num, int base)
{
	int	i;

	i = 0;
	if (num <= 0)
		i++;
	while (num != 0)
	{
		num /= base;
		i++;
	}
	return (i);
}

int	base_unumlen(unsigned long num, int base)
{
	int	i;

	i = 0;
	if (num == 0)
		return (1);
	while (num != 0)
	{
		num /= base;
		i++;
	}
	return (i);
}
