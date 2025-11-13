/**
 * @file tokenizer_utils.c
 * @brief Utility functions for tokenization process
 * 
 * @author Lilith Estévez Boeta y Begoña Varea Kuhn
 * @date 2025-09-21
 */

#include "minishell.h"

/**
 * @brief Initializes a new command structure
 * 
 * @details Allocates and zero-initializes a command structure with
 * stdout as the default output file descriptor.
 * 
 * @ingroup parsing_module
 * 
 * @return Newly allocated command structure, or NULL on allocation failure
 */
t_command	*init_command(void)
{
	t_command	*cmd;

	cmd = callocation(1, sizeof(t_command));
	cmd[0].outfile = 1;
	return (cmd);
}

/**
 * @brief Extracts tokens from input string
 * 
 * @details Wrapper function that calls split_command to perform
 * tokenization with environment variable expansion.
 * 
 * @ingroup parsing_module
 * 
 * @param[in] input Command line string to tokenize
 * @param[in] shell Shell state for variable expansion
 * @return Array of tokens extracted from input
 */
t_token	*get_tokens(char *input, t_shell shell)
{
	t_token	*tokens;

	tokens = split_command(input, &shell);
	return (tokens);
}

/**
 * @brief Checks if token is a pipe operator
 * 
 * @details Determines if the given token string represents a pipe
 * operator ("|") for command chaining.
 * 
 * @ingroup parsing_module
 * 
 * @param[in] token Token string to check
 * @return 1 if token is pipe operator, 0 otherwise
 */
int	is_pipe_token(char *token)
{
	if (str_compare_all(token, "|"))
		return (1);
	return (0);
}

/**
 * @brief Checks if token is a redirection operator
 * 
 * @details Determines if the given token string represents any of the
 * redirection operators: "<", ">", ">>", or "<<".
 * 
 * @ingroup parsing_module
 * 
 * @param[in] token Token string to check
 * @return 1 if token is redirection operator, 0 otherwise
 */
int	is_redir_token(char *token)
{
	if (str_compare_all(token, ">"))
		return (1);
	if (str_compare_all(token, "<"))
		return (1);
	if (str_compare_all(token, ">>"))
		return (1);
	if (str_compare_all(token, "<<"))
		return (1);
	return (0);
}
