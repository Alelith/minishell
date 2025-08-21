/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_alphabetic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:04:55 by acesteve          #+#    #+#             */
/*   Updated: 2025/08/20 17:00:32 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file is_alphabetic.c
 * @author Begonia de todos los santos
 * @author Liliana la de la ehquina
 * @brief This file contains the implementation of the is_alphabetic function.
 */

int	is_alphabetic(int c)
{
	return ((c >= 65 && c <= 90) || (c >= 97 && c <= 122));
}
