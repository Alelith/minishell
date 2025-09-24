/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_last_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 09:07:27 by bvarea-k          #+#    #+#             */
/*   Updated: 2025/09/24 09:22:55 by bvarea-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_last_path(char *this_path)
{
	char	*last;

	if (this_path[str_len(this_path) - 1] == '/')
		this_path[str_len(this_path) - 1] = 0;
	last = str_search_rev_char(this_path, '/');
	*last = 0;
	return (this_path);
}
