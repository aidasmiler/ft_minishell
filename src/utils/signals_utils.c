/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airodrig <airodrig@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:19:03 by airodrig          #+#    #+#             */
/*   Updated: 2022/05/13 14:01:13 by airodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	manage_signals(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	my_signal(void)
{
	signal(SIGINT, manage_signals);
	signal(SIGQUIT, SIG_IGN);
}

void	signals_heredoc(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_DFL);
}

void	ignore_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
}

void	child_signals(int signal)
{
	if (signal == SIGQUIT)
		ft_putstr_fd("Quit: 3\n", STDOUT_FILENO);
	else if (signal == SIGINT)
		ft_putchar_fd('\n', STDOUT_FILENO);
}
