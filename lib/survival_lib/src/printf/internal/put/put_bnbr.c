/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_bnbr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 08:37:16 by acesteve          #+#    #+#             */
/*   Updated: 2025/08/21 09:46:59 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf_internal.h"
#include "survival_lib.h"

static int	absolute(int nbr)
{
	if (nbr < 0)
		return (-nbr);
	return (nbr);
}

int	put_bnbr(int nbr, int base)
{
	char	*digits;
	int		len;
	int		sign;

	digits = "0123456789ABCDEF";
	len = 0;
	if (nbr < 0)
		sign = -1;
	else
		sign = 1;
	if (nbr == 0)
		return (write(1, "0", 1));
	while (nbr != 0)
	{
		write(1, &digits[absolute(nbr % base)], 1);
		nbr /= base;
		len++;
	}
	return (len);
}