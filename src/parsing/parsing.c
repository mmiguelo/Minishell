/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:11:48 by yes               #+#    #+#             */
/*   Updated: 2025/04/23 18:02:19 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_parsing(t_shell *shell, char *s)
{
	int	i;

	inizialize_info(&shell->info);
	i = 0;
	while (s[i])
	{
		if (ft_strchr(WHITE_SPACES, s[i]))
			i++;
		else if (ft_strchr(QUOTES, s[i])
			&& check_syntax_quotes(shell, s, &i) != SUCCESS)
			return (SYNTAX_ERROR);
		else if (ft_strchr(T_REDIR, s[i])
			&& shell->info.mode == GENERAL
			&& check_syntax_redir(shell, s, &i) != SUCCESS)
			return (SYNTAX_ERROR);
		else if (ft_strchr(T_PIPE, s[i])
			&& shell->info.mode == GENERAL
			&& check_syntax_pipes(shell, s, &i) != SUCCESS)
			return (SYNTAX_ERROR);
		else
			i++;
	}
	return (SUCCESS);
}
