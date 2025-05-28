/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:35:32 by frbranda          #+#    #+#             */
/*   Updated: 2025/05/28 13:47:30 by frbranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_syntax_first_pipe(t_shell *shell, char *s, int *i)
{
	while (s && s[*i] && ft_strchr(WHITE_SPACES, s[*i]))
		(*i)++;
	if (s && s[*i] && s[*i] == '|')
	{
		shell->exit_status = SYNTAX_ERROR;
		ft_printf_fd(2, "minishell: "ERROR_UNCLOSED_PIPE);
		return (SYNTAX_ERROR);
	}
	return (SUCCESS);
}

int	check_syntax_pipes(t_shell *shell, char *s, int *i)
{
	if (!s[*i] || !(ft_strchr(T_PIPE, s[*i])))
		return (SUCCESS);
	(*i)++;
	while (s[*i] && ft_strchr(WHITE_SPACES, s[*i]))
		(*i)++;
	if (!s[*i])
	{
		shell->exit_status = SYNTAX_ERROR;
		return (ft_printf_fd(2, ERROR_UNCLOSED_PIPE), SYNTAX_ERROR);
	}
	if (ft_strchr(QUOTES, s[*i]))
	{
		if (check_syntax_quotes(shell, s, i) != SUCCESS)
			return (SYNTAX_ERROR);
	}
	else if (ft_strchr(T_PIPE, s[*i]))
	{
		shell->exit_status = SYNTAX_ERROR;
		return (handle_syntax_error(s, *i), SYNTAX_ERROR);
	}
	return (SUCCESS);
}
