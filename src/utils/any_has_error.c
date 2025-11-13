/**
 * @file any_has_error.c
 * @brief Error state checking for command array
 * 
 * @author Lilith Estévez Boeta y Begoña Varea Kuhn
 * @date 2025-09-17
 */

#include "minishell.h"

/**
 * @brief Checks if any command has an error flag set
 * 
 * @details Iterates through command array to detect if any command
 * encountered a syntax or semantic error during parsing. Used to
 * prevent execution of invalid command pipelines.
 * 
 * @ingroup utils_module
 * 
 * @param[in] cmd Array of command structures
 * @param[in] cmd_count Number of commands in array
 * @retval 1 At least one command has error
 * @retval 0 No errors detected
 */
int	any_has_error(t_command *cmd, unsigned short cmd_count)
{
	unsigned short	i;

	i = 0;
	while (i < cmd_count)
	{
		if (cmd[i].has_error)
			return (1);
		i++;
	}
	return (0);
}
