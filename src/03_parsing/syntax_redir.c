/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:39:24 by yes               #+#    #+#             */
/*   Updated: 2025/05/05 15:22:06 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_syntax_redir(t_shell *shell, char *s, int *i)
{
	if (!s[*i] || !(ft_strchr(T_REDIR, s[*i])))
		return (SUCCESS);
	(*i)++;
	if (ft_strchr(T_REDIR, s[*i]))
		(*i)++;
	while (s[*i] && ft_strchr(WHITE_SPACES, s[*i]))
		(*i)++;
	if (!s[*i])
	{
		shell->exit_status = SYNTAX_ERROR;
		return (ft_printf_fd(2, "minishell: "ERROR_SYNTAX_END), SYNTAX_ERROR);
	}
	if (ft_strchr(QUOTES, s[*i]))
	{
		if (check_syntax_quotes(shell, s, i) != SUCCESS)
			return (SYNTAX_ERROR);
	}
	if (ft_strchr(T_REDIR, s[*i]) || ft_strchr(T_PIPE, s[*i]))
	{
		shell->exit_status = SYNTAX_ERROR;
		return (handle_syntax_error(s, *i), SYNTAX_ERROR);
	}
	return (SUCCESS);
}
