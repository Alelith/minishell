/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 10:31:52 by acesteve          #+#    #+#             */
/*   Updated: 2025/09/09 17:37:07 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//https://manytools.org/hacker-tools/ascii-banner/
# define OPEN_BANNER "\033c\033[0;95m\
██╗    ██╗███████╗██╗      ██████╗ ██████╗ ███╗   ███╗███████╗ \n\
██║    ██║██╔════╝██║     ██╔════╝██╔═══██╗████╗ ████║██╔════╝ \n\
██║ █╗ ██║█████╗  ██║     ██║     ██║   ██║██╔████╔██║█████╗   \n\
██║███╗██║██╔══╝  ██║     ██║     ██║   ██║██║╚██╔╝██║██╔══╝   \n\
╚███╔███╔╝███████╗███████╗╚██████╗╚██████╔╝██║ ╚═╝ ██║███████╗ \n\
 ╚══╝╚══╝ ╚══════╝╚══════╝ ╚═════╝ ╚═════╝ ╚═╝     ╚═╝╚══════╝ \n\n\
████████╗ ██████╗                                              \n\
╚══██╔══╝██╔═══██╗                                             \n\
   ██║   ██║   ██║                                             \n\
   ██║   ██║   ██║                                             \n\
   ██║   ╚██████╔╝                                             \n\
   ╚═╝    ╚═════╝                                              \n\n\
██████╗  ██████╗ ███╗   ██╗ ██████╗██╗  ██╗██╗████████╗ █████╗  \n\
██╔════╝██╔═══██╗████╗  ██║██╔════╝██║  ██║██║╚══██╔══╝██╔══██╗ \n\
██║     ██║   ██║██╔██╗ ██║██║     ███████║██║   ██║   ███████║ \n\
██║     ██║   ██║██║╚██╗██║██║     ██╔══██║██║   ██║   ██╔══██║ \n\
╚██████╗╚██████╔╝██║ ╚████║╚██████╗██║  ██║██║   ██║   ██║  ██║ \n\
 ╚═════╝ ╚═════╝ ╚═╝  ╚═══╝ ╚═════╝╚═╝  ╚═╝╚═╝   ╚═╝   ╚═╝  ╚═╝ \n\n\033[0;39m"
# define CLOSE_BANNER ""

# include "survival_lib.h"
# include <unistd.h>
# include <fcntl.h>
# include <dirent.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/wait.h>
# include <readline/history.h>
# include <readline/readline.h>

typedef struct s_env	t_env;

typedef enum e_bool
{
	true = 1,
	false = 0
}	t_bool;

typedef struct s_command
{
	int				args_c;
	char			**args;
}	t_command;

typedef struct s_key_value
{
	char	*key;
	char	*value;
}	t_key_value;

struct s_env
{
	t_key_value	pair;
	t_env		*next;
};

typedef struct s_shell
{
	t_env			*env_list;
	t_command		*commands;
	unsigned short	cmd_length;
}	t_shell;

/*=============================================================================
--------------------------- Tokenization and Parsing --------------------------
=============================================================================*/
t_command	*tokenize(char *input, unsigned short *len);
void		free_commands(t_command *commands, unsigned short length);
void		handle_redirection(char *tokens, t_command **result,
				unsigned short *len);
void		handle_command_or_pipe(char *tokens,
				t_command **result, unsigned short *len, int *is_first);
void		handle_quoted_arg(char **tokens,
				int *i, t_command **res, unsigned short *len, int *is_quoted);
void		handle_regular_arg(char *token, t_command **res, unsigned short *len);
int			is_redirection_token(char *tokens);
int			should_handle_as_command(char *tokens, int is_first);
int			starts_with_quote(char *tokens);

/*=============================================================================
---------------------------- Environment variables ----------------------------
=============================================================================*/
int			update_env(t_env *env_list, const char *key, const char *value);
t_env		*set_env(char **envp);
int			add_env(t_env **env_list, char *key, char *value);
char		*get_key(char *envp);
char		*get_value(char *envp);
void		free_env(t_env *env_list);
int			exists_env(char *key, t_env *env);
int			delete_env(t_env **env_list, char *key);
char		**env_to_string_list(t_env *env_list);
char		*search_env(t_env *envs, const char *key);

/*=============================================================================
---------------------------------- Built-insint ----------------------------------
=============================================================================*/
int			echo(t_command command);
int			exit_exec(t_shell shell);
int			pwd(void);
int			cd(t_command command);
int			env(t_env *env_list);
int			export(t_command cmd, t_env *env);
int			unset(t_command cmd, t_env **env_list);
int			execute(t_command command, t_env *env_list);
char		*search_command(char *command, char *exec_paths);
void		set_signals_main(void);
void		set_signals_child(void);

#endif
