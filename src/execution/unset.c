/**
 * @file unset.c
 * @brief Implementation of the unset built-in command
 * 
 * @author Lilith Estévez Boeta y Begoña Varea Kuhn
 * @date 2025-09-01
 */

#include "minishell.h"

/**
 * @brief Implements the unset built-in command
 * 
 * @details Removes environment variables from both the main environment
 * list and its copy. Requires exactly one argument (the variable name
 * to unset).
 * 
 * @ingroup builtins_module
 * 
 * @param[in] cmd Command structure containing arguments
 * @param[in,out] env_list Pointer to main environment variable list
 * @param[in,out] env_cpy Pointer to environment variable list copy
 * @return 0 on success, error code if no arguments provided
 */
int	unset(t_command cmd, t_env **env_list, t_env **env_cpy)
{
	if (cmd.args_c == 2)
	{
		delete_env(env_list, cmd.args[1]);
		delete_env(env_cpy, cmd.args[1]);
	}
	else if (cmd.args_c == 1)
		return (print_comm_err("unset: not enough arguments", ""));
	return (0);
}
