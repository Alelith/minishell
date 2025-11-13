/**
 * @file get_last_path.c
 * @brief Parent directory path extraction
 * 
 * @author Lilith Estévez Boeta y Begoña Varea Kuhn
 * @date 2025-09-24
 */

#include "minishell.h"

/**
 * @brief Extracts parent directory from path
 * 
 * @details Removes the last path component by finding the last '/'
 * separator and truncating the string. Handles trailing slashes by
 * removing them first. Modifies the input string in place.
 * 
 * @ingroup utils_module
 * 
 * @param[in,out] this_path Path string to modify
 * @return Modified path string (same pointer as input)
 */
char	*get_last_path(char *this_path)
{
	char	*last;

	if (this_path[str_len(this_path) - 1] == '/')
		this_path[str_len(this_path) - 1] = 0;
	last = str_search_rev_char(this_path, '/');
	*last = 0;
	return (this_path);
}
