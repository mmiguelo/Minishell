/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setget_signo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:33:35 by yes               #+#    #+#             */
/*   Updated: 2025/04/10 14:05:57 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// act global variable that is the bridge between the signal handlers 
/**
 * @brief Handles internal signal state used across the program 
 * g_signo acts like a global variable
 * 
 * Acts as a controlled accessor to a static signal value (g_signo),
 * storing signal codes like SIGINT from signal handlers,
 * and allowing the main shell loop to retrieve them later.
 * 
 * @param action Either SET or GET (macro-defined)
 * @param ntoset New signal value to store (if action == SET)
 * @return Stored signal value (if action == GET), otherwise 0
 */
static int	setget_signo(int action, int ntoset)
{
	static int	g_signo = 0;

	if (action == SET)
		g_signo = ntoset;
	else if (action == GET)
		return (g_signo);
	return (0);
}

void	set_signo(int new_value)
{
	setget_signo(SET, new_value);
}

int	get_signo(void)
{
	return (setget_signo(GET, 0));
}
