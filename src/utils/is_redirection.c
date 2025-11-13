/**
 * @file is_redirection.c
 * @brief Redirection operator detection
 * 
 * @author Lilith Estévez Boeta y Begoña Varea Kuhn
 * @date 2025-09-16
 */

#include "minishell.h"

/**
 * @brief Tests if character is a redirection operator
 * 
 * @details Checks if character is '<', '>', or '|'. Used during parsing
 * to identify redirection and pipe operators.
 * 
 * @ingroup utils_module
 * 
 * @param[in] c Character to test
 * @retval 1 Character is a redirection operator
 * @retval 0 Character is not a redirection operator
 */
int	is_redirection(char c)
{
	return (c == '<' || c == '>' || c == '|');
}
