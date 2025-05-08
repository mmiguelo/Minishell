/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setget_heredoc_id.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:00:19 by yes               #+#    #+#             */
/*   Updated: 2025/05/08 18:23:28 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	setget_heredoc_id(int action)
{
	static int	counter = 0;

	if (action == SET)
		return (++counter);
	else
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
