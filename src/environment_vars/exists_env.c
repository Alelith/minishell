/**
 * @file exists_env.c
 * @brief Function to check environment variable existence
 * 
 * @author Lilith Estévez Boeta y Begoña Varea Kuhn
 * @date 2025-09-02
 */

#include "minishell.h"

/**
 * @brief Checks if an environment variable exists in the list
 * 
 * @details Searches the environment variable list for a variable with
 * the specified key name.
 * 
 * @ingroup environment_module
 * 
 * @param[in] key Environment variable name to search for
 * @param[in] env Head of environment variable linked list
 * @return 1 if variable exists, 0 otherwise
 */
int	exists_env(char *key, t_env *env)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (str_compare_all(current->pair.key, key))
			return (1);
		current = current->next;
	}
	return (0);
}
