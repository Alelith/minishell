/**
 * @file pwd.c
 * @brief Implementation of the pwd built-in command
 * 
 * @author Lilith Estévez Boeta y Begoña Varea Kuhn
 * @date 2025-08-27
 */

#include "minishell.h"

/**
 * @brief Implements the pwd built-in command
 * 
 * @details Prints the current working directory to standard output.
 * Validates that no extra arguments are provided and handles errors
 * if the current directory cannot be retrieved.
 * 
 * @ingroup builtins_module
 * 
 * @param[in] cmd Command structure containing arguments
 * @return 0 on success, 1 if too many arguments provided
 */
int	pwd(t_command cmd)
{
	char	cwd[2048];

	if (cmd.args_c > 1)
	{
		print_comm_err("pwd: Too many arguments", "");
		return (1);
	}
	if (getcwd(cwd, sizeof(cwd)) != false)
	{
		printf("%s\n", cwd);
		return (0);
	}
	print_comm_err("pwd: error retrieving current directory", "");
	return (0);
}
