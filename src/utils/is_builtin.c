/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 16:55:21 by acesteve          #+#    #+#             */
/*   Updated: 2025/09/21 16:58:01 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	if (str_compare_all(cmd, "echo"))
		return (1);
	else if (str_compare_all(cmd, "exit"))
		return (1);
	else if (str_compare_all(cmd, "cd"))
		return (1);
	else if (str_compare_all(cmd, "pwd"))
		return (1);
	else if (str_compare_all(cmd, "export"))
		return (1);
	else if (str_compare_all(cmd, "unset"))
		return (1);
	else if (str_compare_all(cmd, "env"))
		return (1);
	else if (str_compare_all(cmd, "clear"))
		return (1);
	return (0);
}
