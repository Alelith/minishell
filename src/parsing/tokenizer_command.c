/**
 * @file tokenizer_command.c
 * @brief Command argument processing for tokenization
 * 
 * @author Lilith Estévez Boeta y Begoña Varea Kuhn
 * @date 2025-09-21
 */

#include "minishell.h"

/**
 * @brief Adds a token as an argument to a command structure
 * 
 * @details Expands the command's argument array and appends the token
 * string. Takes ownership of the token string (no duplication).
 * 
 * @ingroup parsing_module
 * 
 * @param[in] token Token string to add as argument
 * @param[in,out] cmd Command structure to update
 */
void	proccess_command(char *token, t_command *cmd)
{
	void	*tmp;

	tmp = reallocation(cmd->args, (cmd->args_c + 1) * sizeof(t_command),
			(cmd->args_c) * sizeof(t_command));
	cmd->args = tmp;
	cmd->args[cmd->args_c] = token;
	cmd->args_c++;
}
