/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 22:46:43 by acesteve          #+#    #+#             */
/*   Updated: 2025/09/16 09:15:20 by bvarea-k         ###   ########.fr       */
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
