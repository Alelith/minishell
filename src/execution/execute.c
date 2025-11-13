/**
 * @file execute.c
 * @brief External command execution with PATH resolution
 * 
 * @author Lilith Estévez Boeta y Begoña Varea Kuhn
 * @date 2025-09-02
 */

#include "minishell.h"

/**
 * @brief Checks if a string consists only of whitespace characters
 * 
 * @details Validates that a string contains only spaces, tabs, newlines,
 * or carriage returns. Used to filter out empty command paths.
 * 
 * @ingroup execution_module
 * 
 * @param[in] str String to check
 * @return 1 if string is all whitespace, 0 otherwise
 */
static int	is_all_spaces(char *str)
{
	while (str && *str)
	{
		if (!is_from_set(*str, " \n\t\r"))
			return (0);
		str++;
	}
	return (1);
}

/**
 * @brief Executes an external command using execve
 * 
 * @details Resolves the command path using the PATH environment variable,
 * converts the environment list to string array format, and executes the
 * command using execve(). Handles command not found and execution errors.
 * 
 * @ingroup execution_module
 * 
 * @param[in] command Command structure with arguments
 * @param[in] env_list Environment variable linked list
 * @return Error code on failure (function doesn't return on success)
 * @retval 0 Success (never actually returned as execve replaces process)
 * @retval 1 Execution error or command not found
 */
int	execute(t_command command, t_env *env_list)
{
	char	*path;
	char	**envp;
	int		err_code;
	int		i;

	i = 0;
	err_code = 0;
	envp = env_to_string_list(env_list);
	if (!envp)
		return (1);
	path = search_command(command.args[0], search_env(env_list, "PATH"));
	if (path)
	{
		if (!is_all_spaces(path) && execve(path, command.args, envp) == -1)
			err_code = print_comm_err("Error executing command: ", path);
		free(path);
	}
	else
		err_code = print_comm_err("Command not found: ", command.args[0]);
	while (envp[i])
		free(envp[i++]);
	free(envp);
	return (err_code);
}
