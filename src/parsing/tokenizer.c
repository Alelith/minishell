/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 13:33:37 by bvarea-k          #+#    #+#             */
/*   Updated: 2025/09/17 12:59:23 by bvarea-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_file(char *file, t_redir redir_type)
{
	if (redir_type == OVERWRITE || redir_type == OUTPUT)
	{
		if (access(file, F_OK) == 0)
		{
			if (access(file, W_OK) == 0)
				return (1);
			else
				print_comm_err("Permission denied: ", file);	
		}
		else
		{
			close(open(file, O_CREAT, 00777));
			return (1);
		}		
	}
	else if (redir_type == INPUT)
	{
		if (access(file, F_OK) == 0)
		{
			if (access(file, R_OK) == 0)
				return (1);
			else
				print_comm_err("Permission denied: ", file);	
		}
		else
			print_comm_err("No such file or directory: ", file);
	}
	return (0);
}

static void	proccess_command(char *token, t_command *cmd)
{
	cmd->args = reallocation(cmd->args,
			(cmd->args_c + 1) * sizeof(t_command),
			(cmd->args_c) * sizeof(t_command));
	cmd->args[cmd->args_c] = token;
	cmd->args_c++;
}

static void proccess_redir(char **tokens, int index, t_command *cmd)
{
	if (str_compare_all(tokens[index], "<") && check_file(tokens[index + 1], INPUT))
		cmd->infile = open(tokens[index + 1], O_RDONLY);
	else if (str_compare_all(tokens[index], ">") && check_file(tokens[index + 1], OVERWRITE))
		cmd->outfile = open(tokens[index + 1], O_WRONLY);
	else if (str_compare_all(tokens[index], ">>") && check_file(tokens[index + 1], OUTPUT))
		cmd->outfile = open(tokens[index + 1], O_WRONLY);
}

t_command	*tokenize(char *input, unsigned short *len, t_shell shell)
{
	int			i;
	char		**tokens;
	t_command	*result;

	i = 0;
	if (str_len(input) == 0)
		return (0);
	result = callocation(1, sizeof(t_command));
	result[0].outfile = 1;
	*len = 1;
	tokens = split_command(input, shell.env_list);
	while (tokens && tokens[i])
	{
		if (str_compare_all(tokens[i], ">") || str_compare_all(tokens[i], "<")
				|| str_compare_all(tokens[i], ">>") || str_compare_all(tokens[i], "<<"))
		{
			proccess_redir(tokens, i, result);
			i++;
		}
		else if (!str_compare_all(tokens[i], "|"))
		{
			proccess_command(tokens[i], &result[*len - 1]);
		}
		else
		{
			free(tokens[i]);
			result = reallocation(result, (*len + 1) * sizeof(t_command),
					*len * sizeof(t_command));
			result[*len].outfile = 1;
			*len += 1;
		}
		i++;
	}
	free(tokens);
	return (result);
}
