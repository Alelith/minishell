/**
 * @file split_command.c
 * @brief Command line tokenization into tokens
 * 
 * @author Lilith Estévez Boeta y Begoña Varea Kuhn
 * @date 2025-09-10
 */

#include "minishell.h"

/**
 * @brief Splits command line string into token array
 * 
 * @details Tokenizes the input line into an array of t_token structures.
 * Skips leading whitespace, processes each token through switch_assign_tmp,
 * and builds a null-terminated array. Handles quotes, operators, and
 * variable expansion via helper functions.
 * 
 * @ingroup utils_module
 * 
 * @param[in] line Command line string to tokenize
 * @param[in] shell Shell state for variable expansion
 * @return Null-terminated array of tokens, NULL on error
 */
t_token	*split_command(char *line, t_shell *shell)
{
	char	type;
	char	*tmp;
	int		argc;
	t_token	*args;

	argc = 0;
	args = 0;
	while (line && *line)
	{
		tmp = 0;
		while (*line && isspace(*line))
			line++;
		type = *line;
		switch_assign_tmp(&line, &tmp, shell);
		if (tmp)
			increment_args(&args, &argc, tmp, type);
	}
	args = reallocation(args, sizeof(t_token) * (argc + 1),
			sizeof(t_token) * argc);
	return (args);
}
