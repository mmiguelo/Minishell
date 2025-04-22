/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:11:48 by yes               #+#    #+#             */
/*   Updated: 2025/04/22 17:42:25 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_syntax_quotes(t_shell *shell, char *s, int *i)
{
	while (s[*i])
	{
		if (shell->info.mode == DOUBLE_QUO && s[*i] == '\"')
		{
			quote_changer(s, i, shell->info.mode);
			return (SUCCESS);
		}
		if (shell->info.mode == SINGLE_QUO && s[*i] == '\'')
		{
			quote_changer(s, i, shell->info.mode);
			return (SUCCESS);
		}
		(*i)++;
	}
	shell->exit_status = SYNTAX_ERROR;
	ft_printf_fd(2, ERROR_UNCLOSED_QUO);
	return (SYNTAX_ERROR);
}

int	ft_parsing(t_shell *shell, char *s)
{
	int	i;
	
	inizialize_info(&shell->info);
	i = 0;
	while (s[i])
	{
		if (ft_strchr(WHITE_SPACES, s[i]))
			i++;
		else if (ft_strchr(QUOTES, s[i]))
		{
			quote_changer(s, &i, &shell->info);
			if (check_syntax_quotes(shell, s, &i) != SUCCESS)
				return (SYNTAX_ERROR);
		}
		else if (ft_strchr(T_REDIR, s[i]) && shell->info.mode == GENERAL)
		{
			if (check_syntax_reddir(shell, s, &i) != SUCCESS)
				return (SYNTAX_ERROR);
		}
		else if (ft_strchr(T_PIPE, s[i]) && shell->info.mode == GENERAL)
		{
			if (check_syntax_pipes(shell, s, &i) != SUCCESS)
				return (SYNTAX_ERROR);
		}
		else
			i++;
		
	}
	return (SUCCESS);
}
