/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 10:31:52 by acesteve          #+#    #+#             */
/*   Updated: 2025/09/23 11:32:50 by bvarea-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
# include <sys/types.h>

typedef struct s_env	t_env;

typedef enum e_bool
{
	true = 1,
	false = 0
}	t_bool;

typedef enum e_redir
{
	INPUT,
	OUTPUT,
	OVERWRITE
}	t_redir;

typedef struct s_command
{
	int		args_c;
	char	**args;
	int		infile;
	int		outfile;
	char	*heredoc_eof;
	int		has_error;
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
	t_env			*env_list_cpy;
	t_command		*commands;
	unsigned short	cmd_length;
	int				std_out;
	int				std_in;
	char			*last_path;
	int				last_exitcod;
}	t_shell;

/*=============================================================================
--------------------------- Tokenization and Parsing --------------------------
=============================================================================*/
char		**split_command(char *line, t_shell *shell);
t_command	*tokenize(char *input, unsigned short *len, t_shell shell);
void		free_commands(t_command *commands, unsigned short length);

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
---------------------------------- Built-insint -------------------------------
=============================================================================*/
int			echo(t_command command);
int			exit_exec(t_shell shell, char *line);
int			pwd(void);
int			cd(t_command command);
int			env(t_env *env_list);
int			export(t_command cmd, t_env *env, t_env *env_cpy);
int			unset(t_command cmd, t_env **env_list);
int			execute(t_command command, t_env *env_list);
char		*search_command(char *command, char *exec_paths);
void		set_signals_main(void);
void		set_signals_child(void);
void		switch_flag(int i);

int			check_command_line(char *line);
int			is_builtin(char *cmd);
int			is_redirection(char c);
void		print_open_banner(void);
void		print_close_banner(void);
int			print_comm_err(const char *message, const char *comm);
void		print_export(const char *key, const char *value);
int			any_has_error(t_command *cmd, unsigned short cmd_count);

void		proccess_command(char *token, t_command *cmd);
int			check_file(char *file, t_redir redir_type);
void		proccess_redir(char **tokens, int index, t_command *cmd);
t_command	*init_command(void);
char		**get_tokens(char *input, t_shell shell);
int			is_pipe_token(char *token);
int			is_redir_token(char *token);
int			try_command(t_shell shell, char *line);
void		handle_heredoc(t_command *cmd);
//TODO: delete all these functions
void		print_str_lst(char **lst);

#endif
