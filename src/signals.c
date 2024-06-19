/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:43:32 by rhorvath          #+#    #+#             */
/*   Updated: 2024/06/13 10:44:01 by rhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ctrl_c(void)
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

void	ctrl_bs(void)
{
	rl_on_new_line();
	rl_redisplay();
}

void	sig_type(int sig)
{
	if (sig == SIGINT)
		ctrl_c();
	else if (sig == SIGQUIT)
		ctrl_bs();
}

void	block_signal(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	clear_sigargs(void)
{
	struct termios	arg;

	tcgetattr(1, &arg);
	arg.c_lflag &= ~ECHOCTL;
	tcsetattr(1, TCSAFLUSH, &arg);
}
