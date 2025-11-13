/**
 * @file export_vars.c
 * @brief Formatted output for export command
 * 
 * @author Lilith Estévez Boeta y Begoña Varea Kuhn
 * @date 2025-09-10
 */

#include "minishell.h"

/**
 * @brief Prints an environment variable in export format
 * 
 * @details Displays an environment variable in the format used by
 * the export built-in: "declare -x KEY="VALUE"". Uses ANSI color
 * codes for syntax highlighting. Handles variables without values.
 * 
 * @ingroup output_module
 * 
 * @param[in] key Environment variable name
 * @param[in] value Environment variable value (can be NULL)
 */
void	print_export(const char *key, const char *value)
{
	if (value)
		printf("\e[38;5;44mdeclare \e[38;5;165m-x "
			"\e[38;5;35m%s=\"%s\"\n\033[0;39m", key, value);
	else
		printf("\e[38;5;44mdeclare \e[38;5;165m-x "
			"\e[38;5;35m%s=\n\033[0;39m", key);
}
