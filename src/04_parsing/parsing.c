/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:11:48 by yes               #+#    #+#             */
/*   Updated: 2025/05/05 15:41:00 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parsing_core(t_shell *shell, char *s, int *i)
{
	while (s[*i])
	{
		if (ft_strchr(WHITE_SPACES, s[*i]))
			(*i)++;
		else if (ft_strchr(QUOTES, s[*i])
			&& shell->info.mode == GENERAL
			&& check_syntax_quotes(shell, s, i) != SUCCESS)
			return (SYNTAX_ERROR);
		else if (ft_strchr(T_REDIR, s[*i])
			&& shell->info.mode == GENERAL
			&& check_syntax_redir(shell, s, i) != SUCCESS)
			return (SYNTAX_ERROR);
		else if (ft_strchr(T_PIPE, s[*i])
			&& shell->info.mode == GENERAL
			&& check_syntax_pipes(shell, s, i) != SUCCESS)
			return (SYNTAX_ERROR);
		else if (s[*i])
			(*i)++;
	}
	return (SUCCESS);
}

int	ft_parsing(t_shell *shell, char *s)
{
	int	i;

	inizialize_info(&shell->info);
	i = 0;
	if (check_syntax_first_pipe(shell, s, &i) != SUCCESS)
		return (SYNTAX_ERROR);
	return (parsing_core(shell, s, &i));
}
