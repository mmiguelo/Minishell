/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setget_heredoc_id.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:00:19 by yes               #+#    #+#             */
/*   Updated: 2025/05/09 15:23:05 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	setget_heredoc_id(int action)
{
	static int	counter = 0;

	if (action == SET)
		return (++counter);
	else if (action == GET)
		return (counter);
	else if (action == RESET)
		counter = 0;
	return (counter);
}

int	set_heredoc_id(void)
{
	return (setget_heredoc_id(SET));
}

int	get_heredoc_id(void)
{
	return (setget_heredoc_id(GET));
}

void	reset_heredoc_id(void)
{
	setget_heredoc_id(RESET);
}
