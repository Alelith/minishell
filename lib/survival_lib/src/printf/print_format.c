/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 22:45:17 by acesteve          #+#    #+#             */
/*   Updated: 2025/08/25 09:38:30 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "survival_lib.h"
#include "printf_internal.h"

static int	proccess_format(va_list args, char format)
{
	char	c;
	int		len;

	len = 0;
	if (format == '%')
		len = write(1, "%", 1);
	else if (format == 'd' || format == 'i' || format == 'u' || format == 'x'
		|| format == 'X' || format == 'p' || format == 'f' || format == 'o')
		len = print_nbr(args, format);
	else if (format == 's')
		len = print_str(va_arg(args, char *));
	else if (format == 'c')
	{
		c = (char)va_arg(args, int);
		len = write(1, &c, 1);
	}
	return (len);
}

int	print_format(const char *format, ...)
{
	va_list	args;
	int		len;

	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			len += proccess_format(args, *format);
			format++;
		}
		else
		{
			write(1, format, 1);
			format++;
			len++;
		}
	}
	va_end(args);
	return (len);
}
