/**
 * @file checker.c
 * @brief Command line syntax validation and error checking
 * 
 * @author Lilith Estévez Boeta y Begoña Varea Kuhn
 * @date 2025-08-21
 */

#include "survival_lib.h"
#include "minishell.h"

/**
 * @brief Handles pipe token validation
 * 
 * @details Checks if a pipe appears in an invalid position (e.g., at
 * the beginning or after another pipe) and updates the expectation flag.
 * 
 * @ingroup parsing_module
 * 
 * @param[in,out] expect_cmd Flag indicating if a command is expected
 * @return 1 on success, 0 if syntax error detected
 */
static int	handle_pipe(int *expect_cmd)
{
	if (*expect_cmd)
	{
		printf("Syntax error: unexpected pipe\n");
		return (0);
	}
	*expect_cmd = 1;
	return (1);
}

/**
 * @brief Handles redirection token validation
 * 
 * @details Validates that a redirection operator is followed by a valid
 * file or delimiter token. Advances the index past the file/delimiter.
 * 
 * @ingroup parsing_module
 * 
 * @param[in] tokens Array of parsed tokens
 * @param[in,out] i Current token index
 * @return 1 on success, 0 if syntax error detected
 */
static int	handle_redirection(t_token *tokens, int *i)
{
	if (!tokens[*i + 1].token || str_contains(tokens[*i + 1].token, "<>|"))
	{
		printf("Syntax error: redirection without file/limiter\n");
		return (0);
	}
	(*i)++;
	return (1);
}

/**
 * @brief Checks for unclosed quotes in command line
 * 
 * @details Validates that all single and double quotes are properly
 * closed in the command line string. Tracks quote state through the
 * entire string.
 * 
 * @ingroup parsing_module
 * 
 * @param[in] line Command line string to check
 * @return 1 if quotes are balanced, 0 if unclosed quotes found
 */
static int	check_quotes(char *line)
{
	int	i;
	int	single_quote;
	int	double_quote;

	i = 0;
	single_quote = 0;
	double_quote = 0;
	while (line[i])
	{
		if (line[i] == '\'' && !double_quote)
			single_quote = !single_quote;
		else if (line[i] == '"' && !single_quote)
			double_quote = !double_quote;
		i++;
	}
	if (single_quote || double_quote)
	{
		printf("Syntax error: unclosed quotes\n");
		return (0);
	}
	return (1);
}

/**
 * @brief Processes tokens for syntax validation
 * 
 * @details Iterates through token array checking for syntax errors in
 * pipes, redirections, and command placement. Returns error code if
 * validation fails.
 * 
 * @ingroup parsing_module
 * 
 * @param[in] tokens Array of parsed tokens
 * @return 0 on success, 1 if command expected, 2 on syntax error
 */
static int	process_tokens(t_token *tokens)
{
	int	i;
	int	expect_cmd;

	i = 0;
	expect_cmd = 1;
	while (tokens[i].token)
	{
		if (str_compare_all(tokens[i].token, "|") && !tokens[i].is_literal)
		{
			if (!handle_pipe(&expect_cmd))
				return (2);
		}
		else if (is_redir_token(tokens[i].token) && !tokens[i].is_literal)
		{
			if (!handle_redirection(tokens, &i))
				return (2);
		}
		else
			expect_cmd = 0;
		i++;
	}
	return (expect_cmd);
}

/**
 * @brief Main command line validation function
 * 
 * @details Performs comprehensive syntax checking on the command line
 * including quote balance, token syntax, pipe usage, and redirection
 * validity. Prints specific error messages for each type of error.
 * 
 * @ingroup parsing_module
 * 
 * @param[in] line Command line string to validate
 * @return 1 if command line is valid, 0 if syntax errors found
 */
int	check_command_line(char *line)
{
	t_token	*tokens;
	int		err_code;
	int		i;

	if (!check_quotes(line))
		return (0);
	tokens = split_command(line, 0);
	err_code = process_tokens(tokens);
	if (tokens[0].token == 0)
	{
		free(tokens);
		return (0);
	}
	i = 0;
	while (tokens[i].token)
		free(tokens[i++].token);
	free(tokens);
	if (err_code == 1 && str_len(line))
	{
		printf("Syntax error: command expected after pipe\n");
		return (0);
	}
	else if (err_code == 2)
		return (0);
	return (1);
}
