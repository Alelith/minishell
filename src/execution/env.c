/**
 * @file env.c
 * @brief Implementation of the env built-in command
 * 
 * @author Lilith Estévez Boeta y Begoña Varea Kuhn
 * @date 2025-08-28
 */

#include "minishell.h"

/**
 * @brief Implements the env built-in command
 * 
 * @details Prints all environment variables to standard output in
 * "KEY=VALUE" format, one per line. Does not accept any arguments.
 * 
 * @ingroup builtins_module
 * 
 * @param[in] cmd Command structure containing arguments
 * @param[in] env_list Head of environment variable linked list
 * @return 0 on success, 1 if arguments are provided
 */
int	env(t_command cmd, t_env *env_list)
{
	t_env	*current;

	if (cmd.args_c > 1)
	{
		print_comm_err("env: Too many arguments", "");
		return (1);
	}
	current = env_list;
	while (current)
	{
		printf("%s=%s\n", current->pair.key, current->pair.value);
		current = current->next;
	}
	return (0);
}
