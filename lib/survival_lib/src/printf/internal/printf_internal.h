/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_internal.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 22:40:25 by acesteve          #+#    #+#             */
/*   Updated: 2025/08/25 09:54:29 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_INTERNAL_H
# define PRINTF_INTERNAL_H

# include <stdarg.h>
# include <unistd.h>

/**
 * @brief Prints a number in a specified format.
 * 
 * @param args The argument list containing the value to print.
 * @param format The format specifier ('d', 'i', 'u', 'x', 'X', 'p', 'f', 'o').
 * 
 * @return The number of characters printed.
 */
int		print_nbr(va_list args, char format);
int		print_str(const char *str);

#endif
