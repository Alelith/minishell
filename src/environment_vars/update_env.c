/**
 * @file update_env.c
 * @brief Function to update existing environment variable values
 * 
 * @author Lilith Estévez Boeta y Begoña Varea Kuhn
 * @date 2025-09-01
 */

#include "minishell.h"

/**
 * @brief Updates the value of an existing environment variable
 * 
 * @details Searches for an environment variable with the specified key
 * and updates both its key and value with newly allocated duplicates
 * of the provided strings. Frees the old key and value strings.
 * 
 * @ingroup environment_module
 * 
 * @param[in,out] env_list Head of environment variable linked list
 * @param[in] key Environment variable name to update
 * @param[in] value New value for the environment variable
 * @return Always returns 0
 */
int	update_env(t_env *env_list, const char *key, const char *value)
{
	t_env	*current;

	current = env_list;
	while (current)
	{
		if (str_compare_all(current->pair.key, key))
		{
			free(current->pair.key);
			free(current->pair.value);
			current->pair.key = str_duplicate(key);
			current->pair.value = str_duplicate(value);
			return (0);
		}
		current = current->next;
	}
	return (0);
}
