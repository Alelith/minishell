/**
 * @file env_to_string_list.c
 * @brief Function to convert environment list to string array
 * 
 * @author Lilith Estévez Boeta y Begoña Varea Kuhn
 * @date 2025-09-02
 */

#include "minishell.h"

/**
 * @brief Fills an array element with formatted environment variable string
 * 
 * @details Creates a string in "KEY=VALUE" format from an environment node
 * and stores it in the provided array position. Handles cases where value
 * may be NULL.
 * 
 * @ingroup environment_module
 * 
 * @param[out] envp Pointer to array element to fill
 * @param[in] current Environment node containing key-value pair
 */
static void	fill_element(char **envp, t_env *current)
{
	char	*tmp;

	if (current->pair.value)
	{
		tmp = str_join(current->pair.key, "=");
		*envp = str_join(tmp, current->pair.value);
		free(tmp);
	}
	else
		*envp = str_join(current->pair.key, "=");
}

/**
 * @brief Converts environment variable list to NULL-terminated string array
 * 
 * @details Transforms the linked list of environment variables into a
 * traditional execve-compatible string array where each element is in
 * "KEY=VALUE" format and the array is NULL-terminated.
 * 
 * @ingroup environment_module
 * 
 * @param[in] env_list Head of environment variable linked list
 * @return Newly allocated NULL-terminated string array, must be freed
 * @retval NULL if allocation fails
 */
char	**env_to_string_list(t_env *env_list)
{
	t_env	*current;
	char	**envp;
	int		size;

	size = 0;
	current = env_list;
	while (current)
	{
		size++;
		current = current->next;
	}
	envp = callocation(size + 1, sizeof(char *));
	if (!envp)
		return (NULL);
	current = env_list;
	size = 0;
	while (current)
	{
		fill_element(&envp[size], current);
		size++;
		current = current->next;
	}
	envp[size] = NULL;
	return (envp);
}
