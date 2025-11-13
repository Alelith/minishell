/**
 * @file add_env.c
 * @brief Function to add a new environment variable to the list
 * 
 * @author Lilith Estévez Boeta y Begoña Varea Kuhn
 * @date 2025-09-01
 */

#include "minishell.h"

/**
 * @brief Adds a new environment variable to the end of the list
 * 
 * @details Creates a new environment variable node and appends it to
 * the end of the linked list. Takes ownership of the provided key and
 * value strings (no duplication is performed).
 * 
 * @ingroup environment_module
 * 
 * @param[in,out] env_list Pointer to the environment variable list head
 * @param[in] key Environment variable name (ownership transferred)
 * @param[in] value Environment variable value (ownership transferred)
 * @return 1 on success, 0 on allocation failure
 */
int	add_env(t_env **env_list, char *key, char *value)
{
	t_env	*last_node;
	t_env	*new_node;

	new_node = callocation(1, sizeof(t_env));
	if (!new_node)
		return (0);
	new_node->pair.key = NULL;
	new_node->pair.value = NULL;
	new_node->next = NULL;
	if (key)
		new_node->pair.key = key;
	if (value)
		new_node->pair.value = value;
	last_node = *env_list;
	while (last_node && last_node->next)
		last_node = last_node->next;
	if (!last_node)
		*env_list = new_node;
	else
		last_node->next = new_node;
	return (1);
}
