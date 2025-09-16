/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 13:26:02 by acesteve          #+#    #+#             */
/*   Updated: 2025/09/16 09:16:29 by bvarea-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export(const char *key, const char *value)
{
	if (value)
		printf("\e[38;5;44mdeclare \e[38;5;165m-x "
			"\e[38;5;35m%s=\"%s\"\n\033[0;39m", key, value);
	else
		printf("\e[38;5;44mdeclare \e[38;5;165m-x "
			"\e[38;5;35m%s=\n\033[0;39m", key);
}
