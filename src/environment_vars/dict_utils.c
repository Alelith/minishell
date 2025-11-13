/**
 * @file dict_utils.c
 * @brief Utility functions for parsing environment variable strings
 * 
 * @author Lilith Estévez Boeta y Begoña Varea Kuhn
 * @date 2025-09-01
 */

#include "minishell.h"

/**
 * @brief Extracts the key portion from an environment string
 * 
 * @details Parses an environment string in "KEY=VALUE" format and
 * returns a newly allocated string containing only the key portion
 * (everything before the '=' character).
 * 
 * @ingroup environment_module
 * 
 * @param[in] envp Environment string in "KEY=VALUE" format
 * @return Newly allocated string with the key, must be freed by caller
 */
char	*get_key(char *envp)
{
	return (str_substring(envp, 0, str_search_char(envp, '=') - envp));
}

/**
 * @brief Extracts the value portion from an environment string
 * 
 * @details Parses an environment string in "KEY=VALUE" format and
 * returns a newly allocated string containing only the value portion
 * (everything after the '=' character).
 * 
 * @ingroup environment_module
 * 
 * @param[in] envp Environment string in "KEY=VALUE" format
 * @return Newly allocated string with the value, must be freed by caller
 */
char	*get_value(char *envp)
{
	return (str_duplicate(str_search_char(envp, '=') + 1));
}
