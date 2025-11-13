/**
 * @file tokenizer.c
 * @brief Main tokenization and command structure creation
 * 
 * @author Lilith Estévez Boeta y Begoña Varea Kuhn
 * @date 2025-09-09
 */

#include "minishell.h"

/**
 * @brief Initializes variables for tokenization process
 * 
 * @details Sets initial values for index, tokens array, and result
 * command array before starting tokenization.
 * 
 * @ingroup parsing_module
 * 
 * @param[out] i Index counter pointer
 * @param[out] tokens Token array pointer
 * @param[out] result Command array pointer
 */
static void	declare_vars_tokenize(int *i, t_token **tokens, t_command **result)
{
	*i = 0;
	*tokens = 0;
	*result = 0;
}

/**
 * @brief Handles pipe token during tokenization
 * 
 * @details Creates a new command structure in the result array when a
 * pipe token is encountered. Extends the command array and initializes
 * the new command's output file descriptor.
 * 
 * @ingroup parsing_module
 * 
 * @param[in] tokens Token array
 * @param[in] i Current token index
 * @param[in,out] result Command array pointer
 * @param[in,out] len Command count pointer
 */
static void	handle_pipe_token(t_token *tokens, int i, t_command **result,
	unsigned short *len)
{
	free(tokens[i].token);
	*result = reallocation(*result, (*len + 1) * sizeof(t_command),
			*len * sizeof(t_command));
	(*result)[*len].outfile = 1;
	*len = *len + 1;
}

/**
 * @brief Handles redirection token during tokenization
 * 
 * @details Processes a redirection operator and its associated file or
 * delimiter, updating the command structure accordingly. Advances the
 * index to skip the processed tokens.
 * 
 * @ingroup parsing_module
 * 
 * @param[in] tokens Token array
 * @param[in,out] i Current token index pointer
 * @param[in,out] result Command array pointer
 * @param[in] len Current command count
 */
static void	handle_redir_token(t_token *tokens, int *i, t_command **result,
	unsigned short *len)
{
	proccess_redir(tokens, *i, &result[0][*len - 1]);
	*i = *i + 1;
}

/**
 * @brief Tokenizes input string into command structures
 * 
 * @details Parses the input command line into an array of t_command
 * structures, handling pipes, redirections, and command arguments.
 * Creates separate command structures for each pipe-separated command.
 * 
 * @ingroup parsing_module
 * 
 * @param[in] input Command line string to tokenize
 * @param[out] len Pointer to store number of commands created
 * @param[in] shell Shell state for environment variable expansion
 * @return Array of parsed command structures, or NULL if empty input
 */
t_command	*tokenize(char *input, unsigned short *len, t_shell shell)
{
	int			i;
	t_token		*tokens;
	t_command	*result;

	i = 0;
	if (str_len(input) == 0)
		return (0);
	declare_vars_tokenize(&i, &tokens, &result);
	result = init_command();
	*len = 1;
	tokens = get_tokens(input, shell);
	while (tokens && tokens[i].token)
	{
		if (is_pipe_token(tokens[i].token) && !tokens[i].is_literal)
			handle_pipe_token(tokens, i, &result, len);
		else if (is_redir_token(tokens[i].token) && !tokens[i].is_literal)
			handle_redir_token(tokens, &i, &result, len);
		else
			proccess_command(tokens[i].token, &result[*len - 1]);
		i++;
	}
	free(tokens);
	return (result);
}
