/**
 * @file free_commands.c
 * @brief Memory deallocation for command structures
 * 
 * @author Lilith Estévez Boeta y Begoña Varea Kuhn
 * @date 2025-08-26
 */

#include "minishell.h"

/**
 * @brief Frees array of command structures and their contents
 * 
 * @details Deallocates all memory associated with a command array,
 * including argument arrays, argument strings, and heredoc delimiters.
 * Iterates through each command and frees all dynamically allocated
 * members before freeing the array itself.
 * 
 * @ingroup utils_module
 * 
 * @param[in] commands Array of command structures to free
 * @param[in] length Number of commands in the array
 */
void	free_commands(t_command *commands, unsigned short length)
{
	while (length--)
	{
		while (commands[length].args_c--)
			free(commands[length].args[commands[length].args_c]);
		if (commands[length].args)
			free(commands[length].args);
		if (commands[length].heredoc_eof)
			free(commands[length].heredoc_eof);
	}
	free(commands);
}
