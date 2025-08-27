/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 10:31:52 by acesteve          #+#    #+#             */
/*   Updated: 2025/08/27 13:54:55 by bvarea-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "survival_lib.h"
# include "get_next_line.h"
# include <unistd.h>
# include <dirent.h>

typedef enum e_bool
{
	true = 1,
	false = 0
}	t_bool;

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
void		handle_redirection(char *tokens, t_command **result,
				short *len);
void		handle_command_or_pipe(char *tokens,
				t_command **result, short *len, int *is_first);
void		handle_quoted_arg(char **tokens,
				int *i, t_command **res, short *len, int *is_quoted);
void		handle_regular_arg(char *token, t_command **res, short *len);
int			is_redirection_token(char *tokens);
int			should_handle_as_command(char *tokens, int is_first);
int			starts_with_quote(char *tokens);

int			echo(t_command command);
int			exit_exec(void);
int			pwd(void);
int			cd(t_command command);
#endif
