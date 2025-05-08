/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:03:40 by yes               #+#    #+#             */
/*   Updated: 2025/05/08 18:22:46 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_default_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_printf_fd(1, "\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		set_signo(SIGINT);
	}
}

void	signal_pipe_handler(int signo)
{
	if (signo == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		set_signo(SIGINT);
	}
}

void	signal_heredoc_handler(int signo)
{
	if (signo == SIGINT)
	{
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		set_signo(SIGINT);
	}
}
