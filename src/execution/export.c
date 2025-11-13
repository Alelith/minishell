/**
 * @file export.c
 * @brief Implementation of the export built-in command
 * 
 * @author Lilith Estévez Boeta y Begoña Varea Kuhn
 * @date 2025-09-01
 */

#include "minishell.h"

/**
 * @brief Saves or updates an environment variable
 * 
 * @details Updates an existing environment variable or adds a new one
 * if it doesn't exist. Creates duplicates of the key and value strings.
 * 
 * @ingroup builtins_module
 * 
 * @param[in] key Variable name
 * @param[in] value Variable value
 * @param[in,out] env Pointer to environment variable list
 */
static void	save_env(char *key, char *value, t_env **env)
{
	if (exists_env(key, *env))
		update_env(*env, key, value);
	else
		add_env(env, str_duplicate(key), str_duplicate(value));
}

/**
 * @brief Validates an environment variable key name
 * 
 * @details Checks that a key contains only alphabetic characters and
 * underscores, and is not empty.
 * 
 * @ingroup builtins_module
 * 
 * @param[in] key Variable name to validate
 * @return 1 if valid, 0 otherwise
 */
static int	is_valid_key(char *key)
{
	if (*key == 0)
		return (0);
	while (key && *key)
	{
		if (!is_alphabetic(*key) && *key != '_')
			return (0);
		key++;
	}
	return (1);
}

/**
 * @brief Saves environment variables from command arguments
 * 
 * @details Parses command arguments in "KEY=VALUE" format, validates
 * keys, and updates both the main environment and its copy. Prints
 * error for invalid identifiers.
 * 
 * @ingroup builtins_module
 * 
 * @param[in] cmd Command structure with arguments
 * @param[in,out] env Pointer to main environment variable list
 * @param[in,out] env_cpy Pointer to environment variable list copy
 * @return 0 on success, error code if invalid identifier found
 */
static int	save_var(t_command cmd, t_env **env, t_env **env_cpy)
{
	int		i;
	char	*key;
	char	*value;
	int		result;

	i = 0;
	while (++i < cmd.args_c)
	{
		key = get_key(cmd.args[i]);
		value = 0;
		if (is_valid_key(key) && str_search_char(cmd.args[i], '=') != NULL)
		{
			value = get_value(cmd.args[i]);
			save_env(key, value, env);
		}
		result = 0;
		if (!is_valid_key(key))
			result = print_comm_err("Invalid identifier: ", cmd.args[i]);
		else
			save_env(key, value, env_cpy);
		free(key);
		if (value)
			free(value);
	}
	return (result);
}

/**
 * @brief Implements the export built-in command
 * 
 * @details Exports environment variables or displays all exported
 * variables. With arguments, sets or modifies variables. Without
 * arguments, displays all variables in sorted order.
 * 
 * @ingroup builtins_module
 * 
 * @param[in] cmd Command structure containing arguments
 * @param[in,out] env Pointer to main environment variable list
 * @param[in,out] env_cpy Pointer to environment variable list copy
 * @return 0 on success, error code on invalid identifier
 */
int	export(t_command cmd, t_env **env, t_env **env_cpy)
{
	if (cmd.args_c > 1)
		return (save_var(cmd, env, env_cpy));
	else
		return (print_sorted_env(*env_cpy));
}
