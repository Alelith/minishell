/**
 * @file search_command.c
 * @brief Command executable path resolution
 * 
 * @author Lilith Estévez Boeta y Begoña Varea Kuhn
 * @date 2025-09-04
 */

#include "minishell.h"

/**
 * @brief Constructs full path by joining directory and command
 * 
 * @details Helper function that concatenates a PATH directory with a
 * command name, inserting "/" separator.
 * 
 * @ingroup utils_module
 * 
 * @param[in] path Directory path
 * @param[in] command Command name
 * @return Newly allocated full path string
 */
static char	*make_res(char	*path, char *command)
{
	char	*tmp;
	char	*result;

	tmp = str_join(path, "/");
	result = str_join(tmp, command);
	free(tmp);
	return (result);
}

/**
 * @brief Frees array of path strings
 * 
 * @details Deallocates each string in a null-terminated array and the
 * array itself.
 * 
 * @ingroup utils_module
 * 
 * @param[in] paths Null-terminated array of path strings
 */
static void	free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
}

/**
 * @brief Validates execute permission for a path
 * 
 * @details Checks if the current user has execute permission for the
 * specified path. Prints error message if permission is denied.
 * 
 * @ingroup utils_module
 * 
 * @param[in] path File path to check
 * @retval 1 Execute permission granted
 * @retval 0 Execute permission denied
 */
static int	permissions_check(char *path)
{
	if (access(path, X_OK) != 0)
	{
		print_comm_err("You don't have permissions to execute this file: ",
			path);
		return (0);
	}
	return (1);
}

/**
 * @brief Validates if path is an executable file
 * 
 * @details Checks if the path exists and is a regular file (not a
 * directory). Verifies execute permissions. Frees the paths array if
 * the file is valid.
 * 
 * @ingroup utils_module
 * 
 * @param[in] result Path to validate
 * @param[in] paths Paths array to free on success
 * @return Result path if valid executable, NULL otherwise
 */
static char	*check_path(char *result, char **paths)
{
	struct stat	stat_buf;

	stat(result, &stat_buf);
	if (access(result, F_OK) == 0
		&& !((((stat_buf.st_mode)) & 0170000) == (0040000)))
	{
		if (permissions_check(result))
		{
			free_paths(paths);
			return (result);
		}
	}
	free(result);
	return (0);
}

/**
 * @brief Searches for command executable in PATH directories
 * 
 * @details Resolves command to full executable path using PATH
 * environment variable. Handles special cases:
 * - Absolute paths ("/command")
 * - Relative paths ("./command" or "../command")
 * - PATH directory search for bare command names
 * Checks file existence and execute permissions.
 * 
 * @ingroup utils_module
 * 
 * @param[in] command Command name or path to resolve
 * @param[in] exec_paths Colon-separated PATH directories
 * @return Newly allocated full path to executable, NULL if not found
 */
char	*search_command(char *command, char *exec_paths)
{
	int		i;
	char	*result;
	char	**paths;

	if ((str_compare_n(command, "/", 1) || str_compare_n(command, "./", 2)
			|| str_compare_n(command, "../", 3)) && !access(command, F_OK))
	{
		if (permissions_check(command))
			return (str_duplicate(command));
		return (0);
	}
	if (!exec_paths)
		return (0);
	i = 0;
	paths = str_split(exec_paths, ':');
	while (paths[i])
	{
		result = check_path(make_res(paths[i], command), paths);
		if (result)
			return (result);
		i++;
	}
	free_paths(paths);
	return (0);
}
