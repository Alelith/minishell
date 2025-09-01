/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 11:45:52 by bvarea-k          #+#    #+#             */
/*   Updated: 2025/09/01 13:14:35 by bvarea-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export(t_command cmd, t_env *env)
{
	return (add_env(&env, get_key(cmd.args[0]), get_value(cmd.args[0])));
}
