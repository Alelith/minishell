/**
 * @file set_env.c
 * @brief Function to initialize environment variable list from array
 * 
 * @author Lilith Estévez Boeta y Begoña Varea Kuhn
 * @date 2025-09-01
 */

#include "minishell.h"

/**
 * @brief Creates an environment variable linked list from string array
 * 
 * @details Parses a NULL-terminated array of environment strings in
 * "KEY=VALUE" format and constructs a linked list of t_env nodes.
 * This is typically used to convert the main() envp parameter into
 * the shell's internal environment representation.
 * 
 * @ingroup environment_module
 * 
 * @param[in] envp NULL-terminated array of environment strings
 * @return Head of newly created environment variable list
 * @retval NULL if envp is empty or allocation fails
 */
t_env	*set_env(char **envp)
{
	t_env	*env_list;
	int		i;
	char	*key;
	char	*value;

	env_list = NULL;
	i = 0;
	while (envp[i])
	{
		key = get_key(envp[i]);
		value = get_value(envp[i]);
		add_env(&env_list, key, value);
		i++;
	}
	return (env_list);
}
