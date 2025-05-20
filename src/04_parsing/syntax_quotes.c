/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:38:17 by yes               #+#    #+#             */
/*   Updated: 2025/05/20 18:37:40 by frbranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_syntax_quotes(t_shell *shell, char *s, int *i)
{
	char	quote;

	if (!s[*i] || !(ft_strchr(QUOTES, s[*i])))
		return (SUCCESS);
	quote = s[*i];
	quote_changer(s, i, &shell->info);
	while (s[*i])
	{
		if (s[*i] == quote)
		{
			shell->info.mode = GENERAL;
			return (SUCCESS);
		}
		(*i)++;
	}
	shell->exit_status = SYNTAX_ERROR;
	ft_printf_fd(2, "minishell: "ERROR_UNCLOSED_QUO);
	return (SYNTAX_ERROR);
}
