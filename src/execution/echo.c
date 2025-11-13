/**
 * @file echo.c
 * @brief Implementation of the echo built-in command
 * 
 * @author Lilith Estévez Boeta y Begoña Varea Kuhn
 * @date 2025-08-27
 */

#include "minishell.h"

/**
 * @brief Checks if a string consists only of 'n' characters
 * 
 * @details Helper function to validate -n flag format for echo command.
 * Used to support multiple -n flags like -nn, -nnn, etc.
 * 
 * @ingroup builtins_module
 * 
 * @param[in] ptr String to check
 * @return 1 if string contains only 'n' characters, 0 otherwise
 */
static int	is_all_n(char *ptr)
{
	while (*ptr)
	{
		if (*ptr != 'n')
			return (0);
		ptr++;
	}
	return (1);
}

/**
 * @brief Implements the echo built-in command
 * 
 * @details Prints arguments to standard output separated by spaces.
 * Supports the -n flag to suppress the trailing newline. Multiple
 * consecutive -n flags (e.g., -nn, -nnn) are treated as a single -n.
 * 
 * @ingroup builtins_module
 * 
 * @param[in] command Command structure containing arguments
 * @return Always returns 0 (success)
 */
int	echo(t_command command)
{
	int	flag;
	int	i;

	flag = 0;
	i = 1;
	while (i < command.args_c && command.args[i] && command.args[i][0] == '-'
			&& is_all_n(&command.args[i][1]))
	{
		flag = 1;
		i++;
	}
	while (i < command.args_c - 1)
	{
		printf("%s ", command.args[i]);
		i++;
	}
	if (command.args[i])
		printf("%s", command.args[i]);
	if (!flag)
		printf("\n");
	return (0);
}
