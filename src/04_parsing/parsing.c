/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:11:48 by yes               #+#    #+#             */
/*   Updated: 2025/05/20 18:34:24 by frbranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_and_parse(t_shell *shell, char *s, int *i)
{
	if (ft_strchr(QUOTES, s[*i]) && shell->info.mode == GENERAL)
		return (check_syntax_quotes(shell, s, i));
	if (ft_strchr(T_REDIR, s[*i]) && shell->info.mode == GENERAL)
		return (check_syntax_redir(shell, s, i));
	if (ft_strchr(T_PIPE, s[*i]) && shell->info.mode == GENERAL)
		return (check_syntax_pipes(shell, s, i));
	return (SUCCESS);
}

static int	parsing_core(t_shell *shell, char *s, int *i)
{
	while (s[*i])
	{
		if (ft_strchr(WHITE_SPACES, s[*i]))
			(*i)++;
		else if (check_and_parse(shell, s, i) != SUCCESS)
			return (SYNTAX_ERROR);
		else if (s[*i])
			(*i)++;
	}
	return (SUCCESS);
}

int	ft_parsing(t_shell *shell, char *s)
{
	int	i;

	if (only_spaces(shell->input) == TRUE)
	{
		free_ref(&shell->input);
		return (ERROR);
	}
	inizialize_info(&shell->info);
	i = 0;
	if (check_syntax_first_pipe(shell, s, &i) != SUCCESS)
	{
		free_ref(&shell->input);
		return (SYNTAX_ERROR);
	}
	i = 0;
	if (parsing_core(shell, s, &i) != SUCCESS)
	{
		free_ref(&shell->input);
		return (SYNTAX_ERROR);
	}
	return (SUCCESS);
}
