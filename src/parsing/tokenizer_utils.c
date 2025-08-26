/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgo <bgo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:31:40 by bvarea-k          #+#    #+#             */
/*   Updated: 2025/08/26 17:07:05 by bgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirection_token(char *tokens)
{
	return (str_compare_all(tokens, "<") || str_compare_all(tokens, ">")
			|| str_compare_all(tokens, "<<") || str_compare_all(tokens, ">>"));
}

int	should_handle_as_command(char *tokens, int is_first)
{
	return (is_first || str_compare_all(tokens, "|")
			|| str_compare_n(tokens, "-", 1));
}
int	starts_with_quote(char *tokens)
{
	return (str_search_char(tokens, '"') == tokens);
}
