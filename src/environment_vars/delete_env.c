/**
 * @file delete_env.c
 * @brief Function to delete an environment variable from the list
 * 
 * @author Lilith Estévez Boeta y Begoña Varea Kuhn
 * @date 2025-09-02
 */

#include "minishell.h"

/**
 * @brief Deletes an environment variable from the list by key
 * 
 * @details Searches for an environment variable with the specified key
 * and removes it from the linked list. Frees all associated memory
 * including the key, value, and node structure.
 * 
 * @ingroup environment_module
 * 
 * @param[in,out] env_list Pointer to the environment variable list head
 * @param[in] key Environment variable name to delete
 * @return Always returns 0
 */
int	delete_env(t_env **env_list, char *key)
{
	t_env	*current;
	t_env	*previous;

	current = *env_list;
	previous = NULL;
	while (current)
	{
		if (str_compare_all(current->pair.key, key))
		{
			if (previous)
				previous->next = current->next;
			else
				*env_list = current->next;
			free(current->pair.key);
			free(current->pair.value);
			free(current);
			return (0);
		}
		previous = current;
		current = current->next;
	}
	return (0);
}
