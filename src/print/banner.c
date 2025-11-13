/**
 * @file banner.c
 * @brief ASCII art banner display functions
 * 
 * @author Lilith Estévez Boeta y Begoña Varea Kuhn
 * @date 2025-09-10
 */

#include "minishell.h"

/**
 * @brief Displays the welcome banner with ASCII art
 * 
 * @details Clears the screen and prints a colorful ASCII art banner
 * with "WELCOME TO PONCHITA" message. Uses ANSI escape codes for
 * cyan coloring.
 * 
 * @ingroup output_module
 */
void	print_open_banner(void)
{
	printf("\033c\e[38;5;78m");
	printf("██╗    ██╗███████╗██╗      ██████╗ ██████╗ ███╗   ███╗███████╗\n");
	printf("██║    ██║██╔════╝██║     ██╔════╝██╔═══██╗████╗ ████║██╔════╝\n");
	printf("██║ █╗ ██║█████╗  ██║     ██║     ██║   ██║██╔████╔██║█████╗\n");
	printf("██║███╗██║██╔══╝  ██║     ██║     ██║   ██║██║╚██╔╝██║██╔══╝\n");
	printf("╚███╔███╔╝███████╗███████╗╚██████╗╚██████╔╝██║ ╚═╝ ██║███████╗\n");
	printf(" ╚══╝╚══╝ ╚══════╝╚══════╝ ╚═════╝ ╚═════╝ ╚═╝     ╚═╝╚══════╝\n");
	printf("\n████████╗ ██████╗\n");
	printf("╚══██╔══╝██╔═══██╗\n");
	printf("   ██║   ██║   ██║\n");
	printf("   ██║   ██║   ██║\n");
	printf("   ██║   ╚██████╔╝\n");
	printf("   ╚═╝    ╚═════╝\n\n");
	printf("██████╗  ██████╗ ███╗   ██╗ ██████╗██╗  ██╗██╗████████╗ █████╗\n");
	printf("██╔════╝██╔═══██╗████╗  ██║██╔════╝██║  ██║██║╚══██╔══╝██╔══██╗\n");
	printf("██║     ██║   ██║██╔██╗ ██║██║     ███████║██║   ██║   ███████║\n");
	printf("██║     ██║   ██║██║╚██╗██║██║     ██╔══██║██║   ██║   ██╔══██║\n");
	printf("╚██████╗╚██████╔╝██║ ╚████║╚██████╗██║  ██║██║   ██║   ██║  ██║\n");
	printf(" ╚═════╝ ╚═════╝ ╚═╝  ╚═══╝ ╚═════╝╚═╝  ╚═╝╚═╝   ╚═╝   ╚═╝  ╚═╝\n");
	printf("\n\033[0;39m");
}

/**
 * @brief Displays the exit banner with ASCII art
 * 
 * @details Prints a colorful ASCII art banner with "EXIT PONCHITA"
 * message. Uses ANSI escape codes for pink coloring.
 * 
 * @ingroup output_module
 */
void	print_close_banner(void)
{
	printf("\e[38;5;218m\n");
	printf("███████╗██╗  ██╗██╗████████╗\n");
	printf("██╔════╝╚██╗██╔╝██║╚══██╔══╝\n");
	printf("█████╗   ╚███╔╝ ██║   ██║\n");
	printf("██╔══╝   ██╔██╗ ██║   ██║\n");
	printf("███████╗██╔╝ ██╗██║   ██║\n");
	printf("╚══════╝╚═╝  ╚═╝╚═╝   ╚═╝\n\n");
	printf("██████╗  ██████╗ ███╗   ██╗ ██████╗██╗  ██╗██╗████████╗ █████╗\n");
	printf("██╔════╝██╔═══██╗████╗  ██║██╔════╝██║  ██║██║╚══██╔══╝██╔══██╗\n");
	printf("██║     ██║   ██║██╔██╗ ██║██║     ███████║██║   ██║   ███████║\n");
	printf("██║     ██║   ██║██║╚██╗██║██║     ██╔══██║██║   ██║   ██╔══██║\n");
	printf("╚██████╗╚██████╔╝██║ ╚████║╚██████╗██║  ██║██║   ██║   ██║  ██║\n");
	printf(" ╚═════╝ ╚═════╝ ╚═╝  ╚═══╝ ╚═════╝╚═╝  ╚═╝╚═╝   ╚═╝   ╚═╝  ╚═╝\n");
	printf("\n\033[0;39m");
}

/**
 * @brief Prints a formatted error message
 * 
 * @details Displays an error message in color with two components:
 * a message prefix in purple and a command/detail in cyan. Always
 * returns 1 to indicate error status.
 * 
 * @ingroup output_module
 * 
 * @param[in] message Error message prefix
 * @param[in] comm Command or detail to append to error message
 * @return Always returns 1 (error status)
 */
int	print_comm_err(const char *message, const char *comm)
{
	printf("\e[38;5;139m%s", message);
	printf("\e[38;5;116m%s\n\033[0;39m", comm);
	return (1);
}
