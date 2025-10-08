/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 17:12:26 by bvarea-k          #+#    #+#             */
/*   Updated: 2025/10/08 10:36:53 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	g_is_on_prompt = 1;

static void	sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	if (g_is_on_prompt)
		rl_redisplay();
}

static void	sigquit_handler(int sig)
{
	(void)sig;
	printf("Quit (core dumped)\n");
}

void	set_signals_main(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	set_signals_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, sigquit_handler);
}

void	switch_flag(int i)
{
	g_is_on_prompt = i;
}
