/**
 * @file utils2.c
 * @brief Token extraction utilities for command parsing
 * 
 * @author Lilith Estévez Boeta y Begoña Varea Kuhn
 * @date 2025-10-14
 */

#include "minishell.h"

/**
 * @brief Extracts redirection or pipe operator token
 * 
 * @details Extracts up to max characters from the set (e.g., "<<" from "<",
 * or ">>" from ">"). Advances the line pointer past the operator.
 * 
 * @ingroup utils_module
 * 
 * @param[in] set Character set to extract from
 * @param[out] tmp Pointer to store extracted token
 * @param[in,out] line Pointer to current position in line
 * @param[in] max Maximum characters to extract
 */
void	process_redir_pipe(char *set, char **tmp, char **line, int max)
{
	int	size;

	size = count_while(*line, set, max);
	*tmp = str_substring(*line, 0, size);
	*line = *line + size;
}

/**
 * @brief Advances past quote character if present
 * 
 * @details Increments the line pointer if current character is a single
 * or double quote. Used for consuming opening and closing quotes during
 * tokenization.
 * 
 * @ingroup utils_module
 * 
 * @param[in,out] line Pointer to current position in line
 */
void	increment_if_quote(char **line)
{
	if (**line == '\'' || **line == '\"')
		*line = *line + 1;
}

/**
 * @brief Recursively extracts token with quote and variable handling
 * 
 * @details Core tokenization function that handles:
 * - Quote context tracking (single and double quotes)
 * - Variable expansion within appropriate contexts
 * - Character-by-character accumulation until delimiter
 * - Recursive processing for nested quotes
 * Processes characters until reaching a delimiter from the set.
 * 
 * @ingroup utils_module
 * 
 * @param[in,out] line Pointer to current position in line
 * @param[in] delimiters Delimiter character set
 * @param[in] type Current quote context (' ', '\"', or '\'')
 * @param[in] shell Shell state for variable expansion
 * @return Newly allocated token string
 */
char	*get_token(char **line, const char *delimiters, char type,
			t_shell *shell)
{
	char	*tmp;
	char	*res;

	tmp = 0;
	res = 0;
	increment_if_quote(line);
	while (**line && !is_from_set(**line, delimiters))
		process_result(line, &res, shell, type);
	if ((type == '\'' && **line == '\'') || (type == '\"' && **line == '\"'))
		increment_if_quote(line);
	if (**line && !isspace(**line))
	{
		if (**line == '\"')
			tmp = get_token(line, "\"", '\"', shell);
		else if (**line == '\'')
			tmp = get_token(line, "\'", '\'', shell);
		else if (!is_from_set(**line, "<>|"))
			tmp = get_token(line, " \t\n\r\'\"<>|", ' ', shell);
		if (tmp)
			free_and_assign(&res, tmp);
	}
	if (!res)
		res = str_duplicate("");
	return (res);
}

/**
 * @brief Dispatches token extraction based on current character
 * 
 * @details Determines token type and extracts appropriate content:
 * - Double quotes: extract quoted string with variable expansion
 * - Single quotes: extract literal string without expansion
 * - Operators: extract <, >, <<, >>, or |
 * - Words: extract unquoted text with variable expansion
 * 
 * @ingroup utils_module
 * 
 * @param[in,out] line Pointer to current position in line
 * @param[out] tmp Pointer to store extracted token
 * @param[in] shell Shell state for variable expansion
 */
void	switch_assign_tmp(char **line, char **tmp, t_shell *shell)
{
	if (**line == '\"')
		*tmp = get_token(line, "\"", '\"', shell);
	else if (**line == '\'')
		*tmp = get_token(line, "\'", '\'', shell);
	else if (**line == '<')
		process_redir_pipe("<", tmp, line, 2);
	else if (**line == '>')
		process_redir_pipe(">", tmp, line, 2);
	else if (**line == '|')
		process_redir_pipe("|", tmp, line, 1);
	else if (**line)
		*tmp = get_token(line, " \t\n\r\'\"<>|", ' ', shell);
}

/**
 * @brief Adds token to token array
 * 
 * @details Appends a new token to the array, reallocating as needed.
 * Sets the is_literal flag based on the quote type to preserve literal
 * interpretation for single-quoted tokens.
 * 
 * @ingroup utils_module
 * 
 * @param[in,out] args Pointer to token array
 * @param[in,out] argc Pointer to token count
 * @param[in] tmp Token string value
 * @param[in] type Quote context (' ', '\"', or '\'')
 */
void	increment_args(t_token **args, int *argc, char *tmp, char type)
{
	*args = reallocation(*args, sizeof(t_token) * (*argc + 1),
			sizeof(t_token) * *argc);
	(*args)[*argc].token = tmp;
	if (type == '\'' || type == '\"')
		(*args)[*argc].is_literal = true;
	else
		(*args)[*argc].is_literal = false;
	*argc = *argc + 1;
}
