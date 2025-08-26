/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 22:46:43 by acesteve          #+#    #+#             */
/*   Updated: 2025/08/24 22:47:34 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "survival_lib.h"
#include "printf_internal.h"

int	print_str(const char *str)
{
	if (!str)
		return (0);
	return (write(1, str, str_len(str)));
}
