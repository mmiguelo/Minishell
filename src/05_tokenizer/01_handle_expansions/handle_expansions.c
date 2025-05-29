/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expansions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:19:21 by frbranda          #+#    #+#             */
/*   Updated: 2025/05/29 17:24:24 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_variable(t_shell *shell, char **s_ptr, int *i, t_info *info)
{
	char	*var_name;
	char	*var_value;
	char	*new_s;
	int		before_after;

	var_name = take_var_name(*s_ptr, i);
	info->env_end = (*i);
	var_value = get_env_value_expansion(var_name, shell->envp);
	before_after = check_if_var_is_alone(*s_ptr, *i, info);
	if (info->mode == GENERAL
		&& (info->type >= REDIR_IN && info->type <= HEREDOC)
		&& (ft_has_white_spaces(var_value)
			|| ((!var_value || var_value[0] == '\0') && !before_after)))
	{
		shell->exit_status = 1;
		info->error_flag = TRUE;
		ft_printf("minishell: $%s: ambiguous redirect\n", var_name);
		free(var_name);
		return (NULL);
	}
	new_s = expand_var_in_str(*s_ptr, var_value, *i, info);
	free(var_name);
	*i = info->env_start + ft_strlen(var_value);
	return (new_s);
}

int	expand_env(t_shell *shell, char **s_ptr, int *i, t_info *info)
{
	char	*s;
	char	*new_s;

	s = *s_ptr;
	info->env_start = (*i);
	(*i)++;
	if (!(s[*i]) || ft_strchr(WHITE_SPACES, s[*i]))
		return (FALSE);
	else if (ft_strchr(QUOTES, s[*i]) && info->mode == DOUBLE_QUO)
		return (FALSE);
	else if (ft_strchr(QUOTES, s[*i]) && info->mode == GENERAL)
		new_s = remove_dollar(&s, i, info);
	else if (ft_strchr(NUMBERS, s[*i]))
		new_s = remove_number(&s, i, info);
	else if (s[*i] == '?')
		new_s = handle_question_mark(shell, s, i, info);
	else
	{
		new_s = expand_variable(shell, &s, i, info);
		if (!new_s)
			return (TRUE);
	}
	*s_ptr = new_s;
	return (TRUE);
}

static int	expand_loop(t_shell *shell, char **s_ptr, int *i, t_info *info)
{
	char	*s;

	s = *s_ptr;
	while (s[*i] && *i < info->end)
	{
		if (s[*i] && ft_strchr(QUOTES, s[*i]))
			quote_changer(s, i, info);
		else if (s[*i] == '$' && info->mode != SINGLE_QUO)
		{
			if (expand_env(shell, s_ptr, i, info) == TRUE)
			{
				free(s);
				if (info->error_flag == TRUE)
					return (FALSE);
				*i = info->start;
				return (TRUE);
			}
		}
		else if (s[*i] == '\\' && info->mode != SINGLE_QUO && s[*i + 1])
			*i += 2;
		else
			(*i)++;
	}
	return (FALSE);
}

int	handle_expansions(t_shell *shell, char **s_ptr, int *i, t_info *info)
{
	info->mode = GENERAL;
	*i = info->start;
	return (expand_loop(shell, s_ptr, i, info));
}
