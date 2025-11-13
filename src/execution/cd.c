/**
 * @file cd.c
 * @brief Implementation of the cd built-in command
 * 
 * @author Lilith Estévez Boeta y Begoña Varea Kuhn
 * @date 2025-08-27
 */

#include "minishell.h"

/**
 * @brief Retrieves the current working directory path with trailing slash
 * 
 * @details Gets the current directory using getcwd and appends a trailing
 * slash for path concatenation operations.
 * 
 * @ingroup builtins_module
 * 
 * @return Newly allocated path string with trailing slash, or NULL on error
 */
static char	*get_current_path(void)
{
	char	*cwd;
	char	*current_path;

	cwd = getcwd(0, 0);
	if (!cwd)
		return (NULL);
	current_path = str_join(cwd, "/");
	free(cwd);
	return (current_path);
}

/**
 * @brief Resolves the target path for cd command
 * 
 * @details Determines the target directory based on command arguments:
 * - No args or "~": HOME directory
 * - Relative path: appended to current path
 * - Handles error cases like missing HOME variable
 * 
 * @ingroup builtins_module
 * 
 * @param[in] command Command structure with arguments
 * @param[in] current_path Current working directory path
 * @return Newly allocated target path, or NULL on error
 */
static char	*resolve_cd_path(t_command command, char *current_path)
{
	char	*path;

	if (command.args_c == 1 || (command.args_c == 2
			&& str_compare_all(command.args[1], "~")))
	{
		path = str_duplicate(getenv("HOME"));
		if (!path)
		{
			free(current_path);
			print_comm_err("cd: HOME not set", "");
			return (NULL);
		}
	}
	else if (command.args_c == 2)
		path = str_join(current_path, command.args[1]);
	else
	{
		free(current_path);
		return (NULL);
	}
	return (path);
}

/**
 * @brief Handles cd command errors and cleanup
 * 
 * @details Prints error message and frees allocated memory when cd fails.
 * 
 * @ingroup builtins_module
 * 
 * @param[in] path Target path that failed
 * @param[in] current_path Current working directory path
 * @param[in] arg Original argument passed to cd
 * @return Always returns 1 (error)
 */
static int	handle_cd_error(char *path, char *current_path, char *arg)
{
	print_comm_err("cd: cannot access file or directory: ", arg);
	if (current_path)
		free(current_path);
	if (path)
		free(path);
	return (1);
}

/**
 * @brief Executes the directory change operation
 * 
 * @details Handles special cases like "-" (previous directory) and ".."
 * (parent directory), updates the shell's last_path, and performs the
 * actual chdir system call.
 * 
 * @ingroup builtins_module
 * 
 * @param[in] command Command structure with arguments
 * @param[in,out] path Target directory path
 * @param[in,out] current_path Current working directory path
 * @param[in,out] shell Shell state structure
 * @return 0 on success, 1 on error
 */
static int	execute_cd(t_command command, char **path,
	char **current_path, t_shell *shell)
{
	if (str_compare_all(command.args[1], "-") || str_compare_all(*path, ".."))
	{
		if (*path)
			free(*path);
		*path = str_duplicate(shell->last_path);
		while (access(*path, F_OK) != 0)
		{
			free(*path);
			shell->last_path = get_last_path(shell->last_path);
			*path = str_duplicate(shell->last_path);
		}
		if (str_len(*path) == 0)
		{
			free(*path);
			*path = str_duplicate("/");
		}
	}
	if (chdir(*path))
		return (handle_cd_error(*path, *current_path, command.args[1]));
	if (*current_path)
	{
		free(shell->last_path);
		shell->last_path = str_duplicate(*current_path);
	}
	return (0);
}

/**
 * @brief Implements the cd built-in command
 * 
 * @details Changes the current working directory. Supports:
 * - No arguments or "~": change to HOME
 * - Absolute path: change to specified directory
 * - Relative path: change relative to current directory
 * - "-": change to previous directory (OLDPWD)
 * - "..": change to parent directory
 * 
 * @ingroup builtins_module
 * 
 * @param[in,out] shell Shell state structure
 * @param[in] command Command structure containing arguments
 * @return 0 on success, 1 on error
 */
int	cd(t_shell *shell, t_command command)
{
	char	*current_path;
	char	*path;

	current_path = get_current_path();
	path = 0;
	if (command.args_c == 1 || (command.args_c == 2
			&& !str_compare_n(command.args[1], "/", 1)))
		path = resolve_cd_path(command, current_path);
	else if (command.args_c == 2 && !str_compare_all(command.args[1], "-"))
		path = str_duplicate(command.args[1]);
	else
	{
		free(current_path);
		return (print_comm_err("cd: too many arguments", ""));
	}
	if (execute_cd(command, &path, &current_path, shell))
		return (1);
	free(path);
	free(current_path);
	return (0);
}
