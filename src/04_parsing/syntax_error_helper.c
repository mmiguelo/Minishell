/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:55:17 by frbranda          #+#    #+#             */
/*   Updated: 2025/05/27 16:55:20 by frbranda         ###   ########.fr       */
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
