/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_nbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 22:48:45 by acesteve          #+#    #+#             */
/*   Updated: 2025/09/16 09:15:19 by bvarea-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "survival_lib.h"
#include "printf_internal.h"

int	print_nbr(va_list args, char format)
{
	char	*str;
	int		len;

	len = 0;
	str = NULL;
	if (format == 'd' || format == 'i')
		str = int_to_str(va_arg(args, int));
	else if (format == 'u')
		str = uint_to_str((unsigned int)va_arg(args, int));
	else if (format == 'x' || format == 'X')
		str = bnum_to_str(va_arg(args, unsigned int), 16, format == 'X');
	else if (format == 'p')
	{
		len += print_str("0x");
		str = bnum_to_str((unsigned long)va_arg(args, void *), 16, 0);
	}
	else if (format == 'f')
		str = float_to_str((float)va_arg(args, double), 6);
	else if (format == 'o')
		str = bnum_to_str((unsigned int)va_arg(args, int), 8, 0);
	if (!str)
		return (0);
	len += print_str(str);
	free(str);
	return (len);
}
