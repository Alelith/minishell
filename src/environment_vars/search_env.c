/**
 * @file search_env.c
 * @brief Function to search for environment variable values
 * 
 * @author Lilith Estévez Boeta y Begoña Varea Kuhn
 * @date 2025-09-04
 */

#include "minishell.h"

/**
 * @brief Searches for an environment variable and returns its value
 * 
 * @details Traverses the environment variable list to find a variable
 * with the specified key and returns a pointer to its value string.
 * 
 * @ingroup environment_module
 * 
 * @param[in] envs Head of environment variable linked list
 * @param[in] key Environment variable name to search for
 * @return Pointer to the value string if found, NULL otherwise
 */
char	*search_env(t_env *envs, const char *key)
{
	t_env	*curr;

	curr = envs;
	while (curr)
	{
		if (str_compare_all(curr->pair.key, key))
			return (curr->pair.value);
		curr = curr->next;
	}
	return (0);
}
