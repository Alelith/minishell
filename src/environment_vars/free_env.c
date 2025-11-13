/**
 * @file free_env.c
 * @brief Function to free environment variable list memory
 * 
 * @author Lilith Estévez Boeta y Begoña Varea Kuhn
 * @date 2025-09-01
 */

#include "minishell.h"

/**
 * @brief Frees all memory associated with the environment variable list
 * 
 * @details Iterates through the entire linked list, freeing each node's
 * key, value, and the node structure itself.
 * 
 * @ingroup environment_module
 * 
 * @param[in,out] env_list Head of environment variable linked list to free
 */
void	free_env(t_env *env_list)
{
	t_env	*tmp;

	while (env_list)
	{
		tmp = env_list;
		env_list = env_list->next;
		if (tmp->pair.key)
			free(tmp->pair.key);
		if (tmp->pair.value)
			free(tmp->pair.value);
		free(tmp);
	}
}
