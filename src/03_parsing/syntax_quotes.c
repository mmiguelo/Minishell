/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:38:17 by yes               #+#    #+#             */
/*   Updated: 2025/04/23 18:03:40 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_syntax_quotes(t_shell *shell, char *s, int *i)
{
	quote_changer(s, i, &shell->info);
	while (s[*i])
	{
		if (shell->info.mode == DOUBLE_QUO && s[*i] == '\"')
		{
			quote_changer(s, i, &shell->info);
			return (SUCCESS);
		}
		if (shell->info.mode == SINGLE_QUO && s[*i] == '\'')
		{
			quote_changer(s, i, &shell->info);
			return (SUCCESS);
		}
		(*i)++;
	}
	shell->exit_status = SYNTAX_ERROR;
	ft_printf_fd(2, "minishell: "ERROR_UNCLOSED_QUO);
	return (SYNTAX_ERROR);
}
