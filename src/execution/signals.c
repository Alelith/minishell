/**
 * @file signals.c
 * @brief Signal handling for interactive and child processes
 * 
 * @author Lilith Estévez Boeta y Begoña Varea Kuhn
 * @date 2025-09-06
 */

#include "minishell.h"

static int	g_is_on_prompt = 1;

/**
 * @brief Handles SIGINT (Ctrl-C) signal
 * 
 * @details Clears the current line and displays a new prompt when
 * SIGINT is received. Behavior depends on g_is_on_prompt flag to
 * handle prompt redisplay correctly.
 * 
 * @ingroup execution_module
 * 
 * @param[in] sig Signal number (not used)
 */
static void	sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	if (g_is_on_prompt)
		rl_redisplay();
}

/**
 * @brief Handles SIGQUIT (Ctrl-\) signal
 * 
 * @details Prints "Quit (core dumped)" message when SIGQUIT is received.
 * Used for child processes to mimic bash behavior.
 * 
 * @ingroup execution_module
 * 
 * @param[in] sig Signal number (not used)
 */
static void	sigquit_handler(int sig)
{
	(void)sig;
	printf("Quit (core dumped)\n");
}

/**
 * @brief Sets signal handlers for main shell process
 * 
 * @details Configures SIGINT to use custom handler for interactive
 * prompt behavior and ignores SIGQUIT.
 * 
 * @ingroup execution_module
 */
void	set_signals_main(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

/**
 * @brief Sets signal handlers for child processes
 * 
 * @details Restores SIGINT to default behavior and sets SIGQUIT to
 * custom handler for proper core dump messages.
 * 
 * @ingroup execution_module
 */
void	set_signals_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, sigquit_handler);
}

/**
 * @brief Switches the prompt display flag for signal handling
 * 
 * @details Controls whether SIGINT handler should redisplay the prompt.
 * Used to prevent double prompts during command execution.
 * 
 * @ingroup execution_module
 * 
 * @param[in] i Flag value (1 for on prompt, 0 for executing command)
 */
void	switch_flag(int i)
{
	g_is_on_prompt = i;
}
