/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 10:31:52 by acesteve          #+#    #+#             */
/*   Updated: 2025/08/26 12:43:02 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "survival_lib.h"
# include "get_next_line.h"

typedef enum e_redirection
{
	INPUT,
	OUTPUT,
	DELIMITED,
	APPEND
}	t_redirection;

typedef struct s_command
{
	char			*name;
	char			*flag;
	int				redirections_c;
	t_redirection	*redirections;
	int				args_c;
	char			**args;
}	t_command;

t_command	*tokenize(char *input, short *len);
void		free_commands(t_command *commands, short length);

#endif
