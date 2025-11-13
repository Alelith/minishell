/**
 * @file tokenizer_redir.c
 * @brief Redirection processing and file validation
 * 
 * @author Lilith Estévez Boeta y Begoña Varea Kuhn
 * @date 2025-09-21
 */

#include "minishell.h"

/**
 * @brief Checks file accessibility for redirection operations
 * 
 * @details Validates that files exist and have appropriate permissions
 * for the specified redirection type:
 * - INPUT: File must exist and be readable
 * - OUTPUT/OVERWRITE: File must be writable if it exists
 * Prints error messages for permission or existence issues.
 * 
 * @ingroup parsing_module
 * 
 * @param[in] file File path to check
 * @param[in] redir_type Type of redirection (INPUT, OUTPUT, OVERWRITE)
 * @return 1 if file is accessible, 0 if error
 */
int	check_file(char *file, t_redir redir_type)
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
			return (1);
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

/**
 * @brief Processes redirection tokens and updates command structure
 * 
 * @details Handles all redirection types:
 * - "<": Input redirection (opens file for reading)
 * - ">": Output redirection with truncation (creates/overwrites file)
 * - ">>": Output redirection with append (creates/appends to file)
 * - "<<": Heredoc delimiter (stores delimiter for later processing)
 * Opens files with appropriate flags and stores file descriptors.
 * Sets error flag if file checks fail.
 * 
 * @ingroup parsing_module
 * 
 * @param[in] tokens Token array containing redirection and file tokens
 * @param[in] index Index of redirection operator token
 * @param[in,out] cmd Command structure to update with redirection info
 */
void	proccess_redir(t_token *tokens, int index, t_command *cmd)
{
	if (str_compare_all(tokens[index].token, "<")
		&& check_file(tokens[index + 1].token, INPUT))
		cmd->infile = open(tokens[index + 1].token, O_RDONLY);
	else if (str_compare_all(tokens[index].token, ">")
		&& check_file(tokens[index + 1].token, OVERWRITE))
		cmd->outfile = open(tokens[index + 1].token,
				O_WRONLY | O_TRUNC | O_CREAT, 00777);
	else if (str_compare_all(tokens[index].token, ">>")
		&& check_file(tokens[index + 1].token, OUTPUT))
		cmd->outfile = open(tokens[index + 1].token,
				O_WRONLY | O_APPEND | O_CREAT, 00777);
	else if (str_compare_all(tokens[index].token, "<<"))
	{
		if (cmd->heredoc_eof)
			free(cmd->heredoc_eof);
		cmd->heredoc_eof = str_duplicate(tokens[index + 1].token);
	}
	else
		cmd->has_error = 1;
	free(tokens[index].token);
	free(tokens[index + 1].token);
}
