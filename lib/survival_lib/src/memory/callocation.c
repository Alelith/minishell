/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callocation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:11:14 by acesteve          #+#    #+#             */
/*   Updated: 2025/08/20 18:09:37 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "survival_lib.h"

void	*callocation(size_t nmemb, size_t size)
{
	void	*result;

	result = malloc(nmemb * size);
	if (!result)
		return (NULL);
	set_zero(result, nmemb * size);
	return (result);
}
