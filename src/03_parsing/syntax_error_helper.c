/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:34:53 by yes               #+#    #+#             */
/*   Updated: 2025/04/23 18:03:26 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_syntax_error(char *s, int i)
{
	if (s[i] == '>')
	{
		if (s[i + 1] == '>')
			ft_printf_fd(2, "minishell: "ERROR_SYNTAX, ">>");
		else
			ft_printf_fd(2, "minishell: "ERROR_SYNTAX, ">");
	}
	else if (s[i] == '<')
	{
		if (s[i + 1] == '<')
			ft_printf_fd(2, "minishell: "ERROR_SYNTAX, "<<");
		else
			ft_printf_fd(2, "minishell: "ERROR_SYNTAX, "<");
	}
	else if (s[i] == '|')
	{
		if (s[i + 1] == '|')
			ft_printf_fd(2, "minishell: "ERROR_SYNTAX, "||");
		else
			ft_printf_fd(2, "minishell: "ERROR_SYNTAX, "|");
	}
	else
		ft_printf_fd(2, "minishell: " ERROR_SYNTAX, NULL);
}
