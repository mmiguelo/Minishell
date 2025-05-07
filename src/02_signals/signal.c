/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:46:22 by yes               #+#    #+#             */
/*   Updated: 2025/05/07 18:16:27 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_signal_mode(int mode)
{
	if (mode == SIGMODE_DEFAULT)
	{
		signal(SIGINT, signal_default_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == SIGMODE_PIPELINE)
	{
		signal(SIGINT, signal_pipe_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == SIGMODE_CHILD)
	{
		// TODO might be wrong an SIGINT be SIG_DFL
		signal(SIGINT, signal_pipe_handler);
		signal(SIGQUIT, SIG_DFL);
	}
	else if (mode == SIGMODE_HEREDOC)
	{
		signal(SIGINT, signal_heredoc_handler);
		signal(SIGQUIT, SIG_IGN);
	}
}
