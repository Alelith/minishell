/**
 * @file utils1.c
 * @brief String parsing utilities for command tokenization
 * 
 * @author Lilith Estévez Boeta y Begoña Varea Kuhn
 * @date 2025-10-14
 */

#include "minishell.h"

/**
 * @brief Counts characters until a delimiter is found
 * 
 * @details Counts consecutive characters that are not in the delimiter
 * set, used for token boundary detection.
 * 
 * @ingroup utils_module
 * 
 * @param[in] line String to scan
 * @param[in] delimiters Set of delimiter characters
 * @return Number of characters before first delimiter
 */
int	count_until(char *line, const char *delimiters)
{
	int	res;

	res = 0;
	while (line[res] && !is_from_set(line[res], delimiters))
		res++;
	return (res);
}

/**
 * @brief Counts consecutive delimiter characters
 * 
 * @details Counts characters that are in the delimiter set, up to a
 * maximum count. Used for parsing repeated delimiters like ">>" or "<<".
 * 
 * @ingroup utils_module
 * 
 * @param[in] line String to scan
 * @param[in] delimiters Set of delimiter characters
 * @param[in] max Maximum count to return
 * @return Number of consecutive delimiter characters, up to max
 */
int	count_while(char *line, const char *delimiters, int max)
{
	int	res;

	res = 0;
	while (line[res] && is_from_set(line[res], delimiters) && res < max)
		res++;
	return (res);
}

/**
 * @brief Expands environment variable or special parameter
 * 
 * @details Parses and expands environment variable references starting
 * with '$'. Handles special cases:
 * - "$?": expands to last exit code
 * - "$": expands to empty string
 * - "$VAR": expands to value of VAR from environment
 * Advances the line pointer past the variable reference.
 * 
 * @ingroup utils_module
 * 
 * @param[in,out] line Pointer to current position in line
 * @param[in] shell Shell state for environment and exit code
 * @return Newly allocated string with expanded value
 */
char	*get_value_from_env(char **line, t_shell *shell)
{
	char	*res;
	char	*tmp;

	tmp = 0;
	if (*(*line + 1) == '?')
	{
		*line = *line + 2;
		return (int_to_str(shell->last_exitcod));
	}
	else
	{
		if (*(*line + 1) == '\0')
		{
			*line = *line + 1;
			return (str_duplicate(""));
		}
		tmp = str_substring(*line, 1, count_until(*line + 1,
					" \t\n\r\"\'<>|$="));
		res = search_env(shell->env_list, tmp);
		*line = *line + count_until(*line + 1, " \t\n\r\"\'<>|$=") + 1;
		free(tmp);
		if (!res)
			return (str_duplicate(""));
		return (str_duplicate(res));
	}
}

/**
 * @brief Concatenates string to result and frees both inputs
 * 
 * @details Helper function to append a string to an accumulator,
 * freeing the old accumulator and the appended string.
 * 
 * @ingroup utils_module
 * 
 * @param[in,out] res Pointer to accumulator string
 * @param[in] tmp String to append (will be freed)
 */
void	free_and_assign(char **res, char *tmp)
{
	char	*old_res;

	old_res = *res;
	*res = str_join(*res, tmp);
	free(old_res);
	free(tmp);
}

/**
 * @brief Processes next character or variable expansion in token
 * 
 * @details Handles character-by-character token building with variable
 * expansion. Expands "$" references in double quotes or unquoted context.
 * Advances line pointer and appends result to accumulator.
 * 
 * @ingroup utils_module
 * 
 * @param[in,out] line Pointer to current position in line
 * @param[in,out] res Pointer to result accumulator string
 * @param[in] shell Shell state for variable expansion
 * @param[in] type Quote context (' ', '\"', or '\'')
 */
void	process_result(char **line, char **res, t_shell *shell, char type)
{
	char	*tmp;

	if (**line == '$' && shell && (type == '\"' || type == ' '))
		tmp = get_value_from_env(line, shell);
	else
	{
		tmp = str_substring(*line, 0, 1);
		(*line)++;
	}
	free_and_assign(res, tmp);
}
