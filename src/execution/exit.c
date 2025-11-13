/**
 * @file exit.c
 * @brief Implementation of the exit built-in command
 * 
 * @author Lilith Estévez Boeta y Begoña Varea Kuhn
 * @date 2025-08-27
 */

#include "minishell.h"

/**
 * @brief Cleans up resources and exits the shell
 * 
 * @details Frees all allocated memory including the current line,
 * environment lists, and command structures before calling exit().
 * 
 * @ingroup builtins_module
 * 
 * @param[in] shell Shell state structure
 * @param[in] line Current command line to free
 * @param[in] exit_cod Exit code to pass to exit()
 */
static void	clean_exit(t_shell shell, char *line, int exit_cod)
{
	free(line);
	free_env(shell.env_list);
	free_env(shell.env_list_cpy);
	free_commands(shell.commands, shell.cmd_length);
	exit(exit_cod);
}

/**
 * @brief Implements the exit built-in command
 * 
 * @details Exits the shell with an optional status code. Validates that
 * the provided argument is numeric and handles multiple argument errors.
 * Displays the closing banner before exit.
 * 
 * @ingroup builtins_module
 * 
 * @param[in] shell Shell state structure
 * @param[in] line Current command line
 * @return Exit status code (only returned on error, otherwise exits)
 * @retval 0 Success
 * @retval 1 Invalid numeric argument or too many arguments
 */
int	exit_exec(t_shell shell, char *line)
{
	int		exit_cod;
	char	*temp;

	exit_cod = 0;
	if (shell.cmd_length > 1)
		exit (0);
	print_close_banner();
	if (shell.commands[0].args_c == 2)
	{
		exit_cod = str_to_int(shell.commands[0].args[1]);
		temp = int_to_str(exit_cod);
		if (!str_compare_all(shell.commands[0].args[1], temp))
		{
			exit_cod = 1;
			print_comm_err("exit: ", "Numeric argument required");
		}
		free(temp);
	}
	else if (shell.commands[0].args_c > 2)
	{
		exit_cod = 1;
		print_comm_err("exit: ", "Too many arguments");
	}
	clean_exit(shell, line, exit_cod);
	return (exit_cod);
}
