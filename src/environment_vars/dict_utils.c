/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 12:24:23 by bvarea-k          #+#    #+#             */
/*   Updated: 2025/09/16 09:16:06 by bvarea-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_key(char *envp)
{
	return (str_substring(envp, 0, str_search_char(envp, '=') - envp));
}

char	*get_value(char *envp)
{
	return (str_duplicate(str_search_char(envp, '=') + 1));
}
