/**
 * @file is_builtin.c
 * @brief Built-in command detection
 * 
 * @author Lilith Estévez Boeta y Begoña Varea Kuhn
 * @date 2025-09-21
 */

#include "minishell.h"

/**
 * @brief Checks if command is a shell built-in
 * 
 * @details Tests the command name against all recognized built-in
 * commands: echo, exit, cd, pwd, export, unset, env, clear.
 * 
 * @ingroup utils_module
 * 
 * @param[in] cmd Command name to test
 * @retval 1 Command is a built-in
 * @retval 0 Command is not a built-in
 */
int	is_builtin(char *cmd)
{
	if (str_compare_all(cmd, "echo"))
		return (1);
	else if (str_compare_all(cmd, "exit"))
		return (1);
	else if (str_compare_all(cmd, "cd"))
		return (1);
	else if (str_compare_all(cmd, "pwd"))
		return (1);
	else if (str_compare_all(cmd, "export"))
		return (1);
	else if (str_compare_all(cmd, "unset"))
		return (1);
	else if (str_compare_all(cmd, "env"))
		return (1);
	else if (str_compare_all(cmd, "clear"))
		return (1);
	return (0);
}
